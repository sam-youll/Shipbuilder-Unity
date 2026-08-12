using System.Collections.Generic;
using NUnit.Framework;
using UnityEngine;

public interface ISelectable
{
    public void Select();
}

public static class Common
{
    /// <summary>
    /// Weapons, shields, and other components in Audionaut can be typed,
    /// which can multiply effectiveness when interacting with other types.
    /// Izki -> Aubo -> Dwth -> Izki. Hysh -> (Izki, Aubo, Dwth).  None -> Hysh.
    /// </summary>
    public enum SoundType
    {
        Pure,
        Izki,
        Aubo,
        Dwth,
        Hysh
    }

    /// <summary>
    /// Type of projectile fired from a weapon. This can have impacts on ship
    /// vulnerabilities, shields, bullet effects, and more.
    /// </summary>
    public enum BulletType
    {
        None,
        Slug,
        Energy,
        Explosive
    }
    
    /// <summary>
    /// Certain weapons can impart effects on ships their projectiles hit.
    /// These vary from disabling weapons to ignoring shields to dealing damage over time.
    /// </summary>
    public enum Effect
    {
        None,
        Stun, // disables weapons/systems
        Slow, // slows weapons
        Splash, // hits multiple systems
        Skip, // ignores shields
        Sustain, // damage over time
        Siphon, // steal energy
        Scrap, // drop scrap on hit
        SeekReactor,
        SeekWeapon,
        SeekAux
    }
    
    public static readonly Dictionary<string, float> NoteInfo = new()
    {
        { "pitch", 440 },
        { "length", .17f },
        { "attack", 100 },
        { "decay", 70 },
        { "release", 100 },
        { "delayTime", 0 }
    };

    public static readonly Dictionary<SoundType, float> EmptySoundType = new()
    {
        { SoundType.Pure, 0 },
        { SoundType.Izki, 0 },
        { SoundType.Aubo, 0 },
        { SoundType.Dwth, 0 },
        { SoundType.Hysh, 0 },
    };
    
    public static Dictionary<string, float> RandomEnemyWeaponStats(int difficulty)
    {
        var dict = new Dictionary<string, float>(BaseWeaponStats().Stats);

        dict["damage"] = 4 + Random.value * .5f + .5f * difficulty;
        dict["hullDamage"] = Random.value * .2f;
        dict["systemDamage"] = .2f - dict["hullDamage"];
        dict["heat"] = Random.value * .1f + .1f;
        dict["accuracy"] = Random.value * .3f + .6f;
        dict["soundType"] = Random.Range(0, 4);

        return dict;
    }

    public static Dictionary<SoundType, float> RandomEnergyCost()
    {
        return new Dictionary<SoundType, float>()
        {
            { SoundType.Pure, Random.Range(0, 3) },
            // { SoundType.Izki, Random.Range(0, 1) },
            // { SoundType.Aubo, Random.Range(0, 1) },
            // { SoundType.Dwth, Random.Range(0, 1) }
        };
    }

    public static Dictionary<SoundType, float> EmptyEnergyCost()
    {
        return new Dictionary<SoundType, float>
        {
            { SoundType.Pure, 0 },
            { SoundType.Izki, 0 },
            { SoundType.Aubo, 0 },
            { SoundType.Dwth, 0 }
        };
    }

    public static IWeaponModule.WeaponStats BaseWeaponStats()
    {
        var bws = new IWeaponModule.WeaponStats();

        bws.Stats = new Dictionary<string, float>
        {
            { "damage", 0 }, // Base damage dealt (Damage is equal to sum of all "damage").
            { "hullDamage", 0 }, // Multiplier for damage to hull. (Damage mult is equal to 1 + sum, which is then used as a coefficient for damage).
            { "systemDamage", 0 }, // Multiplier for damage to systems. Bonus system damage almost always means less hull damage, and vice versa.
            { "heat", 0 }, // The amount of heat generated on trigger. This should roughly correlate to power draw.
            { "accuracy", 0 }, // Multiplier for chance to hit (1 + sum). 
            { "soundType", 0 }
        };

        bws.Effects = new Dictionary<Effect, float>
        {
            { Effect.None, 0 },
            { Effect.Stun, 0 },
            { Effect.Slow, 0 },
            { Effect.Splash, 0 },
            { Effect.Skip, 0 },
            { Effect.Sustain, 0 },
            { Effect.Siphon, 0 },
            { Effect.Scrap, 0 },
            { Effect.SeekReactor, 0 },
            { Effect.SeekWeapon, 0 },
            { Effect.SeekAux, 0 }
        };

        bws.SoundType = new Dictionary<SoundType, float>(EmptySoundType);
        
        return bws;
    }

    public static float SoundTypeEffectMult(SoundType attacker, SoundType defender, float strength)
    {
        var mult = 1f;
        switch (attacker)
        {
            case SoundType.Pure:
                break;
            case SoundType.Izki:
                if (defender == SoundType.Aubo)
                {
                    mult *= 1.5f;
                }
                break;
            case SoundType.Aubo:
                if (defender == SoundType.Dwth)
                {
                    mult *= 1.5f;
                }
                break;
            case SoundType.Dwth:
                if (defender == SoundType.Izki)
                {
                    mult *= 1.5f;
                }
                break;
            case SoundType.Hysh:
                if (defender == SoundType.Pure)
                {
                    mult *= 1.15f;
                }
                break;
        }
        return mult * strength;
    }
}
