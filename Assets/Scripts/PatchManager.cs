using System;
using System.Collections.Generic;
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
    
    public List<List<GameObject>> Patches = new List<List<GameObject>>();
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void UpdatePatch(GameObject patchSource)
    {
        List<GameObject> patch = new List<GameObject>();
        
        GameObject currentMod = patchSource;
        int loopCount = 0;
        while (currentMod.GetComponent<Module>().nextModule != null)
        {
            patch.Add(currentMod);
            currentMod = currentMod.GetComponent<Module>().nextModule;
            
            loopCount++;
            if (loopCount > 100)
            {
                break;
            }
        }
        patch.Add(currentMod);

        int patchIndex = -1;
        if (Patches != null)
        {
            for (int i = 0; i < Patches.Count; i++)
            {
                if (Patches[0][0] == patchSource)
                {
                    patchIndex = i;
                }
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
        
        AudioManager.Instance.SetParameters(0, AudioManager.Instance.testParams);
    }
}