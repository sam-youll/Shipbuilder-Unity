using UnityEngine;
using FMOD;
using FMODUnity;
using FMOD.Studio;
using System.Collections;
using System.Collections.Generic;
using UnityEngine.Serialization;
using Debug = UnityEngine.Debug;

public class ReactorSounds : MonoBehaviour
{
    public static ReactorSounds Instance;
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
    private EventInstance reactor;
    
    public EventReference reactorRef;

    //params 
    private float pitch;
    private float power;
    private float conversion;
    private float constellation;

    private float powerMax = 120;
    private float conversionMax = 100;

    //theoretical maximum current value based on how many converters can fit in the reactor. can tweak as needed or tbh delete if we scale more
    public float converterTMax = 22;

    private Reactor myReactor;
    
    //currentChord variable is the position in the changes list. 
    public int changesIndex;

    //THIS is a placeholder list. It's just a I IV II- V I progression. We will move this logic into the map and nav system when we get there.
    public List<int> changes = new List<int>()
    {
        0,
        3,
        1,
        4
    };
    

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        myReactor = GetComponent<Reactor>();

        reactor = FMODUnity.RuntimeManager.CreateInstance(reactorRef);
        
        //line to set constellation will go here
        
        //setting params based on reactor variables
        UpdateReactorParams();
        
        reactor.start();
        
        //Subscribing all the instruments so they're quantized
        Conductor.Instance.onBar.AddListener(UpdateChord);
        Conductor.Instance.onBar.AddListener(UpdateReactorListeners);

        //idk setting current chord to 0 
        changesIndex = 0;

        
    }

    // Update is called once per frame
    void Update()
    {
        pitch = (Notes.GetPitch(Conductor.Instance.keyRoot, Conductor.Instance.mode, (changes[changesIndex])));
        power = Funcs.Remap(myReactor.TotalPowerGenerated(), 0, 10, 0, powerMax);
        conversion = Funcs.Remap(myReactor.TotalPowerConverted(), 0, converterTMax, 0, conversionMax);
        Debug.Log("power: " + power + " conversion: " + conversion);
        
        UpdateReactorParams();
    }
    

    void UpdateChord()
    {
        //add
        changesIndex++;
        //this function updates the current chord every bar 
        if (changesIndex >= changes.Count)
        {
            //SHOULD reset it to 0... this shit is broken tho it doesnt change the number of currentChord at all. the values work fine tho
            changesIndex = 0;
        }

        //UnityEngine.Debug.Log("chord: " + changes[changesIndex]);
        //UnityEngine.Debug.Log("currentChord: " + changesIndex);

        
    }


    public void UpdateReactorParams()
    {
        reactor.setParameterByName("pitch", pitch);
        //TODO: make the constellations change
        reactor.setParameterByName("constellation", 1);
        reactor.setParameterByName("power", power);
        reactor.setParameterByName("conversion", conversion);
    }

    public void UpdateReactorListeners()
    {
        int subdivision = 4;
        if (conversion <= 20)
        {
            subdivision = 4;
        }
        else if (conversion <= 40)
        {
            subdivision = 3;
        }
        else if (conversion <= 60)
        {
            subdivision = 2;
        }
        else if (conversion <= 80)
        {
            subdivision = 1;
        }
        else if (conversion > 80)
        {
            subdivision = 0;
        }
        
        UpdateSubdivision(subdivision);
    }

    
    //p much copied over from the weapons firing in audiomanager
    IEnumerator PlayNoteCoroutine(int noteLength)
    {
        //need to feed in note length thru dictionary like in audiomanager 

        var started = false;

        if (!started)
        {
            reactor.setParameterByName("adsr", 1);

            started = true;
            yield return new WaitForSeconds(5);
        }

        reactor.setParameterByName("adsr", 0);
    }

    //ts is stupid surely there's a better way
    void PlayNote()
    {
        PlayNoteCoroutine(Conductor.Instance.sixteenth);
    }
    
    void UpdateSubdivision(int value)
    {
        Conductor.Instance.onSixteenth.RemoveListener(PlayNote);
        Conductor.Instance.onEighth.RemoveListener(PlayNote);
        Conductor.Instance.onQuarter.RemoveListener(PlayNote);
        Conductor.Instance.onHalf.RemoveListener(PlayNote);
        Conductor.Instance.onWhole.RemoveListener(PlayNote);
        Conductor.Instance.onBar.RemoveListener(PlayNote);
        
        switch (value)
        {
            case 0:
                Conductor.Instance.onSixteenth.AddListener(PlayNote);
                break;
            case 1:
                Conductor.Instance.onEighth.AddListener(PlayNote);
                break;
            case 2:
                Conductor.Instance.onQuarter.AddListener(PlayNote);
                break;
            case 3:
                Conductor.Instance.onHalf.AddListener(PlayNote);
                break;
            case 4:
                Conductor.Instance.onWhole.AddListener(PlayNote);
                break;
            case 5:
                Conductor.Instance.onBar.AddListener(PlayNote);
                break;
        }
    }

}
