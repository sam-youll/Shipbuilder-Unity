using UnityEngine;

public class SineScale : MonoBehaviour
{
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        var scale = transform.localScale;
        scale = Vector3.one * (1 + .5f * Mathf.Sin(Time.timeSinceLevelLoad));
        transform.localScale = scale;
    }
}
