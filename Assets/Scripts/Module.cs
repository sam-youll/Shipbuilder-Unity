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
    public float izki;
    public float aubo;
    public float dwth;
    public Dictionary<SoundType, float> soundType = new Dictionary<SoundType, float>
    {
        { SoundType.None, 0 },
        { SoundType.Izki, 0 },
        { SoundType.Aubo, 0 },
        { SoundType.Dwth, 0 },
    };
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
    public GameObject snapSquare;

    private GameObject objUnderMouse;
    private bool isMouseDragging;
    private Vector2 dragOffset;

    private bool isInInventory;
    private bool isOverInventory;
    private bool isOverConveyor;

    public bool isReactorModule;
    public bool isPowerModule;

    private Vector3 lastPos;

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        // assign delegates to unity events from rack movement script
        GetComponent<RackMovement>().bodyClick.AddListener(onBodyClick);
        GetComponent<RackMovement>().jackClick.AddListener(onJackClick);
        GetComponent<RackMovement>().inventoryEnter.AddListener(onInventoryEnter);
        GetComponent<RackMovement>().inventoryExit.AddListener(onInventoryExit);
        
        soundType[SoundType.Izki] = izki;
        soundType[SoundType.Aubo] = aubo;
        soundType[SoundType.Dwth] = dwth;
        
        parameters.Add(parameter, parameterValue);
        stats.Add(stat, statValue);
        
        // set onLFO to true if parent has LFO component
        onConveyor = transform.GetComponentInParent<Conveyor>() != null;
        
        // Set color of module based on type
        // switch (soundType)
        // {
        //     case SoundType.Izki:
        //         GetComponent<SpriteRenderer>().color = Color.yellow;
        //         break;
        //     case SoundType.Aubo:
        //         GetComponent<SpriteRenderer>().color = Color.cyan;
        //         break;
        //     case SoundType.Dwth:
        //         GetComponent<SpriteRenderer>().color = Color.magenta;
        //         break;
        // }
        
        if (isSourceModule)
        {
            sourceModule = gameObject;
        }

        if (transform.parent == Inventory.Instance.transform)
        {
            isInInventory = true;
        }
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void UpdatePosParameter()
    {
        if (parameter == "pitch")
        {
            // y values go from -3 to 3
            int interval = (int)transform.position.y + 4; // normalize to 1-7
            interval = Mathf.Clamp(interval, 0, 7);
            
            parameters["pitch"] = Notes.GetPitch(Notes.C, Notes.MODE.IONIAN, interval);
            PatchManager.Instance.UpdateAllPatches();
        }
    }

    private void onBodyClick()
    {
        
    }

    private void onJackClick()
    {
        if (transform.parent == Inventory.Instance.transform)
        {
            return;
        }
        
        // is there already a wire there?
        if (outputJack.transform.childCount > 0)
        {
            // get rid of it
            outputJack.transform.GetChild(0).gameObject.GetComponent<Wire>().DeleteSelf();
        }
        // make a new wire
        GameObject newWire = Instantiate(wirePrefab, outputJack.transform);
    }

    private void onInventoryEnter()
    {
        if (previousModule != null)
        {
            previousModule.GetComponent<Module>().outputJack.transform.GetChild(0).gameObject.GetComponent<Wire>().DeleteSelf();
        }

        if (outputJack.transform.childCount > 0)
        {
            outputJack.transform.GetChild(0).gameObject.GetComponent<Wire>().DeleteSelf();
        }
    }

    private void onInventoryExit()
    {
        
    }
}
