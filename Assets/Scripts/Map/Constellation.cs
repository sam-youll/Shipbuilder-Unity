using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Constellation : MonoBehaviour
{
    //this constellation's sector
    public MapManager.Sector sector;
    
    //if this constellation is active
    public bool isActive = true;
    
    //list of all nodes in this constellation
    public List<Node> nodes = new List<Node>();
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        if (sector == MapManager.Instance.sector)
        {
            isActive = true;
        }
        else
        {
            isActive = false;
        }

        if (SceneManager.GetActiveScene() == SceneManager.GetSceneByName("SectorMap"))
        {
            MapManager.Instance.UpdateNodeMap();
        }

    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void NodeCleanup()
    {
        
    }
    
}
