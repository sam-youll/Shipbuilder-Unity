using UnityEngine;

public class wiggler : MonoBehaviour
{
    private Vector2 startPos;
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        startPos = transform.position;
    }

    // Update is called once per frame
    void Update()
    {
        transform.position = startPos + new Vector2(Mathf.Sin(Time.time * 2 + Mathf.PerlinNoise1D(Mathf.Sin(Time.time*3))) * .5f, Mathf.Cos(Time.time*2) + Mathf.PerlinNoise1D(Mathf.Cos(Time.time*2)))*.25f;
    }
}
