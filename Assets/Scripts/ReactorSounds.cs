using UnityEngine;
using FMOD;
using FMODUnity;
using FMOD.Studio;
using System.Collections;
using System.Collections.Generic;

public class ReactorSounds : MonoBehaviour
{
    //FMOD Event Instance variables
    private EventInstance enemyBass;
    private EventInstance playerBass;
    private EventInstance enemyPad;
    private EventInstance playerPad;
    private EventInstance enemyPerc;
    private EventInstance playerPerc;
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

    public int bassSyncProb;


    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        //Makin all the event instances
        enemyPerc = FMODUnity.RuntimeManager.CreateInstance(enemyPercRef);
        playerPerc = FMODUnity.RuntimeManager.CreateInstance(playerPercRef);

        enemyBass = FMODUnity.RuntimeManager.CreateInstance(enemyBassRef);
        playerBass = FMODUnity.RuntimeManager.CreateInstance(playerBassRef);

        enemyPad = FMODUnity.RuntimeManager.CreateInstance(enemyPadRef);
        playerPad = FMODUnity.RuntimeManager.CreateInstance(playerPadRef); 

        //setting the placeholder parameters that will just work for now
        SetTestParams();

        //starting the FMOD events
        enemyPerc.start();
        playerPerc.start();
        enemyBass.start();
        playerBass.start();
        enemyPad.start();
        playerPad.start();

        //Subscribing all the instruments so they're quantized
        Conductor.Instance.onSixteenth.AddListener(PlayerPerc);
        Conductor.Instance.onEighth.AddListener(EnemyPerc);
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
        //These are placeholders to get generative shit working, we need to figure out how we're setting them in the reactor 

        //PERC
        //standard adsr stuff
        playerPerc.setParameterByName("attack", 10);
        playerPerc.setParameterByName("decay", 60);
        //bpfreq determines what band of frequencies the filter is passing over - more or less how high/low it is
        playerPerc.setParameterByName("bpfreq", 5600);
        //reson is how resonant the bp freq is -- how much does it sound like noise vs a pitch
        playerPerc.setParameterByName("reson", 80);

        enemyPerc.setParameterByName("attack", 10);
        enemyPerc.setParameterByName("decay", 60);
        enemyPerc.setParameterByName("bpfreq", 100);
        enemyPerc.setParameterByName("reson", 100);

        //BASS
        //standard adsr stuff 
        playerBass.setParameterByName("attack", 100);
        playerBass.setParameterByName("decay", 1550);
        playerBass.setParameterByName("release", 80);
        //the time on the delay, it's for babies
        playerBass.setParameterByName("delaytime", 750);

        enemyBass.setParameterByName("attack", 150);
        enemyBass.setParameterByName("decay", 1120);
        enemyBass.setParameterByName("release", 60);

        //PADS
        //Feedback gain - how loud the feedback noise is... these params are probably better to play with IN FMOD to get an idea.
        playerPad.setParameterByName("fbgain", 0.48f);
        //Feedforward gain
        playerPad.setParameterByName("ffgain", 0.33f);
        //Delay time - literal delay, the longer it is the more cool and alien it sounds, but leads to clustery pitch stuff 
        playerPad.setParameterByName("delaytime", 650);
        //im gonna keep it real w u i dont fuckin remember 
        playerPad.setParameterByName("cgain", 0.47f);
        //frequency of the bandpass filter, if u make it lower than the current pitch it's gonna be quiet af but that might be good
        playerPad.setParameterByName("bpfreq", 11200);
        //resonance of the bandpass filter, honestly if it's higher it's mostly gonna be louder
        playerPad.setParameterByName("reson", 36);
        //grit is how much of the Gritty source ur getting . vibes based param im sorry to say
        playerPad.setParameterByName("grit", 99);
        //soft is how much of the Soft source ur getting, same as above. just mixing stuff 
        playerPad.setParameterByName("soft", 78);

        enemyPad.setParameterByName("fbgain", 0.58f);
        enemyPad.setParameterByName("ffgain", 0.41f);
        enemyPad.setParameterByName("delaytime", 400);
        enemyPad.setParameterByName("cgain", 0.51f);
        enemyPad.setParameterByName("bpfreq", 8200);
        enemyPad.setParameterByName("reson", 41);
        enemyPad.setParameterByName("grit", 0);
        enemyPad.setParameterByName("soft", 106);
    }

    void PlayerPerc()
    {
        //shouldPlay is telling it whether it's cool to trigger adsr on the dam beat 
        var shouldPlay = false;
        playerPerc.getParameterByName("bpfreq", out var bpfreq);

        if (bpfreq < 500)
        {
            //if this shit sounds like a kick drum, play it on 1 and 3
            if (Conductor.Instance.quarter == 0 || Conductor.Instance.quarter == 2)
            {
                shouldPlay = true;
            }
        }
        else if (bpfreq < 1000)
        {
            //if this shit sounds like a snare or tom, play it on 2. idk why. 
            if (Conductor.Instance.quarter == 1)
            {
                shouldPlay = true;
            }
        }
        else if (bpfreq > 1000)
        {
            //if this shit sounds like a hi hat, play it on 3 and 4. truly all this is placeholder logic, we should get funkier w it 
            if (Conductor.Instance.quarter > 2)
            {
                shouldPlay = true;
            }
        }

        //pretty much copied from the weapon firing, should put a variable in the length field that's the combined ADSR params later
        if (shouldPlay)
        {
            StartCoroutine(PlayNoteCoroutine(playerPerc, .07f));
        }
        
    }

    void EnemyPerc()
    {
        //See PlayerPerc
        var shouldPlay = false;
        enemyPerc.getParameterByName("bpfreq", out var bpfreq);

        if (bpfreq < 500)
        {
            if (Conductor.Instance.quarter == 0 || Conductor.Instance.quarter == 2)
            {
                shouldPlay = true;
            }
        }
        else if (bpfreq < 1000)
        {
            if (Conductor.Instance.quarter == 1)
            {
                shouldPlay = true;
            }
        } else if (bpfreq > 1000)
        {
            if (Conductor.Instance.quarter > 2)
            {
                shouldPlay = true;
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
        
        var syncDice = 0;

        syncDice = Random.Range(0, 100);

        if (syncDice > bassSyncProb)
        {
            //should play on 1 and 3
            if (Conductor.Instance.quarter == 0 || Conductor.Instance.quarter == 2)
            {
                shouldPlay = true;
            }

            
        }

        if (syncDice < bassSyncProb)
        {
            if (Conductor.Instance.quarter == 0 || Conductor.Instance.eighth == 3 || Conductor.Instance.eighth == 5 || Conductor.Instance.eighth == 7)
            {
                shouldPlay = true;
            }
        }

        if (shouldPlay)
        {
            //if it should play, get the pitch of the root of the current chord, drop it 2 octaves
            bassPitch = (Notes.GetPitch(Notes.A, Notes.MODE.IONIAN, (changes[currentChord])))/4;
            //sets the pitch
            playerBass.setParameterByName("basspitch", bassPitch);
            //plays the note
            StartCoroutine(PlayNoteCoroutine(playerBass, 1.73f));

           
        }
    }

    void EnemyBass()
    {
        var shouldPlay = false;
        //var pitchDice = 0;
        var bassPitch = 440f;

        var syncDice = 0;

        syncDice = Random.Range(0, 100);

        if (syncDice > bassSyncProb)
        {
            //should play on 1 and 3
            if (Conductor.Instance.quarter == 0 || Conductor.Instance.quarter == 2)
            {
                shouldPlay = true;
            }
        }

        if (syncDice < bassSyncProb)
        {
            if (Conductor.Instance.quarter == 0 || Conductor.Instance.eighth == 3 || Conductor.Instance.eighth == 5 || Conductor.Instance.eighth == 7)
            {
                shouldPlay = true;
            }
        }

        if (shouldPlay)
        {
            //same as before but drops it a couple more octaves
            bassPitch = (Notes.GetPitch(Notes.A, Notes.MODE.IONIAN, changes[currentChord])) / 8;
            playerBass.setParameterByName("basspitch", bassPitch);
            StartCoroutine(PlayNoteCoroutine(playerBass, 1.73f));
        }
    }

    void PlayerPad()
    {
        //every bar change pitch
        if (Conductor.Instance.quarter == 0)
        {
            //gets the current chord value from the changes list
            var chord = changes[currentChord];
            //sets it to a string according to the list of chords
            string chordstring = chords[chord];

            //picks a random note from the current chord
            var padPitch = (Notes.RandomNoteInChord(Notes.A, Notes.MODE.IONIAN, Notes.SCALE_CHORD[chordstring])) * 2;

            //sets the pitch
            playerPad.setParameterByName("pitch", padPitch);

            float paramValue = 0f;
            playerPad.getParameterByName("pitch", out paramValue);
            UnityEngine.Debug.Log(paramValue);
        }
    }

    void EnemyPad()
    {
        if (Conductor.Instance.quarter == 0)
        {
            var chord = changes[currentChord];
            string chordstring = chords[chord];

            var padPitch = (Notes.RandomNoteInChord(Notes.A, Notes.MODE.IONIAN, Notes.SCALE_CHORD[chordstring])) * 2;

            enemyPad.setParameterByName("pitch", padPitch);
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
}
