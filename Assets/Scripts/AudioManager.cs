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

<<<<<<< Updated upstream
    //param variables 
    public float pitch;
    public float source;
    public float arp;
    public float thruster;
    public float ringmod;
    //shipstate: 0 not started, 1 started, 2 off
    public float shipstate;
=======
    
    public List<EventInstance> fmodEvents = new List<EventInstance>();
    
    // this is an example of how data is passed to FMOD instances
    public Dictionary<string, float> testParams = new Dictionary<string, float>();
>>>>>>> Stashed changes


    void Start()
    {
<<<<<<< Updated upstream
        //assign events
=======
        testParams.Add("pitch", 1f);
        testParams.Add("source", 1f);
        testParams.Add("arp", 1f);
        testParams.Add("thruster", 1f);
        testParams.Add("ringmod", 1f);
        
        
>>>>>>> Stashed changes
        moduleInst = FMODUnity.RuntimeManager.CreateInstance(moduleRef);
        amb_spaceInst = FMODUnity.RuntimeManager.CreateInstance(amb_spaceRef);
        sfx_shipInst = FMODUnity.RuntimeManager.CreateInstance(sfx_shipRef);
        ui_pickupInst = FMODUnity.RuntimeManager.CreateInstance(ui_pickupRef);
        ui_putdownInst = FMODUnity.RuntimeManager.CreateInstance(ui_putdownRef);

        //start events
        moduleInst.start();
<<<<<<< Updated upstream
        amb_spaceInst.start();

        //init variables
        shipstate = 0;
        pitch = 440;
        source = 1;
        arp = 0;
        thruster = 0;
        ringmod = 0;
=======
        fmodEvents.Add(moduleInst);
>>>>>>> Stashed changes
    }

    void Update()
    {
<<<<<<< Updated upstream
        //set params
        moduleInst.setParameterByName("arpstart", 1);
        moduleInst.setParameterByName("pitch", pitch);
        moduleInst.setParameterByName("source", source);
        moduleInst.setParameterByName("arp", arp);
        moduleInst.setParameterByName("thruster", thruster);
        moduleInst.setParameterByName("ringmod", ringmod);
        sfx_shipInst.setParameterByName("shipstate", shipstate);

=======
        
    }

    public void SetParameters(int instanceIndex, Dictionary<string, float> parameters)
    {
        Debug.Log(fmodEvents.Count);
        if (!fmodEvents[instanceIndex].isValid()) return;
                
        fmodEvents[instanceIndex].setParameterByName("arpstart", parameters["arpstart"]);
        fmodEvents[instanceIndex].setParameterByName("pitch", parameters["pitch"]);
        fmodEvents[instanceIndex].setParameterByName("source", parameters["source"]);
        fmodEvents[instanceIndex].setParameterByName("arp", parameters["arp"]);
        fmodEvents[instanceIndex].setParameterByName("thruster", parameters["thruster"]);
        fmodEvents[instanceIndex].setParameterByName("ringmod", parameters["ringmod"]);
>>>>>>> Stashed changes
    }
}
