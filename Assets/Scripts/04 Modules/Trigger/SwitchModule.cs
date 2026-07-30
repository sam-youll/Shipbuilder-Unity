using System.Collections.Generic;
using UnityEngine;

public class SwitchModule : TriggerModule
{
    public int currentIndex;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    public override string Description()
    {
        return "When triggered by a secondary module, switches output that this module will trigger. " +
               "Sending a higher number will switch that many times. When triggered by a primary module," +
               "triggers the currently selected output.";
    }

    public override string Info()
    {
        return childWires.Count > 0 ? $"Will trigger {childWires[currentIndex]}." : "No modules downstream.";
        
    }

    //what happens if we get a value (increment)
    public override void Trigger(float value, int inputIndex)
    {
        switch (inputIndex)
        {
            case 0:
                childWires[currentIndex].GetComponent<Wire>().Trigger();
                break;
            case 1:
                currentIndex += (int)value;
                if (currentIndex > childWires.Count - 1) currentIndex = 0;
                break;
        }
    }

    // public override void Trigger()
    // {
    //     childWires[currentIndex].GetComponent<Wire>().Trigger();
    // }
}
