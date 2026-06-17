using System.Collections.Generic;
using UnityEngine;

public class PitchModule : PrimaryModule, IWeaponModule
{
    public float pitch;

    public override string Description()
    {
        return "Sets pitch based on the received value, quantized to the current scale.";
    }

    public override string Info()
    {
        return $"Current pitch is {pitch}.";
    }

    public override void Trigger(float value, int inputIndex)
    {
        switch (inputIndex)
        {
            case 0:
                base.Trigger();
                break;
            case 1:
                value %= 7;
                pitch = Notes.GetPitch(Conductor.Instance.keyRoot, Conductor.Instance.mode, (int)value);
                // Debug.Log($"PitchModule received a value {value} and set pitch to {pitch}.");
                break;
        }
    }

    public override Dictionary<string, float> MusicParams()
    {
        return new Dictionary<string, float>
        {
            { "pitch", pitch }
        };
    }

    public IWeaponModule.WeaponStats MyWeaponStats()
    {
        return new IWeaponModule.WeaponStats()
        {
            SoundType = new()
            {
                { Common.SoundType.Izki, izki },
                { Common.SoundType.Aubo, aubo },
                { Common.SoundType.Dwth, dwth },
                { Common.SoundType.Hysh, hysh }
            }
        };
    }
}
