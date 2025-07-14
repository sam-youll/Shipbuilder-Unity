using UnityEngine;

public class CounterModule : SecondaryModule
{

    public float currentValue;
    public float limit;

    public override void Trigger(float value)
    {
        currentValue += value;
        if (currentValue > limit)
        {
            currentValue -= limit;
        }
        base.Trigger(currentValue);
    }

    public override void Trigger()
    {
        base.Trigger(currentValue);
    }
}
