using UnityEngine;

public class Button2D : MonoBehaviour
{
    public Color defaultColor;
    public Color hoverColor;
    public Color pressedColor;
    private Color currentColor;

    public SpriteRenderer sr;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        // sr = GetComponent<SpriteRenderer>();
        sr.color = defaultColor;
        currentColor = sr.color;
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        if (currentColor == Color.clear)
        {
            currentColor = sr.color;
        }
        
        var col = sr.color;
        col = Color.Lerp(col, currentColor, .1f);
        sr.color = col;
    }

    private void OnMouseEnter()
    {
        sr.color = hoverColor;
        currentColor = hoverColor;
    }

    private void OnMouseExit()
    {
        sr.color = defaultColor;
        currentColor = defaultColor;
    }

    private void OnMouseDown()
    {
        sr.color = pressedColor;
        currentColor = hoverColor;
        OnClick();
    }

    protected virtual void OnClick()
    {
        Debug.Log("Button2D.OnClick");
    }
}
