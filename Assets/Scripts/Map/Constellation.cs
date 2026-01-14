using System;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Constellation : MonoBehaviour
{
    //this constellation's sector
    public MapManager.Sector sector;
    
    //if this constellation is active
    public bool isActive = true;
    
    //list of all nodes in this constellation - needed for pathing
    public List<Node> nodes = new List<Node>();
    
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        
    }

    /// <summary>
    /// checks if this constellation should be active 
    /// </summary>
    public void CheckIfActive()
    {
        //if this constellation's sector is the same as the one we are in
        if (sector == MapManager.Instance.sector)
        {
            //it should be active
            isActive = true;
            Debug.Log(sector + " is active");
        }
        //otherwise
        else
        {
            //it shouldn't
            Debug.Log(sector + " is not active");
            isActive = false;
        }
    }
    
    
}
