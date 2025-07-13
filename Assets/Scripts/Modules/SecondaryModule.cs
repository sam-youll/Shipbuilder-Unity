using UnityEngine;

public abstract class SecondaryModule : Module
{
    public enum ActiveState
    {
        Triggered,
        Always
    }
    public ActiveState activeState = ActiveState.Triggered;

    protected override void Update()
    {
        base.Update();
        
        if (activeState == ActiveState.Always)
        {
            Trigger();
        }
    }
    
    public override void Trigger(float value)
    {
        base.Trigger(value);
        
        
    }
}
