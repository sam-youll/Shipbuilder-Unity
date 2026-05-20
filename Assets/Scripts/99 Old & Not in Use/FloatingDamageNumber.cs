using TMPro;
using UnityEngine;

public class FloatingDamageNumber : MonoBehaviour
{
    TextMeshPro text;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        text = gameObject.GetComponent<TextMeshPro>();
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    void FixedUpdate()
    {
        var pos = transform.position;
        pos.y += 0.05f;
        transform.position = pos;
        
        var col = text.color;
        col.a -= 0.04f;
        if (col.a <= 0)
        {
            Destroy(gameObject);
        }
        text.color = col;

    }
}
