using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

public class HarmonicModule : PrimaryModule
{
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

    protected override void Start()
    {
        MusicParams["harmonics"] = (float)profile;
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
                MusicParams["harmonics"] = value;
                // base.Trigger();
                break;
        }
    }
}
