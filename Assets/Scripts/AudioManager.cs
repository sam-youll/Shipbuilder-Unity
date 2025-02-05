using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using FMOD;
using FMODUnity;
using FMOD.Studio;
using Debug = UnityEngine.Debug;

public class AudioManager: MonoBehaviour
{
    public static AudioManager Instance;

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

    //FMOD Event Instance
    private EventInstance moduleInst;
    private EventInstance amb_spaceInst;
    private EventInstance sfx_shipInst;
    private EventInstance ui_pickupInst;
    private EventInstance ui_putdownInst;
    //FMOD Event Reference 
    public EventReference moduleRef;
    public EventReference amb_spaceRef;
    public EventReference sfx_shipRef;
    public EventReference ui_pickupRef;
    public EventReference ui_putdownRef;
    
    public List<EventInstance> moduleInstances = new List<EventInstance>();

    void Start()
    {
        // moduleInst = FMODUnity.RuntimeManager.CreateInstance(moduleRef);
        
        amb_spaceInst = FMODUnity.RuntimeManager.CreateInstance(amb_spaceRef);
        sfx_shipInst = FMODUnity.RuntimeManager.CreateInstance(sfx_shipRef);
        ui_pickupInst = FMODUnity.RuntimeManager.CreateInstance(ui_pickupRef);
        ui_putdownInst = FMODUnity.RuntimeManager.CreateInstance(ui_putdownRef);

        //start events
        // moduleInst.start();
        amb_spaceInst.start();

        // moduleInstances.Add(moduleInst);
    }

    void Update()
    {

    }

    public void SetParametersByDict(int instanceIndex, Dictionary<string, float> parameters)
    {
        if (instanceIndex >= moduleInstances.Count)
        {
            var newInst = FMODUnity.RuntimeManager.CreateInstance(moduleRef);
            newInst.start();
            moduleInstances.Add(newInst);
        }
        
        // fmodEvents[instanceIndex].setParameterByName("shipstate", parameters["shipstate"]);
        moduleInstances[instanceIndex].setParameterByName("arpstart", parameters["arpstart"]);
        moduleInstances[instanceIndex].setParameterByName("pitch", parameters["pitch"]);
        moduleInstances[instanceIndex].setParameterByName("source", parameters["source"]);
        moduleInstances[instanceIndex].setParameterByName("arp", parameters["arp"]);
        moduleInstances[instanceIndex].setParameterByName("arpspeed", parameters["arpspeed"]); //speed of arpeggiator 50-2000, higher = slower. ms between pitch changes
        moduleInstances[instanceIndex].setParameterByName("thruster", parameters["thruster"]);
        moduleInstances[instanceIndex].setParameterByName("thrusterspeed", parameters["thrusterspeed"]); //how fast thruster goes, 1-15. 15 fastest, 1 slowest (frequency of LFO)
        moduleInstances[instanceIndex].setParameterByName("ringmod", parameters["ringmod"]); 
        moduleInstances[instanceIndex].setParameterByName("shields", parameters["shields"]); //shields param: 1-4. 1 is "off" (one voice), 2 is 2 voices, etc. 
    }

    public void PickUpModuleSFX()
    {
        FMODUnity.RuntimeManager.PlayOneShot(ui_pickupRef);
    }

    public void PutDownModuleSFX()
    {
        FMODUnity.RuntimeManager.PlayOneShot(ui_putdownRef);
    }
}
