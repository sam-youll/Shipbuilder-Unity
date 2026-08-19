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
            Destroy(gameObject);
        }
        else
        {
            Instance = this;
            DontDestroyOnLoad(this);
        }
    }

    //FMOD Event Instance
    private EventInstance moduleInst;
    private EventInstance amb_spaceInst;
    private EventInstance sfx_shipInst;
    private EventInstance enemySongInst;
    private EventInstance sfx_stormInst;
    private EventInstance sfx_explosionInst;


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
    public EventReference sfx_explosionRef;
    public EventReference sfx_win;
    public EventReference sfx_loss;
    public EventReference sfx_escape;
    public EventReference sfx_end;
    
    //ui
    [Header("UI References")]
    public EventReference ui_pickupRef;
    public EventReference ui_putdownRef;
    public EventReference ui_dialogueRef;
    public EventReference ui_chime;
    //enemy songs
    [Header("Enemy References")]
    public EventReference enemySongRef;
    public EventReference test_enemySong1Ref;
    public EventReference test_enemySong2Ref;
    public EventReference test_enemySong3Ref;
    
    
    
    public EventInstance[] patchInstances = new EventInstance[12];
    public EventInstance[] enemyPatchInstances = new EventInstance[12];
    public List<EventReference> enemySongs = new();
    public List<EventReference> enemySongsPlayed = new();

    public List<Weapon> weapons = new();
    private List<EventInstance> weaponsEventInstances = new();
    private List<Coroutine> weaponsCoroutines = new();
    

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
    
    private Dictionary<string, float> DefaultNoteInfo()
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
            { "apitch4", 880 },
            //harmonicizer params
            {"harmonics", 0}
        };
    }

    void Start()
    {
        EventBus.Instance.weaponFired.AddListener(OnWeaponFired);
        // moduleInst = FMODUnity.RuntimeManager.CreateInstance(moduleRef);
        
        amb_spaceInst = FMODUnity.RuntimeManager.CreateInstance(amb_spaceRef);
        sfx_shipInst = FMODUnity.RuntimeManager.CreateInstance(sfx_shipRef);


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
        // UnityEngine.Debug.Log("note length: " + noteLength + "attack: " + attack + "decay: " + decay + "release" + release);
        
        //sfx calls 
        EventBus.Instance.enemyDefeated.AddListener(PlayWinSound);
        EventBus.Instance.playerDefeated.AddListener(PlayLossSound);
        EventBus.Instance.playerEscaped.AddListener(PlayEscapeSound);
        EventBus.Instance.runComplete.AddListener(PlayEndSound);

    }

    private void Update()
    {
        // Debug.Log($"weaponsEventInstances.Count: {weaponsEventInstances.Count}\npatchInstances.Length: {patchInstances.Length}");
    }

    #region SetParams
    // TODO: SetParametersByDict and SetEnemyParam... should be combined into one method.
    // A target should be passed in as an argument and values set regardless of target type.
    public void SetParametersByDict(int instanceIndex, Dictionary<string, float> parameters)
    {
        if (instanceIndex >= patchInstances.Length)
        {
            Debug.Log("Parameter index is out of range of patchInstances.");
            // var newInst = FMODUnity.RuntimeManager.CreateInstance(moduleRef);
            // newInst.start();
            // patchInstances.Add(newInst);
        }

        foreach (var pair in parameters)
        {
            patchInstances[instanceIndex].setParameterByName(pair.Key, pair.Value);
            Debug.Log("parameter: " + pair.Key + " value: " + pair.Value);
        }
        
        
        
        if (!IsPlaying(patchInstances[instanceIndex]))
        {
            patchInstances[instanceIndex].start();
        }
    }

    #endregion
    
    private void OnWeaponFired(Weapon weapon)
    {
        // Debug.Log("playing note");
        StartCoroutine(PlayNoteCoroutine(weapon, weapon.MusicParams()));
    }

    private IEnumerator PlayNoteCoroutine(Weapon weapon, Dictionary<string, float> noteInfo)
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
                Debug.Log("Added new weapon instance in audio manager");
                weapons.Add(weapon);
                weaponsEventInstances.Add(RuntimeManager.CreateInstance(moduleRef));
                weaponIndex = weapons.Count - 1;
                SetInstanceParametersByDict(weaponsEventInstances[weaponIndex], DefaultNoteInfo());
                weaponsEventInstances[weaponIndex].start();
            }

            SetInstanceParametersByDict(weaponsEventInstances[weaponIndex], noteInfo);
            weaponsEventInstances[weaponIndex].setParameterByName("adsr", 1);
            
            Debug.Log("current weapon index is " + weaponIndex);
            
            started = true;
            yield return new WaitForSeconds(noteInfo["length"]);
        }
        // Debug.Log(weaponIndex);
        weaponsEventInstances[weaponIndex].setParameterByName("adsr", 0);
    }

    public void StartStorm()
    {
        sfx_stormInst = FMODUnity.RuntimeManager.CreateInstance(sfx_stormRef);
        //sfx_stormInst.setParameterByName("storm", 0);
        sfx_stormInst.start();
    }

    public void StormStun()
    {
        //sfx_stormInst.setParameterByName("storm", 1);
    }

    public void StopStorm()
    {
        sfx_stormInst.stop(0);
    }

    void SetInstanceParametersByDict(EventInstance inst, Dictionary<string, float> parameters)
    {
        // Debug.Log("=== NEW NOTE ===");
        foreach (var parameter in parameters)
        {
            // Debug.Log($"{parameter.Key} = {parameter.Value}");
            inst.setParameterByName(parameter.Key, parameter.Value);
        }
        
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

    #region Soundboard
    public void PlayDialogueSound()
    {
        FMODUnity.RuntimeManager.PlayOneShot(ui_dialogueRef);
    }

    public void PlayPaperSound()
    {
        FMODUnity.RuntimeManager.PlayOneShot(sfx_paperRef);
    }
    
    public void PickUpModuleSFX()
    {
        FMODUnity.RuntimeManager.PlayOneShot(ui_pickupRef);
    }

    public void PutDownModuleSFX()
    {
        FMODUnity.RuntimeManager.PlayOneShot(ui_putdownRef);
    }
    
    public void PlayExplosionSFX()
    {
        FMODUnity.RuntimeManager.PlayOneShot(sfx_explosionRef);
    }

    public void PlayChime()
    {
        FMODUnity.RuntimeManager.PlayOneShot(ui_chime);
    }

    public void PlayWinSound()
    {
        FMODUnity.RuntimeManager.PlayOneShot(sfx_win);
        Debug.Log("playing win sound");
    }

    public void PlayLossSound()
    {
        FMODUnity.RuntimeManager.PlayOneShot(sfx_loss);
        Debug.Log("playing loss sound");
    }

    public void PlayEscapeSound()
    {
        FMODUnity.RuntimeManager.PlayOneShot(sfx_escape);
        Debug.Log("playing escape sound");
    }

    public void PlayEndSound()
    {
        FMODUnity.RuntimeManager.PlayOneShot(sfx_end);
    }
    
    #endregion
    
    bool IsPlaying(FMOD.Studio.EventInstance instance) {
        FMOD.Studio.PLAYBACK_STATE state;   
        instance.getPlaybackState(out state);
        return state != FMOD.Studio.PLAYBACK_STATE.STOPPED;
    }
}
