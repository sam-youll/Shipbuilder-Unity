using System;
using System.Collections.Generic;
using UnityEngine;

public class Reactor : MonoBehaviour
{
    public static Reactor Instance;

    private void Awake()
    {
        Instance = this;
    }

    public float power; // default power module adds 1, can be more or less (upper limit 30-40 maybe?)
    public float rate; // 1-4, but tempo is 200-600
    public float strength; // 1-4
    public float izki;
    public float aubo;
    public float dwth;
    private List<Module> myPatch;

    public GameObject previousModule;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
    
    public void SetPatch()
    {
        if (previousModule == null)
            return;
        
        myPatch = new();
        var prev = previousModule.GetComponent<Module>();
        while (prev.previousModule != null)
        {
            // Debug.Log(prev.name);
            myPatch.Add(prev);
            prev = prev.previousModule.GetComponent<Module>();
        }
        // Debug.Log(prev.name);
        myPatch.Add(prev);

        power = 0;
        rate = 0;
        foreach (var module in myPatch)
        {
            if (module.stat == "power")
            {
                power += module.statValue;
            }
            else if (module.stat == "rate")
            {
                rate += module.statValue;
            }
        }

        strength = power / rate;
        
        Conductor.Instance.tempo = 120 + (rate * 100);

        // TODO: set values of ReactorSounds.Instance based on adsrValues[adsrIndex]
        ReactorSounds.Instance.SetReactorParams();
    }
}
