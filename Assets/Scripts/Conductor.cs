using UnityEngine;
using UnityEngine.Events;

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
    private int lastBeat;
    public int measureLength;
    
    public UnityEvent onBeat;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        time += Time.deltaTime * tempo / 60;
        // time = Mathf.Repeat(beat, measureLength*tempo/60);
        beat = (int)(time % measureLength);

        if (beat != lastBeat)
        {
            onBeat.Invoke();
        }
        lastBeat = beat;
    }
}
