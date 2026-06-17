using System;
using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEditor;
using UnityEngine;
using UnityEngine.UI;

public class UISystemPanel : MonoBehaviour
{
    public ModuleRack systemReferenced;
    
    [Header("Visual Components")]
    public Image icon;
    public TextMeshProUGUI nameLabel;
    public Image healthBar;
    public Image heatBar;

    private Color defaultColor = new(0.7803922f, 0.8862746f, 0.6705883f);
    private Color overheatedCol = new Color(1, .5f, .2f);
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    public void Setup(ModuleRack system)
    {
        systemReferenced = system;
        name = system.name;
        nameLabel.text = system.name;

        if (system is Reactor)
        {
            icon.sprite = Resources.Load<Sprite>("Sprites/UI/reactor icon");
            heatBar.transform.parent.gameObject.SetActive(false);
        }
        else if (system is Weapon)
        {
            icon.sprite = Resources.Load<Sprite>("Sprites/UI/weapon icon");
        }
        else
        {
            throw new System.Exception("Tried to assign an unknown system type to UISystemPanel.");
        }
        
        EventBus.Instance.weaponFired.AddListener(OnWeaponFired);
        EventBus.Instance.systemHit.AddListener(OnSystemHit);
        
        SetColor(defaultColor);
    }

    private void Update()
    {
        // TODO: there's a weird frame one problem where it doesn't calculate the child transforms properly until like the second frame
        
        // Debug.Log($"child(0) rect is {transform.GetChild(0).GetComponent<RectTransform>().rect}");
        
        GetComponent<RectTransform>().sizeDelta = new Vector2(GetComponent<RectTransform>().sizeDelta.x, transform.GetChild(0).GetComponent<RectTransform>().sizeDelta.y+.3125f);

        if (systemReferenced != null)
        {
            healthBar.fillAmount = Mathf.Clamp01(systemReferenced.health / systemReferenced.maxHealth);

            if (systemReferenced is Weapon weapon)
            {
                heatBar.fillAmount = Mathf.Clamp01(weapon.heat);
                if (weapon.overheated && GetComponentInChildren<Image>().color != overheatedCol)
                {
                    SetColor(overheatedCol);
                }
                else if (GetComponentInChildren<Image>().color == overheatedCol && !weapon.overheated)
                {
                    SetColor(defaultColor);
                }
            }
        }
        if (systemReferenced != null && systemReferenced.health <= 0)
        {
            SetColor(Color.gray);
        }
    }

    private void OnWeaponFired(Weapon weapon)
    {
        if (weapon == systemReferenced)
        {
            StopAllCoroutines();
            StartCoroutine(FlashColor(Color.white));
        }
    }

    private void OnSystemHit(ModuleRack system)
    {
        // Debug.Log($"System hit was {system}. My systemReferenced is {systemReferenced}.");
        if (system == systemReferenced)
        {
            StopAllCoroutines();
            StartCoroutine(FlashColor(Color.red));
        }
    }

    public void SetColor(Color color)
    {
        StopAllCoroutines();
        
        var allComponents = GetComponentsInChildren<MonoBehaviour>();
        foreach (var component in allComponents)
        {
            switch (component)
            {
                case Image image:
                    image.color = color;
                    break;
                case TextMeshProUGUI text:
                    text.color = color;
                    break;
            }
        }
    }
    
    public IEnumerator FlashColor(Color color)
    {
        var allComponents = GetComponentsInChildren<MonoBehaviour>();
        foreach (var component in allComponents)
        {
            switch (component)
            {
                case Image image:
                    image.color = color;
                    break;
                case TextMeshProUGUI text:
                    text.color = color;
                    break;
            }
        }
        yield return null;

        var currentDefaultCol = systemReferenced is Weapon { overheated: true } ? overheatedCol : defaultColor;
        var currentColor = color;
        while (currentColor != currentDefaultCol)
        {
            currentColor = new Color(
                Funcs.Damp(currentColor.r, currentDefaultCol.r, 3f, Time.deltaTime),
                Funcs.Damp(currentColor.g, currentDefaultCol.g, 3f, Time.deltaTime),
                Funcs.Damp(currentColor.b, currentDefaultCol.b, 3f, Time.deltaTime));
            // Debug.Log(currentColor);
            if (Mathf.Approximately(currentColor.r, currentDefaultCol.r) &&
                Mathf.Approximately(currentColor.g, currentDefaultCol.g) &&
                Mathf.Approximately(currentColor.b, currentDefaultCol.b))
            {
                currentColor = currentDefaultCol;
            }
            foreach (var component in allComponents)
            {
                switch (component)
                {
                    case Image image:
                        image.color = currentColor;
                        break;
                    case TextMeshProUGUI text:
                        text.color = currentColor;
                        break;
                }
            }
            
            yield return null;
        }
    }
}
