using System;
using System.Numerics;
using UnityEngine;
using Vector2 = UnityEngine.Vector2;
using Vector3 = UnityEngine.Vector3;

public class Sequencer : MonoBehaviour
{
    private bool isMouseDragging = false;
    private Vector2 dragOffset;
    
    public GameObject snapSquare;
    public GameObject outputJack;
    public GameObject wirePrefab;
    public GameObject buttonOne;
    public GameObject buttonTwo;
    public GameObject buttonThree;
    public GameObject buttonFour;
    public bool buttonOnePressed = true;
    public bool buttonTwoPressed = true;
    public bool buttonThreePressed = true;
    public bool buttonFourPressed = true;
    public GameObject moduleAttached;
    public Color onCol;
    public Color offCol;

    public GameObject[] pitchSquares;
    public Vector3[] pitchSquareLastPositions;
    bool pitchOneDragging = false;
    bool pitchTwoDragging = false;
    bool pitchThreeDragging = false;
    bool pitchFourDragging = false;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
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
            while (IsOverlapping(snappedPos, new Vector2(3, .5f))) // THIS IS PROBABLY A BAD IDEA
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
        if (Input.GetMouseButtonDown(0))
        {
            var hit = Physics2D.Raycast(mousePos, Vector2.zero, 0, LayerMask.GetMask("Sequencer Buttons"));
            var jackHit = Physics2D.Raycast(mousePos, Vector2.zero, 0, LayerMask.GetMask("Jacks"));
            var bodyHit = Physics2D.Raycast(mousePos, Vector2.zero, 0, LayerMask.GetMask("Module Bodies"));
            Debug.Log(hit);
            Debug.Log(jackHit);
            Debug.Log(bodyHit);
            if (hit)
            {
                if (hit.collider.gameObject == buttonOne)
                {
                    buttonOnePressed = !buttonOnePressed;
                    if (buttonOnePressed)
                    {
                        buttonOne.GetComponent<SpriteRenderer>().color = onCol;
                    }
                    else
                    {
                        buttonOne.GetComponent<SpriteRenderer>().color = offCol;
                    }
                    UpdateSequence();
                }
                else if (hit.collider.gameObject == buttonTwo)
                {
                    buttonTwoPressed = !buttonTwoPressed;
                    if (buttonTwoPressed)
                    {
                        buttonTwo.GetComponent<SpriteRenderer>().color = onCol;
                    }
                    else
                    {
                        buttonTwo.GetComponent<SpriteRenderer>().color = offCol;
                    }
                    UpdateSequence();
                }
                else if (hit.collider.gameObject == buttonThree)
                {
                    buttonThreePressed = !buttonThreePressed;
                    if (buttonThreePressed)
                    {
                        buttonThree.GetComponent<SpriteRenderer>().color = onCol;
                    }
                    else
                    {
                        buttonThree.GetComponent<SpriteRenderer>().color = offCol;
                    }
                    UpdateSequence();
                }
                else if (hit.collider.gameObject == buttonFour)
                {
                    buttonFourPressed = !buttonFourPressed;
                    if (buttonFourPressed)
                    {
                        buttonFour.GetComponent<SpriteRenderer>().color = onCol;
                    }
                    else
                    {
                        buttonFour.GetComponent<SpriteRenderer>().color = offCol;
                    }
                    UpdateSequence();
                }
            }
            else if (jackHit)
            {
                if (jackHit.collider.gameObject == outputJack)
                {
                    // is there already a wire there?
                    if (outputJack.transform.childCount > 0)
                    {
                        // get rid of it
                        outputJack.transform.GetChild(0).gameObject.GetComponent<Wire>().DeleteSelf();
                    }
                    // make a new wire
                    GameObject newWire = Instantiate(wirePrefab, outputJack.transform);
                }
            }
            else if (bodyHit)
            {
                if (bodyHit.collider.gameObject == gameObject)
                {
                    dragOffset = transform.position - Camera.main.ScreenToWorldPoint(Input.mousePosition);
                    isMouseDragging = true;
                    snapSquare.SetActive(true);
                }
            }
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

    public void OnModuleAttached(Module mod)
    {
        moduleAttached = mod.gameObject;
        moduleAttached.GetComponent<Module>().parameters.Add("arpstart", 1);
        moduleAttached.GetComponent<Module>().parameters.Add("arp", 1);
        moduleAttached.GetComponent<Module>().parameters.Add("metro", 500);
        moduleAttached.GetComponent<Module>().parameters.Add("attack", 200);
        moduleAttached.GetComponent<Module>().parameters.Add("decay", 200);
        moduleAttached.GetComponent<Module>().parameters.Add("sustain", .2f);
        moduleAttached.GetComponent<Module>().parameters.Add("release", 500);
        moduleAttached.GetComponent<Module>().parameters.Add("apitch1", 440);
        moduleAttached.GetComponent<Module>().parameters.Add("apitch2", 554.27f);
        moduleAttached.GetComponent<Module>().parameters.Add("apitch3", 659.26f);
        moduleAttached.GetComponent<Module>().parameters.Add("apitch4", 880);
        UpdateSequence();
    }

    public void OnModuleDetached(Module mod)
    {
        moduleAttached.GetComponent<Module>().parameters.Remove("arpstart");
        moduleAttached.GetComponent<Module>().parameters.Remove("arp");
        moduleAttached.GetComponent<Module>().parameters.Remove("metro");
        moduleAttached.GetComponent<Module>().parameters.Remove("attack");
        moduleAttached.GetComponent<Module>().parameters.Remove("decay");
        moduleAttached.GetComponent<Module>().parameters.Remove("sustain");
        moduleAttached.GetComponent<Module>().parameters.Remove("release");
        moduleAttached.GetComponent<Module>().parameters.Remove("apitch1");
        moduleAttached.GetComponent<Module>().parameters.Remove("apitch2");
        moduleAttached.GetComponent<Module>().parameters.Remove("apitch3");
        moduleAttached.GetComponent<Module>().parameters.Remove("apitch4");
        moduleAttached.GetComponent<Module>().parameters.Remove("note1");
        moduleAttached.GetComponent<Module>().parameters.Remove("note2");
        moduleAttached.GetComponent<Module>().parameters.Remove("note3");
        moduleAttached.GetComponent<Module>().parameters.Remove("note4");
        moduleAttached.GetComponent<Module>().parameters.Add("note1", Convert.ToInt32(buttonOnePressed));
        moduleAttached.GetComponent<Module>().parameters.Add("note2", Convert.ToInt32(buttonTwoPressed));
        moduleAttached.GetComponent<Module>().parameters.Add("note3", Convert.ToInt32(buttonThreePressed));
        moduleAttached.GetComponent<Module>().parameters.Add("note4", Convert.ToInt32(buttonFourPressed));
        PatchManager.Instance.UpdateAllPatches();
    }

    void UpdateSequence()
    {
        moduleAttached.GetComponent<Module>().parameters["note1"] = Convert.ToInt32(buttonOnePressed);
        moduleAttached.GetComponent<Module>().parameters["note2"] = Convert.ToInt32(buttonTwoPressed);
        moduleAttached.GetComponent<Module>().parameters["note3"] = Convert.ToInt32(buttonThreePressed);
        moduleAttached.GetComponent<Module>().parameters["note4"] = Convert.ToInt32(buttonFourPressed);
        PatchManager.Instance.UpdateAllPatches();
        
    }
}
