using System;
using TMPro;
using UnityEngine;
using UnityEngine.UI;

public class ShopSlotPanel : MonoBehaviour, ITooltipInfo
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
        descriptionLabel.text = mod.GetComponent<ITooltipInfo>().Description();
        
        SetLayoutIcon(mod);

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
        
        costLabel.text = "Cost: ???";
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
}
