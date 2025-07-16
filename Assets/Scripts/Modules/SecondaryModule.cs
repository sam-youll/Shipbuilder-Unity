using UnityEngine;

public abstract class SecondaryModule : Module
{
    public enum ActiveState
    {
        Triggered,
        Always
    }
    public ActiveState activeState = ActiveState.Triggered;

    public int myInputIndex;
    
    protected override void Update()
    {
        base.Update();
        
        if (activeState == ActiveState.Always)
        {
            Trigger();
        }
    }
    
    // public override void Trigger(float value,  int inputIndex)
    // {
    //     Debug.Log($"SecondaryModule on {gameObject.name} called base.Trigger().");
    //     base.Trigger(value, inputIndex);
    // }
}
