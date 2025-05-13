using UnityEngine;

public class Tooltip : MonoBehaviour
{
    public GameObject tooltip;
    public bool hover;
    private float hoverTimer;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        tooltip.SetActive(false);
    }

    // Update is called once per frame
    void Update()
    {
        if (hover)
        {
            hoverTimer += Time.deltaTime;
        }
        else
        {
            hoverTimer = 0;
        }

        if (hoverTimer > 1)
        {
            tooltip.SetActive(true);
        }
        else
        {
            tooltip.SetActive(false);
        }
    }
}
