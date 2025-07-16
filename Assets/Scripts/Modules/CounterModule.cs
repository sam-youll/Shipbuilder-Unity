using UnityEngine;

public class CounterModule : SecondaryModule
{

    public float currentValue;
    public float limit = 14;

    public override void Trigger(float value, int inputIndex)
    {
        currentValue += value;
        if (currentValue > limit)
        {
            currentValue -= limit;
        }
        base.Trigger(currentValue, myInputIndex);
    }
    
    public override void Trigger(float value)
    {
        currentValue += value;
        if (currentValue > limit)
        {
            currentValue -= limit;
        }
        base.Trigger(currentValue, myInputIndex);
        
        //Debug.Log("Counter: " + currentValue);
    }

    public override void Trigger()
    {
        base.Trigger(currentValue,  myInputIndex);
        //Debug.Log("Counter: " + currentValue);
    }
}
