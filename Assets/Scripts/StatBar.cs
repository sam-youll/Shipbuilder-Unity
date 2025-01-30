using System;
using UnityEngine;

public class StatBar : MonoBehaviour
{
    public float value = .2f;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void FixedUpdate()
    {
        var myScale = transform.localScale;
        myScale.y = Mathf.Lerp(myScale.y, value, .1f);
        transform.localScale = myScale;
        var myPos = transform.localPosition;
        var offset = 1 - transform.localScale.y;
        myPos.y = -(offset / 2);
        transform.localPosition = myPos;
    }
}
