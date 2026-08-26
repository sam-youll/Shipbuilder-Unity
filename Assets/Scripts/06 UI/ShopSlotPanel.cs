using System;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.UI;

public class ShopSlotPanel : MonoBehaviour, ITooltipInfo, INeedEnergy
{
    public Sprite defaultIcon;
    private Color defaultColor = new(0.7803922f, 0.8862746f, 0.6705883f);

    public GameObject itemForSale;
    
    [Header("Components")]
    public Image moduleIcon;
    public TextMeshProUGUI nameLabel;
    public TextMeshProUGUI descriptionLabel;
    public TextMeshProUGUI costLabel;
    public GridLayoutGroup moduleLayoutIcon;
    public GameObject pureEnergyCost;
    public GameObject izkiEnergyCost;
    public GameObject auboEnergyCost;
    public GameObject dwthEnergyCost;

    private void Start()
    {
        name = name.Replace("(Clone)", "");
    }

    public void Setup(GameObject module)
    {
        var mod = module.GetComponent<Module>();
        
        if (mod.icon != null)
        {
            moduleIcon.sprite = mod.icon;
        }

        itemForSale = module;

        nameLabel.text = module.name;
        descriptionLabel.text = mod.GetComponent<ITooltipInfo>().Description() + "\n" +
                                mod.GetComponent<ITooltipInfo>().Info();
        
        SetLayoutIcon(mod);
        
        if (module.TryGetComponent(out INeedEnergy energy))
        {
            var energyCost = energy.ChangeEnergyCost(new Dictionary<Common.SoundType, float>(Common.EmptyEnergyCost()));
            var energySum = 0f;
            foreach (var kvp in energyCost)
            {
                energySum += kvp.Value;
            }
            if (energySum > 0)
            {
                pureEnergyCost.transform.parent.gameObject.SetActive(true);

                foreach (var kvp in energyCost)
                {
                    if (energyCost[Common.SoundType.Pure] > 0)
                    {
                        pureEnergyCost.SetActive(true);
                        pureEnergyCost.transform.GetChild(0).GetComponent<TextMeshProUGUI>().text =
                            energyCost[Common.SoundType.Pure].ToString();
                    }
                    else
                    {
                        pureEnergyCost.SetActive(false);
                    }
                    if (energyCost[Common.SoundType.Izki] > 0)
                    {
                        izkiEnergyCost.SetActive(true);
                        izkiEnergyCost.transform.GetChild(0).GetComponent<TextMeshProUGUI>().text =
                            energyCost[Common.SoundType.Izki].ToString();
                    }
                    else
                    {
                        izkiEnergyCost.SetActive(false);
                    }
                    if (energyCost[Common.SoundType.Aubo] > 0)
                    {
                        auboEnergyCost.SetActive(true);
                        auboEnergyCost.transform.GetChild(0).GetComponent<TextMeshProUGUI>().text =
                            energyCost[Common.SoundType.Aubo].ToString();
                    }
                    else
                    {
                        auboEnergyCost.SetActive(false);
                    }
                    if (energyCost[Common.SoundType.Dwth] > 0)
                    {
                        dwthEnergyCost.SetActive(true);
                        dwthEnergyCost.transform.GetChild(0).GetComponent<TextMeshProUGUI>().text =
                            energyCost[Common.SoundType.Izki].ToString();
                    }
                    else
                    {
                        dwthEnergyCost.SetActive(false);
                    }
                }
            }
            else
            {
                pureEnergyCost.transform.parent.gameObject.SetActive(false);
            }
        }

        costLabel.text = "Cost: " + mod.price;
    }

    void SetLayoutIcon(Module mod)
    {
        var xOffset = (int)(.5f * (8 - mod.dimensions.x));
        var yOffset = (int)(.5f * (8 - mod.dimensions.y));
        
        for (var x = 0; x < 8; x++)
        {
            for (var y = 0; y < 8; y++)
            {
                var child = moduleLayoutIcon.transform.GetChild(8 * (y) + (x));
                
                if (x < xOffset ||
                    y < yOffset ||
                    x >= mod.dimensions.x + xOffset || 
                    y >= mod.dimensions.y + yOffset)
                {
                    child.GetComponent<Image>().color = new Color(0, 0, 0, 0);
                    continue;
                }
                
                child.GetComponent<Image>().color = mod.moduleShape[x - xOffset, y - yOffset] == Module.ModuleComponent.Empty
                    ? new Color(0, 0, 0, 0)
                    : defaultColor;
            }
        }
    }

    public void PurchaseItem()
    {
        if (InventoryManager.Instance.ShopSlotPurchase(gameObject))
        {
            Clear();
        }
    }

    public void Clear()
    {
        moduleIcon.sprite = defaultIcon;
        nameLabel.text = "";
        descriptionLabel.text = "";

        foreach (var image in moduleLayoutIcon.transform.GetComponentsInChildren<Image>())
        {
            image.color = new Color(0, 0, 0, 0);
        }

        itemForSale = null;
        
        costLabel.text = "Scrap Cost: ???";
    }

    public string Description()
    {
        if (itemForSale == null) return "";
        
        return "For sale: " + itemForSale.name + "\n" + itemForSale.GetComponent<ITooltipInfo>().Description();
    }

    public string Info()
    {
        if (itemForSale == null) return "";
        
        return itemForSale.GetComponent<ITooltipInfo>().Info();
    }

    public bool Warning(out string message)
    {
        message = "";
        return false;
    }

    public Dictionary<Common.SoundType, float> ChangeEnergyCost(Dictionary<Common.SoundType, float> input)
    {
        if (itemForSale == null) return input;
        
        if (itemForSale.TryGetComponent(out INeedEnergy energyCost))
        {
            return energyCost.ChangeEnergyCost(input);
        }

        return input;
    }
}
