using System.Collections.Generic;
using UnityEngine;

public class SwitchModule : TriggerModule
{
    public List<Wire> outWires = new();

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
        return "Come back later I'm not ready yet.";
    }

    protected override void Start()
    {
        base.Start();
    }

    //what happens if we get a value (increment)
    public override void Trigger(float value, int inputIndex)
    {
        currentIndex += (int)value;
        childWires[currentIndex].GetComponent<Wire>().Trigger();
    }

    public override void Trigger()
    {
        childWires[currentIndex].GetComponent<Wire>().Trigger();
    }
}
