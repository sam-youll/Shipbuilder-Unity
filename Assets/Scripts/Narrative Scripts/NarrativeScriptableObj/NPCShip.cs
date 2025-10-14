using System.Collections.Generic;
using System.Data.SqlTypes;
using UnityEngine;

public enum Faction
{
    Corporate, 
    Aristocrat,
    Green,
    Wetslap
}
[CreateAssetMenu(fileName = "NPCShip", menuName = "Scriptable Objects/NPCShip")]
public class NPCShip : ScriptableObject
{
    public Faction faction;
    
    //likely to hold more info for rank, role, etc, but we'll cross that bridge when we get to it
    //sprites too, maybe module info here? 

    public List<string> scenarioText;

    public List<string> talkOutcomes;

    public int fightChance;
    
    //loot stuff
    public int moduleChance;
    public int creditsChance;
    public int intelChance;
    public bool acceptsModule;
    public bool acceptsCredits;
    
}
