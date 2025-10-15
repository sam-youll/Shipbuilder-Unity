using UnityEngine;

public class HideShopButton : Button2D
{

    public GameObject shopMenu;
    private SpriteRenderer[] children;
    private Color newColor;
    private Color[] oldColor;
    private Color panelColor;
    private float alpha = 0.5f;
    
   

    protected override void OnMouseDown()
    {
        //shop menu
        panelColor = shopMenu.GetComponent<SpriteRenderer>().color;
        newColor = shopMenu.GetComponent<SpriteRenderer>().color;
        newColor.a = alpha;
        shopMenu.GetComponent<SpriteRenderer>().color = newColor;
        
        //children
        children = shopMenu.GetComponentsInChildren<SpriteRenderer>();
        oldColor = new Color[children.Length];
        for (var index = 0; index < children.Length; index++)
        {
            var child = children[index];
            oldColor[index] = child.color;
            newColor = child.color;
            newColor.a = alpha;
            child.color = newColor;
        }
    }

    protected void OnMouseUp()
    {
        shopMenu.GetComponent<SpriteRenderer>().color = panelColor;
        children = shopMenu.GetComponentsInChildren<SpriteRenderer>();
        for (var index = 0; index < children.Length; index++)
        {
            var child = children[index];
            child.color = oldColor[index];
        }
    }
}
