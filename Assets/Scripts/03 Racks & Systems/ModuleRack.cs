using System;
using System.Collections.Generic;
using System.Linq;
using SaintsField;
using SaintsField.Playa;
using UnityEngine;
using UnityEngine.UI;

public abstract class ModuleRack : MonoBehaviour, ITooltipInfo
{
    [Header("Components")]
    [GetComponent] public BoxCollider2D coll;
    public GameObject patchEndJack;
    public GameObject parentWire;

    [Header("Properties")]
    public Vector2Int dimensionsMax = new(50, 50);
    [OnValueChanged(nameof(SetDimensions))] public Vector2Int dimensions = new(4, 4);
    public bool enemySystem;
    public float maxHealth = 30;
    public float health;
    public SwitchComponent transformControlSwitch;
    public GameObject transformControls;
    private Vector2 handleDragOffset;
    
    // ENERGY
    public EnergyReservoir energyReservoir;

    protected virtual void Start()
    {
        EventBus.Instance.rackEditXUp.AddListener(OnXUp);
        EventBus.Instance.rackEditYUp.AddListener(OnYUp);
        EventBus.Instance.rackEditYDown.AddListener(OnYDown);
        EventBus.Instance.rackEditXDown.AddListener(OnXDown);

        health = maxHealth;
    }

    protected virtual void Update()
    {
        SnapToGrid();
        
        slowTimer -= Time.deltaTime;
        slowTimer = Mathf.Max(0, slowTimer);
        
        
        // transform controls
        if (!enemySystem)
        {
            transformControls.SetActive(transformControlSwitch.on);

            if (transformControls.activeSelf)
            {
                for (var i = 0; i < transformControls.transform.childCount; i++)
                {
                    Vector2 mousePos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
                    var handle = transformControls.transform.GetChild(i).gameObject;
                    if (Input.GetMouseButtonDown(0))
                    {
                        if (UIManager.Instance.TopRaycastResult() == handle || UIManager.Instance.cursor.heldObject == handle)
                        {
                            handleDragOffset = mousePos - (Vector2)handle.transform.position;
                            
                            Debug.Log($"mousePos: {mousePos}, handle: {handle.transform.position}, offset: {handleDragOffset}");
                        }
                    }
                    
                    if (UIManager.Instance.cursor.heldObject == handle)
                    {
                        var rt = transformControls.GetComponent<RectTransform>();
                        var oMax = rt.offsetMax;
                        var oMin = rt.offsetMin;
                        var corners = new Vector3[4];
                        GetComponent<RectTransform>().GetWorldCorners(corners); // clockwise from bottom left
                        
                        switch (i)
                        {
                            case 0:
                                // TOP LEFT
                                oMax.y = mousePos.y - corners[1].y + .21875f - handleDragOffset.y;
                                oMin.x = mousePos.x - corners[1].x - .21875f - handleDragOffset.x;
                                break;
                            case 1:
                                // TOP RIGHT
                                oMax.x = mousePos.x - corners[2].x + .21875f - handleDragOffset.x;
                                oMax.y = mousePos.y - corners[2].y + .21875f - handleDragOffset.y;
                                break;
                            case 2:
                                // BOTTOM LEFT
                                oMin.x = mousePos.x - corners[0].x - .21875f - handleDragOffset.x;
                                oMin.y = mousePos.y - corners[0].y - .21875f - handleDragOffset.y;
                                break;
                            case 3:
                                // BOTTOM RIGHT
                                oMax.x = mousePos.x - corners[3].x + .21875f - handleDragOffset.x;
                                oMin.y = mousePos.y - corners[3].y - .21875f - handleDragOffset.y;
                                break;
                            case 4:
                                // TOP MIDDLE
                                var notCorner = new Vector2(.5f * (corners[0].x + corners[3].x), corners[1].y);
                                oMax.x = .625f + mousePos.x - notCorner.x - handleDragOffset.x;
                                oMax.y = .21875f + mousePos.y - notCorner.y - handleDragOffset.y;
                                oMin.x = -.625f + mousePos.x - notCorner.x - handleDragOffset.x;
                                oMin.y = -.28125f + mousePos.y - notCorner.y - handleDragOffset.y;
                                break;
                        }
                        
                        rt.offsetMax = oMax;
                        rt.offsetMin = oMin;
                        
                        // rt.offsetMax.x -> right side (1)
                        // rt.offsetMax.y -> top side (.25)
                        // rt.offsetMin.x -> left side (.25)
                        // rt.offsetMin.y -> bottom side (.25)
                        
                        if (rt.offsetMax.x > 2)
                        {
                            var newDim = dimensions;
                            newDim.x++;
                            SetDimensions(newDim);
                            transform.position += new Vector3(.5f, 0, 0);
                        }
                        else if (rt.offsetMax.x < 0)
                        {
                            var newDim = dimensions;
                            newDim.x--;
                            SetDimensions(newDim);
                            transform.position -= new Vector3(.5f, 0, 0);
                        }

                        if (rt.offsetMax.y > 1.25f)
                        {
                            var newDim = dimensions;
                            newDim.y++;
                            SetDimensions(newDim);
                            transform.position += new Vector3(0, .5f, 0);
                        }
                        else if (rt.offsetMax.y < -.75f)
                        {
                            var newDim = dimensions;
                            newDim.y--;
                            SetDimensions(newDim);
                            transform.position -= new Vector3(0, .5f, 0);
                        }

                        if (rt.offsetMin.x < -1.25f)
                        {
                            var newDim = dimensions;
                            newDim.x++;
                            SetDimensions(newDim);
                            transform.position -= new Vector3(.5f, 0, 0);
                        }
                        else if (rt.offsetMin.x > .75f)
                        {
                            var newDim = dimensions;
                            newDim.x--;
                            SetDimensions(newDim);
                            transform.position += new Vector3(.5f, 0, 0);
                        }

                        if (rt.offsetMin.y < -1.25f)
                        {
                            var newDim = dimensions;
                            newDim.y++;
                            SetDimensions(newDim);
                            transform.position -= new Vector3(0, .5f, 0);
                        }
                        else if (rt.offsetMin.y > .75f)
                        {
                            var newDim = dimensions;
                            newDim.y--;
                            SetDimensions(newDim);
                            transform.position += new Vector3(0, .5f, 0);
                        }
                    }
                }

                if (Input.GetMouseButtonUp(0))
                {
                    var rt = transformControls.GetComponent<RectTransform>();
                    rt.offsetMax = new Vector2(1, .25f);
                    rt.offsetMin = new Vector2(-.25f, -.25f);
                }
            }
        }
    }

    private void SetDimensions(Vector2Int newDimensions)
    {
        // Debug.Log("RESIZING");
        var diff = newDimensions - dimensions;
        dimensions = new Vector2Int(Mathf.Clamp(newDimensions.x, 2, dimensionsMax.x), Mathf.Clamp(newDimensions.y, 2, dimensionsMax.y));
        GetComponent<RectTransform>().sizeDelta = new Vector2(dimensions.x + 1.5f, dimensions.y + 1.5f);
        coll.size = new Vector2(dimensions.x, dimensions.y);

        SnapToGrid();
        
        if (IsOverlapping(out var contacts))
        {
            foreach (var contact in contacts)
            {
                var positionDiff = contact.transform.position - transform.position;
                if (positionDiff.x != 0) positionDiff.x = Mathf.Sign(positionDiff.x);
                if (positionDiff.y != 0) positionDiff.y = Mathf.Sign(positionDiff.y);
                contact.transform.position += positionDiff;
                contact.GetComponent<ModuleRack>().SnapToGrid();
                
                if (contact.GetComponent<ModuleRack>().IsOverlapping(out var theirContacts))
                {
                    foreach (var c in theirContacts)
                    {
                        var pDiff = c.transform.position - contact.transform.position;
                        if (pDiff.x != 0) pDiff.x = Mathf.Sign(pDiff.x);
                        if (pDiff.y != 0) pDiff.y = Mathf.Sign(pDiff.y);
                        c.transform.position += pDiff;
                        c.GetComponent<ModuleRack>().SnapToGrid();
                    }
                    Physics2D.SyncTransforms();
                }
            }
            Physics2D.SyncTransforms();
        }
    }

    private void OnXUp(GameObject target)
    {
        if (target != gameObject) return;
        dimensions.x++;
        SetDimensions(dimensions);
    }

    private void OnXDown(GameObject target)
    {
        if (target != gameObject) return;
        dimensions.x--;
        SetDimensions(dimensions);
    }

    private void OnYUp(GameObject target)
    {
        if (target != gameObject) return;
        dimensions.y++;
        SetDimensions(dimensions);
    }

    private void OnYDown(GameObject target)
    {
        if (target != gameObject) return;
        dimensions.y--;
        SetDimensions(dimensions);
    }

    public abstract string Description();

    public virtual string Info()
    {
        var info = CompletePatch() ? "Complete patch\n" : "Patch is incomplete\n";

        info += "~~~\n";

        // if (this is Reactor reactor)
        // {
        //     info += "Weapon Stats:\n";
        //     foreach (var kvp in reactor.ReactorStats())
        //     {
        //         if (kvp.Key == "bulletType")
        //         {
        //             info += Funcs.ConvertCamelCase(kvp.Key.ToString()) + ": " + Enum.GetName(typeof(Common.BulletType), (int)kvp.Value) + "\n";
        //         }
        //         else if (kvp.Key == "soundType")
        //         {
        //             info += Funcs.ConvertCamelCase(kvp.Key.ToString()) + ": " + Enum.GetName(typeof(Common.SoundType), (int)kvp.Value) + "\n";
        //         }
        //         else
        //         {
        //             info += Funcs.ConvertCamelCase(kvp.Key.ToString()) + ": " + kvp.Value + "\n";
        //         }
        //     }
        // }
    
        return info;
    }

    public abstract bool Warning(out string message);

    public List<Module> ActivePatch()
    {
        if (enemySystem)
            return new List<Module>();

        if (parentWire == null)
            return new List<Module>();

        if (PreviousModule() == null)
            return new List<Module>();

        var patch = new List<Module>();
        var prev = PreviousModule().GetComponent<Module>();
        var loopCount = 0;
        while (prev.PreviousModule() != null)
        {
            if (loopCount > 299)
            {
                parentWire.GetComponent<Wire>().DeleteSelf();
                Debug.Log("Wire privileges revoked because you made an infinite loop.\n>:(");
                break;
            }

            loopCount++;
            // Debug.Log(prev.name);
            patch.Add(prev);

            if (prev.PreviousModule().TryGetComponent(out Module mod))
            {
                prev = mod;
            }
            else
            {
                break;
            }
        }

        patch.Add(prev);
        patch.Reverse();
        return patch;
    }

    public virtual bool CompletePatch()
    {
        return ActivePatch().Count > 0;
    }
    
    public GameObject PreviousModule()
    {
        if (parentWire == null)
        {
            return null;
        }
        else
        {
            return parentWire.GetComponent<Wire>().previousModule;
        }
    }
    
    
    public virtual void Stun(float time)
    {
        
    }

    protected float slowTimer;
    public virtual void Slow(float time)
    {
        slowTimer += time;
    }

    public void DeleteRack()
    {
        Destroy(gameObject);
    }

    public bool IsOverlapping(out List<GameObject> contacts)
    {
        Physics2D.SyncTransforms();
        var pos = transform.position;
        var size = GetComponent<RectTransform>().sizeDelta;
        size += new Vector2(3f, .5f);
        var hits = Physics2D.OverlapBoxAll(pos,  size, 0);
        contacts = new();
        foreach (var hit in hits)
        {
            if (hit.TryGetComponent(out ModuleRack _))
            {
                contacts.Add(hit.gameObject);
            }
        }
        return contacts.Count > 0;
    }

    public void SnapToGrid()
    {
        var pos = transform.position;
        pos.x = dimensions.x % 2 == 0 ? Mathf.Floor(pos.x) : Mathf.Floor(pos.x) + .5f;
        pos.y = dimensions.y % 2 == 0 ? Mathf.Floor(pos.y) : Mathf.Floor(pos.y) + .5f;
        transform.position = pos;
    }

    public virtual List<Module> ModulesOnRack()
    {
        // get all modules on the rack
        return GetComponentsInChildren<Module>().ToList();
        // if we want to filter these modules more specifically,
        // we override this method in an inherited class like Reactor
    }

    public virtual void Trigger()
    {
        
    }
}
