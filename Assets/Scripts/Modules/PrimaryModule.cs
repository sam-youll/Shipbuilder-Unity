using UnityEngine;

public abstract class PrimaryModule : Module
{
    public override void Trigger()
    {
        Debug.Log($"PrimaryModule on {gameObject.name} called base.Trigger().");
        base.Trigger();
    }
}
