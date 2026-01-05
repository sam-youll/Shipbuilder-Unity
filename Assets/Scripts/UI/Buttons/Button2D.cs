using UnityEngine;
using UnityEngine.Events;

public class Button2D : MonoBehaviour
{
    public Sprite defaultSprite;
    public Sprite pressedSprite;

    private SpriteRenderer sr;

    public UnityEvent click;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        sr = GetComponent<SpriteRenderer>();
        sr.sprite = defaultSprite;
    }
    protected virtual void OnMouseEnter()
    {
        // sr.color = new Color(.9f, .9f, .9f, 1);
    }

    protected virtual void OnMouseExit()
    {
        // sr.color = Color.white;
        sr.sprite = defaultSprite;
    }

    protected virtual void OnMouseDown()
    {
        sr.sprite = pressedSprite;
        // sr.color = Color.white;
        click.Invoke();
    }

    protected virtual void OnMouseUp()
    {
        sr.sprite = defaultSprite;
        // sr.color = Color.white;
    }
    
    protected virtual void OnClick()
    {
        Debug.Log("Button2D.OnClick");
    }
}
