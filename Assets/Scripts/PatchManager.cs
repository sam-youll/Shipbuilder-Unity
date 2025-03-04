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
            //source params
            { "pitch", 440 },
            { "source", 2 },
            { "wiresplitter", 0 },
            //AM params
            { "AM", 0 },
            { "AMsource", 1 },
            { "AMfreq", 1 },
            { "AMdepth", 1 },
            //FM params
            { "FM", 0 },
            { "FMsource", 1 },
            { "FMfreq", 1 },
            { "FMdepth", 100 },
            //AM2 params
            { "AM2", 0 },
            { "AM2source", 1 },
            { "AM2freq", 1 },
            { "AM2depth", 1 },
            //FM2 params
            { "FM2", 0 },
            { "FM2source", 1 },
            { "FM2freq", 1 },
            { "FM2depth", 100 },
            //AM on FM params 
            { "FMAM", 0 },
            { "FMAMsource", 1 },
            { "FMAMfreq", 1 },
            { "FMAMdepth", 1 },
            //FM on AM params
            { "AMFM", 0 },
            { "AMFMsource", 1 },
            { "AMFMfreq", 1 },
            { "AMFMdepth", 100 }
            
            //old ones, just keeping them here in case there's a last minute crisis
            /*{ "arpstart", 1 },
            { "arp", 0 },
            { "arpspeed", 1000 },
            { "thruster", 0 },
            { "thrusterspeed", 1 },
            { "ringmod", 0 },
            { "shields", 1 }*/
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
        }
        AudioManager.Instance.SetParametersByDict(i, paramDict);
        CombatManager.Instance.SetStatsByDict(i, OutputRack.Instance.ModuleOutputType(patch[0].GetComponent<Module>()), statDict);
    }
}