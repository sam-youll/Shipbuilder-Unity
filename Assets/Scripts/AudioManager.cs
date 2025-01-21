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
    //FMOD Event Reference 
    public EventReference moduleRef;

    //param variables 
    public float pitch;
    public float source;
    public float arp;
    public float thruster;
    public float ringmod;


    void Start()
    {
        moduleInst = FMODUnity.RuntimeManager.CreateInstance(moduleRef);
        moduleInst.start();
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
    }
}
