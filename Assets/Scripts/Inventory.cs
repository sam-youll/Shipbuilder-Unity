using System;
using UnityEngine;

public class Inventory : MonoBehaviour
{
    public static Inventory Instance;
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

    public Color defaultColor;
    public Color highlightColor;
    public Vector2 upPos;
    public Vector2 downPos;
    public bool isPulledDown = false;
    public SpriteRenderer sr;
    
    void Start()
    {
        sr = GetComponent<SpriteRenderer>();
        sr.color = defaultColor;
    }

    void Update()
    {
        if (Input.GetMouseButtonDown(0) && sr.color == defaultColor) // if click when not over collider
        {
            // close tray
            isPulledDown = false;
        }
        
        Vector2 mousePos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
        RaycastHit2D hit = Physics2D.Raycast(mousePos, Vector2.zero, Mathf.Infinity, LayerMask.GetMask("Inventory"));
        if (hit)
        {
            sr.color = highlightColor;
            if (Input.GetMouseButtonDown(0))
            {
                isPulledDown = true;
            }
        }
        else
        {
            sr.color = defaultColor;
        }
    }

    private void FixedUpdate()
    {
        if (isPulledDown)
        {
            if (transform.position.y > downPos.y)
            {
                var pos = transform.position;
                pos = Vector3.Lerp(pos, downPos, .2f);
                pos.z = -2;
                transform.position = pos;
            }
        }
        else
        {
            if (transform.position.y < upPos.y)
            {
                var pos = transform.position;
                pos = Vector3.Lerp(pos, upPos, .2f);
                pos.z = -2;
                transform.position = pos;
            }
        }
    }
    //
    // private void OnMouseEnter()
    // {
    //     sr.color = highlightColor;
    // }
    //
    // private void OnMouseExit()
    // {
    //     sr.color = defaultColor;
    // }
    //
    // private void OnMouseDown()
    // {
    //     isPulledDown = true;
    // }
}