using System.Collections.Generic;
using UnityEngine;

public class SourceModule : PrimaryModule
{
    // TODO: reorder these to match FMOD source parameter
    public enum Waveform
    {
        Saw,
        Sine,
        Square,
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
