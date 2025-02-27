using System;
using System.Collections.Generic;
using System.Linq;
using FMOD.Studio;
using UnityEngine;

public class PatchManager : MonoBehaviour
{
    public static PatchManager Instance { get; private set; }
    private void Awake()
    {
        if (Instance != null && Instance != this)
        {
            Destroy(this);
        }
        else
        {
            Instance = this;
        }
    }

    public GameObject moduleRack;
    public OutputRack outputRack;
    
    public List<GameObject>[] Patches = new List<GameObject>[12];
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        UpdateAllPatches();
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void UpdateAllPatches()
    {
        for (int i = 0; i < 6; i++)
        {
            if (outputRack.previousModsWeapons[i] != null)
            {
                var currentMod = outputRack.previousModsWeapons[i];
                List<GameObject> patch = new List<GameObject>()
                {
                    currentMod
                };
                while (currentMod.GetComponent<Module>().previousModule != null)
                {
                    currentMod = currentMod.GetComponent<Module>().previousModule;
                    patch.Add(currentMod);
                }

                if (patch[^1].GetComponent<Module>().isSourceModule)
                {
                    UpdatePatch(patch, i);
                }
                else
                {
                    UpdatePatch(null, i);
                }
            }
            else if (Patches[i] != null)
            {
                UpdatePatch(null, i);
            }
        }

        for (int i = 6; i < 12; i++)
        {
            if (outputRack.previousModsShields[i - 6] != null)
            {
                var currentMod = outputRack.previousModsShields[i - 6];
                List<GameObject> patch = new List<GameObject>()
                {
                    currentMod
                };
                while (currentMod.GetComponent<Module>().previousModule != null)
                {
                    currentMod = currentMod.GetComponent<Module>().previousModule;
                    patch.Add(currentMod);
                }

                if (patch[^1].GetComponent<Module>().isSourceModule)
                {
                    UpdatePatch(patch, i);
                }
                else
                {
                    UpdatePatch(null, i);
                }
            }
            else if (Patches[i] != null)
            {
                UpdatePatch(null, i);
            }
        }
        // Debug.Log(Patches);
        // foreach (var patch in Patches)
        // {
        //     Debug.Log(patch);
        // }
    }


    void UpdatePatch(List<GameObject> patch, int i)
    {
        if (patch == null)
        {
            AudioManager.Instance.patchInstances[i].stop(STOP_MODE.IMMEDIATE);
            Patches[i] = null;
            return;
        }
        
        Patches[i] = patch;
        
        var p = Patches[i];
        p = patch;
        var paramDict = new Dictionary<string, float>
        {
            { "shipstate", 0 },
            { "arpstart", 1 },
            { "pitch", 440 },
            { "source", 2 },
            { "arp", 0 },
            { "arpspeed", 1000 },
            { "thruster", 0 },
            { "thrusterspeed", 1 },
            { "ringmod", 0 },
            { "shields", 1 }
        };
        var statDict = new Dictionary<string, float>
        {
            { "", 0 },
            { "extraHealth", 0 },
            { "incomingDamageMult", 0 },
            { "damage", 0 },
            { "attackSpeed", 1 },
            { "accuracy", 0 },
            { "evasion", 0 },
            { "izki", 0 },
            { "aubo", 0 },
            { "dwth", 0 }
        };

        Module.OutputType outputType = Module.OutputType.None;
        foreach (var mod in p)
        {
            paramDict[mod.GetComponent<Module>().parameter] = mod.GetComponent<Module>().parameterValue;
            statDict[mod.GetComponent<Module>().stat] += mod.GetComponent<Module>().statValue;
            // statDict["soundType"] = (float)mod.GetComponent<Module>().soundType;
            switch (mod.GetComponent<Module>().soundType)
            {
                case Module.SoundType.None:
                    break;
                case Module.SoundType.Izki:
                    statDict["izki"]++;
                    break;
                case Module.SoundType.Aubo:
                    statDict["aubo"]++;
                    break;
                case Module.SoundType.Dwth:
                    statDict["dwth"]++;
                    break;
            }
            if (mod.GetComponent<Module>().isOutputModule)
            {
                outputType = mod.GetComponent<Module>().outputType;
            }
        }
        AudioManager.Instance.SetParametersByDict(i, paramDict);
        CombatManager.Instance.SetStatsByDict(i, outputType, statDict);
    }
}