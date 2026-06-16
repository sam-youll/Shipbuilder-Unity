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
    
    // ENERGY
    [ShowInInspector] public Dictionary<Common.SoundType, float> storedEnergy = new()
    {
        { Common.SoundType.None, 0 },
        { Common.SoundType.Izki, 0 },
        { Common.SoundType.Aubo, 0 },
        { Common.SoundType.Dwth, 0 }
    };
    public EnergyReservoirDisplay energyReservoirDisplay;
    
    private EventInstance[] pads = new EventInstance[8];

    public bool tempoOverride;

    public bool invisible;

    public float maxStoredEnergy = 30;

    protected override void Start()
    {
        Debug.Log("Reactor Start");
        if (energyReservoirDisplay == null)
        {
            invisible = true;
            // strength = 1;
            // power = 1;
            // rate = 1;
        }
        
        EventBus.Instance.combatStarted.AddListener(OnCombatStarted);
    }

    // Update is called once per frame
    void Update()
    {
        GenerateEnergy();
    }

    private void GenerateEnergy()
    {
        var newEnergy = new Dictionary<Common.SoundType, float>
        {
            { Common.SoundType.None, 0 },
            { Common.SoundType.Izki, 0 },
            { Common.SoundType.Aubo, 0 },
            { Common.SoundType.Dwth, 0 }
        };
        
        foreach (var mod in ActivePatch())
        {
            if (mod is IReactorModule iReactorMod)
            {
                if (mod is PowerModule)
                {
                    // Add the energy amount as untyped energy (right now, this assumes a power module)
                    newEnergy[Common.SoundType.None] += iReactorMod.MyReactorStats().PowerGenerated;
                }
                if (mod is ConverterModule)
                {
                    // this is probably gonna throw errors, but I'm not sure exactly how
                    var enCon = iReactorMod.MyReactorStats().EnergyConversion;
                    var conAmt = Mathf.Min(enCon.EnergyLimit, newEnergy[Common.SoundType.None]);

                    newEnergy[Common.SoundType.None] -= conAmt;

                    foreach (var kvp in iReactorMod.MyReactorStats().EnergyConversion.ConversionRatios)
                    {
                        newEnergy[kvp.Key] += conAmt * kvp.Value;
                    }
                }
            }
        }

        if (!EnergyFull())
        {
            foreach (var kvp in newEnergy)
            {
                storedEnergy[kvp.Key] += kvp.Value * Time.deltaTime;
            }
            if (!invisible)
            {
                energyReservoirDisplay.UpdateDisplay(storedEnergy);
            }
        }

        // TODO: once a system for adding invisible modules to enemy ships is in place, delete this
        // the above code will work once that's all in place
        // This is a stopgap for enemy ships
        if (invisible)
        {
            storedEnergy[Common.SoundType.None] += Time.deltaTime;
        }
    }

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

        return Mathf.Clamp01(conversionLimit / powerGenerated) * 100;
    }

    public void AddEnergy(Dictionary<Common.SoundType, float> energyToAdd)
    {
        foreach (var energyType in energyToAdd)
        {
            storedEnergy[energyType.Key] += energyType.Value;
        }
        
        if (!invisible)
        {
            energyReservoirDisplay.UpdateDisplay(storedEnergy);
        }
    }

    private void OnCombatStarted()
    {
        // Debug.Log($"{name} has {storedEnergy[Common.SoundType.None]} stored energy.");
        var allEnergy = new Dictionary<Common.SoundType, float>(storedEnergy);
        TrySpendEnergy(allEnergy);
        // Debug.Log($"After TrySpendEnergy(), {name} has {storedEnergy[Common.SoundType.None]} stored energy.");
    }

    private bool EnergyFull()
    {
        float totalEnergy = 0;
        foreach (var type in storedEnergy.Values)
        {
            totalEnergy += type;
        }
        return totalEnergy >= maxStoredEnergy;
    }
    
    public bool TrySpendEnergy(Dictionary<Common.SoundType, float> cost)
    {
        // before we start actually removing any energy, make sure we have enough of each type
        foreach (var key in cost.Keys)
        {
            if (storedEnergy.ContainsKey(key) && storedEnergy[key] >= cost[key])
            {
                continue;
            }

            return false;
        }

        // ok now we actually remove the energy
        foreach (var key in cost.Keys)
        {
            storedEnergy[key] -= cost[key];
            // invisible reactors don't have a display, but otherwise we update the display
            if (!invisible)
            {
                energyReservoirDisplay.UpdateDisplay(storedEnergy);
            }
            // Debug.Log($"Removed {cost[key]} energy of type {key}.");
        }

        return true;
    }
}