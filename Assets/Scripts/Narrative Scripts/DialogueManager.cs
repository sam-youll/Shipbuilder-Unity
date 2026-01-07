using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class DialogueManager : MonoBehaviour
{
    [Header("UI Objects")]
    //textmeshpro object that holds character name
    public TextMeshPro nameplateText;
    //tmp object that holds dialogue text
    public TextMeshPro dialogueText;
    
    //UI panel that holds the tmp objects
    public GameObject dialogueBox;
    
    [Header("ScriptableObjects")]
    //all existing dialogue lists -- probably a better way to do this
    public List<DialogueList> dialogueLists = new List<DialogueList>();
    //list of dialogue lists (SOs) that are available 
    private List<DialogueList> availableLists =  new List<DialogueList>();
    
    //The dialogue list (SO) that is selected to set text and other info 
    private DialogueList currentList;
    
    //whether or not dialogue is happening
    private bool dialogueStarted = false;
    //index of which line in the dialogue list's "lines" list is currently active
    private int index = 0;
    
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        //this is for testing only, startdialogue should be called when dialogue should be started. duh
        StartDialogue();
    }

    // Update is called once per frame
    void Update()
    {
        //when dialogue is active
        if (dialogueStarted)
        {
            //if you press the space bar
            if (Input.GetKeyDown(KeyCode.Space))
            {
                    //it advances the line of dialogue
                    index++;
                    //and sets that line of text if it's within the size of the list
                    if (index < currentList.lines.Count)
                    {
                        dialogueText.text = currentList.lines[index];
                    }
                    //if it's bigger than the list
                    else if (index >= currentList.lines.Count)
                    {
                        Debug.Log(index + " list done");
                        //the dialogue ends and the text box gets set inactive
                        dialogueBox.SetActive(false);
                        //and the index resets to 0
                        index = 0;
                    }
            }
        }
    }

    public void StartDialogue()
    {
        dialogueBox.SetActive(true);
        //should be set in a more elegant way since sometimes we'll want to force events, this is just here for now
        SetCurrentListRandomly();
        //dialogue enabled
        dialogueStarted = true;
        //should set the first line of dialogue at 0 
        dialogueText.text = currentList.lines[index];
        //should set the character name 
        nameplateText.text = currentList.characterName;
        
        //TODO: figure out what happens when dialogue ends 
    }

    /// <summary>
    /// Creates a list of all currently available lists, and picks a random one from that list
    /// </summary>
    public void SetCurrentListRandomly()
    {
        Debug.Log("Dialogue list size: " + dialogueLists.Count);
        //for each list in the big ol list of dialogue lists (which we should probably handle diff) 
        foreach (DialogueList list in dialogueLists)
        {
            //set each list's ability, and if it's available, add it to the list
            SetAvailability(dialogueLists[list]);
            if (list.isAvailable)
            {
                availableLists.Add(list);
            }
        }
            
        
        //set the current list
        currentList = availableLists[Random.Range(0, availableLists.Count)];
        Debug.Log("Current List: " + currentList.name);
    }
    
    /// <summary>
    /// Sets the availability of each scriptable object 
    /// </summary>
    /// <param name="checkedList"></param>
    public void SetAvailability(DialogueList checkedList)
    {
        //for each gamestate trigger listed here
        for (int i = 0; i < checkedList.gamestateTriggers.Count; i++)
        {
            //if it isn't true
            if (GamestateManager.Instance.Gamestate[checkedList.gamestateTriggers[i]] == false)
            {
                //this list isn't available
                checkedList.isAvailable = false;
            }
        }

        //for each node listed here
        for (int i = 0; i < checkedList.nodes.Count; i++)
        {
            //if any of them are the current node
            if (GamestateManager.Instance.currentNode == checkedList.nodes[i])
            {
                //there's a match
                checkedList.nodeMatch = true;
            }
        }

        //for each constellation in this list
        for (int i = 0; i < checkedList.constellations.Count; i++)
        {
            //if any of them are the current constellation
            if (GamestateManager.Instance.currentConstellation == checkedList.constellations[i])
            {
                //there's a match
                checkedList.constellationMatch = true;
            }
        }
        
        //for each stage in this list
        for (int i = 0; i < checkedList.stages.Count; i++)
        {
            //if any of them are the current stage
            if (GamestateManager.Instance.currentStage == checkedList.stages[i])
            {
                //there's a match
                checkedList.stageMatch = true;
            }
        }

        //if either the node, stage, or the constellation don't have a match
        if (!checkedList.nodeMatch || !checkedList.constellationMatch || !checkedList.stageMatch)
        {
            //this list isn't available
            checkedList.isAvailable = false;
        }
        
        //debug to check
        Debug.Log(checkedList.ToString() + " " + checkedList.isAvailable);
    }
}
