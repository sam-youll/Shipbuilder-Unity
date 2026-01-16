using UnityEngine;
using UnityEngine.SceneManagement;

public class Planet : MapNode
{
    //which planet this is
    public MapManager.Node thisPlanet;

    //whether the planet is here
    public bool planetHere = false;

    //this planet's gameobject
    public GameObject planetObject;
    
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        //sets this object's sprite renderer
        sr = gameObject.GetComponent<SpriteRenderer>();
        //sets planet node type - it will always start as a story node
        node = Node.Story;
        //set this planet's color
        sr.color = color;
        //Debug.Log("planet's color " + color);

        //if it's instantiated in the sector map, it's here
        if (SceneManager.GetActiveScene() == SceneManager.GetSceneByName("SectorMap"))
        {
            planetHere = true;
        }
            
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    /// <summary>
    /// Updates planet color
    /// </summary>
    /// <param name="newColor"></param>
    public void UpdateColor(Color newColor)
    {
        //Debug.Log("new color: " + newColor);
        color = newColor;
        sr.color = color;
    }

    /// <summary>
    /// Updates whether this planet has been visited and sets its availability in main map accordingly
    /// </summary>
    /// <param name="newStatus"></param>
    public void UpdateVisitedStatus(bool newStatus)
    {
        visited = newStatus;
        if (visited)
        {
            MakeUnavailable();
        }
    }
    
}
