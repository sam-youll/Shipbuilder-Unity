using System;
using System.Collections;
using System.Collections.Generic;
using TMPro;
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

    private Color defaultColor = new(188, 219, 145);
    
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
            }
        }
    }

    private void OnWeaponFired(Weapon weapon)
    {
        if (weapon == systemReferenced)
        {
            StartCoroutine(FlashColor(Color.white));
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
        
        var currentColor = color;
        while (currentColor != defaultColor)
        {
            currentColor = new Color(
                Funcs.Damp(currentColor.r, defaultColor.r, .2f, Time.deltaTime),
                Funcs.Damp(currentColor.g, defaultColor.g, .2f, Time.deltaTime),
                Funcs.Damp(currentColor.b, defaultColor.b, .2f, Time.deltaTime));
            
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
        }
    }
}
