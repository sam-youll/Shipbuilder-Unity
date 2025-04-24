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

    public int sixteenth;
    public int eighth;
    public int quarter;
    public int half;
    public int whole;
    public int bar;


    private int lastSixteenth;
    private int lastEighth;
    private int lastQuarter;
    private int lastHalf;
    private int lastWhole;
    private int lastBar;

    public int measureLength;
    
    public UnityEvent onSixteenth;
    public UnityEvent onEighth;
    public UnityEvent onQuarter;
    public UnityEvent onHalf;
    //onWhole won't really do anything until we get into meters that have more than 16 16th notes, don't worry about it
    public UnityEvent onWhole;
    public UnityEvent onBar;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        time += Time.deltaTime * tempo / 60;
        // time = Mathf.Repeat(beat, measureLength*tempo/60);
        sixteenth = (int)(time % measureLength);
        eighth = (int)(time % measureLength) / 2;
        quarter = (int)(time % measureLength) / 4;
        half = (int)(time % measureLength) / 8;
        whole = (int)(time % measureLength) / 16;



        if (sixteenth != lastSixteenth)
        {
            onSixteenth.Invoke();

            if (sixteenth == 0)
            {
                bar++;
            }
        }
        lastSixteenth = sixteenth;

        if (eighth != lastEighth)
        {
            onEighth.Invoke();
        }
        lastEighth = eighth;

        if (quarter != lastQuarter) 
        {
            onQuarter.Invoke();
        }
        lastQuarter = quarter;

        if (half != lastHalf)
        {
            onHalf.Invoke();
        }
        lastHalf = half;

        if (whole != lastWhole) 
        {
            onWhole.Invoke();
        }
        lastWhole = whole;




    }
}
