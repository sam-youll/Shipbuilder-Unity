using System;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using Random = System.Random;

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

    public float combatBaseProbability = 60;
    public float storyBaseProbability = 30;
    public float shopBaseProbability = 10;
    
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        //TODO: create function to determine node type at scene start based on sector and probability
        
        SetNodeType();
        
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
                if (TryGetComponent(out Planet planet))
                {
                    for (int i = 0; i < MapManager.Instance.planets.Length; i++)
                    {
                        Debug.Log(MapManager.Instance.planets[i].node);
                        if (MapManager.Instance.planets[i].node == planet.thisPlanet)
                        {
                            MapManager.Instance.planets[i].visited = true;
                            Debug.Log(MapManager.Instance.planets[i].node + " is visited. " + MapManager.Instance.planets[i].visited);
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

                    foreach (Constellation nodeMap in FindObjectsByType<Constellation>(FindObjectsSortMode.InstanceID))
                    {
                        Destroy(nodeMap.gameObject);
                    }
                    
                    
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

    private void SetNodeType()
    {
        if (SceneManager.GetActiveScene() == SceneManager.GetSceneByName("SectorMap"))
        {
            combatBaseProbability = 60;
            storyBaseProbability = 30;
            shopBaseProbability = 10;
            //setting node types based on variable probability multipliers
            float combatProbability = combatBaseProbability * GetComponentInParent<Constellation>().combatMultiplier;
            float storyProbability = storyBaseProbability *  GetComponentInParent<Constellation>().storyMultiplier;
            float shopProbability =  shopBaseProbability *  GetComponentInParent<Constellation>().shopMultiplier;
            
            //Debug.Log(" combat probability: " + combatProbability + " story probability: " + storyProbability + " shop probability: " + shopProbability);
            
            
            //creating an array of probabilities to be sorted after they've been modified
            float[] probabilities = new float[]
            {
                combatProbability,
                storyProbability,
                shopProbability
            };
            
            //sorting the probabilities so we know which is smaller and which is larger
            Array.Sort(probabilities);
            
            
            //defining node types by their probability
            Dictionary<NodeType, float> nodeTypesByProbability = new Dictionary<NodeType, float>()
            {
                {NodeType.Combat, combatProbability},
                {NodeType.Story, storyProbability},
                {NodeType.Shop, shopProbability}
                
            };
            

            //see if the largest probable number is larger than 100
            float max = Mathf.Max(100, probabilities[2]);
            
            //roll for a number between 0 and the largest possible number
            float typeRoll = UnityEngine.Random.Range(0, max);
            float lookupValue = typeRoll;

            //if it's less than or equal to the lowest probability
            if (typeRoll < probabilities[0])
            {
                //then it's the lowest probable option
                lookupValue = probabilities[0];
                //Debug.Log("Roll was " + typeRoll + " and lookup value was " + lookupValue);
            } 
            //if it's larger than the lowest probability but less than the next largest probability
            //(plus the previous probability to make its percentage more real)
            else if (typeRoll < (probabilities[1] + probabilities[0]))
            {
                //then it's that option 
                lookupValue = probabilities[1];
                //Debug.Log("Roll was " + typeRoll + " and lookup value was " + lookupValue);
            } 
            //but if it's between the second larges probability and the maximum number
            else if (typeRoll > probabilities[1] && typeRoll < max)
            {
                //then its the most likely option
                lookupValue = probabilities[2];
                //Debug.Log("Roll was " + typeRoll + " and lookup value was " + lookupValue);
            }

            foreach (NodeType nodeType in nodeTypesByProbability.Keys)
            {
                if (nodeTypesByProbability[nodeType] == lookupValue)
                {
                    type = nodeType;
                }
            }



        }
    }
    
    
}
