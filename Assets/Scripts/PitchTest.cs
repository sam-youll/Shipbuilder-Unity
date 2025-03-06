using UnityEngine;
using TMPro;
using FMOD.Studio;
using FMODUnity;

public class PitchTest : MonoBehaviour
{
    //is this the higher pitch
    public bool isHigher;


    //FMOD event instances
    private EventInstance testInstance;
    public EventReference testRef;

    //timer
    private bool timerRunning = false;
    private float targetTime;

    //ear training tutorial manager
    public GameObject etTutorialManager;

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
    }

    private void OnMouseDown()
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

    }

    private void TimerStart()
    {
        targetTime = 2;
        timerRunning = true;
    }

    private void TimerEnd()
    {
        testInstance.stop(0);
    }

    public void AnswerSelect()
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
    }
}
