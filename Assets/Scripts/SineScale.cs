using UnityEngine;

public class SineScale : MonoBehaviour
{
    public float amplitude = .5f;

    public float rate = 1;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        var scale = transform.localScale;
        scale = Vector3.one * (1 + amplitude * Mathf.Sin(Time.time * rate));
        transform.localScale = scale;
    }
}
