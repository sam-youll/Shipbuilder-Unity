using System;
using UnityEngine;

public class Conveyor : MonoBehaviour
{
    public GameObject moduleAttached;

    private bool isMouseDragging;
    private Vector2 dragOffset;

    public GameObject snapSquare;

    public float source = 2;
    public float freq = 8;
    public float depth = 20;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        // move the module attached
        if (moduleAttached != null)
        {
            var pos = moduleAttached.transform.position;
            pos.y = Mathf.Sin(Time.time*6.5f) + transform.position.y;
            pos.z = transform.position.z - .2f;
            moduleAttached.transform.position = pos;
        }
        
        
        // convert mouse position to world coordinates
        Vector2 mousePos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
        
        // mouse movement
        if (isMouseDragging)
        {
            // add offset from center of module to mouse position
            mousePos += dragOffset;
            // set position
            var myPos = new Vector3(mousePos.x, mousePos.y, -1);
            transform.position = myPos;

            // set position of snap square
            var snappedPos = new Vector2
            {
                x = Mathf.Round(mousePos.x),
                y = Mathf.Round(mousePos.y)
            };
            while (OverlapCheck(snappedPos, new Vector2(.5f, 1.5f))) // THIS IS PROBABLY A BAD IDEA
            {
                var dir = new Vector2(1, 0); // TODO: Make this directional based on diff between snap pos and pos
                snappedPos += dir;
            }
            snapSquare.transform.position = snappedPos;
            
            // drop module
            if (Input.GetMouseButtonUp(0))
            {
                // reset mouse drag
                isMouseDragging = false;
                transform.position = snapSquare.transform.position;
                snapSquare.SetActive(false);
                dragOffset = Vector2.zero;

                AudioManager.Instance.PutDownModuleSFX();
            }
        }
    }

    public void OnModuleAttached(Module mod)
    {
        moduleAttached = mod.gameObject;
        moduleAttached.GetComponent<Module>().parameters.Add("FM", 1);
        moduleAttached.GetComponent<Module>().parameters.Add("FMsource", source);
        moduleAttached.GetComponent<Module>().parameters.Add("FMfreq", freq);
        moduleAttached.GetComponent<Module>().parameters.Add("FMdepth", depth);
        PatchManager.Instance.UpdateAllPatches();
    }

    public void OnModuleDetached(Module mod)
    {
        moduleAttached.GetComponent<Module>().parameters.Remove("FM");
        moduleAttached.GetComponent<Module>().parameters.Remove("FMsource");
        moduleAttached.GetComponent<Module>().parameters.Remove("FMfreq");
        moduleAttached.GetComponent<Module>().parameters.Remove("FMdepth");
        moduleAttached = null;
        PatchManager.Instance.UpdateAllPatches();
    }
    
    private bool OverlapCheck(Vector2 pos, Vector2 size)
    {
        var overlap = Physics2D.OverlapBoxAll(pos, size, 0, LayerMask.GetMask("Module Bodies"));
        foreach (var coll in overlap)
        {
            if (coll.gameObject == gameObject)
                continue;
            if (coll.gameObject == transform.GetChild(3).gameObject)
                continue;
            
            return true;
        }

        return false;
    }

    private void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(0))
        {
            isMouseDragging = true;
            snapSquare.SetActive(true);
                
            var adjPos = transform.position;
            adjPos.z = -1;
            transform.position = adjPos;
            AudioManager.Instance.PickUpModuleSFX();
        }
    }
}
