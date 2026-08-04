using System;
using System.Collections.Generic;
using System.Linq;
using FMOD.Studio;
using SaintsField.Playa;
using TMPro;
using UnityEngine;

public class Reactor : ModuleRack, ITooltipInfo
{
    public override string Description()
    {
        return "Controls energy generation, as well as affecting " +
               "harmonic and rhythmic properties of the overall composition.";
    }
    
    private EventInstance[] pads = new EventInstance[8];

    public bool tempoOverride;

    public bool invisible;

    public float maxStoredEnergy = 30;

    protected override void Start()
    {
        // Debug.Log("Reactor Start");
        if (energyReservoir == null)
        {
            invisible = true;
            // strength = 1;
            // power = 1;
            // rate = 1;
        }

        health = maxHealth;
    }

    // Update is called once per frame
    protected override void Update()
    {
        base.Update();
        
        // GenerateEnergy(energyReservoir);
    }

    // private void GenerateEnergy(EnergyReservoir targetReservoir)
    // {
    //     if (health <= 0)
    //     {
    //         return;
    //     }
    //     
    //     var newEnergy = new Dictionary<Common.SoundType, float>
    //     {
    //         { Common.SoundType.None, 0 },
    //         { Common.SoundType.Izki, 0 },
    //         { Common.SoundType.Aubo, 0 },
    //         { Common.SoundType.Dwth, 0 }
    //     };
    //     
    //     foreach (var mod in ActivePatch())
    //     {
    //         if (mod is IReactorModule iReactorMod)
    //         {
    //             if (mod is PowerModule)
    //             {
    //                 // Add the energy amount as untyped energy (right now, this assumes a power module)
    //                 newEnergy[Common.SoundType.None] += iReactorMod.MyReactorStats().PowerGenerated;
    //             }
    //             if (mod is ConverterModule)
    //             {
    //                 // this is probably gonna throw errors, but I'm not sure exactly how
    //                 var enCon = iReactorMod.MyReactorStats().EnergyConversion;
    //                 var conAmt = Mathf.Min(enCon.EnergyLimit, newEnergy[Common.SoundType.None]);
    //
    //                 newEnergy[Common.SoundType.None] -= conAmt;
    //
    //                 foreach (var kvp in iReactorMod.MyReactorStats().EnergyConversion.ConversionRatios)
    //                 {
    //                     newEnergy[kvp.Key] += conAmt * kvp.Value;
    //                 }
    //             }
    //         }
    //     }
    //
    //     targetReservoir.AddEnergy(newEnergy);
    //
    //
    //     // TODO: once a system for adding invisible modules to enemy ships is in place, delete this
    //     // the above code will work once that's all in place
    //     // This is a stopgap for enemy ships
    //     if (invisible)
    //     {
    //         targetReservoir.storedEnergy[Common.SoundType.None] += Time.deltaTime;
    //     }
    // }

    public float Power()
    {
        var power = 0f;
        
        foreach (var mod in ActivePatch())
        {
            if (mod is IReactorModule iReactorMod)
            {
                if (mod is PowerModule)
                {
                    power += iReactorMod.MyReactorStats().PowerGenerated;
                }
            }
        }

        return power;
    }

    public float ConversionRate()
    {
        var powerGenerated = 0f;
        var conversionLimit = 0f;

        foreach (var mod in ActivePatch())
        {
            if (mod is IReactorModule iReactorMod)
            {
                if (mod is PowerModule)
                {
                    // Add the energy amount as untyped energy (right now, this assumes a power module)
                    powerGenerated += iReactorMod.MyReactorStats().PowerGenerated;
                }
                if (mod is ConverterModule)
                {
                    conversionLimit += iReactorMod.MyReactorStats().EnergyConversion.EnergyLimit;
                }
            }
        }

        if (powerGenerated <= 0) return 0;

        return Mathf.Clamp01(conversionLimit / powerGenerated) * 100;
    }

    public override bool CompletePatch()
    {
        return base.CompletePatch() && 
               ActivePatch().Exists(x => x is PowerModule) && 
               ActivePatch().TrueForAll(x => x is IReactorModule);
    }
    
    public Dictionary<Common.SoundType, float> SoundType()
    {
        var dict = new Dictionary<Common.SoundType, float>(Common.EmptySoundType);
        foreach (var mod in ActivePatch())
        {
            if (mod is IReactorModule reactorModule)
            {
                foreach (var kvp in reactorModule.MyReactorStats().SoundType)
                {
                    dict[kvp.Key] += kvp.Value;
                }
            }
        }
        return dict;
    }
}