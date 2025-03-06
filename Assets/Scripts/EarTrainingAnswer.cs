using UnityEngine;

public class EarTrainingAnswer : MonoBehaviour
{

    public GameObject higherPitch;
    public GameObject lowerPitch;
    public GameObject izkiModule;
    public GameObject auboModule;
    public GameObject dwthModule;
    public GameObject etTutorialManager;

    private bool dialogueSoundPlayed = false;

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        var overlap = Physics2D.OverlapBoxAll(transform.position, transform.localScale / 2, 0, LayerMask.GetMask("Module Bodies"));
        foreach (var coll in overlap)
        {
            if (coll.gameObject == gameObject)
                continue;
            if (coll.gameObject == higherPitch)
            {
                etTutorialManager.GetComponent<EarTrainingTutorial>().pitchAnswered = true;
                etTutorialManager.GetComponent<EarTrainingTutorial>().pitchCorrect = true;
            }
            if (coll.gameObject == lowerPitch)
            {
                etTutorialManager.GetComponent<EarTrainingTutorial>().pitchAnswered = true;
                etTutorialManager.GetComponent<EarTrainingTutorial>().pitchCorrect = false;
            }
            if (CompareTag("Izki"))
            {
                if (coll.gameObject == izkiModule)
                {
                    etTutorialManager.GetComponent<EarTrainingTutorial>().izkiCorrect = true;
                    etTutorialManager.GetComponent<EarTrainingTutorial>().dialogueText.text = "Correct! That sound is Izki.";
                    //add dialogue sound later

                }
                else
                {
                    etTutorialManager.GetComponent<EarTrainingTutorial>().dialogueText.text = "Not quite. Try again. Remember, Izki is a bit buzzy.";
                    //add dialogue sound
                }
            }
            if (CompareTag("Aubo"))
            {
                if (coll.gameObject == auboModule)
                {
                    etTutorialManager.GetComponent<EarTrainingTutorial>().auboCorrect = true;
                    etTutorialManager.GetComponent<EarTrainingTutorial>().dialogueText.text = "Correct! That sound is Aubo.";
                    //add dialogue sound
                }
                else
                {
                    etTutorialManager.GetComponent<EarTrainingTutorial>().dialogueText.text = "Not quite. Try again. Remember, Aubo sounds pure and round.";
                    //add dialogue sound
                }
            }
            if (CompareTag("Dwth"))
            {
                if (coll.gameObject == dwthModule)
                {
                    etTutorialManager.GetComponent<EarTrainingTutorial>().dwthCorrect = true;
                    etTutorialManager.GetComponent<EarTrainingTutorial>().dialogueText.text = "Correct! That sound is Dwth.";
                    //add dialogue sound
                }
                else
                {
                    etTutorialManager.GetComponent<EarTrainingTutorial>().dialogueText.text = "Not quite. Try again. Remember, Dwth sounds pure and round.";
                    //add dialogue sound
                }
            }
        }
    }
}
