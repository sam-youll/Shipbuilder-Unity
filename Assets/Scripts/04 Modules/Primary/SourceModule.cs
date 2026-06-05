using System;
using System.Collections.Generic;
using UnityEngine;

public class SourceModule : PrimaryModule, IWeaponModule
{
    // TODO: reorder these to match FMOD source parameter
    public enum Waveform
    {
        Sine = 2,
        Square = 3,
        Saw = 4,
        Noise = 5,
        Wobble = 6,
        Crunce = 7,
        Bloops = 8
    }
    public Waveform waveform = Waveform.Sine;

    private static List<Waveform> waveforms = new List<Waveform>
    {
        Waveform.Sine,
        Waveform.Square,
        Waveform.Saw,
        Waveform.Noise,
        Waveform.Wobble,
        Waveform.Crunce,
        Waveform.Bloops
    };
    
    public Common.BulletType bulletType = Common.BulletType.Slug;

    public bool waveformKnobEnabled;

    public float damage = 1;

    public Dictionary<string, float> WeaponStats()
    {
        return new Dictionary<string, float>()
        {
            { "bulletType", (float)bulletType },
            { "damage", damage },
        };
    }

    public override string Description()
    {
        return "Creates the base waveform, affecting the damage amount and type of the weapon's projectiles.";
    }

    protected override void Start()
    {
        base.Start();
        
        if (waveformKnobEnabled)
        {
            GetComponentInChildren<Knob>().valueChanged.AddListener(UpdateWaveform);
        }
    }

    public override Dictionary<string, float> MusicParams()
    {
        return new Dictionary<string, float>()
        {
            { "waveform", (float)waveform }
        };
    }

    void UpdateWaveform(float value)
    {
        waveform = waveforms[(int)value];
    }

    void UpdateWaveform(int value)
    {
        waveform = waveforms[value];
    }
}
