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

    public Texture2D baseTexture;
    public Texture2D flippedTexture;
    
    private bool dying; // this gets flipped when a wire deletes itself
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        color = Color.HSVToRGB(Random.value, .5f, 1);
        
        if (!invisible)
        {
            if (transform.parent.CompareTag("OutputJack"))
            {
                previousModuleJack = transform.parent.gameObject;
                previousModule = previousModuleJack.transform.parent.gameObject;

                if (previousModule.TryGetComponent(out Subpatch subpatch))
                {
                    previousModule = subpatch.subpatchDict[^1].module;
                }
            }
            else if (transform.parent.CompareTag("InputJack"))
            {
                nextModuleJack = transform.parent.gameObject;
                nextModule = nextModuleJack.transform.parent.gameObject;
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
            
            UpdateJackHighlights();
        }
    }

    // Update is called once per frame
    void Update()
    {
        #region Grabbing
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
                for (var i = 0; i < positions.Length; i++)
                {
                    if ((positions[i] - Global.Instance.mousePos).magnitude <
                        (positions[grabbedIndex] - Global.Instance.mousePos).magnitude)
                    {
                        grabbedIndex = i;
                    }
                }

                if (Global.Instance.RaycastResultsContains(previousModuleJack))
                {
                    grabbedIndex = 0;
                    grabbed = false;
                    previousModule.GetComponent<Module>().childWires.Remove(gameObject);
                    previousModuleJack = null;
                    previousModule = null;
                    connectedToModule = false;
                    UpdateJackHighlights();
                }
                else if (Global.Instance.RaycastResultsContains(nextModuleJack))
                {
                    grabbedIndex = points - 1;
                    grabbed = false;
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
                    }
                    nextModule = null;
                    nextModuleJack = null;
                    connectedToModule = false;
                    UpdateJackHighlights();
                }
                else if (grabbedIndex == 0)
                {
                    grabbedIndex++;
                }
                else if (grabbedIndex == points - 1)
                {
                    grabbedIndex--;
                }

                // if (grabbedIndex == 0)
                // {
                //     
                // }
                // else if (grabbedIndex == points - 1)
                // {
                //     
                // }
            }

            if (Input.GetMouseButtonDown(1))
            {
                DeleteSelf();
            }
        }
        // edge case where you grab the jack but you're not technically hitting the wire itself
        // we still want to grab the end of the wire
        else if (connectedToModule && Input.GetMouseButtonDown(0))
        {
            if (Global.Instance.RaycastResultsContains(previousModuleJack))
            {
                grabbedIndex = 0;
                grabbed = false;
                previousModule.GetComponent<Module>().childWires.Remove(gameObject);
                previousModuleJack = null;
                previousModule = null;
                connectedToModule = false;
                UpdateJackHighlights();
            }
            else if (Global.Instance.RaycastResultsContains(nextModuleJack))
            {
                grabbedIndex = points - 1;
                grabbed = false;
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
                }
                nextModule = null;
                nextModuleJack = null;
                connectedToModule = false;
                UpdateJackHighlights();
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
        #endregion

        #region Dropping
        // when letting go of mouse click, either connect or destroy wire
        if (Input.GetMouseButtonUp(0) && !connectedToModule)
        {
            // Look for jacks under the mouse
            RaycastHit2D hit = Physics2D.Raycast(Global.Instance.mousePos,Vector2.zero,Mathf.Infinity, LayerMask.GetMask("Jacks"));
            if (hit && !dying)
            {
                // hit weapon output
                if (hit.collider.gameObject.transform.parent.gameObject.CompareTag("Weapon"))
                {
                    if (previousModule == null) // not sure how this would ever happen
                    {
                        DeleteSelf();
                    }
                    else
                    {
                        nextModuleJack = hit.collider.gameObject;
                        nextModule = nextModuleJack.transform.parent.gameObject;
                        nextModule.GetComponent<Weapon>().previousModule = previousModule;
                    }
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
                    PatchManager.Instance.UpdateAllPatches();
                    connectedToModule = true;
                    connected.Invoke();
                }
                // hit a module
                else if (hit.collider.gameObject.CompareTag("InputJack"))
                {
                    // is it the module I'm already connected to?
                    // is there already a wire there?
                    if (nextModule != null ||
                        hit.collider.gameObject.transform.parent.gameObject == previousModule ||
                        hit.collider.gameObject.transform.parent.gameObject == nextModule ||
                        hit.collider.gameObject.GetComponentInParent<Module>().parentWires.Count > 0)
                    {
                        DeleteSelf();
                    }
                    // ok we're good
                    else
                    {
                        nextModuleJack = hit.collider.gameObject;
                        nextModule = nextModuleJack.transform.parent.gameObject;
                        nextModule.GetComponent<Module>().parentWires.Add(gameObject);
                        connectedToModule = true;
                        connected.Invoke();
                        PatchManager.Instance.UpdateAllPatches();
                    }
                }
                else if (hit.collider.gameObject.CompareTag("OutputJack"))
                {
                    // is it the module I'm already connected to?
                    // is there already a wire there?
                    if (previousModule != null ||
                        hit.collider.gameObject.transform.parent.gameObject == previousModule ||
                        hit.collider.gameObject.transform.parent.gameObject == nextModule ||
                        hit.collider.gameObject.GetComponentInParent<Module>().childWires.Count > 0)
                    {
                        DeleteSelf();
                    }
                    // alright go ahead
                    else
                    {
                        previousModuleJack = hit.collider.gameObject;
                        previousModule = previousModuleJack.transform.parent.gameObject;
                        previousModule.GetComponent<Module>().childWires.Add(gameObject);
                        connectedToModule = true;
                        connected.Invoke();
                        PatchManager.Instance.UpdateAllPatches();
                    }
                }
                
                if (!dying && previousModule != null && previousModule.TryGetComponent(out SecondaryModule secondaryModule))
                {
                    // might not work if you plug into primary input jack, not sure though
                    var inputIndex = nextModule.GetComponent<Module>().inputJacks.FindIndex(x => x == nextModuleJack);
                    secondaryModule.myInputIndex = inputIndex;
                }
                
                
                // determine wire type
                UpdateWireType();
                UpdateJackHighlights();
            }
            else
            {
                PatchManager.Instance.UpdateAllPatches();
                DeleteSelf();
            }
        }
        #endregion
        
        #region Visuals
        // flip texture as needed to maintain appearance of being lit from above
        if (lineRenderer.GetPosition(points - 1).x < lineRenderer.GetPosition(0).x)
        {
            lineRenderer.material.mainTexture = baseTexture;
        }
        else
        {
            lineRenderer.material.mainTexture = flippedTexture;
        }
        
        // scrolling texture
        var lrMov = lineRenderer.material.mainTextureOffset;
        lrMov.x -= Time.deltaTime * 2f;
        if (lrMov.x < 0)
        {
            lrMov.x += 1;
        }
        lineRenderer.material.mainTextureOffset = lrMov;
        lineRenderer.colorGradient = ColorGradient(color, grabbed ? (grabStartPos -  Global.Instance.mousePos).magnitude / grabBreakDistance : 0, grabbed || overWire);
        #endregion
    }

    private void FixedUpdate()
    {
        if (!invisible)
        {
            if (!dying)
            {
                if (connectedToModule)
                {
                    UpdatePoints(Vector2.down * .1f, previousModuleJack.transform.position, nextModuleJack.transform.position, false, false, grabbed ? (grabStartPos -  Global.Instance.mousePos).magnitude / grabBreakDistance : 0);
                }
                else if (nextModule == null)
                {
                    
                    UpdatePoints(Vector2.down * .1f, previousModuleJack.transform.position, Global.Instance.mousePos, false, true, grabbed ? (grabStartPos -  Global.Instance.mousePos).magnitude / grabBreakDistance : 0);
                }
                else if (previousModule == null)
                {
                    UpdatePoints(Vector2.down * .1f, Global.Instance.mousePos, nextModuleJack.transform.position, true, false, grabbed ? (grabStartPos -  Global.Instance.mousePos).magnitude / grabBreakDistance : 0);
                }
                else
                {
                    DeleteSelf();
                }
            }
        }
    }


    private void UpdatePoints(Vector3 force, Vector3 startPos, Vector3 endPos, bool draggingStart, bool draggingEnd, float stress)
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
                
                // Aim assist
                if (draggingStart)
                {
                    var overJack = false;
                    GameObject jack = null;
                    foreach (var result in Global.Instance.raycastHits)
                    {
                        if (result.collider.gameObject.CompareTag("OutputJack"))
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
            else if (i == points - 1)
            {
                targetPositions[i] = endPos;
                targetPositions[i].z -= 1f;
                
                // Aim assist
                if (draggingEnd)
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
        if (nextModule != null)
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
        if (previousModule != null)
        {
            previousModule.GetComponent<Module>().childWires.Remove(gameObject);
            if (previousModule.transform.parent.TryGetComponent(out Subpatch subpatch))
            {
                subpatch.childWires.Remove(gameObject);
            }
        }
        UpdateJackHighlights();
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
            UpdatePoints(Vector2.zero, positions[0], positions[^1], false, false, 0);
            yield return new WaitForSeconds(.01f);
        }
        Destroy(gameObject);
    }

    private void UpdateJackHighlights()
    {
        // TODO: move this function into Jack.cs and call it through the Global list of all jacks
        
        if (connectedToModule || dying)
        {
            // reset all highlights
            foreach (var jack in Global.Instance.allJacks)
            {
                jack.GetComponent<SpriteRenderer>().color = Color.white;
            }
        }
        else if (nextModule == null)
        {
            // highlight all input jacks
            foreach (var jack in Global.Instance.allJacks)
            {
                if (jack.CompareTag("OutputJack") ||
                    jack.transform.parent.gameObject == previousModule ||
                    jack.GetComponentInParent<Module>().parentWires.Count > 0)
                {
                    jack.GetComponent<SpriteRenderer>().color = new Color(.5f, .5f, .5f, 1);
                }
                else
                {
                    jack.GetComponent<SpriteRenderer>().color = Color.white;
                }
            }
        }
        else if (previousModule == null)
        {
            // highlight all output jacks
            foreach (var jack in Global.Instance.allJacks)
            {
                if (jack.CompareTag("InputJack") ||
                    jack.transform.parent.gameObject == nextModule ||
                    jack.GetComponentInParent<Module>().childWires.Count > 0)
                {
                    jack.GetComponent<SpriteRenderer>().color = new Color(.5f, .5f, .5f, 1);
                }
                else
                {
                    jack.GetComponent<SpriteRenderer>().color = Color.white;
                }
            }
        }
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
            new GradientColorKey(new Color(.06667f, .06667f, .06667f, 1), 0),
            new GradientColorKey(color, .1f),
            new GradientColorKey(color, .9f),
            new GradientColorKey(new Color(.06667f, .06667f, .06667f, 1), 1)
        };
        return gradient;
    }
}
