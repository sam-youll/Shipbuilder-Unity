using System;
using System.Collections.Generic;
using SaintsField;
using UnityEngine;
using UnityEngine.UI;

public abstract class ModuleRack : MonoBehaviour, ITooltipInfo
{
    [Header("Components")]
    [GetComponent] public BoxCollider2D coll;
    [GetComponent] public SpriteRenderer sr;
    public GameObject patchEndPanel;
    public GameObject inputJack;
    public GameObject parentWire;
    public GameObject label;

    [Header("Properties")]
    public Vector2Int dimensionsMax = new(20, 10);
    [OnValueChanged(nameof(SetDimensions))] public Vector2Int dimensions = new(4, 4);
    public bool enemySystem;

    protected virtual void Start()
    {
        EventBus.Instance.rackEditXUp.AddListener(OnXUp);
        EventBus.Instance.rackEditYUp.AddListener(OnYUp);
        EventBus.Instance.rackEditYDown.AddListener(OnYDown);
        EventBus.Instance.rackEditXDown.AddListener(OnXDown);
    }

    private void SetDimensions()
    {
        dimensions = new Vector2Int(Mathf.Clamp(dimensions.x, 2, dimensionsMax.x), Mathf.Clamp(dimensions.y, 2, dimensionsMax.y));
        coll.size = new Vector2(dimensions.x, dimensions.y);
        sr.size = new Vector2(dimensions.x + 1.5f, dimensions.y + 1.5f);
        patchEndPanel.transform.localPosition = new Vector3((float)dimensions.x/2, -(float)dimensions.y/2 - .5f, -.1f);
        inputJack.transform.localPosition = new Vector3((float)dimensions.x/2 + .375f, -(float)dimensions.y/2 - .5f, -.2f);
        label.transform.localPosition = new Vector3(-(float)dimensions.x / 2 + .75f, -(float)dimensions.y / 2 - .25f, -.2f);

        if (gameObject.TryGetComponent(out Reactor reactor))
        {
            reactor.energyReservoirDisplay.transform.localPosition = new Vector3(-(float)dimensions.x / 2 + 1.155f, -(float)dimensions.y / 2 - 1.5f, -.2f);
        }

        if (gameObject.TryGetComponent(out Weapon weapon))
        {
            weapon.heatOverlay.rectTransform.sizeDelta = new Vector2(dimensions.x + 1, dimensions.y + 1);
        }
    }

    private void OnXUp(GameObject target)
    {
        if (target != gameObject) return;
        dimensions.x++;
        SetDimensions();
    }

    private void OnXDown(GameObject target)
    {
        if (target != gameObject) return;
        dimensions.x--;
        SetDimensions();
    }

    private void OnYUp(GameObject target)
    {
        if (target != gameObject) return;
        dimensions.y++;
        SetDimensions();
    }

    private void OnYDown(GameObject target)
    {
        if (target != gameObject) return;
        dimensions.y--;
        SetDimensions();
    }

    public abstract string Description();

    public string Info()
    {
        var info = CompletePatch() ? "Complete patch\n" : "Patch is incomplete\n";

        info += "~~~\n";

        if (this is Reactor reactor)
        {
            info += "Weapon Stats:\n";
            foreach (var kvp in reactor.ReactorStats())
            {
                if (kvp.Key == "bulletType")
                {
                    info += Funcs.ConvertCamelCase(kvp.Key.ToString()) + ": " + Enum.GetName(typeof(Common.BulletType), (int)kvp.Value) + "\n";
                }
                else if (kvp.Key == "soundType")
                {
                    info += Funcs.ConvertCamelCase(kvp.Key.ToString()) + ": " + Enum.GetName(typeof(Common.SoundType), (int)kvp.Value) + "\n";
                }
                else
                {
                    info += Funcs.ConvertCamelCase(kvp.Key.ToString()) + ": " + kvp.Value + "\n";
                }
            }
        }
        else if (this is Weapon weapon)
        {
            info += "Weapon Stats:\n";
            foreach (var kvp in weapon.WeaponStats())
            {
                if (kvp.Key == "bulletType")
                {
                    info += Funcs.ConvertCamelCase(kvp.Key.ToString()) + ": " + Enum.GetName(typeof(Common.BulletType), (int)kvp.Value) + "\n";
                }
                else if (kvp.Key == "soundType")
                {
                    info += Funcs.ConvertCamelCase(kvp.Key.ToString()) + ": " + Enum.GetName(typeof(Common.SoundType), (int)kvp.Value) + "\n";
                }
                else
                {
                    info += Funcs.ConvertCamelCase(kvp.Key.ToString()) + ": " + kvp.Value + "\n";
                }
            }
        }
    
        return info;
    }

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
        return patch;
    }

    public bool CompletePatch()
    {
        var patch = ActivePatch();
        var nonEmpty = patch.Count > 0;
        var clockCheck = patch.Exists(x => x is ClockModule);
        var sourceCheck = patch.Exists(x => x is SourceModule);
        return nonEmpty && clockCheck && sourceCheck;
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
}
