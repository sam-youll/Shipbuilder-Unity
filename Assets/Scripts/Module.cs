using System;
using System.Collections.Generic;
using System.Numerics;
using TMPro;
using UnityEngine;
using UnityEngine.Serialization;
using Vector2 = UnityEngine.Vector2;
using Vector3 = UnityEngine.Vector3;

public class Module : MonoBehaviour
{
    public enum SoundType
    {
        None,
        Izki,
        Aubo,
        Dwth
    }
    
    [Header("Values")] 
    public bool isSourceModule;
    public string parameter;
    public float parameterValue;
    public string stat;
    public float statValue;
    public SoundType soundType;
    public Dictionary<string, float> parameters = new();
    public Dictionary<string, float> stats = new();
    
    [Header("Connections")]
    public GameObject previousModule;
    public GameObject nextModule;
    public GameObject sourceModule;
    public bool onConveyor;

    [Header("Module Components")]
    public GameObject inputJack;
    public GameObject outputJack;
    public GameObject wirePrefab;
    public GameObject typeLabel;
    public GameObject snapSquare;

    private GameObject objUnderMouse;
    private bool isMouseDragging;
    private Vector2 dragOffset;

    private bool isInInventory;
    private bool isOverInventory;
    private bool isOverConveyor;

    private Vector3 lastPos;

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        parameters.Add(parameter, parameterValue);
        stats.Add(stat, statValue);
        
        // set onLFO to true if parent has LFO component
        onConveyor = transform.GetComponentInParent<Conveyor>() != null;
        
        // Set color of module based on type
        switch (soundType)
        {
            case SoundType.Izki:
                GetComponent<SpriteRenderer>().color = Color.yellow;
                break;
            case SoundType.Aubo:
                GetComponent<SpriteRenderer>().color = Color.cyan;
                break;
            case SoundType.Dwth:
                GetComponent<SpriteRenderer>().color = Color.magenta;
                break;
        }
        
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
        
        // mouse movement
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

            // set position of snap square
            var snappedPos = new Vector2
            {
                x = Mathf.Round(mousePos.x),
                y = Mathf.Round(mousePos.y)
            };
            while (IsOverlapping(snappedPos, new Vector2(.5f, .5f))) // THIS IS PROBABLY A BAD IDEA
            {
                if (OverlapCheck(snappedPos, new Vector2(.5f, .5f)).GetComponent<Conveyor>() != null)
                {
                    isOverConveyor = true;
                    break;
                }
                isOverConveyor = false;
                
                var dir = new Vector2(1, 0); // TODO: Make this directional based on diff between snap pos and pos
                snappedPos += dir;
            }

            if (!IsOverlapping(snappedPos, new Vector2(.5f, .5f)))
            {
                isOverConveyor = false;
            }
            
            snapSquare.transform.position = snappedPos;
            
            HoverInventory(); // open or close inventory based on dragging module over
            
            // drop module
            if (Input.GetMouseButtonUp(0))
            {
                // reset mouse drag
                isMouseDragging = false;
                transform.position = snapSquare.transform.position;
                snapSquare.SetActive(false);
                dragOffset = Vector2.zero;
                UpdatePosParameter();

                AudioManager.Instance.PutDownModuleSFX();
            
                var adjPos = transform.position;
                adjPos.z = 0;
                if (isOverInventory)
                {
                    adjPos.z -= 3;
                }
                transform.position = adjPos;

                if (isOverConveyor)
                {
                    var conveyor = OverlapCheck(snappedPos, new Vector2(.5f, .5f));
                    onConveyor = true;
                    transform.SetParent(conveyor.transform);
                    conveyor.GetComponent<Conveyor>().OnModuleAttached(this);
                }
                
                if (!isInInventory && isOverInventory)
                {
                    isInInventory = true;
                    transform.SetParent(Inventory.Instance.transform);
                    // PatchManager.Instance.UpdateAllPatches();
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
                    // PatchManager.Instance.UpdateAllPatches();
                }
            }
        }
        
        // set objUnderMouse
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

        // left click handles turning on dragging and creating wires
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
                
                if (onConveyor)
                {
                    var snappedPos = new Vector2
                    {
                        x = Mathf.Round(mousePos.x),
                        y = Mathf.Round(mousePos.y)
                    };
                    var conveyor = OverlapCheck(snappedPos, new Vector2(.5f, .5f));
                    onConveyor = false;
                    transform.SetParent(ModuleRack.Instance.transform);
                    conveyor.GetComponent<Conveyor>().OnModuleDetached(this);
                }
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

    private void UpdatePosParameter()
    {
        if (parameter == "pitch")
        {
            // y values go from -3 to 3
            int interval = (int)transform.position.y + 3; // normalize to 1-7
            
            parameters["pitch"] = Notes.GetPitch(Notes.C, Notes.MODE.LYDIAN, interval);
            PatchManager.Instance.UpdateAllPatches();
        }
    }

    private bool IsOverlapping(Vector2 pos, Vector2 size)
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

    private GameObject OverlapCheck(Vector2 pos, Vector2 size)
    {
        var overlap = Physics2D.OverlapBoxAll(pos, size, 0, LayerMask.GetMask("Module Bodies"));
        foreach (var coll in overlap)
        {
            if (coll.gameObject == gameObject)
                continue;
            return coll.gameObject;
        }

        return null;
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
