using UnityEngine;

public class HighlightBlink : MonoBehaviour
{
    private SpriteRenderer spriteRenderer;
    private Color highlightAlpha;
    public float speed;
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        spriteRenderer = GetComponent<SpriteRenderer>();
       
    }

    // Update is called once per frame
    void Update()
    {
        var highlightAlpha = spriteRenderer.color;
        highlightAlpha.a = Mathf.Sin(Time.time * speed)*.5f + .5f;
        spriteRenderer.color = highlightAlpha;
    }
}
