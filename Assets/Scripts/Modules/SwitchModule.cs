using System.Collections.Generic;
using UnityEngine;

public class SwitchModule : TriggerModule
{
    public List<Wire> outWires = new();

    public int currentIndex;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    protected override void Start()
    {
        base.Start();
    }

    //what happens if we get a value (increment)
    public override void Trigger(float value)
    {
        currentIndex += (int)value;
        outWires[currentIndex].Trigger();
    }

    public override void Trigger()
    {
        currentIndex += 1;
        outWires[currentIndex].Trigger();
    }
}
