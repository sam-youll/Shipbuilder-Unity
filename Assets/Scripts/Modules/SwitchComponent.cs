using UnityEngine;

public class SwitchComponent : MonoBehaviour, ITooltipInfo
{
    public Sprite upSprite;
    public Sprite downSprite;

    public bool on;
    private SpriteRenderer sr;

    public string Info()
    {
        return on ? "On" : "Off";
    }
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        sr = GetComponent<SpriteRenderer>();
    }

    // Update is called once per frame
    void Update()
    {
        // we do a lil raycast
        var results = Physics2D.RaycastAll(Camera.main.ScreenToWorldPoint(Input.mousePosition), Vector2.zero);
        
        var isItMe = false;
        foreach (var r in results)
        {
            if (r.collider.gameObject == gameObject)
            {
                isItMe = true;
            }
        }

        if (isItMe)
        {
            if (Input.GetMouseButtonDown(0))
            {
                on = !on;
                if (on)
                {
                    sr.sprite = upSprite;
                }
                else
                {
                    sr.sprite = downSprite;
                }
            }

            sr.color = new Color(.8f,.8f,.8f);
        }
        else
        {
            sr.color = Color.white;
        }
        
    }
}
