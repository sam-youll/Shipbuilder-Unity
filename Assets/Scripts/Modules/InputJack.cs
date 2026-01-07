using TMPro;
using UnityEngine;

public class InputJack : Jack
{
    #if UNITY_EDITOR
    protected override void SetSprite(bool dt)
    {
        var filepath = dt ? "Sprites/Jacks/jack dark in" : "Sprites/Jacks/jack light in";
        GetComponent<SpriteRenderer>().sprite = Resources.Load<Sprite>(filepath);
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
