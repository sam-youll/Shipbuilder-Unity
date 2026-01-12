using UnityEngine;

public class Planet : Node
{
    //the sector this planet obj exists in
    public MapManager.Sector sector;
    
    //which planet this is
    public MapManager.Node thisPlanet;

    private bool planetHere = false;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        //sets this object's sprite renderer
        sr = gameObject.GetComponent<SpriteRenderer>();
        //sets planet node type - it will always start as a story node
        type = NodeType.Story;
        //sets planet obj current sector
        sector = GetComponentInParent<Constellation>().sector;
        
        if (!planetHere)
        {
            color.a = 0;
        }
        
        
        //set this planet's color
        sr.color = color;
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void SetPlanet()
    {
        //for each planet in the array
        for (int i = 0; i < MapManager.Instance.planets.Length; i++)
        {
            //Debug.Log(MapManager.Instance.planets[i].node + "  is in " + MapManager.Instance.planets[i].location);
            
            //if there's a planet located in the currently available constellation
            if (MapManager.Instance.planets[i].location == sector)
            {
                //set this planet's node from the planet struct
                thisPlanet = MapManager.Instance.planets[i].node;
                //set this planet's color from the planet struct
                color = MapManager.Instance.planets[i].color;
                //note that a planet is here
                planetHere = true;
                //make it unavailable 
                MakeUnavailable();
            }
        }
    }
}
