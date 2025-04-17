using System;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;
using UnityEngine.Events;

public class RackMovement : MonoBehaviour
{
    public GameObject snapSquare;
    private Camera cam;
    private bool isMouseDragging;
    private Vector3 dragOffset;
    private Vector3 dragStartPos;
    public float dragHeight = 1;
    public bool canGoInInventory;
    private bool isOverInventory;
    
    public UnityEvent bodyClick;
    public UnityEvent jackClick;
    public UnityEvent inventoryEnter;
    public UnityEvent inventoryExit;
    
    private static Vector2[] dirs = {Vector2.up, Vector2.right, Vector2.down, Vector2.left};
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        cam = Camera.main;
    }

    // Update is called once per frame
    void Update()
    {
        // convert mouse position to world coordinates
        var mousePos = cam.ScreenToWorldPoint(Input.mousePosition);

        if (isMouseDragging)
        {
            // add offset from center of module to mouse position
            mousePos += dragOffset;
            // set position
            var myPos = mousePos;
            myPos.z -= dragHeight;
            transform.position = myPos;
            
            // set potential position of snap square
            var snappedPos = new Vector2
            {
                x = Mathf.Round(mousePos.x),
                y = Mathf.Round(mousePos.y)
            };
            // check for overlap, then move if needed
            for (int i = 0; i < 100; i++)
            {
                if (IsOverlapping(snapSquare.GetComponent<Collider2D>(), snappedPos)) // THIS IS PROBABLY A BAD IDEA
                {
                    // if (OverlapCheck(snappedPos, new Vector2(.5f, .5f)).GetComponent<Conveyor>() != null)
                    // {
                    //     isOverConveyor = true;
                    //     break;
                    // }
                    // isOverConveyor = false;


                    // var dir = (snappedPos - (Vector2)dragStartPos).normalized;
                    // var dots = dirs.ToArray();
                    // Array.ForEach(dots, x => Vector2.Dot(x, dir));
                    // dir = dots.Max();
                    var dir = new Vector2(1, 0); // TODO: Make this directional based on diff between snap pos and pos
                    // Debug.Log(snapSquare.transform.position);
                    snappedPos += dir;

                    if (i == 99)
                    {
                        Debug.Log("too many loop");
                        snappedPos = dragStartPos;
                    }
                }
                else
                {
                    break;
                }
            }
            // if (!IsOverlapping(snapSquare.GetComponent<Collider2D>()))
            // {
            //     isOverConveyor = false;
            // }
            
            snapSquare.transform.position = snappedPos;
            
            HoverInventory();
            
            // drop module
            if (Input.GetMouseButtonUp(0))
            {
                // reset mouse drag
                isMouseDragging = false;
                transform.position = snapSquare.transform.position;
                snapSquare.SetActive(false);
                dragOffset = Vector3.zero;

                AudioManager.Instance.PutDownModuleSFX();
            
                // var adjPos = transform.position;
                // adjPos.z = 0;
                // if (isOverInventory)
                // {
                //     adjPos.z -= 3;
                // }
                // transform.position = adjPos;

                // if (isOverConveyor)
                // {
                //     var conveyor = OverlapCheck(snappedPos, new Vector2(.5f, .5f));
                //     onConveyor = true;
                //     transform.SetParent(conveyor.transform);
                //     conveyor.GetComponent<Conveyor>().OnModuleAttached(this);
                // }
                
                var isInInventory = transform.parent == Inventory.Instance.transform;
                if (!isInInventory && isOverInventory)
                {
                    isInInventory = true;
                    transform.SetParent(Inventory.Instance.transform);
                    inventoryEnter.Invoke();
                }
                else if (isInInventory && !isOverInventory)
                {
                    isInInventory = false;
                    transform.SetParent(ModuleRack.Instance.transform);
                    inventoryExit.Invoke();
                }
            }
        }
        
        // when the left mb is clicked
        if (Input.GetMouseButtonDown(0))
        {
            // we do a lil raycast
            var results = Physics2D.RaycastAll(mousePos, Vector2.zero);
            
            var isItMe = false;
            foreach (var r in results)
            {
                if (r.collider.gameObject == gameObject)
                {
                    isItMe = true;
                }
            }
            if (isItMe)
            {
                foreach (var result in results)
                {
                    // if we hit a jack, invoke that unity event
                    if (result.collider.gameObject.layer == LayerMask.NameToLayer("Jacks"))
                    {
                        Debug.Log(result.collider.gameObject.name);
                        jackClick.Invoke();
                        break;
                    }

                    // if we don't hit a jack, but we do hit the body, turn on dragging
                    if (result.collider.gameObject.layer == LayerMask.NameToLayer("Rack Objects"))
                    {
                        Debug.Log(result.collider.gameObject.name);
                        if (result.collider.gameObject == gameObject)
                        {
                            AudioManager.Instance.PickUpModuleSFX();
                            dragOffset = transform.position - mousePos;
                            snapSquare.SetActive(true);
                            isMouseDragging = true;
                            bodyClick.Invoke();
                            // var adjPos = transform.position;
                            // adjPos.z = -1;
                            // transform.position = adjPos;
                            dragStartPos = transform.position;
                        }
                        // if (onConveyor)
                        // {
                        //     var snappedPos = new Vector2
                        //     {
                        //         x = Mathf.Round(mousePos.x),
                        //         y = Mathf.Round(mousePos.y)
                        //     };
                        //     var conveyor = OverlapCheck(snappedPos, new Vector2(.5f, .5f));
                        //     onConveyor = false;
                        //     transform.SetParent(ModuleRack.Instance.transform);
                        //     conveyor.GetComponent<Conveyor>().OnModuleDetached(this);
                        // }
                    }
                }
            }
        }
    }
    
    void HoverInventory()
    {
        if (!canGoInInventory)
        {
            return;
        }
        
        if (Inventory.Instance.sr.color == Inventory.Instance.highlightColor)
        {
            if (!Inventory.Instance.isPulledDown)
            {
                Inventory.Instance.isPulledDown = true;
            }

            isOverInventory = true;
        }
        else
        {
            if (Inventory.Instance.isPulledDown)
            {
                Inventory.Instance.isPulledDown = false;
            }
            isOverInventory = false;
        }
    }

    /// <summary>
    /// Function for checking if the snap square is overlapping any other rack objects.
    /// </summary>
    /// <param name="coll">The collider of the snap square.</param>
    /// <param name="pos">Position of collider/rigidbody.</param>
    /// <returns>True or false.</returns>
    private bool IsOverlapping(Collider2D coll, Vector2 pos)
    {
        var results = new List<Collider2D>();
        // we only care about checking against objects on the rack
        var filter = new ContactFilter2D
        {
            layerMask = LayerMask.GetMask("Rack Objects")
        };
        // check the collider for overlaps on that layer
        coll.Overlap(pos, 0, filter, results);
        foreach (var result in results)
        {
            Debug.Log(result.gameObject.name);
            if (result.gameObject.layer != LayerMask.NameToLayer("Rack Objects"))
                continue;
            // ignore self
            if (result.gameObject == gameObject)
                continue;
            if (result.gameObject == snapSquare)
                continue;
            // otherwise if we hit something, return true
            return true;
        }
        // no hits means false
        return false;
    }
}
