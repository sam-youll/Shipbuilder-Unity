using UnityEngine;
using FMOD;
using FMODUnity;
using FMOD.Studio;
using System.Collections;
using System.Collections.Generic;

public class ReactorSounds : MonoBehaviour
{
    public static ReactorSounds Instance;

    void Awake()
    {
        Instance = this;
    }
    
    //FMOD Event Instance variables
    private EventInstance enemyBass;
    private EventInstance playerBass;
    private EventInstance enemyPerc;
    private EventInstance playerPerc;

    //pads
    public List<EventInstance> playerPads = new List<EventInstance>();
    public List<EventInstance> enemyPads = new List<EventInstance>();

    //NOTE: these are commented out for now bc we don't actually have anything in to add extra instruments here -- 
    //they're here for if/when we do 
    //---------------------------------
    //perc
    //public List<EventInstance> playerPerc = new List<EventInstance>();
    //public List<EventInstance> enemyPads = new List<EventInstance>();

    [Header("FMOD Events")]
    public EventReference enemyBassRef;
    public EventReference playerBassRef;
    public EventReference enemyPadRef;
    public EventReference playerPadRef;
    public EventReference enemyPercRef;
    public EventReference playerPercRef;

    //currentChord variable is the position in the changes list. 
    public int currentChord;

    //THIS is a placeholder list. It's just a I IV II- V I progression. We will move this logic into the map and nav system when we get there.
    public List<int> changes = new List<int>()
    {
        0,
        3,
        1,
        6
    };

    //list of chord strings to plop in play note from chord function 
    public List<string> chords = new List<string>()
    {
        "I",
        "II",
        "III",
        "IV",
        "V",
        "VI",
        "VII"
    };

    //reactor variables
    public int bassSyncProb;
    public float bassDelayTime;
    public float padDelayTime;
    public int percSyncProb;
    public float percFreq;
    public float strength;
    public float enemyStrength;

    public float baseNoteLength;
    public float enemyBaseNoteLength;

    //reactor params, more hidden
    public float playerBassAttackRatio = .3f;
    public float playerBassDecayRatio = 0.4f;
    public float playerBassReleaseRatio = .3f;
    public float enemyBassAttackRatio = .3f;
    public float enemyBassDecayRatio = 0.4f;
    public float enemyBassReleaseRatio = .3f;
    public float playerPercAttackRatio = .2f;
    public float playerPercDecayRatio = .8f;
    public float playerGrit;
    public float playerSoft;
    public float enemyGrit;
    public float enemySoft;
    public float playerFB;
    public float playerFF;
    public float enemyFF;
    public float enemyFB;


    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        //Makin all the event instances
        enemyPerc = FMODUnity.RuntimeManager.CreateInstance(enemyPercRef);
        playerPerc = FMODUnity.RuntimeManager.CreateInstance(playerPercRef);

        enemyBass = FMODUnity.RuntimeManager.CreateInstance(enemyBassRef);
        playerBass = FMODUnity.RuntimeManager.CreateInstance(playerBassRef);

        

        //setting the placeholder parameters that will just work for now
        SetTestParams();
        //setting params based on reactor variables
        SetReactorParams();

        //starting the FMOD events
        playerPerc.start();
        playerBass.start();
        

        //Subscribing all the instruments so they're quantized
        Conductor.Instance.onSixteenth.AddListener(PlayerPerc);
        Conductor.Instance.onSixteenth.AddListener(EnemyPerc);
        Conductor.Instance.onEighth.AddListener(PlayerBass);
        Conductor.Instance.onEighth.AddListener(EnemyBass);
        Conductor.Instance.onBar.AddListener(UpdateChord);
        Conductor.Instance.onHalf.AddListener(PlayerPad);
        Conductor.Instance.onHalf.AddListener(EnemyPad);

        //idk setting current chord to 0 
        currentChord = changes[0];


    }

    // Update is called once per frame
    void Update()
    {
        strength = Reactor.Instance.strength;
    }

    void SetTestChanges()
    {
        //adding stuff to the list here bc when it was in the variable it was contributing to the weird list errors
        changes.Add(0);
        changes.Add(3);
        changes.Add(1);
        changes.Add(6);
    }

    void UpdateChord()
    {
        //this function updates the current chord every bar 
        if (Conductor.Instance.quarter == 0)
        {
           if (currentChord >= changes.Count)
            {
                //SHOULD reset it to 0... this shit is broken tho it doesnt change the number of currentChord at all. the values work fine tho
                currentChord = changes[0];
            }
            else
            {
                //add
                currentChord++;
            }
           //THIS NEEDS TO BE FIXED OH MY GOD i'm just making the list longer every bar this is not ok lmfao 
           SetTestChanges();

            UnityEngine.Debug.Log("chord: " + changes[currentChord]);
            UnityEngine.Debug.Log("currentChord: " + currentChord);
        }
    }

    void SetTestParams()
    {
        for (int i = 0; i < playerPads.Count; i++)
        {
            playerPads[i].setParameterByName("bpfreq", 500);
        }

        for (int i = 0; i < enemyPads.Count; i++) 
        {
            enemyPads[i].setParameterByName("bpfreq", 200);
        }
    }

    public void SetReactorParams()
    {

        playerBass.setParameterByName("delaytime", bassDelayTime);

        for (int i = 0;i < playerPads.Count; i++)
        {
            playerPads[i].setParameterByName("delaytime", padDelayTime);
        }
        

        playerPerc.setParameterByName("bpfreq", percFreq);

        if (strength <= 1)
        {
            baseNoteLength = 60 / Conductor.Instance.tempo;
            playerGrit = Random.Range(0, 20);
            playerSoft = 80 - playerGrit;

            playerPerc.setParameterByName("reson", Random.Range(0, 10));

            for (int i = 0; i < playerPads.Count; i++)
            {
                playerPads[i].setParameterByName("grit", playerGrit);
                playerPads[i].setParameterByName("soft", playerSoft);
                //playerPads[i].setParameterByName("reson", 0);
                playerPads[i].setParameterByName("fbgain", Random.Range(.4f, .5f));
                playerPads[i].setParameterByName("ffgain", Random.Range(0f, .1f));
            }
            
        } else if (strength <= 2)
        {
            baseNoteLength = (60 / Conductor.Instance.tempo) * .8f;
            playerGrit = Random.Range(20, 40);
            playerSoft = 80 - playerGrit;

            playerPerc.setParameterByName("reson", Random.Range(10, 20));
            for (int i = 0; i < playerPads.Count; i++)
            {
                playerPads[i].setParameterByName("grit", playerGrit);
                playerPads[i].setParameterByName("soft", playerSoft);
                //playerPads[i].setParameterByName("reson", Random.Range(0, 1));
                playerPads[i].setParameterByName("fbgain", Random.Range(.3f, .4f));
                playerPads[i].setParameterByName("ffgain", Random.Range(.2f, .3f));
            }  
        }
        else if (strength <= 3)
        {
            baseNoteLength = (60 / Conductor.Instance.tempo) * .65f;
            playerGrit = Random.Range(40, 60);
            playerSoft = 80 - playerGrit;

            playerPerc.setParameterByName("reson", Random.Range(20, 30));

            for (int i = 0; i < playerPads.Count; i++)
            {
                playerPads[i].setParameterByName("grit", playerGrit);
                playerPads[i].setParameterByName("soft", playerSoft);
                //playerPads[i].setParameterByName("reson", Random.Range(2, 3));
                playerPads[i].setParameterByName("fbgain", Random.Range(.2f, .3f));
                playerPads[i].setParameterByName("ffgain", Random.Range(.3f, .4f));
            }
            
        } else
        {
            baseNoteLength = (60 / Conductor.Instance.tempo) * .5f;
            playerGrit = Random.Range(60, 79);
            playerSoft = 80 - playerGrit;

            playerPerc.setParameterByName("reson", Random.Range(40, 50));

            for (int i = 0; i < playerPads.Count; i++)
            {
                playerPads[i].setParameterByName("grit", playerGrit);
                playerPads[i].setParameterByName("soft", playerSoft);
                //playerPads[i].setParameterByName("reson", Random.Range(4, 5));
                playerPads[i].setParameterByName("fbgain", Random.Range(0f, .2f));
                playerPads[i].setParameterByName("ffgain", Random.Range(.4f, .5f));
            }  
        }

        //ENEMIES 
        if (strength <= 1)
        {
            enemyBaseNoteLength = 60 / Conductor.Instance.tempo;
            enemyGrit = Random.Range(0, 20);
            enemySoft = 80 - playerGrit;

            enemyPerc.setParameterByName("reson", Random.Range(0, 50));

            for (int i = 0; i < enemyPads.Count; i++)
            {
                enemyPads[i].setParameterByName("grit", enemyGrit);
                enemyPads[i].setParameterByName("soft", enemySoft);
                //enemyPad.setParameterByName("reson", 0);
                enemyPads[i].setParameterByName("fbgain", Random.Range(.4f, .5f));
                enemyPads[i].setParameterByName("ffgain", Random.Range(0f, .1f));
            }
            
        }
        else if (strength <= 2)
        {
            enemyBaseNoteLength = (60 / Conductor.Instance.tempo) * .8f;
            enemyGrit = Random.Range(20, 40);
            enemySoft = 80 - enemyGrit;

            enemyPerc.setParameterByName("reson", Random.Range(30, 80));

            for (int i = 0; i < enemyPads.Count; i++)
            {
                enemyPads[i].setParameterByName("grit", enemyGrit);
                enemyPads[i].setParameterByName("soft", enemySoft);
                //enemyPads[i].setParameterByName("reson", Random.Range(0, 1));
                enemyPads[i].setParameterByName("fbgain", Random.Range(.3f, .4f));
                enemyPads[i].setParameterByName("ffgain", Random.Range(.2f, .3f));
            }
            
        }
        else if (strength <= 3)
        {
            enemyBaseNoteLength = (60 / Conductor.Instance.tempo) * .65f;
            enemyGrit = Random.Range(40, 60);
            enemySoft = 80 - enemyGrit;

            enemyPerc.setParameterByName("reson", Random.Range(80, 90));

            for (int i = 0;i < enemyPads.Count; i++)
            {
                enemyPads[i].setParameterByName("grit", enemyGrit);
                enemyPads[i].setParameterByName("soft", enemySoft);
                //enemyPad.setParameterByName("reson", Random.Range(2, 3));
                enemyPads[i].setParameterByName("fbgain", Random.Range(.2f, .3f));
                enemyPads[i].setParameterByName("ffgain", Random.Range(.3f, .4f));
            }
            
        }
        else
        {
            enemyBaseNoteLength = (60 / Conductor.Instance.tempo) * .5f;
            enemyGrit = Random.Range(60, 79);
            enemySoft = 80 - enemyGrit;

            enemyPerc.setParameterByName("reson", Random.Range(90, 100));
            for (int i = 0; i < enemyPads.Count; i++)
            {
                enemyPads[i].setParameterByName("grit", enemyGrit);
                enemyPads[i].setParameterByName("soft", enemySoft);
                //enemyPads.setParameterByName("reson", Random.Range(4, 5));
                enemyPads[i].setParameterByName("fbgain", Random.Range(0f, .2f));
                enemyPads[i].setParameterByName("ffgain", Random.Range(.4f, .5f));
            }
            
        }

        //option for changing perc reson based on pitch rather than strength, tucking this away just in case
        /*if (percFreq < 500)
        {
            playerPerc.setParameterByName("reson", Random.Range(80, 100));
        } else if (percFreq < 1000)
        {
            playerPerc.setParameterByName("reson", Random.Range(30, 80));
        } else
        {
            playerPerc.setParameterByName("reson", Random.Range(0, 50));
        }*/

    }

    void PlayerPerc()
    {
        //shouldPlay is telling it whether it's cool to trigger adsr on the dam beat 
        var shouldPlay = false;
        var syncDice = Random.Range(0, 100);
        var notelength = baseNoteLength;

        float percAttack = notelength * playerPercAttackRatio;
        float percDecay = notelength * playerPercDecayRatio;

        playerPerc.setParameterByName("attack", percAttack * 1000);
        playerPerc.setParameterByName("decay", percDecay * 1000);  

        if (percFreq < 500)
        {
            //if this shit sounds like a kick drum, play it on 1 and 3
            if (syncDice < percSyncProb)
            {
                if (Conductor.Instance.sixteenth == 6 || Conductor.Instance.sixteenth == 14)
                {
                    shouldPlay = true;
                }
            }
            if (syncDice > percSyncProb)
            {
                if (Conductor.Instance.sixteenth == 0 || Conductor.Instance.sixteenth == 8)
                {
                    shouldPlay = true;
                }
            }
        }
        else if (percFreq < 1000)
        {
            //if this shit sounds like a snare or tom, play it on 2 or 4 
            if (Conductor.Instance.sixteenth == 4 || Conductor.Instance.sixteenth == 12)
            {
                shouldPlay = true;
            }
        }
        else if (percFreq > 1000)
        {
            //if this shit sounds like a hi hat, play it on 3 and 4. truly all this is placeholder logic, we should get funkier w it 
            if (syncDice < percSyncProb)
            {
                if (Conductor.Instance.sixteenth % 2 != 0)
                {
                    shouldPlay = true;
                } 
            }
            if (syncDice > percSyncProb)
            {
                if(Conductor.Instance.sixteenth % 2 == 0)
                {
                    shouldPlay = true;
                }
            }
        }

        //pretty much copied from the weapon firing, should put a variable in the length field that's the combined ADSR params later
        if (shouldPlay)
        {
            StartCoroutine(PlayNoteCoroutine(playerPerc, notelength));
        }
        
    }

    void EnemyPerc()
    {
        //See PlayerPerc
        var shouldPlay = false;
        enemyPerc.getParameterByName("bpfreq", out var bpfreq);
        var syncDice = Random.Range(0, 100);
        var notelength = enemyBaseNoteLength;

        //TODO: should give enemy their own ratio at somepoint but rn dont have time for all that, just copy/paste lol
        float percAttack = notelength * playerPercAttackRatio;
        float percDecay = notelength * playerPercDecayRatio;

        enemyPerc.setParameterByName("attack", percAttack * 1000);
        enemyPerc.setParameterByName("decay", percDecay * 1000);

        if (bpfreq < 500)
        {
            //if this shit sounds like a kick drum, play it on 1 and 3
            if (syncDice < percSyncProb)
            {
                if (Conductor.Instance.sixteenth == 6 || Conductor.Instance.sixteenth == 14)
                {
                    shouldPlay = true;
                }
            }
            if (syncDice > percSyncProb)
            {
                if (Conductor.Instance.sixteenth == 0 || Conductor.Instance.sixteenth == 8)
                {
                    shouldPlay = true;
                }
            }
        }
        else if (bpfreq < 1000)
        {
            //if this shit sounds like a snare or tom, play it on 2 or 4 
            if (Conductor.Instance.sixteenth == 4 || Conductor.Instance.sixteenth == 12)
            {
                shouldPlay = true;
            }
        }
        else if (bpfreq > 1000)
        {
            //if this shit sounds like a hi hat, play it on 3 and 4. truly all this is placeholder logic, we should get funkier w it 
            if (syncDice < percSyncProb)
            {
                if (Conductor.Instance.sixteenth % 2 != 0)
                {
                    shouldPlay = true;
                }
            }
            if (syncDice > percSyncProb)
            {
                if (Conductor.Instance.sixteenth % 2 == 0)
                {
                    shouldPlay = true;
                }
            }
        }

        if (shouldPlay)
        {
            StartCoroutine(PlayNoteCoroutine(enemyPerc, .07f));
        }
    }

    void PlayerBass()
    {
        //whether it should play
        var shouldPlay = false;
        //var pitchDice = 0;
        var bassPitch = 440f;

        var syncDice = Random.Range(0, 100);

        var notelength = baseNoteLength;
        

        if (syncDice > bassSyncProb)
        {
            //should play on 1 and 3
            if (Conductor.Instance.quarter == 0 || Conductor.Instance.quarter == 2)
            {
                shouldPlay = true;

                notelength = baseNoteLength * 4;
                float playerBassAttack = notelength * playerBassAttackRatio;
                float playerBassDecay = notelength * playerBassDecayRatio;
                float playerBassRelease = notelength * playerBassReleaseRatio;

                playerBass.setParameterByName("attack", playerBassAttack * 1000);
                playerBass.setParameterByName("decay", playerBassDecay * 1000);
                playerBass.setParameterByName("release", playerBassRelease * 1000);
            }

        }

        if (syncDice < bassSyncProb)
        {
            if (Conductor.Instance.quarter == 0 || Conductor.Instance.eighth == 3 || Conductor.Instance.eighth == 5 || Conductor.Instance.eighth == 7)
            {
                shouldPlay = true;

                notelength = baseNoteLength * 2;
                float playerBassAttack = notelength * playerBassAttackRatio;
                float playerBassDecay = notelength * playerBassDecayRatio;
                float playerBassRelease = notelength * playerBassReleaseRatio;

                playerBass.setParameterByName("attack", playerBassAttack * 1000);
                playerBass.setParameterByName("decay", playerBassDecay * 1000);
                playerBass.setParameterByName("release", playerBassRelease * 1000);
            }

        }

        if (shouldPlay)
        {

            //if it should play, get the pitch of the root of the current chord, drop it 2 octaves
            bassPitch = (Notes.GetPitch(Notes.A, Notes.MODE.IONIAN, (changes[currentChord])))/4;
            //sets the pitch
            playerBass.setParameterByName("basspitch", bassPitch);
            //plays the note
            StartCoroutine(PlayBassCoroutine(playerBass, notelength));
        }
    }

    void EnemyBass()
    {
        var shouldPlay = false;
        //var pitchDice = 0;
        var bassPitch = 440f;

        var notelength = enemyBaseNoteLength * 4;
        float enemyBassAttack = notelength * enemyBassAttackRatio;
        float enemyBassDecay = notelength * enemyBassDecayRatio;
        float enemyBassRelease = notelength * enemyBassReleaseRatio;

        enemyBass.setParameterByName("attack", enemyBassAttack * 1000);
        enemyBass.setParameterByName("decay", enemyBassDecay * 1000);
        enemyBass.setParameterByName("release", enemyBassRelease * 1000);

        //should play on 1 and 3
        if (Conductor.Instance.quarter == 0 || Conductor.Instance.quarter == 2)
            {
               shouldPlay = true;
            }

        if (shouldPlay)
        {
            //same as before but drops it a couple more octaves
            bassPitch = (Notes.GetPitch(Notes.A, Notes.MODE.IONIAN, changes[currentChord])) / 8;
            playerBass.setParameterByName("basspitch", bassPitch);
            StartCoroutine(PlayBassCoroutine(playerBass, notelength));

        }
    }

    void PlayerPad()
    {
        //every bar change pitch
        if (Conductor.Instance.quarter == 0 || Conductor.Instance.quarter == 2)
        {
            //gets the current chord value from the changes list
            var chord = changes[currentChord];
            //sets it to a string according to the list of chords
            string chordstring = chords[chord];
            if (playerPads.Count > 0)
            {
                //picks a random note from the current chord
                for (int i = 0; i < playerPads.Count; i++)
                {
                    var pitch = Notes.RandomNoteInChord(Notes.A, Notes.MODE.IONIAN, Notes.SCALE_CHORD[chordstring]) * 2;
                    playerPads[i].setParameterByName("pitch", pitch);
                    UnityEngine.Debug.Log("pad: " + playerPads[i] + " pitch: " + pitch);
                }
            }
        }
    }

    void EnemyPad()
    {
        if (Conductor.Instance.quarter == 0 || Conductor.Instance.quarter == 2)
        {
            var chord = changes[currentChord];
            string chordstring = chords[chord];

            for (int i = 0; i < enemyPads.Count; i++)
            {
                //picks a random note from the current chord
                var padPitch = Notes.RandomNoteInChord(Notes.A, Notes.MODE.IONIAN, Notes.SCALE_CHORD[chordstring]) * 2;
                //sets the pitch
                enemyPads[i].setParameterByName("pitch", padPitch);
            }
        }
    }

    //p much copied over from the weapons firing in audiomanager
    IEnumerator PlayNoteCoroutine(EventInstance instrument, float noteLength)
    {
        //need to feed in note length thru dictionary like in audiomanager 

        var started = false;

        if (!started)
        {
            instrument.setParameterByName("adsr", 1);

            started = true;
            yield return new WaitForSeconds(noteLength);
        }

        instrument.setParameterByName("adsr", 0);
    }

    IEnumerator PlayBassCoroutine(EventInstance instrument, float noteLength)
    {
        var started = false;

        if (!started)
        {
            instrument.setParameterByName("adsr", 1);

            started = true;
            yield return new WaitForSeconds(noteLength + (baseNoteLength * 4));
        }

        instrument.setParameterByName("adsr", 0);
    }

    public void StartEnemyReactor()
    {
        enemyPerc.start();
        enemyBass.start();
        for (int i = 0; enemyPads.Count > 0; i++)
        {
            enemyPads[i].start();
        }
    }

    public void StopEnemyReactor()
    {
        enemyPerc.stop(0);
        enemyBass.stop(0);
        for (int i = 0; enemyPads.Count > 0; i++)
        {
            enemyPads[i].stop(0);
        }
    }

    public void AddPlayerPad()
    {

        EventInstance addedPad = FMODUnity.RuntimeManager.CreateInstance(playerPadRef);

        playerPads.Add(addedPad);

        addedPad.setParameterByName("grit", playerGrit);
        addedPad.setParameterByName("soft", playerSoft);
        addedPad.setParameterByName("reson", 0);
        addedPad.setParameterByName("fbgain", Random.Range(.4f, .5f));
        addedPad.setParameterByName("ffgain", Random.Range(0f, .1f));
        addedPad.setParameterByName("delaytime", padDelayTime);

        addedPad.start();
        

        UnityEngine.Debug.Log("added player pad: " + addedPad);
        
    }

    public void RemovePlayerPad(EventInstance removedPad)
    {
        removedPad.stop(0);
    }

    public void AddEnemyPad()
    {

        EventInstance addedPad = FMODUnity.RuntimeManager.CreateInstance(enemyPadRef);

        enemyPads.Add(addedPad);

        addedPad.setParameterByName("grit", enemyGrit);
        addedPad.setParameterByName("soft", enemySoft);
        addedPad.setParameterByName("reson", 0);
        addedPad.setParameterByName("fbgain", Random.Range(.4f, .5f));
        addedPad.setParameterByName("ffgain", Random.Range(0f, .1f));
        addedPad.setParameterByName("delaytime", padDelayTime);

        addedPad.start();


        UnityEngine.Debug.Log("added enemy pad: " + addedPad);
    }

    public void RemoveEnemyPad(EventInstance removedPad)
    {
        removedPad.stop(0);
    }

    public void RemoveAllPads(List<EventInstance> pads)
    {
        for (int i = 0; i < pads.Count; i++)
        {
            pads[i].stop(0);
        }
    }
}
