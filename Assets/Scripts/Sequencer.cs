using System;
using System.Collections.Generic;
using System.Numerics;
using UnityEngine;
using Vector2 = UnityEngine.Vector2;
using Vector3 = UnityEngine.Vector3;

public class Sequencer : MonoBehaviour
{
    [Header("Params")]
    public float metro = 200;
    public float attack = 60;
    public float decay = 30;
    public float sustain = 0;
    public float release = 8;
    
    [Header("Combat Stats")]
    public float speed = 1;
    public float damage = 1;
    public float izki;
    public float aubo;
    public float dwth;
    public Dictionary<Module.SoundType, float> soundType = new Dictionary<Module.SoundType, float>
    {
        { Module.SoundType.None, 0 },
        { Module.SoundType.Izki, 0 },
        { Module.SoundType.Aubo, 0 },
        { Module.SoundType.Dwth, 0 },
    };
    
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
    public GameObject[] pitchSnapSquares;
    private Vector3[] pitchSquareLastPositions = new Vector3[4];
    private Vector2[] pitchSquaresDragOffset = new Vector2[4];
    private bool[] pitchSquaresDragged =
    {
        false,
        false,
        false,
        false
    };
    private float[] pitches = new float[4];
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        soundType[Module.SoundType.Izki] = izki;
        soundType[Module.SoundType.Aubo] = aubo;
        soundType[Module.SoundType.Dwth] = dwth;
        
        for (int i = 0; i < pitchSquares.Length; i++)
        {
            pitchSquareLastPositions[i] = pitchSquares[i].transform.position;
            int interval = (int)pitchSquares[i].transform.position.y + 4; // normalize to 1-7
            pitches[i] = Notes.GetPitch(Notes.C, Notes.MODE.LYDIAN, interval);
        }
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
                y = Mathf.Floor(mousePos.y)+.5f
            };
            while (IsOverlapping(gameObject, snappedPos, new Vector2(3, 1f))) // THIS IS PROBABLY A BAD IDEA
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
        for (var i = 0; i < pitchSquares.Length; i++)
        {
            pitchSquares[i].transform.position = pitchSquareLastPositions[i];
            if (pitchSquaresDragged[i])
            {
                pitchSquares[i].transform.position = mousePos + pitchSquaresDragOffset[i];
                var snappedPos = new Vector2
                {
                    x = Mathf.Round(mousePos.x),
                    y = Mathf.Round(mousePos.y)
                };
                while (IsOverlapping(pitchSquares[i], snappedPos, new Vector2(.5f, .5f))) // THIS IS PROBABLY A BAD IDEA
                {
                    var dir = new Vector2(1, 0); // TODO: Make this directional based on diff between snap pos and pos
                    snappedPos += dir;
                }
                pitchSnapSquares[i].transform.position = snappedPos;
                // drop module
                if (Input.GetMouseButtonUp(0))
                {
                    pitchSquaresDragged[i] = false;
                    pitchSquares[i].transform.position = pitchSnapSquares[i].transform.position;
                    pitchSnapSquares[i].SetActive(false);
                    pitchSquaresDragOffset[i] = Vector2.zero;
                    AudioManager.Instance.PutDownModuleSFX();
                    int interval = (int)pitchSquares[i].transform.position.y + 4; // normalize to 1-7
                    pitches[i] = Notes.GetPitch(Notes.C, Notes.MODE.IONIAN, interval);
                    if (moduleAttached != null)
                        UpdatePitches();
                }
            }
            pitchSquareLastPositions[i] = pitchSquares[i].transform.position;
        }
        
        if (Input.GetMouseButtonDown(0))
        {
            var hit = Physics2D.Raycast(mousePos, Vector2.zero, 0, LayerMask.GetMask("Sequencer Buttons"));
            var jackHit = Physics2D.Raycast(mousePos, Vector2.zero, 0, LayerMask.GetMask("Jacks"));
            var bodyHit = Physics2D.Raycast(mousePos, Vector2.zero, 0, LayerMask.GetMask("Module Bodies"));
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
                        outputJack.transform.GetChild(0).gameObject.GetComponent<TriggerWire>().DeleteSelf();
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

                for (var i = 0; i < pitchSquares.Length; i++)
                {
                    var body = pitchSquares[i];
                    if (bodyHit.collider.gameObject == body)
                    {
                        pitchSquaresDragged[i] = true;
                        pitchSnapSquares[i].SetActive(true);
                        pitchSquaresDragOffset[i] = body.transform.position - Camera.main.ScreenToWorldPoint(Input.mousePosition);
                    }
                }
            }
        }
    }
    
    private bool IsOverlapping(GameObject ignore, Vector2 pos, Vector2 size)
    {
        var overlap = Physics2D.OverlapBoxAll(pos, size, 0, LayerMask.GetMask("Module Bodies"));
        foreach (var coll in overlap)
        {
            if (coll.gameObject == ignore)
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
        moduleAttached.GetComponent<Module>().parameters.Add("metro", metro);
        moduleAttached.GetComponent<Module>().parameters.Add("attack", attack);
        moduleAttached.GetComponent<Module>().parameters.Add("decay", decay);
        moduleAttached.GetComponent<Module>().parameters.Add("sustain", sustain);
        moduleAttached.GetComponent<Module>().parameters.Add("release", release);
        moduleAttached.GetComponent<Module>().parameters.Add("apitch1", pitches[0]);
        moduleAttached.GetComponent<Module>().parameters.Add("apitch2", pitches[1]);
        moduleAttached.GetComponent<Module>().parameters.Add("apitch3", pitches[2]);
        moduleAttached.GetComponent<Module>().parameters.Add("apitch4", pitches[3]);
        moduleAttached.GetComponent<Module>().stats.Add("damage", damage);
        moduleAttached.GetComponent<Module>().stats.Add("speed", speed);
        foreach (var type in soundType)
        {
            mod.soundType[type.Key] += type.Value;
        }
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
        moduleAttached.GetComponent<Module>().parameters.Remove("note1");
        moduleAttached.GetComponent<Module>().parameters.Remove("note2");
        moduleAttached.GetComponent<Module>().parameters.Remove("note3");
        moduleAttached.GetComponent<Module>().parameters.Remove("note4");
        moduleAttached.GetComponent<Module>().stats.Remove("damage");
        moduleAttached.GetComponent<Module>().stats.Remove("speed");
        foreach (var type in soundType)
        {
            mod.soundType[type.Key] -= type.Value;
        }
        PatchManager.Instance.UpdateAllPatches();
    }

    void UpdateSequence()
    {
        if (moduleAttached == null)
            return;
        
        moduleAttached.GetComponent<Module>().parameters["note1"] = Convert.ToInt32(buttonOnePressed);
        moduleAttached.GetComponent<Module>().parameters["note2"] = Convert.ToInt32(buttonTwoPressed);
        moduleAttached.GetComponent<Module>().parameters["note3"] = Convert.ToInt32(buttonThreePressed);
        moduleAttached.GetComponent<Module>().parameters["note4"] = Convert.ToInt32(buttonFourPressed);
        PatchManager.Instance.UpdateAllPatches();
        
    }

    void UpdatePitches()
    {
        if (moduleAttached == null)
            return;
        
        moduleAttached.GetComponent<Module>().parameters["apitch1"] = pitches[0];
        moduleAttached.GetComponent<Module>().parameters["apitch2"] = pitches[1];
        moduleAttached.GetComponent<Module>().parameters["apitch3"] = pitches[2];
        moduleAttached.GetComponent<Module>().parameters["apitch4"] = pitches[3];
        PatchManager.Instance.UpdateAllPatches();
    }
}
