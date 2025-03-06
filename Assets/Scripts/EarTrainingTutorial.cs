using TMPro;
using UnityEngine;

public class EarTrainingTutorial : MonoBehaviour
{
    //text refs
    [Header("Tutorial Text")]
    public TextMeshPro dialogueText;
    public TMP_Text directionText;

    //completion
    public bool stepComplete;
    public bool pitchAnswered;
    public bool pitchCorrect;

    private int currentStep;

    //object references 
    [Header("Tutorial Objects")]
    public GameObject higherPitch;
    public GameObject lowerPitch;

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        currentStep = 0;
        higherPitch.SetActive(false);
        lowerPitch.SetActive(false);
    }

    // Update is called once per frame
    void Update()
    {
        if (UnityEngine.Input.GetKeyDown(KeyCode.Space))
        {
            NextStep();
        }

        if (currentStep == 0)
        {
            dialogueText.text = "New recruit, huh?";
            stepComplete = true;
        }
        if (currentStep == 1)
        {
            dialogueText.text = "Okay, I guess I should get you ready to fly.";
            stepComplete = true;
        }
        if (currentStep == 2)
        {
            dialogueText.text = "First we gotta make sure you know what to listen for.";
            stepComplete = true;
        }
        if (currentStep == 3)
        {
            dialogueText.text = "Telling sounds apart is kind of your only hope in battle, so I hope you got good ears.";
            stepComplete = true;
        }
        if (currentStep == 4)
        {
            dialogueText.text = "If you don't, you can try to use your eyes but... they'll only get you so far.";
            stepComplete = true;
        }
        if (currentStep == 5)
        {
            stepComplete = false;
            if (!pitchAnswered)
            {
                dialogueText.text = "Let's see. Which of these do you think is higher?";
                higherPitch.SetActive(true);
                lowerPitch.SetActive(true);
                directionText.text = "Click to listen.";
            }
            else
            {
                if (pitchCorrect)
                {
                    dialogueText.text = "Correct! Let's move on.";
                    directionText.text = "Press space to continue.";
                    stepComplete = true;
                }
                else
                {
                    dialogueText.text = "Not quite. Listen carefully and try again.";
                }
            }
        }
        if (currentStep == 6)
        {
            higherPitch.SetActive(false);
            lowerPitch.SetActive(false);
            dialogueText.text = "Next, we're going to go over the types of sound.";
            stepComplete = true;
        }
        if (currentStep == 7)
        {
            dialogueText.text = "There are three types of sound: Izki, Aubo, and Dwth.";
            stepComplete = true;
        }
        if (currentStep == 8)
        {
            dialogueText.text = "Izki is easiest for some to spot. It's electric and sharp";
            //put a funny izki animation here 
            //put izki text here
            //put izki speaker here
            stepComplete=true;
        }
        if (currentStep == 9) 
        {
            dialogueText.text = "Aubo is the simplest. It sounds pure and round";
            //put an aubo animation here
            //put aubo text here
            //put aubo speaker here
            stepComplete = true;
        }
        if (currentStep == 10)
        {
            dialogueText.text = "Dwth is a little more subtle. It's hollow but stable. A bit toothy, maybe.";
            //put a dwth animation here 
            //put dwth text here 
            //put dwth speaker here
            stepComplete = true;
        }
        if (currentStep == 11)
        {
            dialogueText.text = "This is important to remember because some sounds are better at beating other sounds";
            stepComplete = true;
        }
        if (currentStep == 12)
        {
            dialogueText.text = "Aubo is strong against Izki, which is strong against Dwth, which is strong against Aubo.";
            stepComplete = true;
        }
        if (currentStep == 13)
        {
            dialogueText.text = "If you ever need help remembering this, you can use my old reference sheet.";
            //pull up reference sheet here 
            //paper sfx needed
            stepComplete = true;
        }
        if (currentStep == 14)
        {
            stepComplete = false;
            dialogueText.text = "Let's test it out -- can you sort these for me?";
        }
    }

    private void NextStep()
    {
        if (stepComplete)
        {
            currentStep += 1;
            AudioManager.Instance.PlayDialogueSound();
        }
    }
}
