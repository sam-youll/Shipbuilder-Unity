using System.Collections.Generic;
using NUnit.Framework;
using TreeEditor;
using UnityEngine;

public class NewMonoBehaviourScript : MonoBehaviour
{

    public MapManager.Planet currentPlanet;
    public MapManager.Sector currentSector;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        currentSector = GetComponentInParent<Constellation>().sector;
    }

    // Update is called once per frame
    void Update()
    {
        
    }
    
}
