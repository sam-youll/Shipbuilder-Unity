using System;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.InputSystem;
using UnityEngine.SceneManagement;

public class Constellation : MonoBehaviour
{
    //this constellation's sector
    public MapManager.Sector sector;
    
    //if this constellation is active
    public bool isActive = true;
    
    //list of all nodes in this constellation - needed for pathing
    public List<MapNode> nodes = new List<MapNode>();
    
    public SpriteRenderer sr;

    public Color highlightColor;
    
    public Color inactiveColor;

    public float combatMultiplier;
    public float storyMultiplier;
    public float shopMultiplier;

    //public TextMeshPro label;
    public GameObject labelObject;
    
    //planet object for main map sectors
    public GameObject mainmapPlanet;

    public GameObject playerShip;

    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        //in the main map scene
        if (SceneManager.GetSceneByName("MainMap").isLoaded)
        {
            //set the default color to the inactive color
            sr.color = inactiveColor;
            
            playerShip = transform.GetChild(0).gameObject;
        }
        
    }

    // Update is called once per frame
    void Update()
    {
        
       
    }

    void FixedUpdate()
    {
        RaycastHit hit;
        Ray ray = Global.Instance.cam.ScreenPointToRay(Input.mousePosition);
        if (Physics.Raycast(ray,  out hit) &&  hit.collider == this.GetComponent<Collider>())
        {
            //in the main map scene
            if (SceneManager.GetSceneByName("MainMap").isLoaded)
            {
                //for every planet
                foreach (MapManager.PlanetStruct planet in MapManager.Instance.planets)
                {
                    //if that planet is here
                    if (planet.location == sector && !planet.visited)
                    {
                        //Debug.Log(planet.node + " is in " + planet.location);
                        GetComponentInChildren<Planet>().textObject.SetActive(true);
                        //check every sector 
                        foreach (Constellation constellation in GameObject.FindObjectsByType<Constellation>(FindObjectsSortMode.InstanceID))
                        {
                            //for if it's in that planet's path
                            for (int i = 0; i < planet.path.Count; i++)
                            {
                                //and if it is
                                if (planet.path[i] == constellation.sector)
                                {
                                    //Debug.Log(constellation.sector + " is in the path and should be highlighted");
                                    //then highlight it
                                    constellation.HighlightSector(constellation);
                                    constellation.labelObject.SetActive(true);
                                } 
                            }
                        }
                    }
                }
            }
        }
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
            //Debug.Log(sector + " is active");
        }
        //otherwise
        else
        {
            //it shouldn't
            //Debug.Log(sector + " is not active");
            isActive = false;
        }
    }

    void OnMouseDown()
    {

        foreach (MapManager.PlanetStruct planet in MapManager.Instance.planets)
        {
            if (planet.location == sector && !planet.visited)
            {
                //load the sector map scene
                MapManager.Instance.GoToSectorMap();

                MapManager.Instance.targetPlanet = planet;
                
                
                Planet clickablePlanet = GetComponentInChildren<Planet>();
                //sets whatever was clicked to visited
                clickablePlanet.visited = true;
                //sets this to the currently selected node
                clickablePlanet.isSelected = true;
                //makes this node unavailable 
                clickablePlanet.MakeUnavailable();

                MapManager.Instance.SetCurrentPath(planet.node);
                
            }
        }
        
    }

    void OnMouseExit()
    {
        //in the main map
        if (SceneManager.GetSceneByName("MainMap").isLoaded)
        {
            //for every sector
            foreach (Constellation constellation in GameObject.FindObjectsByType<Constellation>(FindObjectsSortMode.InstanceID))
            {
                //unhighlight it 
                constellation.UnHighlightSector();
                constellation.labelObject.SetActive(false);
                if (GetComponentInChildren<Planet>() != null)
                {
                    GetComponentInChildren<Planet>().textObject.SetActive(false);
                }
            }
        }
        
    }

    /// <summary>
    /// highlights the sector
    /// </summary>
    /// <param name="constellation"></param>
    public void HighlightSector(Constellation constellation)
    {
        
        constellation.sr.color = highlightColor;
    }

    /// <summary>
    /// Unhighlights the sector
    /// </summary>
    public void UnHighlightSector()
    {
        // set it to inactive color
        sr.color = inactiveColor;
    }

    public void ShowPlayerShip()
    {
        playerShip.SetActive(true);
    }

    public void HidePlayerShip()
    {
        playerShip.SetActive(false);
    }
    
}
