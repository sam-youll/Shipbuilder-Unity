using UnityEngine;
using FMODUnity;
using FMOD;
using FMOD.Studio;
using Unity.VisualScripting;

public class ReferenceSpeaker : MonoBehaviour
{
    private float speakerType;
    private bool isPlaying;
    public EventReference speakerRef;
    private EventInstance speakerInst;
    private bool timerRunning;
    private float targetTime;

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        //setting fmod event
        speakerInst = FMODUnity.RuntimeManager.CreateInstance(speakerRef);

        //if tag is aubo, speakerType = 2
        if (CompareTag("Aubo"))
        {
            speakerInst.setParameterByName("source", 2);
        }
        //if tag is izki, speakerType = 3
        if (CompareTag("Izki"))
        {
            speakerInst.setParameterByName("source", 3);
        }
        //if tag is dwth, speakerType = 4
        if (CompareTag("Dwth"))
        {
            speakerInst.setParameterByName("source", 4);
        }
    }

    // Update is called once per frame
    void Update()
    {
        if (timerRunning)
        {
            targetTime -= Time.deltaTime;
        }
        else if (isPlaying)
        {
            if (Input.GetMouseButton(0))
            {
                speakerInst.stop(0);
                isPlaying = false;
            }
        }


        if (targetTime < 0)
        {
            timerEnded();
        }

    }

    private void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(0)) 
        {
            //if not playing, start
            if (!isPlaying)
            {
                speakerInst.start();
                isPlaying = true;
                timerStart();

            }
            //if playing, stop 
            if (isPlaying && !timerRunning)
            {
                speakerInst.stop(0);
                isPlaying = false;
            }
        }
    }

    void timerStart()
    {
        targetTime = 1;
        timerRunning = true;
    }
    void timerEnded()
    {
        timerRunning = false;
    }

}
