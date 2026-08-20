using System;
using System.Collections.Generic;
using UnityEngine;

public class CatalystModule : PrimaryModule, IWeaponModule
{
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

    public override string Description()
    {
        return "Generates the base projectile for the weapon when triggered.";
    }

    public override string Info()
    {
        return $"Projectile deals {damage} base damage.\n" + 
               $"Current waveform is {waveform}.";
    }

    protected override void Start()
    {
        base.Start();
        
        if (waveformKnobEnabled)
        {
            GetComponentInChildren<Knob>().valueChanged.AddListener(UpdateWaveform);
        }
    }

    void UpdateWaveform(float value)
    {
        waveform = waveforms[(int)value];
    }

    void UpdateWaveform(int value)
    {
        waveform = waveforms[value];
    }

    public override Dictionary<string, float> ChangeMusicParams(Dictionary<string, float> musicParams)
    {
        musicParams["source"] = (float)waveform;
        
        
        return musicParams;
    }

    public IWeaponModule.WeaponStats ChangeWeaponStats(IWeaponModule.WeaponStats input)
    {
        input.Stats["damage"] += damage;

        input.Stats["heat"] += heat;
        input.SoundType[Common.SoundType.Izki] += izki;
        input.SoundType[Common.SoundType.Aubo] += aubo;
        input.SoundType[Common.SoundType.Dwth] += dwth;
        input.SoundType[Common.SoundType.Hysh] += hysh;
        
        return input;
    }
}
