using System.Collections.Generic;
using UnityEngine;

public class RandomModule : SecondaryModule
{
    public int randomNumber;

    public override string Description()
    {
        return "When triggered, outputs a random value between 0 and 7";
    }

    public override string Info()
    {
        return $"Current value is {randomNumber}.";
    }

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    public override void Trigger(float value)
    {
        randomNumber = Random.Range(0, 7);
        value += randomNumber;
        Debug.Log($"RandomModule on {gameObject.name} triggered base.Trigger() with a value of {value}.");
        base.Trigger(value, myInputIndex);
    }
    
    public override void Trigger()
    {
        randomNumber = Random.Range(0, 7);
        Debug.Log($"RandomModule on {gameObject.name} triggered base.Trigger() with a value of {randomNumber}.");
        base.Trigger(randomNumber, myInputIndex);
    }
}
