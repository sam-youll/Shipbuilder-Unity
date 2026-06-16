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

    void Awake()
    {
        Instance = this;
    }
    
    private EventInstance reactor;
    
    
    public EventReference reactorRef;

    //currentChord variable is the position in the changes list. 
    public int changesIndex;

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


    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {

        reactor = FMODUnity.RuntimeManager.CreateInstance(reactorRef);

        //setting the placeholder parameters that will just work for now
        SetTestParams();
        //setting params based on reactor variables
        SetReactorParams();
        
        reactor.start();
        
        //Subscribing all the instruments so they're quantized
        Conductor.Instance.onBar.AddListener(UpdateChord);


        //idk setting current chord to 0 
        changesIndex = 0;


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
        //add
        changesIndex++;
        //this function updates the current chord every bar 
        if (changesIndex >= changes.Count)
        {
            //SHOULD reset it to 0... this shit is broken tho it doesnt change the number of currentChord at all. the values work fine tho
            changesIndex = 0;
        }
        //THIS NEEDS TO BE FIXED OH MY GOD i'm just making the list longer every bar this is not ok lmfao 
        //SetTestChanges();

        // UnityEngine.Debug.Log("chord: " + changes[changesIndex]);
        //UnityEngine.Debug.Log("currentChord: " + changesIndex);

        
    }


    public void SetReactorParams()
    {
        
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
