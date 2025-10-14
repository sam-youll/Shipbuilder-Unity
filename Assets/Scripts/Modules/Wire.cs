using System;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;
using UnityEngine.Serialization;
using Random = UnityEngine.Random;

public class Wire : MonoBehaviour
{
    public enum Type
    {
        Trigger,
        Primary,
        Secondary
    }
    public Type type = Type.Trigger;
    
    [Header("Visuals")]
    public int points = 7;
    public Gradient triggerGradient = new Gradient();
    public Gradient primaryGradient = new Gradient();
    public Gradient secondaryGradient = new Gradient();

    public GameObject previousModule;
    public GameObject previousModuleJack;
    public GameObject nextModule;
    public GameObject nextModuleJack;
    
    private LineRenderer lineRenderer;

    public bool connectedToModule = false;
    public bool connectedToWeapon = false;

    public bool invisible = false;

    public UnityEvent connected;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        if (!invisible)
        {
            previousModuleJack = transform.parent.gameObject;
            previousModule = previousModuleJack.transform.parent.gameObject;

            if (previousModule.TryGetComponent(out Subpatch subpatch))
            {
                previousModule = subpatch.subpatchDict[^1].module;
            }
            
            lineRenderer = GetComponent<LineRenderer>();
            lineRenderer.positionCount = points;
            for (int i = 0; i < points; i++)
            {
                lineRenderer.SetPosition(i, transform.position);
            }
        }
    }

    // Update is called once per frame
    void Update()
    {
        // this might be useful later, but it's less performant
        //
        // if (nextModule.GetComponent<RackMovement>().isInInventory ||
        //     previousModule.GetComponent<RackMovement>().isInInventory)
        // {
        //     DeleteSelf();
        // }
        
        // when letting go of mouse click, either connect or destroy wire
        if (Input.GetMouseButtonUp(0) && !connectedToModule)
        {
            Vector2 mousePos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
            RaycastHit2D hit = Physics2D.Raycast(mousePos,Vector2.zero,Mathf.Infinity, LayerMask.GetMask("Jacks"));
            if (hit)
            {
                // hit weapon output
                if (hit.collider.gameObject.transform.parent.gameObject.CompareTag("Weapon"))
                {
                    nextModuleJack = hit.collider.gameObject;
                    nextModule = nextModuleJack.transform.parent.gameObject;
                    nextModule.GetComponent<Weapon>().previousModule = previousModule;
                    // if (nextModule.GetComponent<Weapon>().previousModule != null)
                    // {
                    //     nextModule.GetComponent<Weapon>().previousModule.GetComponent<Module>().outputJack.transform.GetChild(0).gameObject.GetComponent<Wire>().DeleteSelf();
                    // }
                    // nextModule.gameObject.GetComponent<Weapon>().previousModule = previousModule;
                    // previousModule.GetComponent<Module>().nextModule = nextModule;
                    PatchManager.Instance.UpdateAllPatches();
                    
                    connectedToModule = true;
                    connectedToWeapon = true;
                    connected.Invoke();
                }
                // hit reactor output
                else if (hit.collider.transform.parent.CompareTag("Reactor"))
                {
                    nextModuleJack = hit.collider.gameObject;
                    nextModule = nextModuleJack.transform.parent.gameObject;
                    nextModule.GetComponent<Reactor>().previousModule = previousModule;
                    // if (nextModule.GetComponent<Reactor>().previousModule != null)
                    // {
                    //     nextModule.GetComponent<Reactor>().previousModule.GetComponent<Module>().outputJack.transform.GetChild(0).gameObject.GetComponent<Wire>().DeleteSelf();
                    // }
                    // nextModule.gameObject.GetComponent<Reactor>().previousModule = previousModule;
                    // previousModule.GetComponent<Module>().nextModule = nextModule;
                    PatchManager.Instance.UpdateAllPatches();
                    connectedToModule = true;
                    connected.Invoke();
                }
                // hit a module
                else if (hit.collider.gameObject.CompareTag("InputJack"))
                {
                    nextModuleJack = hit.collider.gameObject;
                    nextModule = nextModuleJack.transform.parent.gameObject;
                    
                    
                    nextModule.GetComponent<Module>().parentWires.Add(gameObject);
                    // uh Weapon.cs doesn't have childWires lol it just searches
                    // through its children for the wires it's going to trigger
                    // else if (previousModule.TryGetComponent(out Weapon weapon))
                    // {
                    //     weapon.childWires.Add(gameObject);
                    // }
                    
                    // previousModule.GetComponent<Module>().nextModule = nextModule;
                    // if (nextModule.GetComponent<Module>().previousModule != null)
                    // {
                    //     nextModule.GetComponent<Module>().previousModule.GetComponent<Module>().outputJack.transform.GetChild(0).gameObject.GetComponent<Wire>().DeleteSelf();
                    // }
                    // nextModule.GetComponent<Module>().previousModule = previousModule;
                    connectedToModule = true;
                    connected.Invoke();
                    PatchManager.Instance.UpdateAllPatches();
                }
                else
                {
                    PatchManager.Instance.UpdateAllPatches();
                    DeleteSelf();
                }
                
                if (previousModule.TryGetComponent(out SecondaryModule secondaryModule))
                {
                    // might not work if you plug into primary input jack, not sure though
                    var inputIndex = nextModule.GetComponent<Module>().inputJacks.FindIndex(x => x == nextModuleJack);
                    secondaryModule.myInputIndex = inputIndex;
                }
                
                
                // determine wire type
                UpdateWireType();
            }
            else
            {
                PatchManager.Instance.UpdateAllPatches();
                DeleteSelf();
            }
        }
    }

    private void FixedUpdate()
    {
        if (!invisible)
        {
            UpdatePoints(Vector2.down * .1f);
        }
    }

    private void UpdatePoints(Vector2 force)
    {
        // calculate points
        Vector2[] targetPositions = new Vector2[points];
        for (int i = 0; i < points; i++)
        {
            if (i == 0)
            {
                targetPositions[0] = previousModuleJack.transform.position;
            }
            else if (i == points - 1)
            {
                if (connectedToModule)
                {
                    targetPositions[i] = nextModuleJack.transform.position;
                }
                else
                {
                    var mousePos = (Vector2)Camera.main.ScreenToWorldPoint(Input.mousePosition);
                    var results = Physics2D.RaycastAll(mousePos, Vector2.zero);
                    var overJack = false;
                    GameObject jack = null;
                    foreach (var result in results)
                    {
                        if (result.collider.gameObject.CompareTag("InputJack"))
                        {
                            overJack = true;
                            jack = result.collider.gameObject;
                        }
                    }
                    if (overJack)
                    {
                        targetPositions[i] = jack.transform.position;
                    }
                    else
                    {
                        targetPositions[i] = Camera.main.ScreenToWorldPoint(Input.mousePosition);
                    }
                }
            }
            else
            {
                Vector2 pos = lineRenderer.GetPosition(i);
                Vector2 targetPos = (lineRenderer.GetPosition(i + 1) + lineRenderer.GetPosition(i - 1))*.5f;
                targetPos += force;
                pos = Vector2.Lerp(pos, targetPos, .6f);
                targetPositions[i] = pos;
            }
        }

        Vector3[] adjTargetPositions = new Vector3[points];
        for (int i = 0; i < points; i++)
        {
            adjTargetPositions[i] = targetPositions[i];
            adjTargetPositions[i].z = previousModule.transform.position.z -.2f;
        }

        // apply points
        for (int i = 0; i < points; i++)
        {
            lineRenderer.SetPosition(i, adjTargetPositions[i]);
        }
    }
    
    public void DeleteSelf()
    {
        if (connectedToModule)
        {
            if (nextModule.CompareTag("Weapon"))
            {
                nextModule.GetComponent<Weapon>().previousModule = null;
            }
            else if (nextModule.CompareTag("Reactor"))
            {
                nextModule.GetComponent<Reactor>().previousModule = null;
            }
            else
            {
                nextModule.GetComponent<Module>().parentWires.Remove(gameObject);
                // nextModule.GetComponent<Module>().previousModule = null;
            }
        }
        previousModule.GetComponent<Module>().childWires.Remove(gameObject);
        if (previousModule.transform.parent.TryGetComponent(out Subpatch subpatch))
        {
            subpatch.childWires.Remove(gameObject);
        }
        PatchManager.Instance.UpdateAllPatches();
        Destroy(gameObject);
    }

    void UpdateWireType()
    {
        type = Type.Primary;
        return;
        
        
        // TODO: This sorely needs an update. Trigger wires are not a thing anymore, and
        // wires need a way to parse subpatches.
        
        Module prev = previousModule.GetComponent<Module>();
        Module next = nextModule.GetComponent<Module>();
        if (prev is PrimaryModule && next is PrimaryModule)
        {
            type = Type.Primary;
        }
        else if (prev is SecondaryModule && next is SecondaryModule)
        {
            type = Type.Secondary;
        }
        else if (prev is SecondaryModule && next is PrimaryModule)
        {
            type = Type.Secondary;
        }
        else
        {
            type = Type.Primary;
        }

        switch (type)
        {
            case Type.Trigger:
                lineRenderer.colorGradient = triggerGradient;
                break;
            case Type.Primary:
                lineRenderer.colorGradient = primaryGradient;
                break;
            case Type.Secondary:
                lineRenderer.colorGradient = secondaryGradient;
                break;
        }
    }

    public void Trigger()
    {
        if (!connectedToModule && !connectedToWeapon)
            return;
        
        Debug.Log($"{previousModule.name} triggered {nextModule.name} via {gameObject.name} with no arguments.");
        if (connectedToWeapon)
        {
            nextModule.GetComponent<Weapon>().Fire();
        }
        else
        {
            nextModule.GetComponent<Module>().Trigger();
        }
    }

    public void Trigger(float value)
    {
        if (!connectedToModule && !connectedToWeapon)
            return;
        
        Debug.Log($"{previousModule.name} triggered {nextModule.name} via {gameObject.name} with a value of {value}");
        if (connectedToWeapon)
        {
            nextModule.GetComponent<Weapon>().Fire();
        }
        else
        {
            nextModule.GetComponent<Module>().Trigger(value);
        }
    }
    
    public void Trigger(float value, int inputIndex)
    {
        if (!connectedToModule && !connectedToWeapon)
            return;
        
        Debug.Log($"{previousModule.name} triggered {nextModule.name} via {gameObject.name} with a value of {value} to secondary input jack {inputIndex}");
        if (connectedToWeapon)
        {
            nextModule.GetComponent<Weapon>().Fire();
        }
        else
        {
            nextModule.GetComponent<Module>().Trigger(value, inputIndex);
        }
    }
}
