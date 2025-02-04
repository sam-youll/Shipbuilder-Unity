using UnityEngine;

public class StartCombatButton : MonoBehaviour
{
    public Color defaultColor;
    public Color hoverColor;
    public Color pressedColor;
    private Color currentColor;
    
    private SpriteRenderer sr;
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        sr = GetComponent<SpriteRenderer>();
        sr.color = defaultColor;
        currentColor = sr.color;
    }

    // Update is called once per frame
    void FixedUpdate()
    {
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

        StartCombat();
    }

    void StartCombat()
    {
        Camera.main.transform.position = new Vector3(18, 0, -10);
    }
}

