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
using UnityEngine.SceneManagement;

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
    private EventInstance tutorialEnemyShieldInst;
    private EventInstance tutorialEnemyWeaponInst;
    private EventInstance sfx_stormInst;


    //FMOD Event Reference 
    //module
    [Header("Module Reference")]
    public EventReference moduleRef;
    //ambience
    [Header("Space Reference")]
    public EventReference amb_spaceRef;
    //sfx
    [Header("SFX Reference")]
    public EventReference sfx_shipRef;
    public EventReference sfx_paperRef;
    public EventReference sfx_stormRef;
    //ui
    [Header("UI References")]
    public EventReference ui_pickupRef;
    public EventReference ui_putdownRef;
    public EventReference ui_dialogueRef;
    //enemy songs
    [Header("Enemy References")]
    public EventReference enemySongRef;
    public EventReference test_enemySong1Ref;
    public EventReference test_enemySong2Ref;
    public EventReference test_enemySong3Ref;
    
    
    
    public EventInstance[] patchInstances = new EventInstance[12];
    public EventInstance[] enemyPatchInstances = new EventInstance[12];
    public List<EventReference> enemySongs = new List<EventReference>();
    public List<EventReference> enemySongsPlayed = new List<EventReference>();

    private List<GameObject> weapons = new List<GameObject>();
    private List<EventInstance> weaponsEventInstances = new List<EventInstance>();
    private List<Coroutine> weaponsCoroutines = new List<Coroutine>();

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

    public float noteLength;
    public float attackRatio = 0.3f;
    public float decayRatio = 0.4f;
    public float releaseRatio = 0.3f;
    public float attack;
    public float decay;
    public float release;

    void Start()
    {
        // moduleInst = FMODUnity.RuntimeManager.CreateInstance(moduleRef);
        
        amb_spaceInst = FMODUnity.RuntimeManager.CreateInstance(amb_spaceRef);
        sfx_shipInst = FMODUnity.RuntimeManager.CreateInstance(sfx_shipRef);

        tutorialEnemyShieldInst = FMODUnity.RuntimeManager.CreateInstance(moduleRef);
        tutorialEnemyWeaponInst = FMODUnity.RuntimeManager.CreateInstance(moduleRef);

        for (int i = 0; i < 12; i++)
        {
            patchInstances[i] = FMODUnity.RuntimeManager.CreateInstance(moduleRef);
            enemyPatchInstances[i] = FMODUnity.RuntimeManager.CreateInstance(moduleRef);
        }

        //start events
        amb_spaceInst.start();

        enemySongs.Add(test_enemySong1Ref);
        enemySongs.Add(test_enemySong2Ref);
        enemySongs.Add(test_enemySong3Ref);

        playerVCA = FMODUnity.RuntimeManager.GetVCA("vca:/Player");
        moduleDescription = FMODUnity.RuntimeManager.GetEventDescription("event:/Module");

        noteLength = 60 / Conductor.Instance.tempo;
        attack = noteLength * attackRatio;
        decay = noteLength * decayRatio;
        release = noteLength * releaseRatio;
        UnityEngine.Debug.Log("note length: " + noteLength + "attack: " + attack + "decay: " + decay + "release" + release);
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
        //AM params
        patchInstances[instanceIndex].setParameterByName("AM", parameters["AM"]);
        patchInstances[instanceIndex].setParameterByName("AMsource", parameters["AMsource"]);
        patchInstances[instanceIndex].setParameterByName("AMfreq", parameters["AMfreq"]);
        patchInstances[instanceIndex].setParameterByName("AMdepth", parameters["AMdepth"]);
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

        //adsr params
        patchInstances[instanceIndex].setParameterByName("adsr", parameters["adsr"]);
        patchInstances[instanceIndex].setParameterByName("attack", parameters["attack"]); //attack in ms, 0-2000
        patchInstances[instanceIndex].setParameterByName("decay", parameters["decay"]); //decay in ms, 0-2000
        patchInstances[instanceIndex].setParameterByName("sustain", parameters["sustain"]); //sustain amount, 0-1
        patchInstances[instanceIndex].setParameterByName("release", parameters["release"]); //release in ms, 0-2000


        //OLD PARAMS - just holding this in case shit breaks at a bad time
        //patchInstances[instanceIndex].setParameterByName("arpstart", parameters["arpstart"]);
        /*patchInstances[instanceIndex].setParameterByName("arp", parameters["arp"]);
        patchInstances[instanceIndex].setParameterByName("arpspeed", parameters["arpspeed"]); //speed of arpeggiator 50-2000, higher = slower. ms between pitch changes
        patchInstances[instanceIndex].setParameterByName("thruster", parameters["thruster"]);
        patchInstances[instanceIndex].setParameterByName("thrusterspeed", parameters["thrusterspeed"]); //how fast thruster goes, 1-15. 15 fastest, 1 slowest (frequency of LFO)
        patchInstances[instanceIndex].setParameterByName("ringmod", parameters["ringmod"]); 
        patchInstances[instanceIndex].setParameterByName("shields", parameters["shields"]); //shields param: 1-4. 1 is "off" (one voice), 2 is 2 voices, etc. */

        if (!IsPlaying(patchInstances[instanceIndex]))
        {
            patchInstances[instanceIndex].start();
        }
    }
    
    public void SetEnemyParametersByDict(int instanceIndex, Dictionary<string, float> parameters)
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

        
        //source params
        enemyPatchInstances[instanceIndex].setParameterByName("pitch", parameters["pitch"]);
        enemyPatchInstances[instanceIndex].setParameterByName("source", parameters["source"]);
        //AM params
        enemyPatchInstances[instanceIndex].setParameterByName("AM", parameters["AM"]);
        enemyPatchInstances[instanceIndex].setParameterByName("AMsource", parameters["AMsource"]);
        enemyPatchInstances[instanceIndex].setParameterByName("AMfreq", parameters["AMfreq"]);
        enemyPatchInstances[instanceIndex].setParameterByName("AMdepth", parameters["AMdepth"]);
        //FM params
        enemyPatchInstances[instanceIndex].setParameterByName("FM", parameters["FM"]);
        enemyPatchInstances[instanceIndex].setParameterByName("FMsource", parameters["FMsource"]);
        enemyPatchInstances[instanceIndex].setParameterByName("FMfreq", parameters["FMfreq"]);
        enemyPatchInstances[instanceIndex].setParameterByName("FMdepth", parameters["FMdepth"]);
        //AM on AM params
        enemyPatchInstances[instanceIndex].setParameterByName("AM2", parameters["AM2"]);
        enemyPatchInstances[instanceIndex].setParameterByName("AM2source", parameters["AM2source"]);
        enemyPatchInstances[instanceIndex].setParameterByName("AM2freq", parameters["AM2freq"]);
        enemyPatchInstances[instanceIndex].setParameterByName("AM2depth", parameters["AM2depth"]);
        //FM on FM params - broken rn, wasn't before
        enemyPatchInstances[instanceIndex].setParameterByName("FM2", parameters["FM2"]);
        enemyPatchInstances[instanceIndex].setParameterByName("FM2source", parameters["FM2source"]);
        enemyPatchInstances[instanceIndex].setParameterByName("FM2freq", parameters["FM2freq"]);
        enemyPatchInstances[instanceIndex].setParameterByName("FM2depth", parameters["FM2depth"]);
        //AM on FM params - this doesn't work right now
        enemyPatchInstances[instanceIndex].setParameterByName("FMAM", parameters["FMAM"]);
        enemyPatchInstances[instanceIndex].setParameterByName("FMAMsource", parameters["FMAMsource"]);
        enemyPatchInstances[instanceIndex].setParameterByName("FMAMfreq", parameters["FMAMfreq"]);
        enemyPatchInstances[instanceIndex].setParameterByName("FMAMdepth", parameters["FMAMdepth"]);
        //FM on AM params - this doesn't work right now
        enemyPatchInstances[instanceIndex].setParameterByName("AMFM", parameters["AMFM"]);
        enemyPatchInstances[instanceIndex].setParameterByName("AMFMsource", parameters["AMFMsource"]);
        enemyPatchInstances[instanceIndex].setParameterByName("AMFMfreq", parameters["AMFMfreq"]);
        enemyPatchInstances[instanceIndex].setParameterByName("AMFMdepth", parameters["AMFMdepth"]);

        //adsr params
        enemyPatchInstances[instanceIndex].setParameterByName("adsr", parameters["adsr"]);
        enemyPatchInstances[instanceIndex].setParameterByName("attack", parameters["attack"]); //attack in ms, 0-2000
        enemyPatchInstances[instanceIndex].setParameterByName("decay", parameters["decay"]); //decay in ms, 0-2000
        enemyPatchInstances[instanceIndex].setParameterByName("sustain", parameters["sustain"]); //sustain amount, 0-1
        enemyPatchInstances[instanceIndex].setParameterByName("release", parameters["release"]); //release in ms, 0-2000

        enemyPatchInstances[instanceIndex].start();
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
        if (SceneManager.GetActiveScene() == SceneManager.GetSceneByName("Gameplay Tutorial"))
        {
            PlayTutEnemyShields();
            Debug.Log("In the right scene");
        }
        else if (enemySongsPlayed.Count == 0)
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
        tutorialEnemyShieldInst.stop(0);
        tutorialEnemyWeaponInst.stop(0);
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

    public void PlayDialogueSound()
    {
        FMODUnity.RuntimeManager.PlayOneShot(ui_dialogueRef);
    }

    public void PlayPaperSound()
    {
        FMODUnity.RuntimeManager.PlayOneShot(sfx_paperRef);
    }

    public void PlayTutEnemyShields()
    {
        tutorialEnemyShieldInst.setParameterByName("source", 2);
        tutorialEnemyShieldInst.setParameterByName("pitch", 164.81f);
        tutorialEnemyShieldInst.start();
        Debug.Log("Playing tut enemy shield");
    }

    public void PlayTutEnemyWeapon()
    {
        tutorialEnemyWeaponInst.setParameterByName("source", 3);
        tutorialEnemyWeaponInst.setParameterByName("pitch", 440);
        tutorialEnemyWeaponInst.setParameterByName("arpstart", 1);
        tutorialEnemyWeaponInst.setParameterByName("arp", 1);
        tutorialEnemyWeaponInst.setParameterByName("apitch1", 587.33f);
        tutorialEnemyWeaponInst.setParameterByName("apitch2", 739.99f);
        tutorialEnemyWeaponInst.setParameterByName("apitch3", 880);
        tutorialEnemyWeaponInst.setParameterByName("apitch4", 1108.7f);
        tutorialEnemyWeaponInst.setParameterByName("note1", 1);
        tutorialEnemyWeaponInst.setParameterByName("note2", 1);
        tutorialEnemyWeaponInst.setParameterByName("note3", 1);
        tutorialEnemyWeaponInst.setParameterByName("note4", 1);
        tutorialEnemyWeaponInst.setParameterByName("attack", 10);
        tutorialEnemyWeaponInst.setParameterByName("decay", 10);
        tutorialEnemyWeaponInst.setParameterByName("sustain", 0);
        tutorialEnemyWeaponInst.setParameterByName("release", 20);
        tutorialEnemyWeaponInst.start();
    }
    
    bool IsPlaying(FMOD.Studio.EventInstance instance) {
        FMOD.Studio.PLAYBACK_STATE state;   
        instance.getPlaybackState(out state);
        return state != FMOD.Studio.PLAYBACK_STATE.STOPPED;
    }

    public void PlayNote(GameObject weapon, Dictionary<string, float> noteInfo)
    {
        StartCoroutine(PlayNoteCoroutine(weapon, noteInfo));
    }

    IEnumerator PlayNoteCoroutine(GameObject weapon, Dictionary<string, float> noteInfo)
    {
        var started = false;
        var weaponIndex = -1;
        
        if (!started)
        {
            // compare weapon against all existing weapons
            for (int i = 0; i < weapons.Count; i++)
            {
                if (weapon == weapons[i])
                {
                    weaponIndex = i;
                    break;
                }
            }

            // if weapon doesn't match any existing weapons, make new weapon
            if (weaponIndex == -1)
            {
                weapons.Add(weapon);
                weaponsEventInstances.Add(RuntimeManager.CreateInstance(moduleRef));
                weaponIndex = weapons.Count - 1;
                SetInstanceParametersByDict(weaponsEventInstances[weaponIndex], DefaultNoteInfo());
                weaponsEventInstances[weaponIndex].start();
            }

            SetInstanceParametersByDict(weaponsEventInstances[weaponIndex], noteInfo);
            weaponsEventInstances[weaponIndex].setParameterByName("adsr", 1);

            started = true;
            yield return new WaitForSeconds(noteInfo["length"]);
        }
        // Debug.Log(weaponIndex);
        weaponsEventInstances[weaponIndex].setParameterByName("adsr", 0);
    }

    Dictionary<string, float> DefaultNoteInfo()
    {
        return new Dictionary<string, float>
        {
            { "shipstate", 0 },
            //source params
            { "pitch", 440 },
            { "source", 2 },
            //AM params
            { "AM", 0 },
            { "AMsource", 1 },
            { "AMfreq", 1 },
            { "AMdepth", 1 },
            //FM params
            { "FM", 0 },
            { "FMsource", 1 },
            { "FMfreq", 1 },
            { "FMdepth", 100 },
            //AM2 params
            { "AM2", 0 },
            { "AM2source", 1 },
            { "AM2freq", 1 },
            { "AM2depth", 1 },
            //FM2 params
            { "FM2", 0 },
            { "FM2source", 1 },
            { "FM2freq", 1 },
            { "FM2depth", 100 },
            //AM on FM params 
            { "FMAM", 0 },
            { "FMAMsource", 1 },
            { "FMAMfreq", 1 },
            { "FMAMdepth", 1 },
            //FM on AM params
            { "AMFM", 0 },
            { "AMFMsource", 1 },
            { "AMFMfreq", 1 },
            { "AMFMdepth", 100 },
            //arp adsr params
            { "adsr", 0 },
            { "attack", attack * 1000},
            { "decay", decay * 1000 },
            { "sustain", 0 },
            { "release", release * 1000 },
            // length should be the sum of adsr params divided by 1000
            { "length", noteLength },
            //arp pitch params
            { "apitch1", 440 },
            { "apitch2", 554.37f },
            { "apitch3", 659.26f },
            { "apitch4", 880 }

        };
    }

    public void StartStorm()
    {
        sfx_stormInst = FMODUnity.RuntimeManager.CreateInstance(sfx_stormRef);
        sfx_stormInst.setParameterByName("storm", 1);
        sfx_stormInst.start();
    }

    public void StormStun()
    {
        sfx_stormInst.setParameterByName("storm", 1);
    }

    public void StopStorm()
    {
        sfx_stormInst.stop(0);
    }

    void SetInstanceParametersByDict(EventInstance inst, Dictionary<string, float> parameters)
    {
        foreach (var parameter in parameters)
        {
            inst.setParameterByName(parameter.Key, parameter.Value);
        }
        // inst.setParameterByName("pitch", parameters["pitch"]);
        // inst.setParameterByName("source", parameters["source"]);
        // //AM params
        // inst.setParameterByName("AM", parameters["AM"]);
        // inst.setParameterByName("AMsource", parameters["AMsource"]);
        // inst.setParameterByName("AMfreq", parameters["AMfreq"]);
        // inst.setParameterByName("AMdepth", parameters["AMdepth"]);
        // //FM params
        // inst.setParameterByName("FM", parameters["FM"]);
        // inst.setParameterByName("FMsource", parameters["FMsource"]);
        // inst.setParameterByName("FMfreq", parameters["FMfreq"]);
        // inst.setParameterByName("FMdepth", parameters["FMdepth"]);
        // //AM on AM params
        // inst.setParameterByName("AM2", parameters["AM2"]);
        // inst.setParameterByName("AM2source", parameters["AM2source"]);
        // inst.setParameterByName("AM2freq", parameters["AM2freq"]);
        // inst.setParameterByName("AM2depth", parameters["AM2depth"]);
        // //FM on FM params - broken rn, wasn't before
        // inst.setParameterByName("FM2", parameters["FM2"]);
        // inst.setParameterByName("FM2source", parameters["FM2source"]);
        // inst.setParameterByName("FM2freq", parameters["FM2freq"]);
        // inst.setParameterByName("FM2depth", parameters["FM2depth"]);
        // //AM on FM params - this doesn't work right now
        // inst.setParameterByName("FMAM", parameters["FMAM"]);
        // inst.setParameterByName("FMAMsource", parameters["FMAMsource"]);
        // inst.setParameterByName("FMAMfreq", parameters["FMAMfreq"]);
        // inst.setParameterByName("FMAMdepth", parameters["FMAMdepth"]);
        // //FM on AM params - this doesn't work right now
        // inst.setParameterByName("AMFM", parameters["AMFM"]);
        // inst.setParameterByName("AMFMsource", parameters["AMFMsource"]);
        // inst.setParameterByName("AMFMfreq", parameters["AMFMfreq"]);
        // inst.setParameterByName("AMFMdepth", parameters["AMFMdepth"]);
        //
        // //adsr params
        // inst.setParameterByName("adsr", parameters["adsr"]);
        // inst.setParameterByName("attack", parameters["attack"]); //attack in ms, 0-2000
        // inst.setParameterByName("decay", parameters["decay"]); //decay in ms, 0-2000
        // inst.setParameterByName("sustain", parameters["sustain"]); //sustain amount, 0-1
        // inst.setParameterByName("release", parameters["release"]); //release in ms, 0-2000
    }
}
