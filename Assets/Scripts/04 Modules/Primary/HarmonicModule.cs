using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

public class HarmonicModule : PrimaryModule, IWeaponModule
{
    public float damage = 1.2f;
    public float stun;
    public float siphon;
    
    public enum Profile
    {
        neutral = 0,
        combOdds = 1,
        combEvens = 2,
        naturalCurve = 3
    }
    public Profile profile = Profile.neutral;

    private static List<Profile> profiles = new List<Profile>
    {
        Profile.neutral,
        Profile.combOdds,
        Profile.combEvens,
        Profile.naturalCurve
    };

    public override string Description()
    {
        return "Adds harmonics.";
    }

    public override string Info()
    {
        return $"Current harmonic profile is {profile}.";
    }

    public override void Trigger(float value, int inputIndex)
    {
        switch (inputIndex)
        {
            case 0:
                base.Trigger();
                break;
            case 1:
                value %= profiles.Count;
                profile = profiles[(int)value];
                // base.Trigger();
                break;
        }
    }

    public override Dictionary<string, float> ChangeMusicParams(Dictionary<string, float> musicParams)
    {
        musicParams["harmonics"] = (float)profile;
        return musicParams;
    }

    public IWeaponModule.WeaponStats ChangeWeaponStats(IWeaponModule.WeaponStats input)
    {
        input.Stats["damage"] += damage;
        input.Effects[Common.Effect.Stun] += stun;
        input.Effects[Common.Effect.Siphon] += siphon;
        
        input.Stats["heat"] += heat;
        input.SoundType[Common.SoundType.Izki] += izki;
        input.SoundType[Common.SoundType.Aubo] += aubo;
        input.SoundType[Common.SoundType.Dwth] += dwth;
        input.SoundType[Common.SoundType.Hysh] += hysh;
        
        return input;
    }
}
