using SaintsField;
using TMPro;
using UnityEngine;

public class ShopSlot : MonoBehaviour
{
    public GameObject saleItem;
    public float scrapPrice;
    [GetComponentInChildren] public TextMeshPro label;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        LoadRandomModule();
        EventBus.Instance.shopSlotPurchased.AddListener(OnShopSlotPurchased);
    }

    private void LoadRandomModule()
    {
        saleItem = Instantiate(
            Resources.LoadAll<GameObject>("Prefabs/Modules")[
                Random.Range(0, Resources.LoadAll<GameObject>("Prefabs/Modules").Length - 1)], transform, true);
        saleItem.transform.localPosition = new Vector3(.25f-saleItem.GetComponent<Module>().dimensions.x*.25f, .25f-saleItem.GetComponent<Module>().dimensions.y*.25f, -.1f);
        saleItem.transform.localScale = new Vector3(.5f, .5f, 1);
        scrapPrice = saleItem.GetComponent<Module>().price +
                     Random.Range(0, 3 + Mathf.FloorToInt(.3f * CombatManager.Instance.fightLevel));
        label.text = $"{saleItem.name}\n({scrapPrice} scrap)";
    }

    private void OnShopSlotPurchased(GameObject shopSlotObj)
    {
        if (shopSlotObj == gameObject && InventoryManager.Instance.scrap >= scrapPrice)
        {
            Destroy(saleItem);
            scrapPrice = 0;
        }
    }
}
