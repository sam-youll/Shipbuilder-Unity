using UnityEngine;
using UnityEngine.UI;

public class SwitchComponent : MonoBehaviour, ITooltipInfo, ISelectable
{
    public Sprite upSprite;
    public Sprite downSprite;

    public bool on;
    private SpriteRenderer image;

    public string Description()
    {
        return "Turn me on";
    }

    public string Info()
    {
        return on ? "On" : "Off";
    }
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        image = GetComponent<SpriteRenderer>();
    }

    // Update is called once per frame
    void Update()
    {
        if (UIManager.Instance.TopRaycastResult() == gameObject)
        {
            if (Input.GetMouseButtonDown(0))
            {
                on = !on;
                if (on)
                {
                    image.sprite = upSprite;
                }
                else
                {
                    image.sprite = downSprite;
                }
            }

            image.color = new Color(.8f,.8f,.8f);
        }
        else
        {
            image.color = Color.white;
        }
        
    }

    public void Select()
    {
        
    }
}
