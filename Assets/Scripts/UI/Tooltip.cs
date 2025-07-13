using UnityEngine;

public class Tooltip : MonoBehaviour
{
    public GameObject tooltip;
    public bool hover;
    private float hoverTimer;
    private Vector3 defaultScale;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        tooltip.SetActive(false);
        defaultScale = tooltip.transform.localScale;
    }

    // Update is called once per frame
    void Update()
    {
        var mousePos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
        var results = Physics2D.RaycastAll(mousePos, Vector2.zero);
            
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
            hoverTimer += Time.deltaTime;
        }
        else
        {
            hoverTimer = 0;
        }
        if (hoverTimer > 0.2f)
        {
            tooltip.SetActive(true);
            var sr = tooltip.GetComponent<SpriteRenderer>();
            tooltip.transform.localScale = Vector3.Lerp(tooltip.transform.localScale, defaultScale, .1f);
            tooltip.transform.position = new Vector3(mousePos.x + sr.size.x * .5f + .6f, mousePos.y - sr.size.y * .5f - .6f, transform.position.z - 1);
        }
        else
        {
            tooltip.transform.localScale = Vector3.zero;
            tooltip.SetActive(false);
        }
    }
}
