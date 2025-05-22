using TMPro;
using UnityEngine;

public class Shop : MonoBehaviour
{
    public GameObject[] allShopItems; // array of all items that the shop can stock
    private GameObject[] shopInventory = new GameObject[3];

    public TextMeshPro[] priceLabels = new TextMeshPro[3];
    public TextMeshPro[] nameLabels = new TextMeshPro[3];
    public GameObject[] shopSlots = new GameObject[3];
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void Reroll()
    {
        for (var i = 0; i < shopSlots.Length; i++)
        {
            var slot = shopSlots[i];
            var newItem = allShopItems[Random.Range(0, allShopItems.Length)];
            nameLabels[i].text = newItem.gameObject.name;
            priceLabels[i].text = "Price: " + newItem.GetComponent<Module>().price;
            Destroy(slot.GetComponent<ShopSlotButton>().shopItem);
            slot.GetComponent<ShopSlotButton>().shopItem = Instantiate(newItem, slot.transform);
            var pos = slot.GetComponent<ShopSlotButton>().shopItem.transform.localPosition;
            pos.z = -.1f;
            slot.GetComponent<ShopSlotButton>().shopItem.transform.localPosition = pos;
            slot.GetComponent<ShopSlotButton>().shopItem.SetActive(true);
            // slot.GetComponent<ShopSlotButton>().shopItem.GetComponent<BoxCollider2D>().enabled = false;
        }
    }
}
