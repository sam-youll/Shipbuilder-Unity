using UnityEngine;

public abstract class PrimaryModule : Module
{
    public enum SystemType
    {
        Weapon,
        Reactor
    }
    public SystemType systemType = SystemType.Weapon;
    
    // Primary modules can only be triggered by non-secondary modules.
    // In practice, this means receiving a trigger with any parameters should not go through.
    // So by leaving empty methods, we effectively prevent the method call from going any further.
    public override void Trigger(float value, int inputIndex)
    {
        
    }
    public override void Trigger(float value)
    {
        
    }
}
