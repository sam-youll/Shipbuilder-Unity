using System.Collections.Generic;
using UnityEngine;

public class DelayModule : PrimaryModule, IWeaponModule
{
    public float taps;
    public float fireRate = 2;
    public float damage = 2;
    public float delayTime = 0;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    public override string Description()
    {
        return "Adds delay. Crazy, right?";
    }
    
    public override void Trigger(float value, int inputIndex)
    {
        switch (inputIndex)
        {
            case 0:
                base.Trigger();
                break;
            case 1:
                delayTime = value * 1000;
                break;
        }
    }

    public override Dictionary<string, float> MusicParams()
    {
        return new Dictionary<string, float>
        {
            { "delayTime", delayTime }
        };
    }

    public Dictionary<string, float> WeaponStats()
    {
        return new Dictionary<string, float>
        {

        };
    }
}
