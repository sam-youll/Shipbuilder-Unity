using System;
using System.Collections.Generic;
using FMOD.Studio;
using SaintsField.Playa;
using TMPro;
using UnityEngine;

public class Reactor : MonoBehaviour, ITooltipInfo
{
    public static Reactor Instance;

    private void Awake()
    {
        Instance = this;
    }

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

    public GameObject previousModule;
    public GameObject parentWire;

    private EventInstance[] pads = new EventInstance[8];

    public bool tempoOverride;

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        SetPatch();
        GenerateEnergy();
    }

    private void GenerateEnergy()
    {
        foreach (var mod in myPatch)
        {
            if (mod is PowerModule p)
            {
                storedEnergy[p.soundType] += p.power * Time.deltaTime;
                energyReservoirDisplay.ChangeEnergy(p.soundType, power * Time.deltaTime);
            }
        }
    }
    
    public bool TrySpendEnergy(Dictionary<Common.SoundType, float> cost)
    {
        foreach (var key in cost.Keys)
        {
            if (storedEnergy.ContainsKey(key) && storedEnergy[key] >= cost[key])
            {
                continue;
            }

            return false;
        }

        foreach (var key in cost.Keys)
        {
            storedEnergy[key] -= cost[key];
            energyReservoirDisplay.ChangeEnergy(key, -cost[key]);
            Debug.Log($"Removed {cost[key]} energy of type {key}.");
        }

        return true;
    }
    
    public void SetPatch()
    {
        myPatch = new();
        
        if (previousModule != null)
        {
            var prev = previousModule.GetComponent<Module>();
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
            power += module.CombatStats["power"];
            rate += module.CombatStats["rate"];
            shields += module.CombatStats["shields"];
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
}
