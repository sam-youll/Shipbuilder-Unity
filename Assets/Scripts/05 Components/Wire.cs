using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;
using UnityEngine.Serialization;
using Random = UnityEngine.Random;

public class Wire : MonoBehaviour, ITooltipInfo, ISelectable
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

    public bool isConnected = false;

    public bool invisible = false;

    public UnityEvent connected;

    private bool grabbed;
    private int grabbedIndex;
    private Vector3 grabStartPos;
    public float grabBreakDistance = 4;

    public Texture2D baseTexture;
    public Texture2D flippedTexture;
    
    public bool dying; // this gets flipped when a wire deletes itself
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        color = Color.HSVToRGB(Random.value, .5f, 1);
        
        if (!invisible)
        {
            if (transform.parent.CompareTag("OutputJack"))
            {
                // Debug.Log($"parent is output jack: {transform.parent.transform.parent.gameObject}");
                previousModuleJack = transform.parent.gameObject;
                previousModule = previousModuleJack.GetComponent<Jack>().Parent();

                if (previousModule.TryGetComponent(out Subpatch subpatch))
                {
                    previousModule = subpatch.subpatchDict[^1].module;
                }
            }
            else if (transform.parent.CompareTag("InputJack"))
            {
                // Debug.Log($"parent is input jack: {transform.parent.transform.parent.gameObject}");
                nextModuleJack = transform.parent.gameObject;
                nextModule = nextModuleJack.GetComponent<Jack>().Parent();
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

            EventBus.Instance.updateJackValidity.Invoke(this);
        }
    }

    // Update is called once per frame
    void Update()
    {
        var mousePos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
        mousePos.z = 0;
        #region Grabbing
        bool overWire = false;
        if (isConnected)
        {
            if (UIManager.Instance.RaycastResultsContains(gameObject))
            {
                overWire = true;
            }
        }
        
        if (overWire && isConnected || grabbed)
        {

            if (Input.GetMouseButtonDown(0))
            {
                grabbed = true;
                grabStartPos = mousePos;
                grabbedIndex = 1;
                Vector3[] positions = new Vector3[points];
                lineRenderer.GetPositions(positions);
                for (var i = 0; i < positions.Length; i++)
                {
                    if (((Vector2)positions[i] - (Vector2)mousePos).magnitude <
                        ((Vector2)positions[grabbedIndex] - (Vector2)mousePos).magnitude)
                    {
                        grabbedIndex = i;
                    }
                }

                if (UIManager.Instance.RaycastResultsContains(previousModuleJack))
                {
                    grabbedIndex = 0;
                    grabbed = false;
                    previousModule.GetComponent<Module>().childWires.Remove(gameObject);
                    previousModuleJack = null;
                    previousModule = null;
                    isConnected = false;
                    EventBus.Instance.updateJackValidity.Invoke(this);
                }
                else if (UIManager.Instance.RaycastResultsContains(nextModuleJack))
                {
                    grabbedIndex = points - 1;
                    grabbed = false;
                    if (nextModule.TryGetComponent(out ModuleRack moduleRack))
                    {
                        if (moduleRack is Weapon weapon)
                        {
                            if (nextModuleJack == weapon.patchEndJack)
                            {
                                weapon.parentWire = null;
                            }
                            else if (nextModuleJack == weapon.energyInJack)
                            {
                                weapon.parentEnergyWire = null;
                            }
                        }
                        else
                        {
                            moduleRack.parentWire = null;
                        }
                    }
                    else
                    {
                        nextModule.GetComponent<Module>().parentWires.Remove(gameObject);
                    }
                    nextModule = null;
                    nextModuleJack = null;
                    isConnected = false;
                    EventBus.Instance.updateJackValidity.Invoke(this);
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
        else if (isConnected && Input.GetMouseButtonDown(0))
        {
            // picking up start of wire
            if (UIManager.Instance.RaycastResultsContains(previousModuleJack))
            {
                grabbedIndex = 0;
                grabbed = false;
                previousModule.GetComponent<Module>().childWires.Remove(gameObject);
                previousModuleJack = null;
                previousModule = null;
                isConnected = false;
                EventBus.Instance.updateJackValidity.Invoke(this);
            }
            // picking up end of wire
            else if (UIManager.Instance.RaycastResultsContains(nextModuleJack))
            {
                grabbedIndex = points - 1;
                grabbed = false;
                if (nextModule.TryGetComponent(out ModuleRack moduleRack))
                {
                    if (moduleRack is Weapon weapon)
                    {
                        if (nextModuleJack == weapon.patchEndJack)
                        {
                            weapon.parentWire = null;
                        }
                        else if (nextModuleJack == weapon.energyInJack)
                        {
                            weapon.parentEnergyWire = null;
                        }
                    }
                    else
                    {
                        moduleRack.parentWire = null;
                    }
                }
                else
                {
                    nextModule.GetComponent<Module>().parentWires.Remove(gameObject);
                }
                nextModule = null;
                nextModuleJack = null;
                isConnected = false;
                EventBus.Instance.updateJackValidity.Invoke(this);
            }
        }

        if (grabbed)
        {
            Vector3[] positions = new Vector3[points];
            var lerpPos = Vector2.Lerp(positions[grabbedIndex], mousePos, 1f);
            var newPos = new Vector3(lerpPos.x, lerpPos.y, positions[grabbedIndex].z);
            lineRenderer.SetPosition(grabbedIndex, newPos);

            if (Input.GetMouseButtonUp(0))
            {
                grabbed = false;
                EventBus.Instance.updateJackValidity.Invoke(this);
            }

            if ((grabStartPos - mousePos).magnitude > grabBreakDistance)
            {
                DeleteSelf();
            }
        }
        #endregion

        #region Dropping
        // when letting go of mouse click, either connect or destroy wire
        if (Input.GetMouseButtonUp(0) && !isConnected)
        {
            // Look for jacks under the mouse
            RaycastHit2D hit = Physics2D.Raycast(mousePos,Vector2.zero,Mathf.Infinity, LayerMask.GetMask("Jacks"));
            if (hit && !dying)
            {
                if (!hit.collider.gameObject.GetComponent<Jack>().valid)
                {
                    DeleteSelf();
                }
                else
                {
                    var parentGameObject = hit.collider.gameObject.GetComponent<Jack>().Parent();
                    if (parentGameObject.TryGetComponent(out Module module))
                    {
                        if (hit.collider.TryGetComponent(out InputJack inputJack))
                        {
                            nextModuleJack = hit.collider.gameObject;
                            nextModule = parentGameObject;
                            module.parentWires.Add(gameObject);
                        }
                        else if (hit.collider.TryGetComponent(out OutputJack outputJack))
                        {
                            previousModuleJack = hit.collider.gameObject;
                            previousModule = parentGameObject;
                            module.childWires.Add(gameObject);
                        }
                    }
                    else if (parentGameObject.TryGetComponent(out ModuleRack moduleRack))
                    {
                        nextModuleJack = hit.collider.gameObject;
                        nextModule = parentGameObject;
                        
                        if (moduleRack is Weapon weapon)
                        {
                            if (hit.collider.gameObject == weapon.patchEndJack)
                            {
                                weapon.parentWire = gameObject;
                            }
                            else if (hit.collider.gameObject == weapon.energyInJack)
                            {
                                weapon.parentEnergyWire = gameObject;
                            }
                        }
                        else
                        {
                            moduleRack.parentWire = gameObject;
                        }
                    }
                    
                    isConnected = true;
                }

                // TODO: what am I doing here
                if (isConnected && (previousModule == null || nextModule == null))
                {
                    // throw new Exception("what the fuck");
                    DeleteSelf();
                }
                
                if (!dying && isConnected && previousModule.TryGetComponent(out SecondaryModule secondaryModule))
                {
                    // might not work if you plug into primary input jack, not sure though
                    if (!nextModule.TryGetComponent(out ModuleRack moduleRack))
                    {
                        var inputIndex = nextModule.GetComponent<Module>().inputJacks.FindIndex(x => x == nextModuleJack);
                        secondaryModule.myInputIndex = inputIndex;
                    }
                }
                
                connected.Invoke();
                EventBus.Instance.wireConnected.Invoke(previousModule, nextModule);
                EventBus.Instance.updateJackValidity.Invoke(this);
            }
            else
            {
                EventBus.Instance.updateJackValidity.Invoke(this);
                DeleteSelf();
            }
        }
        #endregion
        
        #region Visuals
        
        if (!invisible)
        {
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
            lineRenderer.colorGradient = ColorGradient(color,
                grabbed ? (grabStartPos - mousePos).magnitude / grabBreakDistance : 0, grabbed || overWire);
        }
        
        #endregion
    }

    private void FixedUpdate()
    {
        var mousePos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
        mousePos.z = 0;
        
        if (!invisible)
        {
            if (!dying)
            {
                if (isConnected || isConnected)
                {
                    UpdatePoints(Vector2.down * .1f, previousModuleJack.GetComponent<Collider2D>().bounds.center, nextModuleJack.GetComponent<Collider2D>().bounds.center, false, false, grabbed ? (grabStartPos -  mousePos).magnitude / grabBreakDistance : 0);
                }
                else if (nextModule == null)
                {
                    
                    UpdatePoints(Vector2.down * .1f, previousModuleJack.GetComponent<Collider2D>().bounds.center, mousePos, false, true, grabbed ? (grabStartPos -  mousePos).magnitude / grabBreakDistance : 0);
                }
                else if (previousModule == null)
                {
                    UpdatePoints(Vector2.down * .1f, mousePos, nextModuleJack.GetComponent<Collider2D>().bounds.center, true, false, grabbed ? (grabStartPos -  mousePos).magnitude / grabBreakDistance : 0);
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
        var zOffset = 3f;
        force *= 1 - stress;
        // calculate points
        Vector3[] targetPositions = new Vector3[points];
        for (int i = 0; i < points; i++)
        {
            if (i == 0)
            {
                startPos.z -= zOffset;
                targetPositions[0] = startPos;
                
                // Aim assist
                if (draggingStart)
                {
                    bool overJack = UIManager.Instance.RaycastResultsContains(x => x.CompareTag("OutputJack"), out var jack);

                    if (overJack)
                    {
                        var jackPos = jack.transform.position;
                        jackPos.z -= zOffset;
                        targetPositions[i] = jackPos;
                    }
                }
            }
            else if (i == points - 1)
            {
                targetPositions[i] = endPos;
                targetPositions[i].z -= zOffset;
                
                // Aim assist
                if (draggingEnd)
                {
                    var overJack = false;
                    GameObject jack = null;
                    if (UIManager.Instance.RaycastResultsContains(x => x.CompareTag("InputJack"), out var match))
                    {
                        overJack = true;
                        jack = match;
                    }

                    if (overJack)
                    {
                        var jackPos = jack.transform.position;
                        jackPos.z -= zOffset;
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
        transform.SetParent(null);
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
            if (nextModule.TryGetComponent(out ModuleRack moduleRack))
            {
               moduleRack.parentWire = null;
            }
            else
            {
                nextModule.GetComponent<Module>().parentWires.Remove(gameObject);
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
        EventBus.Instance.updateJackValidity.Invoke(this);
        Vector3[] positions = new Vector3[points];
        Vector2 deletePos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
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
        
        if (isConnected || dying)
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
                    jack.GetComponentInParent<Module>() != null && jack.GetComponentInParent<Module>().parentWires.Count > 0)
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
        if (!isConnected)
            return;
        
        // Debug.Log($"{previousModule.name} triggered {nextModule.name} via {gameObject.name} with no arguments.");
        if (nextModule.TryGetComponent(out Weapon weapon))
        {
            if (nextModuleJack == weapon.energyInJack)
            {
                // TODO: try to add energy
                // weapon.energyReservoir.AddEnergy();
            }
            else if (nextModuleJack == weapon.patchEndJack)
            {
                weapon.Fire();
            }
        }
        else if (nextModule.TryGetComponent(out Module module))
        {
            module.Trigger();
        }
    }

    public void Trigger(float value)
    {
        if (!isConnected)
            return;
        
        // Debug.Log($"{previousModule.name} triggered {nextModule.name} via {gameObject.name} with a value of {value}");
        if (nextModule.TryGetComponent(out Weapon weapon))
        {
            weapon.Fire();
        }
        else if (nextModule.TryGetComponent(out Module module))
        {
            module.Trigger(value);
        }
    }
    
    public void Trigger(float value, int inputIndex)
    {
        if (!isConnected)
            return;
        
        // Debug.Log($"{previousModule.name} triggered {nextModule.name} via {gameObject.name} with a value of {value} to secondary input jack {inputIndex}");
        if (nextModule.TryGetComponent(out Weapon weapon))
        {
            weapon.Fire();
        }
        else if (nextModule.TryGetComponent(out Module module))
        {
            module.Trigger(value, inputIndex);
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

    public string Description()
    {
        return "Carries values and triggers between modules and systems.";
    }

    public string Info()
    {
        var info = "";
        if (previousModule != null)
        {
            info += $"Upstream: {previousModule.name}\n";
        }
        else
        {
            info += "Not plugged in upstream.\n";
        }

        if (nextModule != null)
        {
            info += $"Downstream: {nextModule.name}\n";
        }
        else
        {
            info += "Not plugged in downstream.\n";
        }

        return info;
    }

    public bool Warning(out string message)
    {
        message = "";
        return false;
    }

    public void Select()
    {
        
    }
}
