using UnityEngine;

public class EnvelopeModule : PrimaryModule, ITooltipInfo
{

    public float attack;
    public float decay;
    public float release;
    
    public string Info()
    {
        return $"Attack: {attack}\n" +
               $"Decay: {decay}\n" +
               $"Release: {release}";
    }

    protected override void Start()
    {
        base.Start();
        
        
    }
}
