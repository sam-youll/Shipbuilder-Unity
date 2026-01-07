using System;
using System.Collections.Generic;
using UnityEngine;


[CreateAssetMenu(fileName = "DialogueList", menuName = "Scriptable Objects/DialogueList")]
public class DialogueList : ScriptableObject
{
    //used by dialogue manager to select character name and portrait
    public String characterName;
    //used by dialogue manager to set the dialogue text 
    public List<String> lines = new List<String>();
    
    //checked against gamestate manager to determine if this list is available
    public List<String> gamestateTriggers = new List<String>();
    public List<GamestateManager.Stage> stages = new List<GamestateManager.Stage>();
    
    //checked against (gamestate manager for now, but should be) map manager to determine if available
    public List<GamestateManager.Node> nodes = new List<GamestateManager.Node>();
    public List<GamestateManager.Constellation> constellations = new List<GamestateManager.Constellation>();
    //bools to check for matches so we can check if something is a positive while keeping w assuming list is available
    public bool nodeMatch = false;
    public bool constellationMatch = false;
    public bool stageMatch = false;
    
    
    //whether the string is available - assumes true, if any condition isn't met, it gets set to false
    public bool isAvailable = true;
    
    
}
