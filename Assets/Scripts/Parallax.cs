using UnityEngine;

public class Parallax : MonoBehaviour
{
    public GameObject backgroundLayerBack;
    public GameObject backgroundLayerMid;
    public GameObject backgroundLayerFront;

    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        var backPos = backgroundLayerBack.transform.position;
        var midPos = backgroundLayerMid.transform.position;
        var frontPos = backgroundLayerFront.transform.position;
        
        backPos.x -= 0.1f * Time.deltaTime;
        if (backPos.x < 0)
        {
            backPos.x = 30; 
        }
        midPos.x -= 0.15f * Time.deltaTime;
        if (midPos.x < 0)
        {
            midPos.x = 30;
        }
        frontPos.x -= 0.2f * Time.deltaTime;
        if (frontPos.x < 0)
        {
            frontPos.x = 30;
        }
        
        backgroundLayerBack.transform.position = backPos;
        backgroundLayerMid.transform.position = midPos;
        backgroundLayerFront.transform.position = frontPos;
    }
}
