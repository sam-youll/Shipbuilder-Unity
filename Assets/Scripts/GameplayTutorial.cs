using TMPro;
using UnityEngine;

public class GameplayTutorial : MonoBehaviour
{

    private int currentStep = 0;
    private bool dialogueSoundPlayed = false;
    public bool stepComplete = false;

    [Header("Game Object References")]
    //Text
    public TextMeshPro dialogueText;
    //Output Module
    public GameObject outputModule;
    //sequencer 
    public GameObject sequencer;
    //envelope
    public GameObject envelopeModule;

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {

        if (Input.GetKeyDown(KeyCode.Space))
        {
            NextStep();
        }

        if (currentStep == 0)
        {
            dialogueText.text = "Welcome to your new ship.";
            stepComplete = true;
        }
        if (currentStep == 1)
        {
            dialogueText.text = "This is your module rack";
            stepComplete = true;
        }
        if (currentStep == 2)
        {
            dialogueText.text = "It's where you'll manage your ship's combat systems.";
            stepComplete = true;
        }
        if (currentStep == 3)
        {
            dialogueText.text = "Your inventory's at the top. It's where you can find your modules.";
            //want a visual here
            stepComplete = true;
        }
        if (currentStep == 4)
        {
            stepComplete = false;
            dialogueText.text = "Try pulling it open and placing one of the colorful modules onto the rack.";
            if (ModuleRack.Instance.transform.childCount > 1)
            {
                dialogueText.text = "Great. Next, we'll look at plugging them in.";
                stepComplete = true;
            }
        }
        if (currentStep == 5)
        {
            dialogueText.text = "This is your output module.";
            outputModule.SetActive(true);
            stepComplete = true;
        }
        if (currentStep == 6)
        {
            dialogueText.text = "It will allow you to connect your modules to your ship's weapons and shields.";
            stepComplete = true;
        }
        if (currentStep == 7)
        {
            dialogueText.text = "White circles are outputs -- they're where your module's signal is coming from.";
            //should probably put a visual here
            stepComplete = true;
        }
        if (currentStep == 8)
        {
            dialogueText.text = "Black circles are inputs -- they're where you're bringing the signal to.";
            //should probably put a visual here
            stepComplete = true;
        }
        if (currentStep == 9)
        {
            stepComplete = false;
            dialogueText.text = "Try plugging in the generator module you put on your rack into your shields.";
            //... this will probably require some more yellow paint
            if (outputModule.GetComponent<OutputRack>().previousModsShields[0] != null) 
            {
                dialogueText.text = "Beautiful. Now you have some defense.";
                stepComplete = true;
            }
        }
        if (currentStep == 10)
        {
            stepComplete = false;
            dialogueText.text = "Now, pull down another generator module.";
            if (ModuleRack.Instance.transform.childCount > 2)
            {
                dialogueText.text = "Nice. This one is going to be our weapon, and we need to plug it into the sequencer.";
                stepComplete = true;
            }
        }
        if (currentStep == 11)
        {
            dialogueText.text = "This is a sequencer. It will let you change the pitch and rhythm you attack with.";
            sequencer.SetActive(true);
            stepComplete = true;
        }
        if (currentStep == 12)
        {
            dialogueText.text = "It needs to be triggered with this envelope module. It will determine how sharp or flowing your attack is.";
            envelopeModule.SetActive(true);
            stepComplete = true;
        }
        if (currentStep == 13)
        {
            stepComplete = false;
            dialogueText.text = "To plug it in, connect the blue trigger output of the envelope into the red trigger input of the sequencer.";
            if (envelopeModule.GetComponent<Envelope>().sequencerAttached)
            {
                dialogueText.text = "Yep, just like that.";
                stepComplete = true;
            }
        }
        if (currentStep == 14)
        {
            stepComplete = false;
            dialogueText.text = "Next, plug your source into the envelope module, and the envelope module into your weapon output.";
            if (envelopeModule.GetComponent<Module>().previousModule != null && outputModule.GetComponent<OutputRack>().previousModsWeapons[0] != null)
            {
                dialogueText.text = "Perfect. Now you're ready for battle.";
                stepComplete = true;
            }
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
