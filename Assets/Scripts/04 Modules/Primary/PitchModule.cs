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
        return "Angles the projectile, changing the audible pitch and increasing likelihood to hit specific enemy systems.";
    }

    public override string Info()
    {
        var info = "";
        if (seekReactor > 0) info += $"Projectiles are {seekReactor:P0} more likely to hit the enemy's reactor.\n";
        if (seekWeapon > 0) info += $"Projectiles are {seekWeapon:P0} more likely to hit one of the enemy's weapons.\n";
        info += $"Audible pitch is {pitch}.";
        return info;
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
