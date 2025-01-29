using System;
using UnityEngine;
using UnityEngine.Serialization;

public class BaseModule : MonoBehaviour
{
    [Header("Connections")]
    public GameObject previousModule;
    public GameObject nextModule;
    public GameObject sourceModule;

    [Header("Module Components")] 
    public GameObject scriptComponent;
    public GameObject inputJack;
    public GameObject outputJack;
    public GameObject wirePrefab;

    private GameObject objUnderMouse;
    private bool isMouseDragging;
    private Vector2 dragOffset;
    

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        sourceModule = this.gameObject;
    }

    // Update is called once per frame
    void Update()
    {
        if (isMouseDragging)
        {
            // convert mouse position to world coordinates
            Vector2 mousePos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
            // add offset from center of module
            mousePos += dragOffset;
            // set position
            transform.position = mousePos;
        }
    }

    #region Mouse Handling
    private void OnMouseOver()
    {

        // use a raycast to determine what object the mouse is hovering over
        Vector2 mousePos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
        RaycastHit2D hit = Physics2D.Raycast(mousePos, Vector2.zero, Mathf.Infinity, LayerMask.GetMask("Jacks"));
        if (hit)
        {
            objUnderMouse = hit.collider.gameObject;
        }
        else
        {
            objUnderMouse = null;
        }

    }

    private void OnMouseExit()
    {
        // just in case you somehow left the collider without hitting the rest of the module
        objUnderMouse = null;
    }

    private void OnMouseDown()
    {
        // only drag if over module body and not a jack
        if (objUnderMouse == null)
        {
            dragOffset = transform.position - Camera.main.ScreenToWorldPoint(Input.mousePosition);
            isMouseDragging = true;
        }
        // if clicking on the output jack, create a wire
        else if (objUnderMouse == outputJack && nextModule == null)
        {
            GameObject newWire = Instantiate(wirePrefab, objUnderMouse.transform);
        }
    }

    private void OnMouseUp()
    {
        // reset mouse drag
        isMouseDragging = false;
        dragOffset = Vector2.zero;
    }
    #endregion
}
