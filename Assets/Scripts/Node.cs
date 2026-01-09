using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Node : MonoBehaviour
{
    public enum NodeType
    {
        Combat,
        Story,
        Shop
    }
    
    public NodeType type;

    public int nodeIndex;

    private Dictionary<NodeType, Color> colors = new Dictionary<NodeType, Color>()
    {
        { NodeType.Combat , Color.yellow},
        { NodeType.Story, Color.cyan},
        { NodeType.Shop, Color.magenta},
    };
    

    private SpriteRenderer sr;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        //TODO: create function to determine node type at scene start based on sector and probability
        
        //TODO: make node available based on nodeIndex matching w map manager
        
        sr = GetComponent<SpriteRenderer>();
        sr.color = colors[type];
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    void OnMouseDown()
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
