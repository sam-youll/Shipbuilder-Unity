using System.Collections.Generic;
using UnityEngine;

public class DelayModule : PrimaryModule, IWeaponModule
{
    public float taps;
    public float damage = 2;
    public float delayTime = 0;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    public override string Description()
    {
        return "Adds delay, causing the weapon to fire twice (deals more damage).";
    }

    public override string Info()
    {
        return $"Currently delaying by {delayTime} milliseconds.";
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

    public override Dictionary<string, float> ChangeMusicParams(Dictionary<string, float> musicParams)
    {
        musicParams["delayTime"] += delayTime;
        return musicParams;
    }

    public IWeaponModule.WeaponStats MyWeaponStats()
    {
        return new IWeaponModule.WeaponStats()
        {
            Stats = new()
            {
                { "damage", damage },
            },
            SoundType = new()
            {
                { Common.SoundType.Izki, izki },
                { Common.SoundType.Aubo, aubo },
                { Common.SoundType.Dwth, dwth },
                { Common.SoundType.Hysh, hysh }
            }
        };
    }

    public IWeaponModule.WeaponStats ChangeWeaponStats(IWeaponModule.WeaponStats input)
    {
        input.Stats["damage"] += damage;
        
        input.Stats["heat"] += heat;
        input.SoundType[Common.SoundType.Izki] += izki;
        input.SoundType[Common.SoundType.Aubo] += aubo;
        input.SoundType[Common.SoundType.Dwth] += dwth;
        input.SoundType[Common.SoundType.Hysh] += hysh;
        
        return input;
    }
}
