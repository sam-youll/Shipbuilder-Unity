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
    
    public List<List<GameObject>> Patches = new List<List<GameObject>>();

    public GameObject atkBar;
    public GameObject defBar;
    public GameObject accBar;
    public GameObject evaBar;
    
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
        // add all source modules to list
        List<GameObject> sources = new List<GameObject>();
        for (int i = 0; i < moduleRack.transform.childCount; i++)
        {
            var mod = moduleRack.transform.GetChild(i).gameObject;
            if (mod.GetComponent<Module>().isSourceModule)
            {
                sources.Add(mod);
            }
        }

        // Loop through all sources to find and handle the patch for each
        for (int i = 0; i < sources.Count; i++)
        {
            List<GameObject> patch = new List<GameObject>();
        
            // Get list of GameObjects connected to source
            GameObject currentMod = sources[i];
            int loopCount = 0;
            while (currentMod.GetComponent<Module>().nextModule != null)
            {
                patch.Add(currentMod);
                currentMod = currentMod.GetComponent<Module>().nextModule;

                loopCount++;
                if (loopCount > 100)
                {
                    Debug.Log("there's a recursion error in a patch. whoopsies!");
                    break;
                }
            }
            patch.Add(currentMod);

            if (!currentMod.GetComponent<Module>().isOutputModule)
            {
                // if the last module in the patch is not an output, the patch should not play
                // if it was a patch playing audio, we need to check and delete the existing patch
                foreach (var p in Patches.ToList())
                {
                    if (p[0] == patch[0])
                    {
                        Patches.Remove(p);
                        if (i < AudioManager.Instance.moduleInstances.Count)
                        {
                            AudioManager.Instance.moduleInstances[i].stop(STOP_MODE.IMMEDIATE);
                            AudioManager.Instance.moduleInstances.RemoveAt(i);
                        }
                    }
                }
    
                // loop to next source
                continue;
            }
            
            // Check if patch exists in Patches master list
            // If it doesn't exist, add it
            int patchIndex = -1;
            foreach (var p in Patches)
            {
                if (p[0] == sources[i])
                {
                    patchIndex = i;
                }
            }
            if (patchIndex == -1)
            {
                Patches.Add(patch);
            }
            else
            {
                Patches[patchIndex] = patch;
            }
        }
        
        // Check Patches master list for deletion
        for (var i = 0; i < Patches.Count; i++)
        {
            var p = Patches[i];
            var del = true;
            foreach (var s in sources)
            {
                if (p[0] == s)
                {
                    del = false;
                }
            }

            if (del)
            {
                Patches.RemoveAt(i);
                AudioManager.Instance.moduleInstances[i].stop(STOP_MODE.IMMEDIATE);
                AudioManager.Instance.moduleInstances.RemoveAt(i);
            }
        }

        // Send values to AudioManager to set parameters in FMOD
        for (var i = 0; i < Patches.Count; i++)
        {
            var p = Patches[i];
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
                // // statDict[mod.GetComponent<Module>().stat] = mod.GetComponent<Module>().statValue;
                // var stat = mod.GetComponent<Module>().stat;
                // var val = mod.GetComponent<Module>().statValue;
                // switch (stat)
                // {
                //     case "extraHealth":
                //         CombatManager.Instance.playerHealth += val;
                //         break;
                //     case "attackSpeed":
                //         break;
                //     case "incomingDamageMult":
                //         break;
                //     case "accuracy":
                //         break;
                //     case "izki":
                //         break;
                //     case "aubo":
                //         break;
                //     case "dwth":
                //         break;
                //     
                // }
            }
            AudioManager.Instance.SetParametersByDict(i, paramDict);
            CombatManager.Instance.SetStatsByDict(i, outputType, statDict);

            // atkBar.GetComponent<StatBar>().value = statDict["atk"];
            // defBar.GetComponent<StatBar>().value = statDict["def"];
            // accBar.GetComponent<StatBar>().value = statDict["acc"];
            // evaBar.GetComponent<StatBar>().value = statDict["eva"];
        }
    }
}