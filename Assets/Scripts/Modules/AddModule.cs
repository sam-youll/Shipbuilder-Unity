using UnityEngine;

public class AddModule : SecondaryModule
{
    // we can set this to different sizes positive or negative
    public float stepSize = 1;

    public override void Trigger(float value)
    {
        value += stepSize;

        base.Trigger(value);
        Debug.Log(value);
    }

    public override void Trigger()
    {
        base.Trigger(stepSize);
        Debug.Log("add " + stepSize);
    }
}
