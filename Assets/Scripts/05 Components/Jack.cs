using System;
using UnityEngine;
using UnityEngine.UI;

public abstract class Jack : MonoBehaviour, ITooltipInfo, ISelectable
{
    private bool _darkTheme;
    public bool darkTheme
    {
        get => _darkTheme;
        set
        {
            _darkTheme = value;
            SetSprite(darkTheme);
        }
    }

    public bool valid = true;

    protected virtual void SetSprite(bool dt)
    {
        
    }
    
    protected virtual void Start()
    {
        Global.Instance.allJacks.Add(gameObject);
        
        EventBus.Instance.updateJackValidity.AddListener(UpdateValidity);

        valid = true;
    }

    protected void OnDestroy()
    {
        // TODO: this is getting called when entering playmode and I have no idea why,
        // but it seems like Global.Instance isn't initialized yet? So it's throwing an error.
        // Awesome.
        // Anyway this check (which shouldn't have to exist) is just to make it work for now.
        if (Global.Instance != null)
        {
            Global.Instance.allJacks.Remove(gameObject);
        }
    }

    protected void Update()
    {
        if (Input.GetMouseButtonDown(0))
        {
            if (UIManager.Instance.TopRaycastResult() == gameObject)
            {
                OnMouseDown();
            }
        }
    }

    protected void OnMouseDown()
    {
        // Debug.Log("module jack clicked");
        if (Parent().transform == InventoryManager.Instance.transform)
            return;

        // input jacks are not allowed to spawn new wires
        // this may change in the future depending on wire behavior
        // if (inputJacks.Contains(jack) || jack.CompareTag("InputJack"))
        //     return;
        //
        // update: they're allowed
        if (Parent().TryGetComponent(out Module module))
        {
            SpawnWire(module);
        }
        else if (Parent().TryGetComponent(out Weapon weapon))
        {
            SpawnWire(weapon);
        }
        else if (Parent().TryGetComponent(out Reactor reactor))
        {
            SpawnWire(reactor);
        }
    }

    protected void SpawnWire(Module module)
    {
        // is there already a wire there?
        foreach (var wire in module.childWires)
        {
            if (wire.GetComponent<Wire>().previousModuleJack == gameObject)
            {
                return;
            }
        }

        foreach (var wire in module.parentWires)
        {
            if (wire.GetComponent<Wire>().nextModuleJack == gameObject)
            {
                return;
            }
        }

        // make a new wire
        GameObject newWire = Instantiate(Resources.Load<GameObject>("Module Components/Wire"), gameObject.transform);
        if (gameObject.CompareTag("InputJack"))
        {
            module.parentWires.Add(newWire);
        }
        else if (gameObject.CompareTag("OutputJack"))
        {
            module.childWires.Add(newWire);
        }
    }

    protected void SpawnWire(Weapon weapon)
    {
        // is there already a wire there?
        if (weapon.parentWire != null ||
            weapon.parentEnergyWire != null)
            return;
        
        if (gameObject == weapon.patchEndJack)
        {
            GameObject newWire = Instantiate(Resources.Load<GameObject>("Module Components/Wire"), gameObject.transform);
            weapon.parentWire = newWire;
        }
        else if (gameObject == weapon.energyInJack)
        {
            GameObject newWire = Instantiate(Resources.Load<GameObject>("Module Components/Wire"), gameObject.transform);
            weapon.parentEnergyWire = newWire;
        }
    }

    protected void SpawnWire(Reactor reactor)
    {
        // is there already a wire there?
        if (reactor.parentWire != null)
        {
            // return so we can grab the existing wire instead of creating a new one
            return;
        }

        // make a new wire
        GameObject newWire = Instantiate(Resources.Load<GameObject>("Module Components/Wire"), gameObject.transform);
        reactor.parentWire = newWire;
    }

    protected virtual void UpdateValidity(Wire activeWire)
    {
        // Debug.Log("UpdateValidity");
        if (Parent().TryGetComponent(out Module module))
        {
            if (Parent().GetComponent<RackMovement>().isInInventory) return;
            
            // Check if this jack already has a wire
            if (module.childWires.Count > 0)
            {
                if (module.childWires.Contains(activeWire.gameObject))
                {
                    valid = false;
                }
                
                foreach (var connectedWire in transform.parent.GetComponent<Module>().childWires)
                {
                    if (connectedWire.GetComponent<Wire>().previousModuleJack == gameObject)
                    {
                        valid = false;
                    }
                }
            }
            if (module.parentWires.Count > 0)
            {
                if (module.parentWires.Contains(activeWire.gameObject))
                {
                    valid = false;
                }
                
                foreach (var connectedWire in transform.parent.GetComponent<Module>().parentWires)
                {
                    if (connectedWire.GetComponent<Wire>().nextModuleJack == gameObject)
                    {
                        valid = false;
                    }
                }
            }
        }
        else if (transform.parent.TryGetComponent(out Weapon weapon))
        {
            if (weapon.parentWire != null)
            {
                valid = false;
            }
        }
        else if (transform.parent.TryGetComponent(out Reactor reactor))
        {
            if (reactor.parentWire != null)
            {
                valid = false;
            }
        }
        
        if (activeWire.isConnected)
        {
            valid = true;
        }
    }

    protected void UpdateHighlights()
    {
        GetComponent<SpriteRenderer>().color = valid ? Color.white : new Color(.5f, .5f, .5f, 1);
    }

    public GameObject Parent()
    {
        var parent = transform.parent.gameObject;
        var loopCount = 0;
        while (!parent.TryGetComponent(out Module m1) && !parent.TryGetComponent(out ModuleRack m2))
        {
            parent = parent.transform.parent.gameObject;
            loopCount++;

            if (loopCount > 100 || parent == null)
            {
                return null;
            }
        }

        if (parent.TryGetComponent(out Module module) || parent.TryGetComponent(out ModuleRack moduleRack))
        {
            return parent;
        }

        return null;
    }

    public abstract string Description();

    public abstract string Info();
    
    public void Select()
    {
        
    }
}
