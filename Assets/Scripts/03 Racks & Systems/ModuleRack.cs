using System;
using SaintsField;
using UnityEngine;
using UnityEngine.UI;

public class ModuleRack : MonoBehaviour
{
    [GetComponent] public BoxCollider2D coll;
    [GetComponent] public SpriteRenderer sr;
    public GameObject patchEndPanel;
    public GameObject inputJack;
    public GameObject label;
    public GameObject energyDisplay;
    public Image cooldownDisplay;
    [OnValueChanged(nameof(SetDimensions))] public Vector2Int dimensions = new(4, 4);

    public Vector2Int dimensionsMax = new(20, 10);

    private void Start()
    {
        EventBus.Instance.rackEditXUp.AddListener(OnXUp);
        EventBus.Instance.rackEditYUp.AddListener(OnYUp);
        EventBus.Instance.rackEditYDown.AddListener(OnYDown);
        EventBus.Instance.rackEditXDown.AddListener(OnXDown);

        if (gameObject.TryGetComponent(out Reactor reactor))
        {
            energyDisplay = reactor.energyReservoirDisplay.transform.parent.transform.parent.gameObject;
        }
        else if (gameObject.TryGetComponent(out Weapon weapon))
        {
            cooldownDisplay = weapon.cooldownOverlay;
        }
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
            energyDisplay.transform.localPosition = new Vector3(-(float)dimensions.x / 2 + 1.155f, -(float)dimensions.y / 2 - 1.5f, -.2f);
        }

        if (gameObject.TryGetComponent(out Weapon weapon))
        {
            cooldownDisplay.rectTransform.sizeDelta = new Vector2(dimensions.x + 1, dimensions.y + 1);
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
}
