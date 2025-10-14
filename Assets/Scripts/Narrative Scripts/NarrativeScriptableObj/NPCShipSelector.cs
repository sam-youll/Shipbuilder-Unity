using System.Collections.Generic;
using UnityEngine;

public class NPCShipSelector : MonoBehaviour
{
    public List<NPCShip> npcShips;

    private int npcRoll;

    public NPCShip npcShip;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        npcRoll = Random.Range(0, npcShips.Count + 1);
        Debug.Log(npcRoll);
        npcShip = npcShips[npcRoll];
        Debug.Log(npcShip.faction);
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
