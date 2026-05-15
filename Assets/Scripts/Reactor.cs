using System;
using System.Collections.Generic;
using System.Linq;
using FMOD.Studio;
using SaintsField.Playa;
using TMPro;
using UnityEngine;

public class Reactor : MonoBehaviour, ITooltipInfo
{
    public string Info()
    {
        var info =  "Total power: " + power.ToString() +
               "\nTempo: " + (120 + rate * 100).ToString() +
               "\nDamage mult: " + (1 + .5f * strength);
        return info;
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
    
    private float shields; // 1-4
    // public float izki;
    // public float aubo;
    // public float dwth;
    public List<Module> myPatch;

    public GameObject parentWire;

    private EventInstance[] pads = new EventInstance[8];

    public bool tempoOverride;

    public bool invisible;

    public float maxStoredEnergy = 30;

    void Awake()
    {
        Debug.Log("reactor awake");
    }
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
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
        SetPatch();
        GenerateEnergy();
        
        // if (!invisible)
        // {
        //     Debug.Log($"There is currently {storedEnergy[Common.SoundType.None]} None energy in reactor.");
        // }
    }

    private void GenerateEnergy()
    {
        foreach (var mod in myPatch)
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
        Debug.Log($"{name} has {storedEnergy[Common.SoundType.None]} stored energy.");
        var allEnergy = new Dictionary<Common.SoundType, float>(storedEnergy);
        TrySpendEnergy(allEnergy);
        Debug.Log($"After TrySpendEnergy(), {name} has {storedEnergy[Common.SoundType.None]} stored energy.");
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
    
    public void SetPatch()
    {
        myPatch = new();
        
        if (PreviousModule() != null)
        {
            var prev = PreviousModule().GetComponent<Module>();
            while (prev.PreviousModule() != null)
            {
                // Debug.Log(prev.name);
                myPatch.Add(prev);
                prev = prev.PreviousModule().GetComponent<Module>();
            }
            // Debug.Log(prev.name);
            myPatch.Add(prev);
        }

        power = 0;
        rate = 0;
        shields = 0;
        foreach (var module in myPatch)
        {
            power += module.combatStats["power"];
            rate += module.combatStats["rate"];
            shields += module.combatStats["shields"];
        }

        shields = Mathf.Clamp(shields, 0, 4);
        // for (var i = 0; i < CombatManager.Instance.playerShipData.shields.Length; i++)
        // {
        //     var shield = CombatManager.Instance.playerShipData.shields[i];
        //     shield.SetActive(false);
        // }

        // for (var i = 0; i < shields; i++)
        // {
        //     CombatManager.Instance.playerShipData.shields[i].SetActive(true);
        // }



        float shieldDiff = shields - ReactorSounds.Instance.playerPads.Count;
        // Debug.Log("shield diff: " + shieldDiff + ", shields: " + shields + ", pads: " + ReactorSounds.Instance.playerPads.Count);

        if (shieldDiff > 0) 
        {
            for (int i = 0; i < shieldDiff; i++)
            {
                ReactorSounds.Instance.AddPlayerPad();
            }
        }
        if (shieldDiff < 0)
        {
            for (int i = 0; i < -shieldDiff; i++)
            {
                ReactorSounds.Instance.RemovePlayerPad();
                Debug.Log("Removing");
            }
        }


        strength = power / rate;
        if (!tempoOverride)
        {
            Conductor.Instance.tempo = 120 + (rate * 100);
        } 

        // TODO: set values of ReactorSounds.Instance based on adsrValues[adsrIndex]

        ReactorSounds.Instance.SetReactorParams();
    }
    
    public GameObject PreviousModule()
    {
        if (parentWire == null)
        {
            return null;
        }
        else
        {
            return parentWire.GetComponent<Wire>().previousModule;
        }
    }
}
