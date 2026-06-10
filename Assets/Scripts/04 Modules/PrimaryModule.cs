using System.Collections.Generic;
using UnityEngine;

public abstract class PrimaryModule : Module, IMusicParams
{
    public float izki;
    public float aubo;
    public float dwth;
    public float hysh;
    
    // Primary modules can only be triggered by non-secondary modules.
    // In practice, this means receiving a trigger with any parameters should not go through.
    // So by leaving empty methods, we effectively prevent the method call from going any further.
    public override void Trigger(float value, int inputIndex)
    {
        
    }
    public override void Trigger(float value)
    {
        
    }

    public abstract Dictionary<string, float> MusicParams();
}
