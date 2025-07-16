using UnityEngine;

public class PitchModule : PrimaryModule
{
    public float pitch;
    
    public override void Trigger(float value, int inputIndex)
    {
        switch (inputIndex)
        {
            case 0:
                base.Trigger();
                break;
            case 1:
                value %= 7;
                pitch = Notes.GetPitch(Conductor.Instance.keyRoot, Conductor.Instance.mode, (int)value);
                MusicParams["pitch"] = pitch;
                Debug.Log($"PitchModule received a value {value} and set pitch to  {pitch}.");
                base.Trigger();
                break;
        }
    }

    protected override void Start()
    {
        base.Start();
        MusicParams["pitch"] = pitch;
    }
}
