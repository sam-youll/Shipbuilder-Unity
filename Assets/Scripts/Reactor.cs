using System;
using System.Collections.Generic;
using FMOD.Studio;
using TMPro;
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
    private float shields; // 1-4
    public float izki;
    public float aubo;
    public float dwth;
    private List<Module> myPatch;

    public GameObject previousModule;

    private EventInstance[] pads = new EventInstance[8];

    public bool tempoOverride;

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
        myPatch = new();
        
        if (previousModule != null)
        {
            var prev = previousModule.GetComponent<Module>();
            while (prev.previousModule != null)
            {
                // Debug.Log(prev.name);
                myPatch.Add(prev);
                prev = prev.previousModule.GetComponent<Module>();
            }
            // Debug.Log(prev.name);
            myPatch.Add(prev);
        }

        power = 0;
        rate = 0;
        shields = 0;
        ReactorSounds.Instance.RemoveAllPads(ReactorSounds.Instance.playerPads);
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
            else if (module.stat == "shield")
            {
                shields += module.statValue;
            }
        }

        shields = Mathf.Clamp(shields, 0, 4);
        for (var i = 0; i < CombatManager.Instance.playerShip.shields.Length; i++)
        {
            var shield = CombatManager.Instance.playerShip.shields[i];
            shield.SetActive(false);
        }

        for (var i = 0; i < shields; i++)
        {
            CombatManager.Instance.playerShip.shields[i].SetActive(true);
        }



        float shieldDiff = shields - ReactorSounds.Instance.playerPads.Count;

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
                ReactorSounds.Instance.RemovePlayerPad(ReactorSounds.Instance.playerPads[i]);
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
