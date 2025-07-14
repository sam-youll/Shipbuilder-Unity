using System;
using System.Collections.Generic;
using System.Numerics;
using TMPro;
using UnityEngine;
using UnityEngine.Serialization;
using Vector2 = UnityEngine.Vector2;
using Vector3 = UnityEngine.Vector3;

public abstract class Module : MonoBehaviour
{
    public enum SystemType
    {
        Weapon,
        Reactor
    }
    public SystemType systemType = SystemType.Weapon;
    
    public enum SoundType
    {
        None,
        Izki,
        Aubo,
        Dwth
    }

    [Header("Values")] 
    [Tooltip("The amount charged for this module in the shop.")]
    public float price;
    public float izki;
    public float aubo;
    public float dwth;
    public Dictionary<string, float> MusicParams = new();
    public Dictionary<string, float> CombatStats = new();
    
    // TODO: combine connections and module components
    // probably don't need references to modules if those references are already stored in the wires
    [Header("Connections")]
    public List<GameObject> parentWires = new();
    public List<GameObject> childWires = new();
    public GameObject wirePrefab;

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    protected virtual void Start()
    {
        // assign delegates to unity events from rack movement script
        GetComponent<RackMovement>().bodyClick.AddListener(OnBodyClick);
        GetComponent<RackMovement>().jackClick.AddListener(OnJackClick);
        GetComponent<RackMovement>().inventoryEnter.AddListener(OnInventoryEnter);
        GetComponent<RackMovement>().inventoryExit.AddListener(OnInventoryExit);
    }

    // Update is called once per frame
    protected virtual void Update()
    {
        
    }
    
    #region Trigger Method + Overloads
    public virtual void Trigger()
    {
        foreach (GameObject wire in childWires)
        {
            wire.GetComponent<Wire>().Trigger();
        }
        // Other behavior should be extended in inherited classes
    }

    public virtual void Trigger(Dictionary<string, float> musicParams, Dictionary<string, float> combatStats)
    {
        foreach (GameObject wire in childWires)
        {
            wire.GetComponent<Wire>().Trigger(musicParams, combatStats);
        }
    }

    public virtual void Trigger(float value)
    {
        foreach (GameObject wire in childWires)
        {
            wire.GetComponent<Wire>().Trigger(value);
        }
    }
    #endregion
    
    #region Event Handlers
    private void OnBodyClick()
    {
        
    }

    private void OnJackClick(GameObject jack)
    {
        if (transform.parent == Inventory.Instance.transform)
        {
            return;
        }
        
        // is there already a wire there?
        if (jack.transform.childCount > 0)
        {
            // get rid of it, unless you're holding left control
            // this way, left control + drag creates a second wire on top of the first
            // same as VCV rack
            // TODO: allow dragging wires from either end and don't just automatically delete to create new
            if (!Input.GetKey(KeyCode.LeftControl))
            {
                jack.transform.GetChild(0).gameObject.GetComponent<Wire>().DeleteSelf();
            }
        }
        // make a new wire
        GameObject newWire = Instantiate(wirePrefab, jack.transform);
    }

    private void OnInventoryEnter()
    {
        ClearWires();
    }

    private static void OnInventoryExit()
    {
        
    }
    #endregion

    public GameObject PreviousModule()
    {
        GameObject result = null;

        foreach (GameObject wire in parentWires)
        {
            if (wire.GetComponent<Wire>().type == Wire.Type.Primary)
            {
                result = wire.GetComponent<Wire>().previousModule;
            }
            else if (wire.GetComponent<Wire>().type == Wire.Type.Trigger && wire.GetComponent<Wire>().previousModule.GetComponent<Weapon>() != null)
            {
                result = wire.GetComponent<Wire>().previousModule;
            }
        }

        return result;
    }
    
    void ClearWires()
    {
        if (parentWires.Count > 0)
        {
            foreach (var wire in parentWires)
            {
                wire.GetComponent<Wire>().DeleteSelf();
            }
        }
        if (childWires.Count > 0)
        {
            foreach (var wire in childWires)
            {
                wire.GetComponent<Wire>().DeleteSelf();
            }
        }
    }
}
