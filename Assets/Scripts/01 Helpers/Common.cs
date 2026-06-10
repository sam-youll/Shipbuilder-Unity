using System.Collections.Generic;
using UnityEngine;

public static class Common
{
    /// <summary>
    /// Weapons, shields, and other components in Audionaut can be typed,
    /// which can multiply effectiveness when interacting with other types.
    /// Izki -> Aubo -> Dwth -> Izki. Hysh -> (Izki, Aubo, Dwth).  None -> Hysh.
    /// </summary>
    public enum SoundType
    {
        None,
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
    };

    public static readonly Dictionary<string, float> CombatStats = new()
    {
        { "damage", 0 }, // Base damage dealt (Damage is equal to sum of all "damage").
        { "hullDamage", 0 }, // Multiplier for damage to hull. (Damage mult is equal to 1 + sum, which is then used as a coefficient for damage).
        { "systemDamage", 0 }, // Multiplier for damage to systems. Bonus system damage almost always means less hull damage, and vice versa.
        { "heat", 0 }, // The amount of heat generated on trigger. This should roughly correlate to power draw.
        { "accuracy", 0 }, // Multiplier for chance to hit (1 + sum). 
        { "soundType", 0 }
    };
    
    public static Dictionary<string, float> RandomEnemyWeaponStats(int difficulty)
    {
        var dict = new Dictionary<string, float>(CombatStats);

        dict["warmupRate"] = Random.value * .2f + .1f * difficulty + .5f;
        dict["fireRate"] = Random.value * .2f + .1f * difficulty + .5f;
        dict["damage"] = 2 + Random.value * .2f + .1f * difficulty + .5f;
        dict["soundType"] = Random.Range(0, 4);

        return dict;
    }
}
