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
        var backPos = backgroundLayerBack.transform.localPosition;
        var midPos = backgroundLayerMid.transform.localPosition;
        var frontPos = backgroundLayerFront.transform.localPosition;
        
        backPos.x -= 0.1f * Time.deltaTime;
        if (backPos.x < -7.5)
        {
            backPos.x = 0; 
        }
        midPos.x -= 0.15f * Time.deltaTime;
        if (midPos.x < -7.5)
        {
            midPos.x = 0;
        }
        frontPos.x -= 0.2f * Time.deltaTime;
        if (frontPos.x < -7.5)
        {
            frontPos.x = 0;
        }
        
        backgroundLayerBack.transform.localPosition = backPos;
        backgroundLayerMid.transform.localPosition = midPos;
        backgroundLayerFront.transform.localPosition = frontPos;
    }
}
