using System.Collections.Generic;
using UnityEngine;

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
        Null,
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
        Null,
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
    
    //current node
    public Node node;

    //list of nodemap game objects
    public List<GameObject> nodeMaps = new List<GameObject>();
    
    //should probably add stuff later to track what planets visited vs not, if a planet is targeted, etc
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
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
    
}
