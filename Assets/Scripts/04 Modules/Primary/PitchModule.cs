using System.Collections.Generic;
using UnityEngine;

public class PitchModule : PrimaryModule, IWeaponModule
{
    public float pitch;
    public float seekReactor;
    public float seekWeapon;
    public float seekAux;

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

    public override Dictionary<string, float> ChangeMusicParams(Dictionary<string, float> musicParams)
    {
        musicParams["pitch"] = pitch;
        return musicParams;
    }


    public IWeaponModule.WeaponStats ChangeWeaponStats(IWeaponModule.WeaponStats input)
    {
        input.Effects[Common.Effect.SeekReactor] += seekReactor;
        input.Effects[Common.Effect.SeekWeapon] += seekWeapon;
        input.Effects[Common.Effect.SeekAux] += seekAux;
        
        input.Stats["heat"] += heat;
        input.SoundType[Common.SoundType.Izki] += izki;
        input.SoundType[Common.SoundType.Aubo] += aubo;
        input.SoundType[Common.SoundType.Dwth] += dwth;
        input.SoundType[Common.SoundType.Hysh] += hysh;
        
        return input;
    }
}
