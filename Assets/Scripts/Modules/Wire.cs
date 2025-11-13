using System;
using System.Collections;
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
    // public Gradient triggerGradient = new Gradient();
    // public Gradient primaryGradient = new Gradient();
    // public Gradient secondaryGradient = new Gradient();
    public Color color;
    public Gradient mainGradient;
    public Gradient hoverGradient;

    public GameObject previousModule;
    public GameObject previousModuleJack;
    public GameObject nextModule;
    public GameObject nextModuleJack;
    
    private LineRenderer lineRenderer;

    public bool connectedToModule = false;
    public bool connectedToWeapon = false;

    public bool invisible = false;

    public UnityEvent connected;

    private bool grabbed;
    private int grabbedIndex;
    private Vector3 grabStartPos;
    public float grabBreakDistance = 4;
    
    private bool dying; // this gets flipped when a wire deletes itself
    
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
            
            // Collision
            var edge = gameObject.AddComponent<EdgeCollider2D>();
            edge.edgeRadius = .07f;
        }
    }

    // Update is called once per frame
    void Update()
    {
        var lrMov = lineRenderer.material.mainTextureOffset;
        lrMov.x -= Time.deltaTime * 2f;
        if (lrMov.x < 0)
        {
            lrMov.x += 1;
        }
        lineRenderer.material.mainTextureOffset = lrMov;
        // this might be useful later, but it's less performant
        //
        // if (nextModule.GetComponent<RackMovement>().isInInventory ||
        //     previousModule.GetComponent<RackMovement>().isInInventory)
        // {
        //     DeleteSelf();
        // }

        bool overWire = false;
        if (connectedToModule)
        {
            foreach (var result in Global.Instance.raycastHits)
            {
                if (result.collider.gameObject == gameObject)
                {
                    overWire = true;
                }
            }
        }

        if (overWire && connectedToModule || grabbed)
        {

            if (Input.GetMouseButtonDown(0))
            {
                grabbed = true;
                grabStartPos = Global.Instance.mousePos;
                grabbedIndex = 1;
                Vector3[] positions = new Vector3[points];
                lineRenderer.GetPositions(positions);
                for (var i = 1; i < positions.Length - 1; i++)
                {
                    if ((positions[i] - Global.Instance.mousePos).magnitude <
                        (positions[grabbedIndex] - Global.Instance.mousePos).magnitude)
                    {
                        grabbedIndex = i;
                    }
                }
            }

            if (Input.GetMouseButtonDown(1))
            {
                DeleteSelf();
            }
        }

        if (grabbed)
        {
            Vector3[] positions = new Vector3[points];
            var lerpPos = Vector2.Lerp(positions[grabbedIndex], Global.Instance.mousePos, 1f);
            var newPos = new Vector3(lerpPos.x, lerpPos.y, positions[grabbedIndex].z);
            lineRenderer.SetPosition(grabbedIndex, newPos);

            if (Input.GetMouseButtonUp(0))
            {
                grabbed = false;
            }

            if ((grabStartPos - Global.Instance.mousePos).magnitude > grabBreakDistance)
            {
                DeleteSelf();
            }
        }
        
        lineRenderer.colorGradient = ColorGradient(color, grabbed ? (grabStartPos -  Global.Instance.mousePos).magnitude / grabBreakDistance : 0, grabbed || overWire);
        
        // when letting go of mouse click, either connect or destroy wire
        if (Input.GetMouseButtonUp(0) && !connectedToModule)
        {
            Vector2 mousePos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
            RaycastHit2D hit = Physics2D.Raycast(mousePos,Vector2.zero,Mathf.Infinity, LayerMask.GetMask("Jacks"));
            if (hit)
            {
                // plugging a module into itself crashes everything, so we don't want to let it happen
                if (hit.collider.gameObject.transform.parent.gameObject == previousModule)
                    DeleteSelf();
                
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
            if (!dying)
            {
                if (connectedToModule)
                {
                    UpdatePoints(Vector2.down * .1f, previousModuleJack.transform.position, nextModuleJack.transform.position, false, grabbed ? (grabStartPos -  Global.Instance.mousePos).magnitude / grabBreakDistance : 0);
                }
                else
                {
                    UpdatePoints(Vector2.down * .1f, previousModuleJack.transform.position, Global.Instance.mousePos, true, grabbed ? (grabStartPos -  Global.Instance.mousePos).magnitude / grabBreakDistance : 0);
                }
            }
        }
    }


    private void UpdatePoints(Vector3 force, Vector3 startPos, Vector3 endPos, bool dragging, float stress)
    {
        force *= 1 - stress;
        // calculate points
        Vector3[] targetPositions = new Vector3[points];
        for (int i = 0; i < points; i++)
        {
            if (i == 0)
            {
                startPos.z -= .2f;
                targetPositions[0] = startPos;
            }
            else if (i == points - 1)
            {
                targetPositions[i] = endPos;
                targetPositions[i].z -= 1f;
                
                // Aim assist
                if (dragging)
                {
                    var overJack = false;
                    GameObject jack = null;
                    foreach (var result in Global.Instance.raycastHits)
                    {
                        if (result.collider.gameObject.CompareTag("InputJack"))
                        {
                            overJack = true;
                            jack = result.collider.gameObject;
                        }
                    }

                    if (overJack)
                    {
                        var jackPos = jack.transform.position;
                        jackPos.z -= .2f;
                        targetPositions[i] = jackPos;
                    }
                }
            }
            else
            {
                Vector3 pos = lineRenderer.GetPosition(i);
                Vector3 targetPos = (lineRenderer.GetPosition(i + 1) + lineRenderer.GetPosition(i - 1))*.5f;
                targetPos += force;
                pos = Vector3.Lerp(pos, targetPos, .6f);
                targetPositions[i] = pos;
            }
        }

        // Vector3[] adjTargetPositions = new Vector3[points];
        // for (int i = 0; i < points; i++)
        // {
        //     adjTargetPositions[i] = targetPositions[i];
        //     adjTargetPositions[i].z = previousModule.transform.position.z -.2f;
        // }
        //
        // apply points
        for (int i = 0; i < points; i++)
        {
            lineRenderer.SetPosition(i, targetPositions[i]);
        }
        
        Vector3[] positions = new Vector3[points];
        lineRenderer.GetPositions(positions);
        var posList = new List<Vector2>();
        for (int i = 0; i < points; i++)
        {
            // adjust for world -> local, because lineRenderer points are in world space, but edgeCollider points are local
            posList.Add(positions[i] - transform.position);
        }
        GetComponent<EdgeCollider2D>().SetPoints(posList);
    }
    
    public void DeleteSelf()
    {
        if (!dying)
        {
            dying = true;
            StartCoroutine(DeleteSelfCoroutine());
        }
    }

    private IEnumerator DeleteSelfCoroutine()
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
        Vector3[] positions = new Vector3[points];
        Vector2 deletePos = Global.Instance.mousePos;
        while ((Vector2)positions[0] != deletePos || (Vector2)positions[^1] != deletePos)
        {
            lineRenderer.GetPositions(positions);
            positions[0] = Vector3.Lerp(positions[0], deletePos, .5f);
            lineRenderer.SetPosition(0, positions[0]);
            positions[^1] =  Vector3.Lerp(positions[^1], deletePos, .5f);
            lineRenderer.SetPosition(points - 1, positions[^1]);
            UpdatePoints(Vector2.zero, positions[0], positions[^1], false, 0);
            yield return new WaitForSeconds(.01f);
        }
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

        // switch (type)
        // {
        //     case Type.Trigger:
        //         lineRenderer.colorGradient = triggerGradient;
        //         break;
        //     case Type.Primary:
        //         lineRenderer.colorGradient = primaryGradient;
        //         break;
        //     case Type.Secondary:
        //         lineRenderer.colorGradient = secondaryGradient;
        //         break;
        // }
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

    private Gradient ColorGradient(Color color, float stress, bool hover)
    {
        Gradient gradient = new Gradient();
        color = hover ? color * .7f : color; // darken color if hovering
        color *= 1 - Mathf.Pow(stress, 2); // darken based on stress
        // TODO: can i make it flash based on time, increasing intensity with stress?
        gradient.colorKeys = new[]
        {
            new GradientColorKey(Color.black, 0),
            new GradientColorKey(color, .1f),
            new GradientColorKey(color, .9f),
            new GradientColorKey(Color.black, 1)
        };
        return gradient;
    }
}
