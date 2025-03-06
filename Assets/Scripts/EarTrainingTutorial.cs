using TMPro;
using UnityEngine;

public class EarTrainingTutorial : MonoBehaviour
{
    //text refs
    [Header("Tutorial Text")]
    public TextMeshPro dialogueText;
    public TMP_Text directionText;

    //completion
    public bool stepComplete = false;
    public bool pitchAnswered = false;
    public bool pitchCorrect = false;
    public bool izkiCorrect = false;
    public bool auboCorrect = false;
    public bool dwthCorrect = false;
    public bool weaponCorrect = false;

    public bool papersfxPlayed = false;
    private bool dialogueSoundPlayed = false;

    private int currentStep;

    //object references 
    [Header("Tutorial Objects")]
    //pitch test
    public GameObject higherPitch;
    public GameObject lowerPitch;
    //test and answer
    public GameObject testSquare;
    public GameObject answerSquare;
    //text examples
    public GameObject izkiText;
    public GameObject auboText;
    public GameObject dwthText;
    //reference sheet
    public GameObject referenceSheet;
    //type test
    public GameObject izkiModule;
    public GameObject auboModule;
    public GameObject dwthModule;
    public GameObject izkiAnswer;
    public GameObject auboAnswer;
    public GameObject dwthAnswer;
    //weapon test
    public GameObject weaponModule;
    public GameObject shieldModule;

    private Vector3 weaponPos;
    private Vector3 shieldPos;

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        currentStep = 0;
        higherPitch.SetActive(false);
        lowerPitch.SetActive(false);

        weaponPos = weaponModule.transform.position;
        shieldPos = shieldModule.transform.position;
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
                testSquare.SetActive(true);
                answerSquare.SetActive(true);
                directionText.text = "Click and drag to listen and answer.";
            }
            else
            {
                if (pitchCorrect)
                {
                    dialogueText.text = "Correct! Let's move on.";
                    directionText.text = "Press space to continue.";
                    stepComplete = true;
                    if (!dialogueSoundPlayed)
                    {
                        AudioManager.Instance.PlayDialogueSound();
                        dialogueSoundPlayed = true;
                    }  
                }
                else
                {
                    if (!dialogueSoundPlayed)
                    {
                        AudioManager.Instance.PlayDialogueSound();
                        dialogueSoundPlayed = true;
                    }
                    dialogueText.text = "Not quite. Listen carefully and try again.";
                }
            }
        }
        if (currentStep == 6)
        {
            higherPitch.SetActive(false);
            lowerPitch.SetActive(false);
            testSquare.SetActive(false);
            answerSquare.SetActive(false);
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
            izkiText.SetActive(true);
            stepComplete=true;
        }
        if (currentStep == 9) 
        {
            dialogueText.text = "Aubo is the simplest. It sounds pure and round";
            //put an aubo animation here
            if (izkiText.GetComponentInChildren<ReferenceSpeaker>().isPlaying)
            {
                izkiText.GetComponentInChildren<ReferenceSpeaker>().speakerInst.stop(0);
            }
            izkiText.SetActive(false);
            auboText.SetActive(true);
            stepComplete = true;
        }
        if (currentStep == 10)
        {
            dialogueText.text = "Dwth is a little more subtle. It's hollow but stable. A bit toothy, maybe.";
            //put a dwth animation here 
            if (auboText.GetComponentInChildren<ReferenceSpeaker>().isPlaying)
            {
                auboText.GetComponentInChildren<ReferenceSpeaker>().speakerInst.stop(0);
            }
            auboText.SetActive(false);
            dwthText.SetActive(true);
            stepComplete = true;
        }
        if (currentStep == 11)
        {
            if (dwthText.GetComponentInChildren<ReferenceSpeaker>().isPlaying)
            {
                dwthText.GetComponentInChildren<ReferenceSpeaker>().speakerInst.stop(0);
            }
            dwthText.SetActive(false);
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
            dialogueText.text = "If you ever need help remembering this, you can use my old cheat sheet.";
            referenceSheet.SetActive(true);
            referenceSheet.GetComponent<ReferenceSheet>().isOpen = true;
            if (!papersfxPlayed)
            {
                AudioManager.Instance.PlayPaperSound();
                papersfxPlayed = true;
            }
            stepComplete = true;
        }
        if (currentStep == 14)
        {
            stepComplete = false;
            dialogueText.text = "Let's test it out -- can you sort these for me?";
            testSquare.SetActive(true);
            izkiModule.SetActive(true);
            auboModule.SetActive(true);
            dwthModule.SetActive(true);
            izkiAnswer.SetActive(true);
            auboAnswer.SetActive(true);
            dwthAnswer.SetActive(true);

            if (izkiCorrect && auboCorrect && dwthCorrect)
            {
                if (!dialogueSoundPlayed)
                {
                    AudioManager.Instance.PlayDialogueSound();
                    dialogueSoundPlayed = true;
                }
                testSquare.SetActive(false);
                izkiModule.SetActive(false);
                auboModule.SetActive(false);
                dwthModule.SetActive(false);
                izkiAnswer.SetActive(false);
                auboAnswer.SetActive(false);
                dwthAnswer.SetActive(false);
                dialogueText.text = "Awesome, you got it. One last step before you can start flying.";
                stepComplete = true;
            }
        }
        if (currentStep == 15)
        {
            dialogueText.text = "We need to see if you can differentiate between weapons and shields.";
            stepComplete = true;
        }
        if (currentStep == 16)
        {
            dialogueText.text = "Shields are usually a constant sound, like this.";
            shieldModule.SetActive(true);
            stepComplete = true;
        }
        if (currentStep == 17)
        {
            dialogueText.text = "Weapons usually are sequenced -- they'll change pitch and can turn on and off.";
            if (shieldModule.GetComponent<WeaponTutorial>().isPlaying)
            {
                shieldModule.GetComponent<WeaponTutorial>().moduleInst.stop(0);
                shieldModule.GetComponent<WeaponTutorial>().isPlaying = false;
            }
            shieldModule.SetActive(false);
            weaponModule.SetActive(true);
            stepComplete = true;
        }
        if (currentStep == 18)
        {
            weaponModule.SetActive(true);
            dialogueText.text = "I'm going to give you two modules.";
            stepComplete = true;
        }
        if (currentStep == 19)
        {
            weaponModule.SetActive(false);
            if (weaponModule.GetComponent<WeaponTutorial>().isPlaying)
            {
                weaponModule.GetComponent<WeaponTutorial>().moduleInst.stop(0);
                weaponModule.GetComponent <WeaponTutorial>().isPlaying = false;
            }
            dialogueText.text = "One will act like shields, the other will act like a weapon.";
            stepComplete = true;
        }
        if (currentStep == 20)
        {
            dialogueText.text = "To tell which one is which, try moving it up and down on the screen to change the pitch.";
            stepComplete = true;
        }
        if (currentStep == 21)
        {
            weaponPos.x = 0;
            weaponModule.transform.position = weaponPos;
            shieldPos.x = -5;
            shieldModule.transform.position = shieldPos;
            dialogueText.text = "Listening for the one that's changing will help you tell them apart";
            stepComplete = true;
        }
        if (currentStep == 22)
        {
            dialogueText.text = "Give it a try -- show me which one is the weapon.";
            directionText.text = "Click and drag.";

            weaponModule.SetActive(true);
            shieldModule.SetActive(true);


            answerSquare.SetActive(true);

            stepComplete = false;

            if (weaponCorrect)
            {
                weaponModule.SetActive(false);
                shieldModule.SetActive(false);
                answerSquare.SetActive(false);
                if (!dialogueSoundPlayed)
                {
                    AudioManager.Instance.PlayDialogueSound();
                }

                dialogueText.text = "Great. You'll be fine. Now let's get you to the module rack.";
                directionText.text = "Press space to continue.";
                stepComplete = true;
            }
        }

        if (currentStep == 23)
        {
            //go to next scene
        }
    }

    private void NextStep()
    {
        if (stepComplete)
        {
            currentStep += 1;
            AudioManager.Instance.PlayDialogueSound();
            dialogueSoundPlayed = false;
        }
    }
}
