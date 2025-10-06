using UnityEngine;

public abstract class PrimaryModule : Module
{
    public enum SystemType
    {
        Weapon,
        Reactor
    }
    public SystemType systemType = SystemType.Weapon;
    // public override void Trigger(float value, int inputIndex)
    // {
    //     Debug.Log($"PrimaryModule on {gameObject.name} called base.Trigger().");
    //     base.Trigger(value, inputIndex);
    // }
}
