using System;
using System.Numerics;
using TMPro;
using UnityEngine;
using UnityEngine.Serialization;
using Vector2 = UnityEngine.Vector2;
using Vector3 = UnityEngine.Vector3;

public class Module : MonoBehaviour
{
    public enum ModuleType
    {
        None,
        Source,
        Pitch,
        Arpeggio,
        Thruster,
        Ringmod
    }
    public ModuleType moduleType = ModuleType.None;

    [Header("Values")] 
    public bool isSourceModule;
    public bool isOutputModule;
    public string parameter;
    public float parameterValue;
    public string stat;
    public float statValue;
    
    [Header("Connections")]
    public GameObject previousModule;
    public GameObject nextModule;
    public GameObject sourceModule;

    [Header("Module Components")]
    public GameObject inputJack;
    public GameObject outputJack;
    public GameObject wirePrefab;
    public GameObject typeLabel;
    public GameObject snapSquare;

    public GameObject objUnderMouse;
    private bool isMouseDragging;
    private Vector2 dragOffset;

    private bool isInInventory;
    private bool isOverInventory;


    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        typeLabel.GetComponent<TextMeshPro>().text = gameObject.name;
        
        if (isSourceModule)
        {
            sourceModule = this.gameObject;
        }

        if (transform.parent == ModuleRack.Instance.transform)
        {
            isInInventory = false;
        }
        else if (transform.parent == Inventory.Instance.transform)
        {
            isInInventory = true;
        }
        
    }

    // Update is called once per frame
    void Update()
    {
        // convert mouse position to world coordinates
        Vector2 mousePos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
        
        if (isMouseDragging)
        {
            // add offset from center of module to mouse position
            mousePos += dragOffset;
            // set position
            var myPos = new Vector3(mousePos.x, mousePos.y, -1);
            if (isOverInventory)
            {
                myPos.z -= 3;
            }
            transform.position = myPos;

            var snappedPos = new Vector2
            {
                x = Mathf.Round(mousePos.x),
                y = Mathf.Round(mousePos.y)
            };
            while (OverlapCheck(snappedPos, new Vector2(.5f, .5f))) // THIS IS PROBABLY A BAD IDEA
            {
                var dir = new Vector2(1, 0); // TODO: Make this directional based on diff between snap pos and pos
                snappedPos += dir;
            }
            snapSquare.transform.position = snappedPos;
            
            HoverInventory(); // open or close inventory based on dragging module over
            
            if (Input.GetMouseButtonUp(0))
            {
                // reset mouse drag
                isMouseDragging = false;
                transform.position = snapSquare.transform.position;
                snapSquare.SetActive(false);
                dragOffset = Vector2.zero;

                AudioManager.Instance.PutDownModuleSFX();
            
                var adjPos = transform.position;
                adjPos.z = 0;
                if (isOverInventory)
                {
                    adjPos.z -= 3;
                }
                transform.position = adjPos;
                
                if (!isInInventory && isOverInventory)
                {
                    isInInventory = true;
                    transform.SetParent(Inventory.Instance.transform);
                    PatchManager.Instance.UpdateAllPatches();
                    if (previousModule != null)
                    {
                        previousModule.GetComponent<Module>().outputJack.transform.GetChild(0).gameObject.GetComponent<Wire>().DeleteSelf();
                    }

                    if (outputJack.transform.childCount > 0)
                    {
                        outputJack.transform.GetChild(0).gameObject.GetComponent<Wire>().DeleteSelf();
                    }
                }
                else if (isInInventory && !isOverInventory)
                {
                    isInInventory = false;
                    transform.SetParent(ModuleRack.Instance.transform);
                    PatchManager.Instance.UpdateAllPatches();
                }
            }
        }
        
        RaycastHit2D hit = Physics2D.Raycast(mousePos, Vector2.zero, Mathf.Infinity, LayerMask.GetMask("Jacks"));
        RaycastHit2D bodyHit = Physics2D.Raycast(mousePos, Vector2.zero);
        // Debug.Log(hit.collider + " : " + hit.distance + " : " + hit.collider.gameObject.name);
        if (hit)
        {
            // Debug.Log(hit.collider.gameObject.name);
            objUnderMouse = hit.collider.gameObject;
        }
        else
        {
            objUnderMouse = null;
        }
        // Debug.Log(objUnderMouse);

        if (Input.GetMouseButtonDown(0))
        {
            // only drag if over module body and not a jack
            if (bodyHit && objUnderMouse == null && bodyHit.collider.gameObject == gameObject)
            {
                // Debug.Log("OnMouseDown objUnderMouse == null");
                dragOffset = transform.position - Camera.main.ScreenToWorldPoint(Input.mousePosition);
                isMouseDragging = true;
                snapSquare.SetActive(true);
                
                var adjPos = transform.position;
                adjPos.z = -1;
                transform.position = adjPos;
                AudioManager.Instance.PickUpModuleSFX();
            }
            // if clicking on the output jack, create a wire
            else if (objUnderMouse == outputJack && !isInInventory)
            {
                // is there already a wire there?
                if (outputJack.transform.childCount > 0)
                {
                    // get rid of it
                    outputJack.transform.GetChild(0).gameObject.GetComponent<Wire>().DeleteSelf();
                }
                // make a new wire
                GameObject newWire = Instantiate(wirePrefab, objUnderMouse.transform);
            }
            else
            {
                // Debug.Log("nothing happened and now we're here");
            }
        }
    }

    private bool OverlapCheck(Vector2 pos, Vector2 size)
    {
        var overlap = Physics2D.OverlapBoxAll(pos, size, 0, LayerMask.GetMask("Module Bodies"));
        foreach (var coll in overlap)
        {
            if (coll.gameObject == gameObject)
                continue;
            return true;
        }

        return false;
    }

    void HoverInventory()
    {
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
}
