using UnityEngine;

public class Conductor : MonoBehaviour
{
    public static Conductor Instance;

    private void Awake()
    {
        if (Instance != null && Instance != this)
        {
            Destroy(this);
        }
        else
        {
            Instance = this;
        }
    }
    
    public float time;
    public float tempo;
    public int beat;
    public int measureLength;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        time += Time.deltaTime;
        beat = (int)(time % tempo);
        beat = (int)Mathf.Repeat(beat, measureLength);
        
    }
}
