using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using FMOD;
using FMODUnity;
using FMOD.Studio;

public class AudioManager: MonoBehaviour
{
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

    //param variables 
    public float pitch;
    public float source;
    public float arp;
    public float thruster;
    public float ringmod;
    //shipstate: 0 not started, 1 started, 2 off
    public float shipstate;


    void Start()
    {
        //assign events
        moduleInst = FMODUnity.RuntimeManager.CreateInstance(moduleRef);
        amb_spaceInst = FMODUnity.RuntimeManager.CreateInstance(amb_spaceRef);
        sfx_shipInst = FMODUnity.RuntimeManager.CreateInstance(sfx_shipRef);
        ui_pickupInst = FMODUnity.RuntimeManager.CreateInstance(ui_pickupRef);
        ui_putdownInst = FMODUnity.RuntimeManager.CreateInstance(ui_putdownRef);

        //start events
        moduleInst.start();
        amb_spaceInst.start();

        //init variables
        shipstate = 0;
        pitch = 440;
        source = 1;
        arp = 0;
        thruster = 0;
        ringmod = 0;
    }

    void Update()
    {
        //set params
        moduleInst.setParameterByName("arpstart", 1);
        moduleInst.setParameterByName("pitch", pitch);
        moduleInst.setParameterByName("source", source);
        moduleInst.setParameterByName("arp", arp);
        moduleInst.setParameterByName("thruster", thruster);
        moduleInst.setParameterByName("ringmod", ringmod);
        sfx_shipInst.setParameterByName("shipstate", shipstate);

    }
}
