using UnityEngine;

public class OutputJack : Jack
{
    #if UNITY_EDITOR
    protected override void SetSprite(bool dt)
    {
        var filepath = dt ? "Sprites/Jacks/jack dark out" : "Sprites/Jacks/jack light out";
        GetComponent<SpriteRenderer>().sprite = Resources.Load<Sprite>(filepath);
    }
    #endif

    protected override void UpdateValidity(Wire activeWire)
    {
        base.UpdateValidity(activeWire);
        if (activeWire.nextModule == null)
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
        var myMod = transform.gameObject.GetComponentInParent<Module>();
        if (myMod is SecondaryModule)
        {
            return "This jack sends a value downstream.";
        }
        else
        {
            return "This jack sends a trigger downstream.";
        }
    }

    public override string Info()
    {
        var myMod = transform.gameObject.GetComponentInParent<Module>();
        foreach (var wire in myMod.childWires)
        {
            if (wire.GetComponent<Wire>().nextModule != null && wire.GetComponent<Wire>().previousModuleJack == gameObject)
            {
                return $"Connected to {wire.GetComponent<Wire>().nextModule.name} downstream.";
            }
        }

        return "Not connected downstream.";
    }
}
