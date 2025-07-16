using UnityEngine;

public class RandomModule : SecondaryModule
{
    public int randomNumber;
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    public override void Trigger(float value)
    {
        randomNumber = Random.Range(0, 7);
        Debug.Log($"RandomModule on {gameObject.name} triggered base.Trigger() with a value of {value}.");
        value += randomNumber;
        base.Trigger(value, myInputIndex);
    }

    public override void Trigger()
    {
        randomNumber = Random.Range(0, 7);
        Debug.Log($"RandomModule on {gameObject.name} triggered base.Trigger() with a value of a random number.");
        base.Trigger(randomNumber, myInputIndex);
    }
}
