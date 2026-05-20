using System;
using System.Collections.Generic;
using System.Linq;
using UnityEditor;
using UnityEngine;
using UnityEngine.Events;
using UnityEngine.Rendering;

public class RackMovement : MonoBehaviour
{
    [Header("Object References")]
    public GameObject snapSquare;
    public GameObject myModuleRack;
    private Camera cam;
    
    [Header("Drag Behavior")]
    public float dragHeight = 1;
    public bool canGoInInventory = true;
    private bool isOverInventory;
    public bool isInInventory;
    public Transform lastParent;
    private bool isMouseDragging;
    private Vector3 dragOffset;
    private Vector3 dragStartPos;
    private Vector3 lastValidPos;
    
    [HideInInspector] public UnityEvent bodyClick;
    [HideInInspector] public UnityEvent<GameObject> jackClick;
    [HideInInspector] public UnityEvent inventoryEnter;
    [HideInInspector] public UnityEvent inventoryExit;
    
    public bool oddSizeX;
    public bool oddSizeY;
    private static Vector2[] dirs = {Vector2.zero, Vector2.up, Vector2.right, Vector2.down, Vector2.left};
    private Vector3 lastInvPos;

    [Header("Temporary Debug Bullshit")] 
    public List<Collider2D> collisionResults;

    public UnityEvent destroyed;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        if (transform.parent.GetComponent<ModuleRack>() != null)
        {
            myModuleRack = transform.parent.gameObject;
        }
        else if (transform.parent.CompareTag("Inventory"))
        {
            isInInventory = true;
        }
        cam = Camera.main;
    }

    // Update is called once per frame
    void Update()
    {
        if (transform.parent.GetComponent<ShopSlot>() != null)
            return;
        
        if (isMouseDragging)
        {
            DragMove();
            
            if (Input.GetMouseButtonUp(0))
            {
                DropModule();
            }
            
        }
        
        // when the left mb is clicked
        if (Input.GetMouseButtonDown(0))
        {
            // pick up module if not also clicking a module component
            LeftClicky();
        }

        if (Input.GetMouseButtonDown(1))
        {
            RightClicky();
        }
        
        DrawBounds(GetComponent<Collider2D>().bounds, Color.green);
    }

    void LeftClicky()
    {
        if (Global.Instance.TopRaycastResult() == gameObject)
        {
            if (isInInventory)
            {
                inventoryExit.Invoke();
                InventoryManager.Instance.RemoveModule(gameObject);
            }
            AudioManager.Instance.PickUpModuleSFX();
            dragOffset = transform.position - Global.Instance.mousePos;
            snapSquare.SetActive(true);
            isMouseDragging = true;
            lastParent = transform.parent;
            transform.SetParent(cam.transform);
            bodyClick.Invoke();
            dragStartPos = transform.position;
        }
    }

    void RightClicky()
    {
        if (Global.Instance.TopRaycastResult() == gameObject)
        {
            if (InventoryManager.Instance.creativeMode)
            {
                destroyed.Invoke();
                Destroy(gameObject);
            }
            else
            {
                InventoryManager.Instance.SendToInventory(gameObject);
            }
        }
    }

    void DragMove()
    {
        var mousePos = Global.Instance.mousePos;
        // add offset from center of module to mouse position
        mousePos += dragOffset;
        
        #region module
        // set position of actual module, so it gets dragged with mouse
        var myPos = mousePos;
        myPos.z -= dragHeight;
        // what am I over?
        if (isOverInventory)
        {
            myPos.z -= 3;
        }
        transform.position = myPos;
        #endregion
        
        #region snap square
        
        var snappedPos = new Vector2
        {
            x = Mathf.Floor(mousePos.x) + .5f,
            y = Mathf.Floor(mousePos.y) + .5f
        };
        if (oddSizeX)
        {
            snappedPos.x = Mathf.Floor(mousePos.x) + .5f;
        }
        if (oddSizeY)
        {
            snappedPos.y = Mathf.Floor(mousePos.y) + .5f;
        }
        snapSquare.transform.position = snappedPos;
        var positionsChecked = new List<Vector2>();
        positionsChecked.Add(snappedPos);
        // Debug.Log($"Mouse is at {snappedPos}.");
        var valid = false;
        for (var i = 0; i < 500; i++)
        {
            // Debug.Log($"Loop: {i}");
            if (valid)
                break;
            
            foreach (var dir in dirs)
            {
                // Debug.Log($"Checking dir: {dir}");
                // Check in the cardinal directions out from the current position
                var dirPos = positionsChecked[i] + dir;
                // If we've already checked this position, move on
                if (i != 0 || dir != Vector2.zero)
                {
                    if (positionsChecked.Contains(dirPos))
                        continue;
                    positionsChecked.Add(dirPos);
                }
                // Set snap square to that position so we can perform collision checks
                snapSquare.transform.position = dirPos;

                // Perform collision checks
                if (OnModuleRack() && !IsOverlapping())
                {
                    valid = true;
                    // Debug.Log("Found valid snap square position.");
                    var newPos = new Vector3(snapSquare.transform.position.x, snapSquare.transform.position.y, transform.position.z + .1f);
                    if (isOverInventory)
                    {
                        newPos.z -= 3;
                    }
                    snapSquare.transform.position = newPos;
                    lastValidPos = snapSquare.transform.position;
                    // Debug.Log($"Setting lastValidPos to {lastValidPos}.");

                    break;
                }
            }
            
        }
        if (!valid)
        {
            // Debug.Log("Did not find a valid space.");
            snapSquare.transform.position = lastValidPos;
            // Debug.Log($"Moving snap square back to lastValidPos at {lastValidPos}.");
        }
        
        #endregion
    }
    
    void DropModule()
    {
        // Debug.Log("DropModule()");
        // reset mouse drag
        isMouseDragging = false;
        transform.position = snapSquare.transform.position;
        // Debug.Log($"Setting lastValidPos to {lastValidPos}");
        snapSquare.SetActive(false);
        dragOffset = Vector3.zero;

        AudioManager.Instance.PutDownModuleSFX();
        
        // either drop the module on a rack, or return it to its previous position
        // are we over a rack we can drop onto?
        var rackCheck = false;
        var results = Physics2D.RaycastAll(lastValidPos, Vector2.zero);
        // Debug.Log(results.Length + " at " + lastValidPos);
        foreach (var result in results)
        {
            // Debug.Log(result.transform.name);
            if (result.collider.gameObject.TryGetComponent(out ModuleRack rack))
            {
                // theoretically, this is the module rack I'm hovering over
                transform.SetParent(result.collider.gameObject.transform);
                var pos = transform.position;
                pos.z = transform.parent.position.z - .1f;
                transform.position = pos;
                myModuleRack = result.collider.gameObject;
                rackCheck = true;
                if (isInInventory)
                {
                    isInInventory = false;
                    inventoryExit.Invoke();
                }
                
                
                lastValidPos = transform.position;
                lastParent = transform.parent;
            }
        }

        if (!rackCheck)
        {
            if (InventoryManager.Instance.creativeMode)
            {
                destroyed.Invoke();
                Destroy(gameObject);
            }
            else
            {
                transform.position = lastValidPos;
                transform.parent = lastParent;
            }
        }
    }
    
    /// <summary>
    /// Function for checking if the snap square is overlapping any other rack objects.
    /// </summary>
    /// <param name="coll">The collider of the snap square.</param>
    /// <param name="pos">Position of collider/rigidbody.</param>
    /// <returns>True or false.</returns>
    private bool IsOverlapping()
    {
        // var results = new List<Collider2D>();
        // we only care about checking against objects on the rack
        var filter = new ContactFilter2D
        {
            // layerMask = LayerMask.GetMask("Rack Objects", "Module Racks")
        };
        filter.NoFilter();
        // check the collider for overlaps on that layer
        snapSquare.GetComponent<Collider2D>().Overlap(snapSquare.transform.position, 0, filter, collisionResults);
        // Debug.Log($"Checking if snapSquare is overlapping at {snapSquare.transform.position}.");
        foreach (var result in collisionResults)
        {
            // Debug.Log(result.gameObject.name);
            // ignore self
            if (result.gameObject == gameObject)
                continue;
            if (result.gameObject.layer == LayerMask.NameToLayer("Module Components"))
                continue;
            if (result.gameObject.CompareTag("Bullet"))
                continue;
            if (result.gameObject == snapSquare)
                continue;
            if (result.gameObject.layer == LayerMask.NameToLayer("Particles"))
                continue;
            if (result.gameObject.layer == LayerMask.NameToLayer("Module Racks"))
                continue;
            if (result.CompareTag("Weapon"))
                continue;
            if (result.gameObject.layer == LayerMask.NameToLayer("Jacks"))
                continue;
            if (result.gameObject.GetComponent<ModuleRack>() != null)
                continue;
            if (result.gameObject.GetComponent<InventoryManager>() != null)
                continue;
            if (result.gameObject.CompareTag("Wire"))
                continue;
            if (result.gameObject.CompareTag("Switch"))
                continue;
            // if (!InsideCol(coll, result))
            // {
            //     Debug.Log("not inside collider");
            //     continue;
            // }
            // Debug.Log("colliding with " + result.gameObject.name + " at " + snapSquare.transform.position);
            
            return true;
            // otherwise if we hit something, return true
        }
        
        return false;
    }

    bool OnModuleRack()
    {
        var results = Physics2D.RaycastAll(snapSquare.transform.position, Vector2.zero);
        foreach (var r in results)
        {
            if (r.collider.gameObject.layer == LayerMask.NameToLayer("Module Racks"))
            {
                if (InsideCollider(snapSquare.GetComponent<Collider2D>(), r.collider))
                {
                    return true;
                }
            }
        }
        
        return false;
    }
    
    bool InsideCollider(Collider2D mycol, Collider2D other)
    {
        Physics2D.SyncTransforms();
        var myColMinPos = mycol.bounds.min;
        myColMinPos.z = other.transform.position.z;
        var myColMaxPos = mycol.bounds.max;
        myColMaxPos.z = other.transform.position.z;
        // Debug.Log($"Checking InsideCollider at {mycol.transform.position}\nsnapSquare bounds are ({myColMinPos}, {myColMaxPos})\nrack bounds are ({other.bounds.min}, {other.bounds.max})");
        if (other.bounds.Contains(myColMinPos) && other.bounds.Contains(myColMaxPos))
        {
            return true;
        }

        return false;
    }
    
    void DrawBounds(Bounds b, Color color)
    {
        Vector3 min = b.min;
        Vector3 max = b.max;
    
        Vector3[] corners = new Vector3[8];
        // Bottom
        corners[0] = new Vector3(min.x, min.y, min.z);
        corners[1] = new Vector3(max.x, min.y, min.z);
        corners[2] = new Vector3(max.x, min.y, max.z);
        corners[3] = new Vector3(min.x, min.y, max.z);
        // Top
        corners[4] = new Vector3(min.x, max.y, min.z);
        corners[5] = new Vector3(max.x, max.y, min.z);
        corners[6] = new Vector3(max.x, max.y, max.z);
        corners[7] = new Vector3(min.x, max.y, max.z);
    
        // Bottom rectangle
        Debug.DrawLine(corners[0], corners[1], color);
        Debug.DrawLine(corners[1], corners[2], color);
        Debug.DrawLine(corners[2], corners[3], color);
        Debug.DrawLine(corners[3], corners[0], color);
    
        // Top rectangle
        Debug.DrawLine(corners[4], corners[5], color);
        Debug.DrawLine(corners[5], corners[6], color);
        Debug.DrawLine(corners[6], corners[7], color);
        Debug.DrawLine(corners[7], corners[4], color);
    
        // Vertical edges
        Debug.DrawLine(corners[0], corners[4], color);
        Debug.DrawLine(corners[1], corners[5], color);
        Debug.DrawLine(corners[2], corners[6], color);
        Debug.DrawLine(corners[3], corners[7], color);
    }
}
