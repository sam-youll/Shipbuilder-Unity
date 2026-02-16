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
        Noise = 5
    }
    public Waveform waveform = Waveform.Sine;

    private static List<Waveform> waveforms = new List<Waveform>
    {
        Waveform.Sine,
        Waveform.Square,
        Waveform.Saw,
        Waveform.Noise
    };
    
    public Common.BulletType bulletType = Common.BulletType.Slug;

    public bool waveformKnobEnabled;

    public float bonusDamage = 1;
    
    protected override void Start()
    {
        base.Start();
        
        MusicParams["source"] = (float)waveform;
        if (waveformKnobEnabled)
        {
            GetComponentInChildren<Knob>().valueChanged.AddListener(UpdateWaveform);
        }
        CombatStats["bulletType"] = (float)bulletType;
        CombatStats["damage"] = (float)bonusDamage;
    }

    void UpdateWaveform(float value)
    {
        waveform = waveforms[(int)value];
        MusicParams["source"] = (float)waveform;
    }

    void UpdateWaveform(int value)
    {
        waveform = waveforms[value];
        MusicParams["source"] = (float)waveform;
    }
}
