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
                { "thruster", 0 },
                { "ringmod", 0 }
            };
            var statDict = new Dictionary<string, float>
            {
                { "atk", .1f },
                { "def", .9f },
                { "acc", .1f },
                { "eva", .1f }
            };
            foreach (var mod in p)
            {
                paramDict[mod.GetComponent<Module>().parameter] = mod.GetComponent<Module>().parameterValue;
                
                // TODO: THIS IS A TEMPORARY FIX SO ON PATCH DOESN'T OVERRIDE ANOTHER
                // TODO: I dn't think this works anyway
                // if (mod.GetComponent<Module>().statValue > statDict[mod.GetComponent<Module>().stat])
                // {
                    statDict[mod.GetComponent<Module>().stat] = mod.GetComponent<Module>().statValue;
                // }
            }
            AudioManager.Instance.SetParametersByDict(i, paramDict);

            atkBar.GetComponent<StatBar>().value = statDict["atk"];
            defBar.GetComponent<StatBar>().value = statDict["def"];
            accBar.GetComponent<StatBar>().value = statDict["acc"];
            evaBar.GetComponent<StatBar>().value = statDict["eva"];
        }
    }
}