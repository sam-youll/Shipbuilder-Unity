using System;
using SaintsField;
using UnityEngine;

public class ModuleRack : MonoBehaviour
{
    [GetComponent] public BoxCollider2D coll;
    [GetComponent] public SpriteRenderer sr;
    public GameObject patchEndPanel;
    public GameObject inputJack;
    public GameObject label;
    [OnValueChanged(nameof(SetDimensions))] public Vector2Int dimensions = new(4, 4);

    public Vector2Int dimensionsMax = new(20, 10);

    private void Start()
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
}
