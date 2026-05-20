using UnityEngine;

public class AddModule : SecondaryModule
{
    // we can set this to different sizes positive or negative
    public float stepSize = 1;

    public override void Trigger(float value)
    {
        // Debug.Log($"AddModule on {gameObject.name} triggered base.Trigger() with a value of {value}.");
        value += stepSize;
        base.Trigger(value, myInputIndex);
    }

    public override void Trigger()
    {
        // Debug.Log($"AddModule on {gameObject.name} triggered base.Trigger() with a value of {stepSize}.");
        base.Trigger(stepSize, myInputIndex);
    }
}
