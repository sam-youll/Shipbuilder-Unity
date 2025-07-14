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

    protected override void Start()
    {
        base.Start();
        
        MusicParams["source"] = (float)waveform;
    }
}
