using UnityEngine;

public class RootModule : SecondaryModule
{

    public int currentRoot;

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
