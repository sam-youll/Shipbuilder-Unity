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
    
    /// <summary>
    /// Color Management
    /// </summary>
    //colors by node type
    private Dictionary<NodeType, Color> colors = new Dictionary<NodeType, Color>()
    {
        { NodeType.Combat , Color.yellow},
        { NodeType.Story, Color.cyan},
        { NodeType.Shop, Color.magenta},
    };
    
    //this node's sprite renderer
    private SpriteRenderer sr;
    
    //this node's color
    private Color color;

    [Header("Navigation")]

    //if this node is an initial option in the constellation
    public bool initial;
    
    //the list of nodes that you can travel to from this node
    public List<Node> nextNodes = new List<Node>();

    //whether this node is available to travel to
    public bool isAvailable = false;

    
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        //TODO: create function to determine node type at scene start based on sector and probability
        
        
        sr = GetComponent<SpriteRenderer>();
        color = sr.color;
        color = colors[type];
        if (!initial)
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
        //TODO: move this somewhere it'll work and hold info between scenesd
        if (Input.GetKeyDown(KeyCode.Space))
        {
            if (isAvailable)
            {
                MakeUnavailable();
                AdvanceToNextNode();
                //Debug.Log("Advancing from " + this.name + " to " + nextNodes[0].name);
            }
        }
    }

    public void MakeAvailable()
    {
        isAvailable = true;
        color.a = 1;
        sr.color = color;
    }

    public void MakeUnavailable()
    {
        isAvailable = false;
        color.a = 0.2f;
        sr.color = color;
    }

    public void AdvanceToNextNode()
    {
        foreach (Node node in nextNodes)
        {
            if (node != null)
            {
                node.MakeAvailable();
            }
        }
    }
    
    
    void OnMouseDown()
    {
        if (isAvailable)
        {
            if (type == NodeType.Combat)
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
            }
        }
        
    }
    
    //these probably should move to eventbus 
    public void GoToCombat()
    {
        SceneManager.LoadScene("Rack");
    }
    
    public void GoToStory()
    {
        //TODO: update when we have a narrative scene
        SceneManager.LoadScene("NarrativePrototype");
    }

    public void GoToShop()
    {
        //TODO: update when we have a scene for shop
        //SceneManager.LoadScene("Shop");
    }

    
}
