using UnityEngine;

public abstract class SecondaryModule : Module
{
    // TODO: is always vs triggered still relevant to current systems design?
    // Should it be removed entirely, or changed to something like a selfTrigger bool?
    public enum ActiveState
    {
        Triggered,
        Always
    }
    public ActiveState activeState = ActiveState.Triggered;

    /// <summary>
    /// Input index lets the triggered module know how to interpret the Trigger() call,
    /// the index typically corresponding to a specific input function reserved for secondary modules.
    /// The input index is set by the wire when a module is attached.
    /// </summary>
    public int myInputIndex;
    
    protected override void Update()
    {
        base.Update();
        
        if (activeState == ActiveState.Always)
        {
            Trigger();
        }
    }
}
