using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Node : MonoBehaviour
{
    
    //the different types of nodes
    public enum NodeType
    {
        Combat,
        Story,
        Shop
    }
    
    [Header("Type")]
    
    //this node's type
    public NodeType type;
    
    [Header("Color")]
    //colors by node type
    private Dictionary<NodeType, Color> colors = new Dictionary<NodeType, Color>()
    {
        { NodeType.Combat , Color.yellow},
        { NodeType.Story, Color.cyan},
        { NodeType.Shop, Color.magenta},
    };
    
    
    //this node's sprite renderer
    public SpriteRenderer sr;
    
    //this node's color
    public Color color;

    [Header("Navigation")]

    //if this node is an initial option in the constellation
    public bool initial;
    
    //the list of nodes that you can travel to from this node
    public List<Node> nextNodes = new List<Node>();

    //whether this node is available to travel to
    public bool isAvailable = false;
    //whether this node is currently selected
    public bool isSelected = false;
    //whether this node has been visited 
    public bool visited = false;
    
    
    
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        //TODO: create function to determine node type at scene start based on sector and probability
        
        //getting spriterenderer to edit node appearance
        sr = GetComponent<SpriteRenderer>();
        //setting node color based on node type
        color = sr.color;
        color = colors[type];
        //darkening nodes if they're not available on scene load
        if (!initial || visited)
        {
            color.a = 0.2f;
        }
        else
        {
            MakeAvailable();
        }
        
        sr.color = color;
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    /// <summary>
    /// Makes nodes lit up and clickable
    /// </summary>
    public void MakeAvailable()
    {
        //sets node's availability
        isAvailable = true;
        //makes it fully lit up
        color.a = 1;
        sr.color = color;
    }

    /// <summary>
    /// Makes nodes greyed out and unclickable
    /// </summary>
    public void MakeUnavailable()
    {
        //set's node's availability and deselects it
        isAvailable = false;
        isSelected = false;
        //makes it lower opacity
        color.a = 0.2f;
        sr.color = color;
    }

    /// <summary>
    /// Makes the subsequent nodes in a selected path lit up and clickable
    /// </summary>
    public void AdvanceToNextNode()
    {
        //NODE CLEANUP
        //for each node in the constellation
        if (!CompareTag("Planet"))
        {
            foreach (Node externalNode in GetComponentInParent<Constellation>().nodes) 
            {
                //if that node was available but not selected
                if (externalNode.isAvailable && !externalNode.isSelected)
                {
                    //make it unavailable
                    externalNode.MakeUnavailable();
                }
                
            }
        }
        

        //if this node is selected or an initial node
        if (isSelected || initial)
        {
            //each node in the list of nodes that follow
            foreach (Node node in nextNodes)
            {
                //as long as it exists
                if (node != null)
                {
                    //and it hasn't been visited
                    if (!node.visited)
                    {
                        //it's made available
                        node.MakeAvailable();
                    }
                }
                //if the node that follows is a planet
                if (node.GetComponent<Planet>() != null)
                {
                    //Debug.Log("Planet found");
                    
                    GameObject instantiatedPlanet = GameObject.FindGameObjectWithTag("Planet");

                    if (instantiatedPlanet != null)
                    {
                        if (node.GetComponent<Planet>().planetHere)
                        {
                            instantiatedPlanet.GetComponent<Planet>().MakeAvailable();
                        }
                    }
                    
                    GameObject foundPlanet = GameObject.FindGameObjectWithTag("Planet");
                    //but the planet isn't there to click
                    if (foundPlanet == null)
                    {
                        //Debug.Log("Advancing to next path");
                        
                        //go to the next path and update the node map
                        MapManager.Instance.AdvanceThroughPath();
                        if (SceneManager.GetActiveScene() == SceneManager.GetSceneByName("SectorMap"))
                        {
                            MapManager.Instance.UpdateNodeMap();
                        }
                        
                    }
                }
            }
        }
        
    }
    
    
    void OnMouseDown()
    {
        Debug.Log("OnMouseDown");
        if (isAvailable)
        {
            //UNIVERSAL NODE BEHAVIOR
            //sets whatever was clicked to visited
            visited = true;
            //sets this to the currently selected node
            isSelected = true;
            //makes the next nodes available
            AdvanceToNextNode();
            //makes this node unavailable 
            MakeUnavailable();
            
            
            //PLANET CLICKING
            
            //if you're in the sector map
            if (SceneManager.GetActiveScene() == SceneManager.GetSceneByName("SectorMap"))
            {
                //and what you click on is a planet 
                if (GetComponent<Planet>() != null)
                {
                    for (int i = 0; i < MapManager.Instance.planets.Length; i++)
                    {
                        if (MapManager.Instance.planets[i].node == GetComponent<Planet>().thisPlanet)
                        {
                            MapManager.Instance.planets[i].visited = true;
                        }
                    }
                    Debug.Log("clicked a planet in sector map");
                    
                    //make sure the sector is here
                    MapManager.Instance.sector = MapManager.Instance.currentPath[MapManager.Instance.pathIndex];
                    //for each planet
                    for (int i = 0; i < MapManager.Instance.planets.Length; i++)
                    { 
                        //clear its list
                       MapManager.Instance.planets[i].path.Clear();
                    }
                    //clear the current path list
                    MapManager.Instance.currentPath.Clear();
                    //update the main map
                    MapManager.Instance.UpdateMainMap();
                    Debug.Log("path complete");
                    //load the main map
                    SceneManager.LoadScene("MainMap");
                    
                }
            }
            
            /*if (type == NodeType.Combat)
            {
                GoToCombat();
            }

            if (type == NodeType.Story)
            {
                GoToStory();
            }

            if (type == NodeType.Shop)
            {
                GoToShop();
            }*/
        }
        
    }
    
    //these probably should move to eventbus 
    /// <summary>
    /// Go to the combat scene
    /// </summary>
    public void GoToCombat()
    {
        SceneManager.LoadScene("Rack");
    }
    
    /// <summary>
    /// Go to the story scene
    /// </summary>
    public void GoToStory()
    {
        //TODO: update when we have a narrative scene
        SceneManager.LoadScene("NarrativePrototype");
    }

    /// <summary>
    /// Go to the shop scene
    /// </summary>
    public void GoToShop()
    {
        //TODO: update when we have a scene for shop
        //SceneManager.LoadScene("Shop");
    }

    
}
