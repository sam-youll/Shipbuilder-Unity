using UnityEngine;

public class PitchModule : PrimaryModule
{
    private float pitch;
    
    public override void Trigger(float value)
    {
        value %= 7;
        pitch = Notes.GetPitch(Conductor.Instance.keyRoot, Conductor.Instance.mode, (int)value);
    }

    protected override void Start()
    {
        base.Start();
        MusicParams["pitch"] = pitch;
    }
}
