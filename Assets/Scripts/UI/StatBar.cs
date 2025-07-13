using System;
using UnityEngine;

public class StatBar : MonoBehaviour
{
    public float value = 1;
    public float lerpRate = 0.1f;

    private Vector2 startPos;
    private Vector2 startScale;

    public enum Direction
    {
        Down,
        Left,
        Right,
        Up
    }
    public Direction startingSide = Direction.Down;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        startPos = transform.localPosition;
        startScale = transform.localScale;
    }

    // Update is called once per frame
    void Update()
    {
        value = Mathf.Clamp(value, 0, 1);
        
        var myScale = transform.localScale;
        var myPos = transform.localPosition;
        float offset;
        
        switch (startingSide)
        {
            case Direction.Down:
                myScale.y = Mathf.Lerp(myScale.y, startScale.y * value, lerpRate);
                offset = startScale.y - myScale.y;
                myPos.y = startPos.y - (offset / 2);
                break;
            case Direction.Left:
                myScale.x = Mathf.Lerp(myScale.x, startScale.x * value, lerpRate);
                offset = startScale.x - myScale.x;
                myPos.x = startPos.x - (offset / 2);
                break;
            case Direction.Right:
                myScale.x = Mathf.Lerp(myScale.x, startScale.x * value, lerpRate);
                offset = startScale.x - myScale.x;
                myPos.x = startPos.x + (offset / 2);
                break;
            case Direction.Up:
                myScale.y = Mathf.Lerp(myScale.y, startScale.y * value, lerpRate);
                offset = startScale.y - myScale.y;
                myPos.y = startPos.y + (offset / 2);
                break;
        }
        
        transform.localScale = myScale;
        transform.localPosition = myPos;
    }

    private void FixedUpdate()
    {
        
    }
}
