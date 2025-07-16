using UnityEngine;

public class ShopSlotButton : Button2D
{
    public GameObject shopItem;
    protected override void OnClick()
    {
        if (shopItem == null)
            return;
        
        if (Inventory.Instance.credits < shopItem.GetComponent<Module>().price)
            return;
        
        if (!shopItem.activeSelf)
            return;
        
        // shopItem.GetComponent<BoxCollider2D>().enabled = true;
        Inventory.Instance.AddModule(shopItem);
        Inventory.Instance.credits -= shopItem.GetComponent<Module>().price;
        // shopItem.SetActive(false);
        Destroy(shopItem);
    }
}
