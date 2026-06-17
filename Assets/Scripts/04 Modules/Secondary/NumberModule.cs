using UnityEngine;

public class NumberModule : SecondaryModule
{
    // we can set this to different sizes positive or negative
    public float number = 1;

    public override string Description()
    {
        return "Holds a number.";
    }

    public override string Info()
    {
        return $"Current value is {number}";
    }

    public override void Trigger(float value)
    {
        // Debug.Log($"AddModule on {gameObject.name} triggered base.Trigger() with a value of {value}.");
        value = number;
        base.Trigger(value, myInputIndex);
    }

    public override void Trigger()
    {
        // Debug.Log($"AddModule on {gameObject.name} triggered base.Trigger() with a value of {stepSize}.");
        base.Trigger(number, myInputIndex);
    }
}
