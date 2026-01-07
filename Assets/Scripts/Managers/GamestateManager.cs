using System.Collections.Generic;
using NUnit.Framework;
using UnityEngine;

public class GamestateManager : MonoBehaviour
{
    public static GamestateManager Instance;

    private void Awake()
    {
        if (Instance != null && Instance != this)
        {
            Destroy(this);
        }
        else
        {
            Instance = this;
        }
    }
    
    //Not sure if this is best way to handle this, but it works for now
    public Dictionary<string, bool> Gamestate = new Dictionary<string, bool>();
    
    //TODO: move location stuff to map manager and have it set location based on where you are on the map
    //TODO: add more node types
    public enum Node
    {
        Base,
        Pallas,
        Pan,
        AsteroidBelt,
        Bailigh,
        Zea,
        Node
    }

    public enum Constellation
    {
        Null,
        Aries,
        Taurus,
        Gemini,
        Cancer,
        Leo,
        Virgo,
        Libra,
        Scorpio,
        Sagittarius,
        Capricorn,
        Aquarius,
        Pisces
    }
    
    public Node currentNode;
    public Constellation currentConstellation;

    // WIP / placeholder, this enum should be where major linear game events go
    public enum Stage
    {
        Testing,
        Tutorial,
        Exposition,
        Pallas,
        Pan,
        AsteroidBelt,
        Bailigh,
        Zea
    }
    
    public Stage currentStage;

    public void Start()
    {
        //Dummy gamestates, should add and test complexity and how to set moving forward.
        //This is just here to get the narrative stuff functioning
        Gamestate.Add("gameStarted", true);
        currentNode = Node.Base;
        currentConstellation = Constellation.Null;
        currentStage = Stage.Testing;
    }
}
