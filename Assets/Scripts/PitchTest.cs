using UnityEngine;
using TMPro;
using FMOD.Studio;
using FMODUnity;
using static UnityEditor.PlayerSettings;
using System.Drawing;

public class PitchTest : MonoBehaviour
{
    //is this the higher pitch
    public bool isHigher;

    //is playing
    private bool isPlaying = false;

    //FMOD event instances
    private EventInstance testInstance;
    public EventReference testRef;

    //timer
    private bool timerRunning = false;
    private float targetTime;

    //ear training tutorial manager
    public GameObject etTutorialManager;

    //cubes 
    public GameObject higherPitch;
    public GameObject lowerPitch;
    public GameObject izkiModule;
    public GameObject auboModule;
    public GameObject dwthModule;

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        testInstance = FMODUnity.RuntimeManager.CreateInstance(testRef);

        testInstance.setParameterByName("source", 2);
    }

    // Update is called once per frame
    void Update()
    {
        if (timerRunning)
        {
            targetTime -= Time.deltaTime;
        }
        if (targetTime < 0)
        {
            TimerEnd();
        }

        transform.rotation = Quaternion.identity;
        //var coll = Physics2D.OverlapBox(transform.position, transform.localScale / 2, 0);

        var overlap = Physics2D.OverlapBoxAll(transform.position, transform.localScale / 2, 0, LayerMask.GetMask("Module Bodies"));
        foreach (var coll in overlap)
        {
            if (coll.gameObject == gameObject)
                continue;

            Debug.Log("collided");
            if (coll.gameObject == higherPitch)
            {
                if (!isPlaying)
                {
                    isPlaying = true;
                    testInstance.setParameterByName("pitch", 659.26f);
                    testInstance.start();
                    TimerStart();
                }   
            }
            if (coll.gameObject == lowerPitch)
            {
                if (!isPlaying)
                {
                    isPlaying = true;
                    testInstance.setParameterByName("pitch", 440);
                    testInstance.start();
                    TimerStart();
                }
            }
            if (coll.gameObject == izkiModule)
            {
                if (!isPlaying)
                {
                    isPlaying = true;
                    testInstance.setParameterByName("pitch", 440);
                    testInstance.setParameterByName("source", 3);
                    testInstance.start();
                    TimerStart();
                }
            }
            if (coll.gameObject == auboModule)
            {
                if (!isPlaying)
                {
                    isPlaying = true;
                    testInstance.setParameterByName("pitch", 440);
                    testInstance.setParameterByName("source", 2);
                    testInstance.start();
                    TimerStart();
                }
            }
            if (coll.gameObject == dwthModule)
            {
                if (!isPlaying)
                {
                    isPlaying = true;
                    testInstance.setParameterByName("pitch", 440);
                    testInstance.setParameterByName("source", 4);
                    testInstance.start();
                    TimerStart();
                }
            }
        }
    }

    private void TimerStart()
    {
        targetTime = 1;
        timerRunning = true;
    }

    private void TimerEnd()
    {
        testInstance.stop(0);
        isPlaying = false;
    }
}

    /*  private void OnMouseDown()
      {
          if (isHigher)
          {
              testInstance.setParameterByName("pitch", 659.26f);
              testInstance.start();
              TimerStart();
          } 
          else
          {
              testInstance.setParameterByName("pitch", 440);
              testInstance.start();
              TimerStart();
          }

      }*/




 /*   public void AnswerSelect()
    {
        if (isHigher)
        {
            etTutorialManager.GetComponent<EarTrainingTutorial>().pitchAnswered = true;
            etTutorialManager.GetComponent<EarTrainingTutorial>().pitchCorrect = true;
        }
        else
        {
            etTutorialManager.GetComponent<EarTrainingTutorial>().pitchAnswered = true;
            etTutorialManager.GetComponent<EarTrainingTutorial>().pitchCorrect = false;

        }
    }*/
//}
