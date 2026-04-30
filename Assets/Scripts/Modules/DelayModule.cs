using UnityEngine;

public class DelayModule : PrimaryModule
{

    public float delayTime = 0;
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    protected override void Start()
    {
        MusicParams["delayTime"] = delayTime;
    }
    public override void Trigger(float value, int inputIndex)
    {
        switch (inputIndex)
        {
            case 0:
                base.Trigger();
                break;
            case 1:
                MusicParams["delaytime"] = value * 1000;
                // base.Trigger();
                break;
        }
    }
}
