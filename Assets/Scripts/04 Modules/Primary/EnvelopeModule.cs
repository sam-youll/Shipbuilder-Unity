using System.Collections.Generic;
using UnityEngine;

public class EnvelopeModule : PrimaryModule, ITooltipInfo, IWeaponModule
{
    // TODO: add weapon stats
    
    public float attack;
    public float decay;
    public float release;

    public override string Description()
    {
        return "Puts da sound in a envelope.";
    }

    public override string Info()
    {
        return $"Attack: {attack}\n" +
               $"Decay: {decay}\n" +
               $"Release: {release}";
    }

    public Dictionary<string, float> WeaponStats()
    {
        return new Dictionary<string, float>();
    }
    
    public override void Trigger(float value, int inputIndex)
    {
        switch (inputIndex)
        {
            case 0:
                base.Trigger();
                break;
            case 1:
                attack = value * 100;
                // base.Trigger();
                break;
            case 2:
                decay = value * 100;
                break;
        }
    }

    public override Dictionary<string, float> MusicParams()
    {
        return new Dictionary<string, float>
        {
            { "attack", attack },
            { "decay", decay },
            { "release", release }
        };
    }
}
