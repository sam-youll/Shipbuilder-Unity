using System;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// Holds all base info for ships, including stats, systems, and any special traits.
/// </summary>
[CreateAssetMenu(fileName = "New Ship", menuName = "Scriptable Objects/ShipData")]
public class ShipData : ScriptableObject
{
    // TODO: THE PLAN
    // The idea is to implement a few different enums to create a tagging system,
    // so ships can be loaded at runtime and automatically categorized.
    // ---
    // Currently, ships determine:
    // -
    // - Dimensions of reactor + weapons (as well as number of weapon bays)
    // - 
    // - 
    // ---
    // In the future, ships may implement:
    // - Type affinities
    // - Constellation affinities
    // - Damage affinities
    // - Preinstalled weapons (WE SHOULD DEF DO THIS SOON)
    // - Special systems/traits (auto-heal, scrap salvage arm, 5G wifi)

    [Flags] // this is so a ship can be used by the player and enemies if we want
    public enum ShipClass
    {
        None    = 0, // 0 for no flags set
        Player  = 1 << 0, // bitshift 1
        Enemy   = 1 << 1, // 2
        Elite   = 1 << 2, // 4
        Boss    = 1 << 3  // 8
    }
    public ShipClass shipClass;

    public GameStateManager.UnlockMilestones playerUnlockRequirement;
    
    #region Core Systems
    [Header("Core Systems")]
    // Hull
    [Tooltip("Maximum hull health.")]
    public float maxHull;
    public Common.SoundType hullSoundTypeAffinity;
    
    // Reactor
    [Tooltip("Determines size of reactor module rack.")]
    public Vector2Int reactorSize;
    public Common.SoundType reactorSoundTypeAffinity;
    
    // Weapon Bays
    [Tooltip("Number of weapon bays is determined by number of list items, " +
             "with dimensions of each module rack being determined by list item value." +
             "These will be unlocked over time.")]
    public List<Vector2Int> weaponBays;
    // public Weapon.StoredWeaponPatch[] startingWeaponPatches;
    #endregion
    
    #region Optional Systems
    // [Header("Optional Systems")]
    // Shields
    // public int shieldLayers;
    // public float shieldHealth;
    // public float shieldRechargeRate;
    
    // Cloaking
    // public bool cloaked;
    // public float cloakDuration;
    
    // Sensors
    // public float sensorStrength;
    
    #endregion
    
    #region Additional Traits
    // public GameStateManager.Constellation constellationAffinity;
    // TODO: add additional traits idk what format though
    #endregion
}
