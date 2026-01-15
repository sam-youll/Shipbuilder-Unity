using TMPro;
using UnityEngine;

public class SectorMapTitle : MonoBehaviour
{

    public TextMeshPro title;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        title.text = MapManager.Instance.sector.ToString();
    }
}
