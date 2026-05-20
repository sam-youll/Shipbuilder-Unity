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
        musicParams["attack"] = attack;
        musicParams["decay"] = decay;
        musicParams["release"] = release;
    }
    
    public override void Trigger(float value, int inputIndex)
    {
        switch (inputIndex)
        {
            case 0:
                base.Trigger();
                break;
            case 1:
                musicParams["attack"] = value * 100;
                // base.Trigger();
                break;
            case 2:
                musicParams["decay"] = value * 100;
                break;
        }
    }
}
