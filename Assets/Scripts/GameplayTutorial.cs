using TMPro;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.SceneManagement;

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
    public GameObject sequencer2;
    //envelope
    public GameObject envelopeModule;
    public GameObject envelopeModule2;
    //buttons 
    public GameObject enemyPlayButton;
    public GameObject startCombatButton;

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
            // if (ModuleRack.Instance.transform.childCount > 3)
            // {
            //     dialogueText.text = "Great. Next, we'll look at plugging them in.";
            //     stepComplete = true;
            // }
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
            if (outputModule.GetComponent<OutputRack>().previousModsWeapons[0] != null) 
            {
                dialogueText.text = "Careful! You plugged it into your weapons. Try plugging it into your shields.";
            }
        }
        if (currentStep == 10)
        {
            stepComplete = false;
            dialogueText.text = "Now, pull down another generator module.";
            // if (ModuleRack.Instance.transform.childCount > 4)
            // {
            //     dialogueText.text = "Nice. This one is going to be our weapon, and we need to plug it into the sequencer.";
            //     stepComplete = true;
            // }
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
            dialogueText.text = "To plug it in, connect the red output of the sequencer into the blue input of the envelope module.";
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
        if (currentStep == 15) 
        {
            dialogueText.text = "Now let's look at how to fight.";
            // for (var i = 0; i < ModuleRack.Instance.transform.childCount; i++)
            // {
            //     if (!ModuleRack.Instance.transform.GetChild(i).CompareTag("OutputRack"))
            //     {
            //         Destroy(ModuleRack.Instance.transform.GetChild(i).GameObject());
            //     }
            // }
            PatchManager.Instance.UpdateAllPatches();
            stepComplete = true;
        }
        if (currentStep == 16)
        {
            dialogueText.text = "This button lets you access your sensor to listen in on your enemy.";
            enemyPlayButton.SetActive(true);
            stepComplete = true;
        }
        if (currentStep == 17)
        {
            dialogueText.text = "Click it now and listen to your enemy's shield";
            stepComplete = true;
        }
        if (currentStep == 18)
        {
            dialogueText.text = "Try to see if you can determine the enemy's shield type by listening.";
            stepComplete = true;
        }
        if (currentStep == 19)
        {
            dialogueText.text = "Use the reference sheet I gave you if you need help.";
            stepComplete = true;
        }
        if (currentStep == 20)
        {
            stepComplete = false;
            sequencer2.SetActive(true);
            envelopeModule2.SetActive(true);
            dialogueText.text = "Using what you've learned, build a weapon you think will beat the enemy's shield";
            if (envelopeModule2.GetComponent<Module>().previousModule != null && outputModule.GetComponent<OutputRack>().previousModsWeapons[0] != null)
            {
                startCombatButton.SetActive(true);
                dialogueText.text = "Okay! Let's see how it works. Press Start Combat when you're ready. Feel free to move on when you feel satisfied with your performance!";
                stepComplete = true;
            }
        }
        if (currentStep == 21)
        {
            dialogueText.text = "Great job. Time to go try your hand at the real thing. Good luck!";
            stepComplete = true;
            AudioManager.Instance.ResetModuleInstances();
        }
        if (currentStep == 22)
        {
            SceneManager.LoadScene("SampleScene");
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
