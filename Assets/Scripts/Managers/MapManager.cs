using System;
using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.SceneManagement;

public class MapManager : MonoBehaviour
{
    public static MapManager Instance;

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

    //existing sectors
    public enum Sector
    {
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
    
    //current sector
    public Sector sector;
    
    //existing node types
    public enum Node
    {
        Base,
        Pallas,
        Pan,
        Bailigh,
        Zea,
        AsteroidBelt,
        Combat,
        Narrative,
        Shop
    }
    
    //current node's type
    public Node currentNodeType;

    //list of nodemap game objects
    public List<GameObject> nodeMaps = new List<GameObject>();

    //planet struct for planet location and movement
    public struct PlanetStruct
    {
        public Node node;
        public Sector location;
        public int speed;
        public Color color;
        //list of the sectors in order 
        public List<Sector> path;
        //read the list backwards wtf 
    }
    
    
    //array of planets for movement
    public PlanetStruct[] planets = new PlanetStruct[4];
    
    
    
    //should probably add stuff later to track what planets visited vs not, if a planet is targeted, etc
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        planets[0].node = Node.Pallas;
        planets[1].node = Node.Pan;
        planets[2].node = Node.Bailigh;
        planets[3].node = Node.Zea;
        
        planets[0].location = Sector.Aries;
        planets[1].location = Sector.Taurus;
        planets[2].location = Sector.Gemini;
        planets[3].location = Sector.Libra;
        
        planets[0].speed = 1;
        planets[1].speed = 2;
        planets[2].speed = 3;
        planets[3].speed = 4;
        
        planets[0].color = new Color(0.627451f, 0.1254902f, 0.9411765f, 1f);
        planets[1].color = Color.green;
        planets[2].color = Color.red;
        planets[3].color = Color.blue;
        
        planets[0].path = new List<Sector>();
        planets[1].path = new List<Sector>();
        planets[2].path = new List<Sector>();
        planets[3].path = new List<Sector>();

        foreach (GameObject nodeMap in nodeMaps)
        {
            //if there's a planet in the child of the constellation
            if (nodeMap.GetComponentInChildren<Planet>() != null)
            {
                //set the planet (this has to be here otherwise that gets called before the array is put together)
                nodeMap.GetComponentInChildren<Planet>().SetPlanet();
            }
        }

        if (SceneManager.GetActiveScene() == SceneManager.GetSceneByName("MainMap"))
        {
            UpdateMainMap();
        }

    }

    // Update is called once per frame
    void Update()
    {
        //just for testing
        /*if (Input.GetKeyDown(KeyCode.LeftShift))
        {
            UpdatePlanetLocations();
        }*/
    }
    

    public void UpdateNodeMap()
    {
        foreach (GameObject nodeMap in nodeMaps)
        {
            if (nodeMap.GetComponent<Constellation>().isActive)
            {
                nodeMap.SetActive(true);
                //Debug.Log("setting " + nodeMap.name + " active");
            }
            else
            {
                nodeMap.SetActive(false);
                //Debug.Log("setting " + nodeMap.name + " inactive");
            }
        }
    }

    public void UpdatePlanetLocations()
    {
        //for each planet struct in the array
        for (int i = 0; i < planets.Length; i++)
        {
            //its location increases by its speed
            planets[i].location += planets[i].speed;
            
            //for each item in the list below this one
            for (int j = 0; j < i; j++)
            {
                //if this location is the same as one before
                if (planets[i].location == planets[j].location)
                {
                    //increment this one by one
                    planets[i].location++;
                    //Debug.Log("Planet " + planets[i].node + " bumped");
                }
            }
            
            //if it goes beyond the number of existing sectors
            if (!Enum.IsDefined(typeof(Sector), planets[i].location))
            {
                //loop back around to the beginning of the enum
                planets[i].location -= 12;
            }
            
            Debug.Log(planets[i].node + " " +  planets[i].location);
        }
    }

    public void UpdateMainMap()
    {
        
        //for each planet 
        for (int i = 0; i < planets.Length; i++)
        {
            //checks the distance between your current sector and that planet
            int distance = sector -  planets[i].location;
            Debug.Log(planets[i].node + " is " + distance + " sectors away");

            if (distance > 0)
            {
                //increment thru the enum of sectors negatively until u get to the destination
                for (Sector s = sector; s > planets[i].location; s--)
                {
                    planets[i].path.Add(s);
                }
                for (int j = 0; j < planets[i].path.Count; j++)
                {
                    Debug.Log(planets[i].node + " path includes " + planets[i].path[j]);
                }
            } else if (distance < 0)
            {
                //increment thru the enum of sectors negatively until u get to the destination
                for (Sector s = sector; s < planets[i].location; s++)
                {
                    planets[i].path.Add(s);
                }
                for (int j = 0; j < planets[i].path.Count; j++)
                {
                    Debug.Log(planets[i].node + " path includes " + planets[i].path[j]);
                }
            } else
            {
                planets[i].path.Add(sector);
            } 

            
            
            
        }
        
    }
    
}
