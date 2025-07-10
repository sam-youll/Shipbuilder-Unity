using UnityEngine;

public class StepModule : MonoBehaviour
{
    public enum direction
    {
        Up,
        Down
    }

    public int steps;

    private int previousNote;

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        previousNote = 8;
    }

    // Update is called once per frame
    void Update()
    {
        //NOTE: This needs to change when we have stuff in place to have it dangling off
        if (GetComponent<Module>().nextModule != null) 
        {
            
        }
    }


}
