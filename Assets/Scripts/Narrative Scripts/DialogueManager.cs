using TMPro;
using UnityEngine;

public class DialogueManager : MonoBehaviour
{

    public TextMeshPro nameplateText;
    public TextMeshPro dialogueText;
    
    public GameObject dialoguePanel;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void StartDialogue()
    {
        dialoguePanel.SetActive(true);
        
    }
}
