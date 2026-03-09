using System;
using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.Rendering.UI;
using UnityEngine.SceneManagement;
using Object = System.Object;

public class MapManager : MonoBehaviour
{
    public static MapManager Instance;

    private void Awake()
    {
        if (Instance != null && Instance != this)
        {
            Destroy(gameObject);
        }
        else
        {
            Instance = this;
            DontDestroyOnLoad(this);
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
    
    [Header("Nodes")]
    //current node's type
    public Node currentNodeType;

    //list of nodemap game objects
    public List<GameObject> nodeMaps = new List<GameObject>();
    public List<GameObject> sectorMaps = new List<GameObject>();

    //planet struct for planet location and movement
    public struct PlanetStruct
    {
        public Node node;
        public Sector location;
        public int speed;
        //public Color color;
        //list of the sectors in order 
        public List<Sector> path;
        public Sprite sprite;

        public bool visited;
    }
    
    public GameObject planet;
    public GameObject activeNodeMap;
    
    
    //array of planets for movement
    public PlanetStruct[] planets = new PlanetStruct[4];
    
    //current target planet
    public PlanetStruct targetPlanet;
    //current path index
    public int pathIndex = 0;
    
    private int planetIndex = 0;
    
    //current path 
    public List<Sector> currentPath = new List<Sector>();

    public Sprite[] planetSprites;
    
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
        
        //planets[0].color = new Color(0.627451f, 0.1254902f, 0.9411765f, 1f);
        //planets[1].color = Color.green;
        //planets[2].color = Color.red;
        //planets[3].color = Color.blue;
        
        planets[0].path = new List<Sector>();
        planets[1].path = new List<Sector>();
        planets[2].path = new List<Sector>();
        planets[3].path = new List<Sector>();
        
        planets[0].visited = false;
        planets[1].visited = false;
        planets[2].visited = false;
        planets[3].visited = false;
        
        planets[0].sprite = planetSprites[0];
        planets[1].sprite = planetSprites[1];
        planets[2].sprite = planetSprites[2];
        planets[3].sprite = planetSprites[3];
        
        EventBus.Instance.enemyDefeated.AddListener(OnEnemyDefeated);
        EventBus.Instance.leftShop.AddListener(OnLeftShop);
    }
    

    // Update is called once per frame
    void Update()
    {
        //just for testing
        /*if (Input.GetKeyDown(KeyCode.LeftShift))
        {
            MovePlanets();
        }*/
    }
    
    /// <summary>
    /// Updates the map of nodes in sector map with current planet locations and current active constellations
    /// </summary>
    public void UpdateNodeMap()
    {
        //Debug.Log("UpdateNodeMap called and active nodemap is " + activeNodeMap);
        //for each node map in the scene
        foreach (GameObject nodeMap in nodeMaps)
        {
            nodeMap.GetComponent<Constellation>().CheckIfActive(); ;
            //if it is active
            if (activeNodeMap == null && nodeMap.GetComponent<Constellation>().isActive)
            {
                var sectorMapScene = SceneManager.GetSceneByName("SectorMap");
                //Debug.Log("instantiating node map");
                //instantiate it 
                activeNodeMap = Instantiate(nodeMap);
                SceneManager.MoveGameObjectToScene(activeNodeMap, sectorMapScene);
                var rootObjects = sectorMapScene.GetRootGameObjects(); // TODO: FOR SOME REASON THIS LITERALLY ONLY RETURNS THE MAP OBJECT I"M GOING INSANE
                foreach (var rootObj in rootObjects)
                {
                    // Debug.Log(rootObj.name);
                    if (rootObj.name == "SectorMap Viewport")
                    {
                        activeNodeMap.transform.SetParent(rootObj.transform);
                    }
                }
                // activeNodeMap.transform.SetParent(GameObject.Find("SectorMap Viewport").transform);
                //Debug.Log("setting " + nodeMap.name + " active");
            } 
        }
        
        UpdatePlanetNodes();
    }

    /// <summary>
    /// Updates the constellations in the Main Map 
    /// </summary>
    public void UpdateMainMap()
    {
        UpdatePlanetPaths();
        UpdatePlanetNodes();
    }

    public void LoadSectorsInMainMap()
    {
        foreach (GameObject sectorMap in sectorMaps)
        {
            sectorMap.transform.localPosition = new Vector3(0, 0, -2);

            var mapScene = SceneManager.GetSceneByName("MainMap");
            var map = Instantiate(sectorMap);
            SceneManager.MoveGameObjectToScene(map.gameObject, mapScene);
            var rootObjects = mapScene.GetRootGameObjects();
            foreach (var rootObj in rootObjects)
            {
                if (rootObj.name == "Map Viewport")
                {
                    map.transform.parent = rootObj.transform;
                }
            }
        }
        UpdateMainMap();
    }

    /// <summary>
    /// Sets any clickable planet nodes active in the proper sectors
    /// </summary>
    public void UpdatePlanetNodes()
    {
        Debug.Log("Updated planet nodes");
        //for every planet
        for (int i = 0; i < planets.Length; i++)
        {
            //if we're in the main map 
            if (SceneManager.GetSceneByName("MainMap").isLoaded)
            {
                Debug.Log("Main map is loaded");
                //for every sector map
                foreach (GameObject sectorMap in sectorMaps)
                {
                    Debug.Log(sectorMap.name + " has been updated");
                    
                    //and if a planet is there
                    if (planets[i].location == sectorMap.GetComponent<Constellation>().sector)
                    {
                        Debug.Log("A planet " + planets[i].node +  " is in " + sectorMap.name);
                        //find the planet child
                        GameObject sectorPlanet = sectorMap.GetComponent<Constellation>().mainmapPlanet;
                        //set its node
                        sectorPlanet.GetComponent<Planet>().thisPlanet = planets[i].node;
                        //and its color 
                        //sectorPlanet.GetComponent<Planet>().color = planets[i].color;
                        //and its sprite
                        sectorPlanet.GetComponent<Planet>().sr.sprite = planets[i].sprite;
                        //and its status
                        sectorPlanet.GetComponent<Planet>().UpdateVisitedStatus(planets[i].visited);
                        sectorPlanet.SetActive(true);
                        Debug.Log("Planet node updated. " + planets[i].node + " visited status: " + planets[i].visited + " and has set the node to: " + sectorPlanet.GetComponent<Planet>().visited);
                    }
                }
            }
            
            //if we're in the sector map
            if (SceneManager.GetSceneByName("SectorMap").isLoaded)
            {
                //and this planet is in the current sector and it is the target planet
                if (planets[i].location == sector && planets[i].node == targetPlanet.node)
                {
                    //TODO: figure out setting this where i have them in the node map prefab
                    
                    //set its node
                    planet.GetComponent<Planet>().thisPlanet = planets[i].node;
                    //and its color 
                    //planet.GetComponent<Planet>().UpdateColor(planets[i].color);
                    //and its sprite
                    planet.GetComponent<Planet>().UpdateSprite(planets[i].sprite);
                    //make it unavailable
                    planet.GetComponent<Planet>().MakeUnavailable();
                    
                    
                    //instantiate it
                    Debug.Log("instantiated planet");
                    var newPlanet = Instantiate(planet);
                    SceneManager.MoveGameObjectToScene(newPlanet, SceneManager.GetSceneByName("SectorMap"));
                    var rootGameObjects = SceneManager.GetSceneByName("SectorMap").GetRootGameObjects();
                    foreach (var rootObj in rootGameObjects)
                    {
                        if (rootObj.name == "SectorMap Viewport")
                        {
                            newPlanet.transform.SetParent(rootObj.transform);
                        }
                    }
                }
            }
        }
    }

    /// <summary>
    /// Changes planet location between runs according to their speed
    /// </summary>
    public void MovePlanets()
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

    /// <summary>
    /// Sets each individual planet's path for use in UI and navigation
    /// </summary>
    public void UpdatePlanetPaths()
    {
        // Debug.Log("Updating planet path");
        //for each planet 
        for (int i = 0; i < planets.Length; i++)
        {
            //checks the distance between your current sector and that planet
            int distance = sector -  planets[i].location;
            //Debug.Log(planets[i].node + " is " + distance + " sectors away");

            if (distance > 0 && planets[i].path.Count < distance)
            {
                //increment thru the enum of sectors negatively until u get to the destination
                for (Sector s = sector; s > planets[i].location; s--)
                {
                    planets[i].path.Add(s - 1);
                }
                for (int j = 0; j < planets[i].path.Count; j++)
                {
                    //Debug.Log(planets[i].node + " path includes " + planets[i].path[j]);
                }
            } else if (distance < 0 & planets[i].path.Count < Mathf.Abs(distance))
            {
                //increment thru the enum of sectors negatively until u get to the destination
                for (Sector s = sector; s < planets[i].location; s++)
                {
                    planets[i].path.Add(s + 1);
                }
                for (int j = 0; j < planets[i].path.Count; j++)
                {
                    //Debug.Log(planets[i].node + " path includes " + planets[i].path[j]);
                }
            } else if (distance == 0 &&  planets[i].path.Count < 1)
            {
                planets[i].path.Add(sector);
            } 
        }
    }

    public void SetCurrentPath(Node clickedNode)
    {
        //for each planet struct in the list 
        for (int i = 0; i < planets.Length; i++)
        {
            //if the planet node is the same as the one clicked
            if (planets[i].node == clickedNode)
            {
                //the target planet is that planet struct
                targetPlanet = planets[i];
                //its path is the current path
                currentPath = planets[i].path;
                
                planetIndex = i;
                
                //the path index is 0 
                pathIndex = 0;
                //and the sector is the first one in that path 
                sector = currentPath[pathIndex];
                
                //Debug.Log("Path set, headed to " + targetPlanet.node + " starting with sector " + currentPath[pathIndex] + " path length is " + currentPath.Count);
            }
        }
    }

    public void AdvanceThroughPath()
    {
        Debug.Log("AdvanceThroughPath");
        //if the path index is less than or equal to the current size of the path
        if (pathIndex < currentPath.Count - 1)
        {
            //increment the path index
            pathIndex++;
            
            //set the current sector to that index 
            sector = currentPath[pathIndex];
            Destroy(activeNodeMap);
            Debug.Log("Destroyed active node map:" + activeNodeMap.name);
            //Debug.Log("Current path length: " + currentPath.Count + " current sector: " + sector + "path index is " + pathIndex);
        }
           
    }

    private void OnEnemyDefeated()
    {
        if (SceneManager.GetSceneByName("SectorMap").isLoaded)
        {
            GoToSectorMap();
        }
        else
        {
            GoToMainMap();
        }
    }

    private void OnLeftShop()
    {
        SceneManager.UnloadSceneAsync("Shop");
        
        if (SceneManager.GetSceneByName("SectorMap").isLoaded)
        {
            GoToSectorMap();
        }
        else
        {
            GoToMainMap();
        }
    }
    
    public void GoToEncounterScene(MapNode.Node myNode)
    {
        Debug.Log("Starting "  + myNode + " scene");
        var sectorMap = SceneManager.GetSceneByName("SectorMap");
        var mainMap = SceneManager.GetSceneByName("MainMap");
        var narrScene = SceneManager.GetSceneByName("NarrativePrototype");
        var shopScene = SceneManager.GetSceneByName("Shop");
        
        SetActiveScene(sectorMap, false);
        
        switch (myNode)
        {
            case MapNode.Node.Combat:
                EventBus.Instance.newCombatEncounterStarted.Invoke();
                break;
            case MapNode.Node.Story:
                if (narrScene.isLoaded)
                {
                    SetActiveScene(narrScene, true);
                }
                else
                {
                    SceneManager.LoadScene("NarrativePrototype", LoadSceneMode.Additive);
                }
                break;
            case MapNode.Node.Shop:
                if (shopScene.isLoaded)
                {
                    SetActiveScene(shopScene, true);
                }
                else
                {
                    SceneManager.LoadScene("Shop", LoadSceneMode.Additive);
                }
                break;
        }
    }

    public void SetActiveScene(Scene scene, bool setActive)
    {
        var rootGameObjects = scene.GetRootGameObjects();
        foreach (var go in rootGameObjects)
        {
            go.SetActive(setActive);
        }
    }

    public void GoToSectorMap()
    {
        var sectorMap = SceneManager.GetSceneByName("SectorMap");
        var mainMap = SceneManager.GetSceneByName("MainMap");
        var narrScene = SceneManager.GetSceneByName("NarrativePrototype");


        if (mainMap.isLoaded)
        {
            SetActiveScene(mainMap, false);
            SceneManager.UnloadSceneAsync("MainMap");
        }
        if (narrScene.isLoaded)
        {
            // SetActiveScene(narrScene, false);
            SceneManager.UnloadSceneAsync(narrScene);
        }
        if (sectorMap.isLoaded)
        {
            SetActiveScene(sectorMap, true);

            if (activeNodeMap == null)
            {
                UpdateNodeMap();
            };
        }
        else
        {
            StartCoroutine(LoadAndSetSectorMap());
        }
    }

    private IEnumerator LoadAndSetSectorMap()
    {
        SceneManager.LoadScene("SectorMap", LoadSceneMode.Additive);
        yield return null;
        UpdateNodeMap();
    }
    
    public void GoToMainMap()
    {
        var sectorMap = SceneManager.GetSceneByName("SectorMap");
        var mainMap = SceneManager.GetSceneByName("MainMap");
        var narrScene = SceneManager.GetSceneByName("NarrativePrototype");

        if (sectorMap.isLoaded)
        {
            SceneManager.UnloadSceneAsync("SectorMap");
        }
        if (mainMap.isLoaded) // This should only happen once at the beginning. If we ever have to unload the map, change this check
        {
            SetActiveScene(sectorMap, false);
            // SetActiveScene(narrScene, false);
            SetActiveScene(mainMap, true);
            SceneManager.UnloadSceneAsync(narrScene);
        }
        else
        {
            SceneManager.LoadScene("MainMap", LoadSceneMode.Additive);
        }
    }
}
