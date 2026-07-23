using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.UI;

public class GameCursor : MonoBehaviour
{
    [Header("Sprites")]
    [SerializeField] private Sprite spritePoint;
    [SerializeField] private Sprite spriteOpen;
    [SerializeField] private Sprite spriteClose;
    private RectTransform rt;
    
    private Image image;
    
    public enum State
    {
        Point,
        Open,
        Close
    }

    public State state { get; private set; }
    public GameObject heldObject;

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        image = GetComponentInChildren<Image>();
        rt = GetComponent<RectTransform>();
    }

    // Update is called once per frame
    void Update()
    {
        transform.position = Input.mousePosition;
    }

    public void SetState(State targetState)
    {
        state = targetState;
        switch (state)
        {
            case State.Point:
                image.sprite = spritePoint;
                break;
            case State.Open:
                image.sprite = spriteOpen;
                break;
            case State.Close:
                image.sprite = spriteClose;
                break;
        }
        rt.pivot = image.sprite.pivot / image.sprite.rect.size;
    }
}
