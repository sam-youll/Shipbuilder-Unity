using UnityEngine;
using FMOD;
using FMODUnity;
using FMOD.Studio;
using System.Collections;

public class ReactorSounds : MonoBehaviour
{
    private EventInstance enemyBass;
    private EventInstance playerBass;
    private EventInstance enemyPad;
    private EventInstance playerPad;
    private EventInstance enemyPerc;
    private EventInstance playerPerc;

    public EventReference enemyBassRef;
    public EventReference playerBassRef;
    public EventReference enemyPadRef;
    public EventReference playerPadRef;
    public EventReference enemyPercRef;
    public EventReference playerPercRef;


    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        enemyPerc = FMODUnity.RuntimeManager.CreateInstance(enemyPercRef);
        playerPerc = FMODUnity.RuntimeManager.CreateInstance(playerPercRef);

        enemyBass = FMODUnity.RuntimeManager.CreateInstance(enemyBassRef);
        playerBass = FMODUnity.RuntimeManager.CreateInstance(playerBassRef);

        SetTestParams();

        enemyPerc.start();
        playerPerc.start();
        enemyBass.start();
        playerBass.start();

        Conductor.Instance.onBeat.AddListener(PlayerPerc);
        Conductor.Instance.onBeat.AddListener(EnemyPerc);
        Conductor.Instance.onBeat.AddListener(PlayerBass);
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    void SetTestParams()
    {
        //These are placeholders to get generative shit working, we need to figure out how we're setting them in the reactor 

        playerPerc.setParameterByName("attack", 10);
        playerPerc.setParameterByName("decay", 60);
        playerPerc.setParameterByName("bpfreq", 5600);
        playerPerc.setParameterByName("reson", 80);

        enemyPerc.setParameterByName("attack", 10);
        enemyPerc.setParameterByName("decay", 60);
        enemyPerc.setParameterByName("bpfreq", 100);
        enemyPerc.setParameterByName("reson", 100);

        playerBass.setParameterByName("attack", 100);
        playerBass.setParameterByName("decay", 1550);
        playerBass.setParameterByName("release", 80);
        playerBass.setParameterByName("delaytime", 750);

        enemyBass.setParameterByName("attack", 150);
        enemyBass.setParameterByName("decay", 1120);
        enemyBass.setParameterByName("release", 60);
    }

    void PlayerPerc()
    {
        var shouldPlay = false;
        playerPerc.getParameterByName("bpfreq", out var bpfreq);

        if (bpfreq < 500)
        {
            if (Conductor.Instance.beat == 0 || Conductor.Instance.beat == 2)
            {
                shouldPlay = true;
            }
        }
        else if (bpfreq < 1000)
        {
            if (Conductor.Instance.beat == 1)
            {
                shouldPlay = true;
            }
        }
        else if (bpfreq > 1000)
        {
            if (Conductor.Instance.beat > 2)
            {
                shouldPlay = true;
            }
        }

        if (shouldPlay)
        {
            StartCoroutine(PlayNoteCoroutine(playerPerc, .07f));
        }
        
    }

    void EnemyPerc()
    {
        var shouldPlay = false;
        enemyPerc.getParameterByName("bpfreq", out var bpfreq);

        if (bpfreq < 500)
        {
            if (Conductor.Instance.beat == 0 || Conductor.Instance.beat == 2)
            {
                shouldPlay = true;
            }
        }
        else if (bpfreq < 1000)
        {
            if (Conductor.Instance.beat == 1)
            {
                shouldPlay = true;
            }
        } else if (bpfreq > 1000)
        {
            if (Conductor.Instance.beat > 2)
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
        var shouldPlay = false;
        var pitchDice = 0;
        var bassPitch = 440f;

        if (Conductor.Instance.beat == 0 || Conductor.Instance.beat == 2)
        {
            shouldPlay = true;
        }

        if (shouldPlay)
        {
            UnityEngine.Debug.Log("BassPlaying");
            pitchDice = Random.Range(0, 100);
            if (pitchDice<50)
            {
                bassPitch = (Notes.GetPitch(Notes.A, Notes.MODE.IONIAN, 0))/8;
                playerBass.setParameterByName("basspitch", bassPitch);

            } else
            {
                bassPitch = (Notes.GetPitch(Notes.A, Notes.MODE.IONIAN, 4))/8;
                playerBass.setParameterByName("basspitch", bassPitch);
            }

            StartCoroutine(PlayNoteCoroutine(playerBass, 1.73f));
        }
    }

    IEnumerator PlayNoteCoroutine(EventInstance instrument, float noteLength)
    {
        //need to feed in note length thru dictionary like in audiomanager 

        var started = false;

        if (!started)
        {
            // if weapon doesn't match any existing weapons, make new weapon
            instrument.setParameterByName("adsr", 1);

            started = true;
            yield return new WaitForSeconds(noteLength);
        }

        instrument.setParameterByName("adsr", 0);
    }
}
