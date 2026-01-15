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
}
