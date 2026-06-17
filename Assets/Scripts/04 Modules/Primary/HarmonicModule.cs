using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

public class HarmonicModule : PrimaryModule, IWeaponModule
{
    public float damage = 1.2f;
    
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

    public override Dictionary<string, float> MusicParams()
    {
        return new Dictionary<string, float>()
        {
            { "harmonics" , (float)profile }
        };
    }

    public IWeaponModule.WeaponStats MyWeaponStats()
    {
        return new IWeaponModule.WeaponStats
        {
            Stats = new Dictionary<string, float>
            {
                { "damage", damage },
            },
            SoundType = new()
            {
                { Common.SoundType.Izki , izki },
                { Common.SoundType.Aubo , aubo },
                { Common.SoundType.Dwth , dwth },
                { Common.SoundType.Hysh , hysh }
            }
        };
    }
}
