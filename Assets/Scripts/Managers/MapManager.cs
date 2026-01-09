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
    
    public Sector sector;

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
    
    public Node node;

    //corresponds to each node's nodeIndex - which stage of the map is avail
    public int progressIndex;
    
    //should probably add stuff later to track what planets visited vs not, if a planet is targeted, etc
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        progressIndex = 0;
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void AdvanceNodeProgress()
    {
        progressIndex++;
        //need to add some logic for picking branch here probs
    }
    
}
