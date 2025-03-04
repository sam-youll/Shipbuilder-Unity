using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using FMOD;
using FMODUnity;
using FMOD.Studio;
using Debug = UnityEngine.Debug;
using Unity.VisualScripting;
using UnityEngine.Rendering;

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
    private EventInstance enemySongInst;


    //FMOD Event Reference 
    public EventReference moduleRef;
    public EventReference amb_spaceRef;
    public EventReference sfx_shipRef;
    public EventReference ui_pickupRef;
    public EventReference ui_putdownRef;
    public EventReference enemySongRef;
    public EventReference test_enemySong1Ref;
    public EventReference test_enemySong2Ref;
    public EventReference test_enemySong3Ref;
    
    public EventInstance[] patchInstances = new EventInstance[12];
    public List<EventReference> enemySongs = new List<EventReference>();
    public List<EventReference> enemySongsPlayed = new List<EventReference>();

    //im sure there's a better way
    private float enemyArpSpeed;
    private float enemyThrusterSpeed;
    private float enemyRingmod;
    private float enemyShields;
    private float enemyAttackPitch;
    private float enemyAttackSource;
    private float enemyDefensePitch;
    private float enemyDefenseSource;
    private float enemyEvasionPitch;
    private float enemyEvasionSource;
    private float enemyAccuracyPitch;
    private float enemyAccuracySource;

    private int pickedInstanceRef;
    private int mostRecent;

    private VCA playerVCA;
    private EventDescription moduleDescription;

    void Start()
    {
        // moduleInst = FMODUnity.RuntimeManager.CreateInstance(moduleRef);
        
        amb_spaceInst = FMODUnity.RuntimeManager.CreateInstance(amb_spaceRef);
        sfx_shipInst = FMODUnity.RuntimeManager.CreateInstance(sfx_shipRef);
        for (int i = 0; i < 12; i++)
        {
            patchInstances[i] = FMODUnity.RuntimeManager.CreateInstance(moduleRef);
        }

        //start events
        amb_spaceInst.start();

        enemySongs.Add(test_enemySong1Ref);
        enemySongs.Add(test_enemySong2Ref);
        enemySongs.Add(test_enemySong3Ref);

        playerVCA = FMODUnity.RuntimeManager.GetVCA("vca:/Player");
        moduleDescription = FMODUnity.RuntimeManager.GetEventDescription("event:/Module");
    }

    void Update()
    {
        
    }

    public void SetParametersByDict(int instanceIndex, Dictionary<string, float> parameters)
    {
        if (instanceIndex >= patchInstances.Length)
        {
            Debug.Log("Parameter index is out of range of patchInstances.");
            // var newInst = FMODUnity.RuntimeManager.CreateInstance(moduleRef);
            // newInst.start();
            // patchInstances.Add(newInst);
        }

        // foreach (var pair in parameters)
        // {
        //     Debug.Log(pair.Key + " " + pair.Value);
        // }
        
        
        // fmodEvents[instanceIndex].setParameterByName("shipstate", parameters["shipstate"]);
        
        //source params
        patchInstances[instanceIndex].setParameterByName("pitch", parameters["pitch"]);
        patchInstances[instanceIndex].setParameterByName("source", parameters["source"]);
        patchInstances[instanceIndex].setParameterByName("wiresplitter", parameters["wiresplitter"]);
        //AM params
        patchInstances[instanceIndex].setParameterByName("AM", parameters["AM"]);
        patchInstances[instanceIndex].setParameterByName("AMsource", parameters["AMsource"]);
        patchInstances[instanceIndex].setParameterByName("AMfreq", parameters["AMfreq"]);
        patchInstances[instanceIndex].setParameterByName("AMdepth", parameters["AMdept"]);
        //FM params
        patchInstances[instanceIndex].setParameterByName("FM", parameters["FM"]);
        patchInstances[instanceIndex].setParameterByName("FMsource", parameters["FMsource"]);
        patchInstances[instanceIndex].setParameterByName("FMfreq", parameters["FMfreq"]);
        patchInstances[instanceIndex].setParameterByName("FMdepth", parameters["FMdepth"]);
        //AM on AM params
        patchInstances[instanceIndex].setParameterByName("AM2", parameters["AM2"]);
        patchInstances[instanceIndex].setParameterByName("AM2source", parameters["AM2source"]);
        patchInstances[instanceIndex].setParameterByName("AM2freq", parameters["AM2freq"]);
        patchInstances[instanceIndex].setParameterByName("AM2depth", parameters["AM2depth"]);
        //FM on FM params - broken rn, wasn't before
        patchInstances[instanceIndex].setParameterByName("FM2", parameters["FM2"]);
        patchInstances[instanceIndex].setParameterByName("FM2source", parameters["FM2source"]);
        patchInstances[instanceIndex].setParameterByName("FM2freq", parameters["FM2freq"]);
        patchInstances[instanceIndex].setParameterByName("FM2depth", parameters["FM2depth"]);
        //AM on FM params - this doesn't work right now
        patchInstances[instanceIndex].setParameterByName("FMAM", parameters["FMAM"]);
        patchInstances[instanceIndex].setParameterByName("FMAMsource", parameters["FMAMsource"]);
        patchInstances[instanceIndex].setParameterByName("FMAMfreq", parameters["FMAMfreq"]);
        patchInstances[instanceIndex].setParameterByName("FMAMdepth", parameters["FMAMdepth"]);
        //FM on AM params - this doesn't work right now
        patchInstances[instanceIndex].setParameterByName("AMFM", parameters["AMFM"]);
        patchInstances[instanceIndex].setParameterByName("AMFMsource", parameters["AMFMsource"]);
        patchInstances[instanceIndex].setParameterByName("AMFMfreq", parameters["AMFMfreq"]);
        patchInstances[instanceIndex].setParameterByName("AMFMdepth", parameters["AMFMdepth"]);


        //OLD PARAMS - just holding this in case shit breaks at a bad time
        //patchInstances[instanceIndex].setParameterByName("arpstart", parameters["arpstart"]);
        /*patchInstances[instanceIndex].setParameterByName("arp", parameters["arp"]);
        patchInstances[instanceIndex].setParameterByName("arpspeed", parameters["arpspeed"]); //speed of arpeggiator 50-2000, higher = slower. ms between pitch changes
        patchInstances[instanceIndex].setParameterByName("thruster", parameters["thruster"]);
        patchInstances[instanceIndex].setParameterByName("thrusterspeed", parameters["thrusterspeed"]); //how fast thruster goes, 1-15. 15 fastest, 1 slowest (frequency of LFO)
        patchInstances[instanceIndex].setParameterByName("ringmod", parameters["ringmod"]); 
        patchInstances[instanceIndex].setParameterByName("shields", parameters["shields"]); //shields param: 1-4. 1 is "off" (one voice), 2 is 2 voices, etc. */

        patchInstances[instanceIndex].start();
    }

    public void PickUpModuleSFX()
    {
        FMODUnity.RuntimeManager.PlayOneShot(ui_pickupRef);
    }

    public void PutDownModuleSFX()
    {
        FMODUnity.RuntimeManager.PlayOneShot(ui_putdownRef);
    }

    private EventReference EnemySongPicked()
    {
        // pickedInstanceRef = UnityEngine.Random.Range(0, enemySongs.Count);
        pickedInstanceRef = 0;

        enemySongRef = enemySongs[pickedInstanceRef];

        return enemySongRef;

    }

    public void PlayEnemySong()
    {
        if (enemySongsPlayed.Count == 0)
        {
            //pick the new song from songs list
            EnemySongPicked();
            //create the instance
            enemySongInst = FMODUnity.RuntimeManager.CreateInstance(enemySongRef);
            //start the instance
            enemySongInst.start();
            //add it to the played song list
            enemySongsPlayed.Add(enemySongRef);
            //get the event's parameters 
            GetEnemyParams(enemySongRef);
            //delete it from the songs list so it doesn't get selected again
            enemySongs.Remove(enemySongRef);

            //Debug.Log(enemySongRef.Guid);
        }
        else
        {
            enemySongInst.start();
            //Debug.Log(enemySongRef.Guid);
        }
        
    }

    public void GetEnemyParams(EventReference enemySongRef)
    {
        //this is where shit gets unhinged this is NOT the way to do it im so so so sorry for the crimes i am committing here pls forgive, surely figuring out dicts will save me one day
        //just setting the things u need to calculate the stats based on which event is playing
        if (enemySongRef.Guid == test_enemySong1Ref.Guid)
        {
            enemyArpSpeed = 226;
            enemyThrusterSpeed = 5;
            enemyRingmod = 1;
            enemyShields = 3;
            enemyAttackPitch = 174.6f;
            enemyAttackSource = 2;
            enemyDefensePitch = 349.2f;
            enemyDefenseSource = 4;
            enemyEvasionPitch = 43.65f;
            enemyEvasionSource = 4;
            enemyAccuracyPitch = 659.3f;
            enemyAccuracySource = 2;
        }
        else if (enemySongRef.Guid == test_enemySong2Ref.Guid)
        {
            enemyArpSpeed = 82;
            enemyThrusterSpeed = 2;
            enemyRingmod = 1;
            enemyShields = 3;
            enemyAttackPitch = 932.3f;
            enemyAttackSource = 4;
            enemyDefensePitch = 116.5f;
            enemyDefenseSource = 3;
            enemyEvasionPitch = 349.2f;
            enemyEvasionSource = 4;
            enemyAccuracyPitch = 1397;
            enemyAccuracySource = 2;
        }
        else if (enemySongRef.Guid == test_enemySong3Ref.Guid)
        {
            enemyArpSpeed = 2000;
            enemyThrusterSpeed = 1;
            enemyRingmod = 1;
            enemyShields = 2;
            enemyAttackPitch = 196;
            enemyAttackSource = 4;
            enemyDefensePitch = 246.9f;
            enemyDefenseSource = 2;
            enemyEvasionPitch = 73.41f;
            enemyEvasionSource = 3;
            enemyAccuracyPitch = 739.9f;
            enemyAccuracySource = 2;
        }
    }

    public void ResetPlayedList()
    {
        if (enemySongsPlayed.Count > 0)
        {
            enemySongsPlayed.RemoveAt(0);
        }
    }

    public void StopEnemySong()
    {
        enemySongInst.stop(0);
    }

    public void MutePlayerVolume()
    {
        playerVCA.setVolume(0);
    }

    public void UnmutePlayerVolume()
    {
        playerVCA.setVolume(1);
    }

    public void ResetModuleInstances()
    {
        moduleDescription.releaseAllInstances();    
    }
}
