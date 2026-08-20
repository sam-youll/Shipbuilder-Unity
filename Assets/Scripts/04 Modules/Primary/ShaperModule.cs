using System.Collections.Generic;
using UnityEngine;

public class ShaperModule : PrimaryModule, ITooltipInfo, IWeaponModule
{
    // TODO: add weapon stats
    public float systemDamageMult;
    public float hullDamageMult;
    
    public float attack;
    public float decay;
    public float release;

    public override string Description()
    {
        return "Shapes the weapon's projectile, adding damage mult to ship hull and/or systems.";
    }

    public override string Info()
    {
        var info = "";
        if (systemDamageMult > 0) info += $"System Damage Mult: +{systemDamageMult}x\n";
        if (hullDamageMult > 0) info +=  $"Hull Damage Mult: +{hullDamageMult}x\n";
        info += "Note Envelope:\n" +
                $"Attack: {attack}\n" +
                $"Decay: {decay}\n" +
                $"Release: {release}";
        return info;
    }
    
    public override void Trigger(float value, int inputIndex)
    {
        switch (inputIndex)
        {
            case 0:
                base.Trigger();
                break;
            case 1:
                attack = value * 100;
                // base.Trigger();
                break;
            case 2:
                decay = value * 100;
                break;
        }
    }

    public override Dictionary<string, float> ChangeMusicParams(Dictionary<string, float> musicParams)
    {
        musicParams["attack"] += attack;
        musicParams["decay"] += decay;
        musicParams["release"] += release;
        return musicParams;
    }

    public IWeaponModule.WeaponStats MyWeaponStats()
    {
        return new IWeaponModule.WeaponStats()
        {
            Stats = new()
            {
                { "hullDamage",  hullDamageMult },
                { "systemDamage", systemDamageMult }
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
        input.Stats["hullDamage"] += hullDamageMult;
        input.Stats["systemDamage"] += systemDamageMult;
        
        input.Stats["heat"] += heat;
        input.SoundType[Common.SoundType.Izki] += izki;
        input.SoundType[Common.SoundType.Aubo] += aubo;
        input.SoundType[Common.SoundType.Dwth] += dwth;
        input.SoundType[Common.SoundType.Hysh] += hysh;
        
        return input;
    }
}
