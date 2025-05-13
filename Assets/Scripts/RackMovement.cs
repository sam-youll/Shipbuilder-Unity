using System;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;
using UnityEngine.Events;
using UnityEngine.Rendering;

public class RackMovement : MonoBehaviour
{
    public GameObject snapSquare;
    private Camera cam;
    private bool isMouseDragging;
    private Vector3 dragOffset;
    private Vector3 dragStartPos;
    private Vector3 lastValidPos;
    public float dragHeight = 1;
    public bool canGoInInventory;
    private bool isOverInventory;
    private bool isInInventory;
    public GameObject myModuleRack;
    private Transform lastParent;
    
    public UnityEvent bodyClick;
    public UnityEvent jackClick;
    public UnityEvent inventoryEnter;
    public UnityEvent inventoryExit;
    public bool oddSize;
    private static Vector2[] dirs = {Vector2.up, Vector2.right, Vector2.down, Vector2.left};
    private Vector3 lastInvPos;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        if (transform.parent.GetComponent<ModuleRack>() != null)
        {
            myModuleRack = transform.parent.gameObject;
        }
        else if (transform.parent.GetComponent<Inventory>() != null)
        {
            isInInventory = true;
        }
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
            if (isOverInventory)
            {
                myPos.z -= 3;
            }
            transform.position = myPos;
            
            // set potential position of snap square
            var snappedPos = new Vector2
            {
                x = Mathf.Round(mousePos.x),
                y = Mathf.Round(mousePos.y)
            };
            if (oddSize)
            {
                snappedPos = new Vector2
                {
                    x = Mathf.Floor(mousePos.x) + .5f,
                    y = Mathf.Floor(mousePos.y) + .5f
                };
            }
            // check for overlap, then move if needed
            for (int i = 0; i < 100; i++) // basically a while loop
            {
                if (IsOverlapping(snapSquare.GetComponent<Collider2D>(), snappedPos)) // THIS IS PROBABLY A BAD IDEA
                {
                    // if (OverlapCheck(snappedPos, new Vector2(.5f, .5f)).GetComponent<Conveyor>() != null)
                    // {
                    //     isOverConveyor = true;
                    //     break;
                    // }
                    // isOverConveyor = false;


                    // TODO: THIS BASICALLY NEEDS TO BE A FLOOD FILL ALGO BUT I DON'T WANT TO DO THAT RIGHT NOW
                    var roundedMousePos = new Vector2
                    {
                        x = Mathf.Round(mousePos.x),
                        y = Mathf.Round(mousePos.y)
                    };
                    var dir = ((Vector2)transform.position - roundedMousePos).normalized;
                    var dots = new float[3];
                    for (var j = 0; j < 3; j++)
                    {
                        dots[j] = Vector2.Dot(dir, dirs[j]);
                    }
                    var highestDot = dots[0];
                    for (var j = 0; j < dots.Length; j++)
                    {
                        highestDot = Mathf.Max(highestDot, dots[j]);
                    }
                    dir = dirs[Array.IndexOf(dots, highestDot)];
                    snappedPos += dir;

                    if (i == 99)
                    {
                        Debug.Log("too many loop");
                        snappedPos = lastValidPos;
                    }
                }
                else
                {
                    lastValidPos = snappedPos;
                    break;
                }
            }
            // if (!IsOverlapping(snapSquare.GetComponent<Collider2D>()))
            // {
            //     isOverConveyor = false;
            // }

            var newPos = new Vector3(snappedPos.x, snappedPos.y, transform.position.z + .1f);
            if (isOverInventory)
            {
                newPos.z -= 3;
            }
            snapSquare.transform.position = newPos;
            
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
                
                // isInInventory = transform.parent == Inventory.Instance.transform;
                if (isOverInventory)
                {
                    isInInventory = true;
                    transform.SetParent(Inventory.Instance.transform);
                    var pos = transform.position;
                    pos.z = transform.parent.transform.position.z - 1f;
                    transform.position = pos;
                    inventoryEnter.Invoke();
                }
                else// if (isInInventory)
                {
                    var rackCheck = false;
                    var results = Physics2D.RaycastAll(mousePos, Vector2.zero);
                    foreach (var result in results)
                    {
                        if (result.collider.gameObject.GetComponent(typeof(ModuleRack)) != null)
                        {
                            // theoretically, this is the module rack I'm hovering over
                            transform.SetParent(result.collider.gameObject.transform);
                            var pos = transform.position;
                            pos.z = transform.parent.position.z - .1f;
                            transform.position = pos;
                            myModuleRack = result.collider.gameObject;
                            rackCheck = true;
                            isInInventory = false;
                            inventoryExit.Invoke();
                        }
                    }

                    if (!rackCheck)
                    {
                        if (isInInventory)
                        {
                            transform.SetParent(Inventory.Instance.transform);
                            transform.localPosition = lastInvPos;
                        }
                        else
                        {
                            transform.position = dragStartPos;
                        }
                    }
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
                        jackClick.Invoke();
                        break;
                    }

                    // if we don't hit a jack, but we do hit the body, turn on dragging
                    if (result.collider.gameObject.layer == LayerMask.NameToLayer("Rack Objects"))
                    {
                        if (result.collider.gameObject == gameObject)
                        {
                            if (isInInventory)
                            {
                                lastInvPos = transform.localPosition;
                            }
                            AudioManager.Instance.PickUpModuleSFX();
                            dragOffset = transform.position - mousePos;
                            snapSquare.SetActive(true);
                            isMouseDragging = true;
                            lastParent = transform.parent;
                            transform.SetParent(cam.transform);
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
        // Debug.Log("checking overlap");
        
        // are we on the rack
        var onRack = false;
        var colliding = false;
        
        var results = new List<Collider2D>();
        // we only care about checking against objects on the rack
        var filter = new ContactFilter2D
        {
            layerMask = LayerMask.GetMask("Rack Objects", "Module Racks")
        };
        // check the collider for overlaps on that layer
        coll.Overlap(pos, 0, filter, results);
        foreach (var result in results)
        {
            // Debug.Log(result.gameObject.name);
            // Debug.Log("colliding with " + result.gameObject.name + " at " + pos);
            // ignore self
            if (result.gameObject == gameObject)
                continue;
            if (result.gameObject.CompareTag("Bullet"))
                continue;
            if (result.gameObject == snapSquare)
                continue;
            if (result.gameObject.layer == LayerMask.NameToLayer("Module Racks"))
            {
                if (InsideCol(coll, result))
                {
                    // Debug.Log("inside rack");
                }
                // Debug.Log("I hit a " + result.gameObject.name);
                onRack = true;
                continue;
            }
            if (result.CompareTag("Weapon"))
                continue;
            if (result.gameObject.GetComponent<ModuleRack>() != null)
                continue;
            if (result.gameObject.GetComponent<Inventory>() != null)
                continue;
            // if (!InsideCol(coll, result))
            // {
            //     Debug.Log("not inside collider");
            //     continue;
            // }
            
            colliding = true;
            // otherwise if we hit something, return true
        }
        // receiving no hits means false
        if (!onRack && !isInInventory && !isOverInventory)
        {
            // Debug.Log("My module rack is " + myModuleRack.gameObject.name + " on " + myModuleRack.transform.parent.gameObject.name);
            return true;
        }

        if (colliding)
        {
            // Debug.Log("colliding");
            return true;
        }
        else
        {
            return false;
        }
    }
    
    bool InsideCol(Collider2D mycol, Collider2D other)
    {
        if (other.bounds.Contains(mycol.bounds.min)
            && other.bounds.Contains(mycol.bounds.max))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}
