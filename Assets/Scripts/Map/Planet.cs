using System.Collections.Generic;
using NUnit.Framework;
using TreeEditor;
using UnityEngine;

public class NewMonoBehaviourScript : MonoBehaviour
{

    public List<MapManager.Node> Planets = new List<MapManager.Node>()
    {
        MapManager.Node.Pallas,
        MapManager.Node.Pan,
        MapManager.Node.Bailigh,
        MapManager.Node.Zea
    };

    public Node currentPlanet;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
