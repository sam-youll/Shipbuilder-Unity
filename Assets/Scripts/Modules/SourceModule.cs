using System.Collections.Generic;
using UnityEngine;

public class SourceModule : PrimaryModule
{
    // TODO: reorder these to match FMOD source parameter
    public enum Waveform
    {
        Nothing,
        Nothing2,
        Sine,
        Square,
        Saw,
        Noise
    }
    public Waveform waveform = Waveform.Sine;

    protected override void Start()
    {
        base.Start();
        
        MusicParams["source"] = (float)waveform;
    }

    public override void Trigger(Dictionary<string, float> MusicParams, Dictionary<string, float> CombatStats)
    {
        base.Trigger(MusicParams, CombatStats);
    }
}
