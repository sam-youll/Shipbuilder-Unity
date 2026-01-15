using UnityEngine;
using UnityEngine.SceneManagement;

public class MapRabbit : MonoBehaviour
{
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        if (SceneManager.GetActiveScene().name == "MainMap")
        {
            MapManager.Instance.UpdateMainMap();
        }
        if (SceneManager.GetActiveScene().name == "SectorMap")
        {
            MapManager.Instance.UpdateNodeMap();
        }   
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
