using UnityEngine;

public class StepModule : SecondaryModule
{
    // we can set this to different sizes positive or negative
    public float stepSize = 1;

    public override void Trigger(float value)
    {
        base.Trigger(value);
        
        // foreach child wire, Trigger(value);
    }
}
