using TMPro;
using UnityEngine;

public class HideShopButton : Button2D
{

    public GameObject shopMenu;
    private SpriteRenderer[] childrenSprites;
    private TextMeshPro[] childrenText;
    private Color newColor;
    private Color[] oldSpriteColor;
    private Color[] oldTextColor;
    private Color panelColor;
    private float alpha = 0.1f;
    
   

    protected void OnMouseDrag()
    {
        //shop menu
        panelColor = shopMenu.GetComponent<SpriteRenderer>().color;
        newColor = shopMenu.GetComponent<SpriteRenderer>().color;
        newColor.a = alpha;
        shopMenu.GetComponent<SpriteRenderer>().color = newColor;
        
        //children
        childrenSprites = shopMenu.GetComponentsInChildren<SpriteRenderer>();
        oldSpriteColor = new Color[childrenSprites.Length];
        for (var index = 0; index < childrenSprites.Length; index++)
        {
            var child = childrenSprites[index];
            oldSpriteColor[index] = child.color;
            newColor = child.color;
            newColor.a = alpha;
            child.color = newColor;
        }
        
        //children text
        childrenText = shopMenu.GetComponentsInChildren<TextMeshPro>();
        oldTextColor = new Color[childrenText.Length];
        for (var index = 0; index < childrenText.Length; index++)
        {
            var child = childrenText[index];
            oldTextColor[index] = child.color;
            newColor = child.color;
            newColor.a = alpha;
            child.color = newColor;
        }
    }

    protected void OnMouseUp()
    {
        panelColor.a = 1;
        shopMenu.GetComponent<SpriteRenderer>().color = panelColor;
        childrenSprites = shopMenu.GetComponentsInChildren<SpriteRenderer>();
        for (var index = 0; index < childrenSprites.Length; index++)
        {
            var child = childrenSprites[index];
            oldSpriteColor[index].a = 1;
            child.color = oldSpriteColor[index];
        }
        childrenText = shopMenu.GetComponentsInChildren<TextMeshPro>();
        for (var index = 0; index < childrenText.Length; index++)
        {
            var child = childrenText[index];
            oldTextColor[index].a = 1;
            child.color = oldTextColor[index];
        }
    }
}
