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
        Siphon, // steal energy/hull TODO: decide which one
        Scrap // drop scrap on hit
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
        { "warmupRate", 0 },
        { "fireRate", 0 },
        { "damage", 0 },
        { "hullDamage", 0 },
        { "shieldDamage", 0 },
        { "bulletSpeed", 0 },
        { "accuracy", 0 },
        { "bulletType", 0 }
    };
}
