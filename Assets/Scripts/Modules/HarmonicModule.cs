using UnityEngine;

public class HarmonicModule : PrimaryModule
{
    public override void Trigger(float value, int inputIndex)
    {
        switch (inputIndex)
        {
            case 0:
                base.Trigger();
                break;
            case 1:
                MusicParams["harmonics"] = value;
                // base.Trigger();
                break;
        }
    }
}
