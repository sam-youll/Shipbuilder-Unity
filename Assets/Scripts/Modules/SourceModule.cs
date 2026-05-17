using System;
using System.Collections.Generic;
using UnityEngine;

public class SourceModule : PrimaryModule
{
    // TODO: reorder these to match FMOD source parameter
    public enum Waveform
    {
        Sine = 2,
        Square = 3,
        Saw = 4,
        Wobble = 5,
        Crunce = 6,
        Bloops = 7
    }
    public Waveform waveform = Waveform.Sine;

    private static List<Waveform> waveforms = new List<Waveform>
    {
        Waveform.Sine,
        Waveform.Square,
        Waveform.Saw,
        Waveform.Wobble,
        Waveform.Crunce,
        Waveform.Bloops
    };
    
    public Common.BulletType bulletType = Common.BulletType.Slug;

    public bool waveformKnobEnabled;

    public float damage = 1;
    
    public override string Info()
    {
        var info = base.Info() + "---\n";
        info += $"bulletType: {Enum.GetName(typeof(Common.BulletType), (int)bulletType)}\n";
        return info;
    }
    
    protected override void Start()
    {
        base.Start();
        
        musicParams["source"] = (float)waveform;
        if (waveformKnobEnabled)
        {
            GetComponentInChildren<Knob>().valueChanged.AddListener(UpdateWaveform);
        }
        combatStats["bulletType"] = (float)bulletType;
        combatStats["damage"] = damage;
    }

    void UpdateWaveform(float value)
    {
        waveform = waveforms[(int)value];
        musicParams["source"] = (float)waveform;
    }

    void UpdateWaveform(int value)
    {
        waveform = waveforms[value];
        musicParams["source"] = (float)waveform;
    }
}
