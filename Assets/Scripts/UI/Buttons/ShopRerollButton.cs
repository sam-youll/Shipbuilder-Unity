using UnityEngine;

public class ShopRerollButton : Button2D
{
    public GameObject shop;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    protected override void OnClick()
    {
        if (Inventory.Instance.scrap < 1)
            return;
        
        Inventory.Instance.scrap -= 1;
        
        shop.GetComponent<Shop>().Reroll();
    }
}
