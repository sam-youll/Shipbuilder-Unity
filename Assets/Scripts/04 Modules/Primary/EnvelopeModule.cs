using UnityEngine;

public class EnvelopeModule : PrimaryModule, ITooltipInfo
{

    public float attack;
    public float decay;
    public float release;
    
    //NOTE: just making decay and release interchangeable for now. what to do long term should probably be based on playtest
    public string Info()
    {
        return $"Attack: {attack}\n" +
               $"Decay: {decay}\n" +
               $"Release: {decay}";
    }

    protected override void Start()
    {
        musicParams["attack"] = attack;
        musicParams["decay"] = decay;
        musicParams["release"] = decay;
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
