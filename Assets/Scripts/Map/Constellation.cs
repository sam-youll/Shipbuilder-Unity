using System.Collections.Generic;
using UnityEngine;

public class Constellation : MonoBehaviour
{
    public MapManager.Sector sector;
    
    public bool isActive = true;
    
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
        
        MapManager.Instance.UpdateNodeMap();
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
