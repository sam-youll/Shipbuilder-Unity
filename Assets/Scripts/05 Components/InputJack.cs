using TMPro;
using UnityEngine;
using UnityEngine.UI;

public class InputJack : Jack
{
    #if UNITY_EDITOR
    protected override void SetSprite(bool dt)
    {
        // var filepath = dt ? "Sprites/Jacks/jack dark in" : "Sprites/Jacks/jack light in";
        // GetComponent<Image>().sprite = Resources.Load<Sprite>(filepath);
    }
    #endif

    protected override void UpdateValidity(Wire activeWire)
    {
        base.UpdateValidity(activeWire);
        if (activeWire.previousModule == null)
        {
            valid = false;
        }
        if (activeWire.dying)
        {
            valid = true;
        }
        
        UpdateHighlights();
    }

    public override string Description()
    {
        var parentIsModule = transform.parent.TryGetComponent(out Module parentModule);
        if (parentIsModule)
        {
            var type = parentModule.inputJacks.FindIndex(x => x == gameObject);
            switch (type)
            {
                case 0:
                    return "This jack receives a trigger from the last upstream module";
                    break;
                case 1:
                    return "This jack receives a value from the last upstream module";
                    break;
            }
        }
        return "This jack receives a trigger from the last upstream module";
    }

    public override string Info()
    {
        if (transform.parent.TryGetComponent(out Module module))
        {
            foreach (var wire in module.parentWires)
            {
                if (wire.GetComponent<Wire>().previousModule != null &&
                    wire.GetComponent<Wire>().nextModuleJack == gameObject)
                {
                    return $"Connected to {wire.GetComponent<Wire>().previousModule.name} upstream.";
                }
            }
        }
        else if (transform.parent.TryGetComponent(out ModuleRack rack))
        {
            if (rack.parentWire != null)
            {
                if (rack.parentWire.GetComponent<Wire>().previousModule != null &&
                    rack.parentWire.GetComponent<Wire>().nextModuleJack == gameObject)
                {
                    return $"Connected to {rack.parentWire.GetComponent<Wire>().previousModule.name} upstream.";
                }
            }
        }

        return "Not connected upstream.";
    }

    protected override void Start()
    {
        base.Start();
        if (transform.childCount > 0 && 
            transform.GetChild(0).TryGetComponent(out TextMeshPro tmp) &&
            transform.parent.TryGetComponent(out Module module))
        {
            tmp.color = darkTheme ? Color.white : Color.black;
            GetComponentInChildren<TextMeshPro>().text = module.inputJacks.FindIndex(x => x.GetComponent<InputJack>() == this).ToString();
        }
    }
}
