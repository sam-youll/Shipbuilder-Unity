using System.Collections.Generic;
using UnityEngine;

public class RootModule : SecondaryModule
{

    public int currentRoot;

    public override string Description()
    {
        return "When triggered, outputs a value equal to the interval of the root of the current scale.";
    }

    public override string Info()
    {
        return $"Current value is {currentRoot}.";
    }

    public override void Trigger(float value, int inputIndex)
    {
        currentRoot = ReactorSounds.Instance.changes[ReactorSounds.Instance.changesIndex]; 
        value += currentRoot;
        base.Trigger(value, myInputIndex);
    }

    public override void Trigger(float value)
    {
        currentRoot = ReactorSounds.Instance.changes[ReactorSounds.Instance.changesIndex]; 
        value += currentRoot;
        base.Trigger(value, myInputIndex);
    }

    public override void Trigger()
    {
        currentRoot = ReactorSounds.Instance.changes[ReactorSounds.Instance.changesIndex];
        base.Trigger(currentRoot, myInputIndex);
    }
}
