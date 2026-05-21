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

    public float power; // default power module adds 1, can be more or less (upper limit 30-40 maybe?)
    public float rate; // 1-4, but tempo is 200-600
    public float strength; // 1-4
    
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
            strength = 1;
            power = 1;
            rate = 1;
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
        foreach (var mod in ActivePatch())
        {
            if (mod is PowerModule p)
            {
                if (!EnergyFull())
                {
                    storedEnergy[p.soundType] += p.power * Time.deltaTime;
                    if (!invisible)
                    {
                        energyReservoirDisplay.UpdateDisplay(storedEnergy);
                    }
                }
            }
        }

        // TODO: once a system for adding invisible modules to enemy ships is in place, delete this
        // the above code will work once that's all in place
        if (invisible)
        {
            storedEnergy[Common.SoundType.None] += Time.deltaTime;
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

    public Dictionary<string, float> ReactorStats()
    {
        var dict = new Dictionary<string, float>();

        return dict;
    }
}