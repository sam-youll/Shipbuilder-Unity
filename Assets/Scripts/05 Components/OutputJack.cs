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
}
