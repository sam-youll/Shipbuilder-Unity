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
        GetComponentInChildren<TextMeshPro>().color = !darkTheme ? Color.white : Color.black;
        if (transform.parent.TryGetComponent(out Module module))
        {
            GetComponentInChildren<TextMeshPro>().text = module.inputJacks.FindIndex(x => x.GetComponent<InputJack>() == this).ToString();
        }
    }
}
