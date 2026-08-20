using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using FMODUnity;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.Serialization;
using Random = UnityEngine.Random;

/// <summary>
/// Manages ships, handling setup, stat changes, and more for player and enemy ships.
/// </summary>
public class ShipManager : MonoBehaviour
{
    public static ShipManager Instance;
    private void Awake()
    {
        if (Instance != null && Instance != this)
        {
            Destroy(gameObject);
        }
        else
        {
            Instance = this;
            DontDestroyOnLoad(this);
        }
    }
    
    [System.Serializable]
    private struct Ship : IEquatable<Ship>
    {
        public ShipData baseShip;
        public string name;
        public float currentHull;
        public float maxHull;
        public float shield;
        public Reactor reactor;
        public List<Weapon> weapons;
        public AuxiliarySystems auxSystems;
        public float evasion;

        public bool Equals(Ship other)
        {
            return Equals(baseShip, other.baseShip) && name == other.name && currentHull.Equals(other.currentHull) && maxHull.Equals(other.maxHull) && shield.Equals(other.shield) && Equals(reactor, other.reactor) && Equals(weapons, other.weapons) && Equals(auxSystems, other.auxSystems) && evasion.Equals(other.evasion);
        }

        public override bool Equals(object obj)
        {
            return obj is Ship other && Equals(other);
        }

        public override int GetHashCode()
        {
            var hashCode = new HashCode();
            hashCode.Add(baseShip);
            hashCode.Add(name);
            hashCode.Add(currentHull);
            hashCode.Add(maxHull);
            hashCode.Add(shield);
            hashCode.Add(reactor);
            hashCode.Add(weapons);
            hashCode.Add(auxSystems);
            hashCode.Add(evasion);
            return hashCode.ToHashCode();
        }
    }

    public float hullRepairCost = 15;

    void Start()
    {
        // InitPlayerShip();
        // InitEnemyShip();

        // Debug.Log("hey im boutta add onsceneloaded");
        SceneManager.sceneLoaded += OnSceneLoaded;
        EventBus.Instance.newCombatEncounterStarted.AddListener(InitEnemyShip);
        EventBus.Instance.combatStarted.AddListener(InitEnemyShip);
        EventBus.Instance.playerHullRepairAttempted.AddListener(OnPlayerHullRepairAttempted);
        
        OnSceneLoaded(SceneManager.GetActiveScene(), LoadSceneMode.Single);
    }

    void Update()
    {
        // Debug.Log(enemy.hull);
        // enemy.hull -= 1f;
    }

    private bool playerShipInitialized = false;
    private void OnSceneLoaded(Scene scene, LoadSceneMode mode)
    {
        // Debug.Log("OnSceneLoaded hi i'm shipmanager");
        if (scene.name == "Cockpit" || scene.name == "Creative Mode")// && !playerShipInitialized)
        {
            InitPlayerShip();
            InitEnemyShip();
            playerShipInitialized = true;
        }
    }
    
    #region Player Ship
    [HideInInspector] public List<ShipData> basePlayerShips;
    [Header("Ships")]
    [SerializeField] private Ship player;

    /// <summary>
    /// Loads all ships, then filters to just ships that can be used
    /// by the player and have been unlocked.
    /// </summary>
    private void LoadPlayerShips()
    {
        basePlayerShips = new List<ShipData>();
        var allShips = Resources.LoadAll<ShipData>("Ships");
        foreach (var ship in allShips)
        {
            if (ship.shipClass == ShipData.ShipClass.Player && IsShipUnlocked(ship))
            {
                basePlayerShips.Add(ship);
            }
        }
    }

    private bool IsShipUnlocked(ShipData ship)
    {
        // TODO: Reference player milestones in save file, once that exists.
        // something like
        // var unlocked = false;
        // foreach (var milestone in PlayerSaveData.milestones)
        // {
        //     if (ship.playerUnlockRequirement == milestone)
        //     {
        //         unlocked = true;
        //     }
        // }
        // return unlocked;
        
        return true;
    }
    
    /// <summary>
    /// Initializes the player's ship stats (as stored in the ShipManager)
    /// based on the base ship the player chooses at the start of a run.
    /// </summary>
    /// <param name="baseShip"> Determines which ship the player is flying.</param>
    public void InitPlayerShip(ShipData baseShip)
    {
        player.baseShip = baseShip;
        player.name = baseShip.name;
        player.maxHull = baseShip.maxHull;
        player.currentHull = baseShip.maxHull;
        player.evasion = 1;
        
        UIManager.Instance.InitPlayerSystemsDisplay();
        InventoryManager.Instance.scrap += 20;
    }

    private void InitPlayerShip()
    {
        // Debug.Log("InitPlayerShip");
        player = new Ship
        {
            name = "Player ship",
            maxHull = 100,
            currentHull = 100,
            shield = 20,
            weapons = new()
        };
        var weaponRacks = GameObject.FindGameObjectsWithTag("Weapon");
        foreach (var weapon in weaponRacks)
        {
            player.weapons.Add(weapon.GetComponent<Weapon>());
        }
        
        if (SceneManager.GetActiveScene() == SceneManager.GetSceneByName("Cockpit"))
        {
            player.reactor = GameObject.FindWithTag("Reactor").GetComponent<Reactor>();
        }
        
        UIManager.Instance.InitPlayerSystemsDisplay();
    }
    // Because the module racks in Creative Mode are instantiated at start, they don't exist when OnLoadScene runs
    // so we just let the Rack Packer in the scene set it later and cross our fingers that things don't break
    public void SetPlayerReactor(Reactor reactor)
    {
        player.reactor = reactor;
    }

    public Weapon[] PlayerWeapons()
    {
        return player.weapons.ToArray();
    }

    public Reactor PlayerReactor()
    {
        return player.reactor;
    }

    public string PlayerName()
    {
        return player.name;
    }

    public float PlayerCurrentHull()
    {
        return player.currentHull;
    }

    public float PlayerMaxHull()
    {
        return 100;
    }

    public bool PlayerReadyForCombat()
    {
        return PlayerWeapons().ToList().Exists(x => !x.Warning(out _));
    }

    public void SetPlayerName(string shipName)
    {
        player.name = shipName;
    }

    public void SetPlayerHull(float hull, bool currentOrMax)
    {
        if (currentOrMax)
        {
            player.maxHull = hull;
        }
        else
        {
            player.currentHull = hull;
        }
    }

    public void SetPlayerEvasion(float evasion)
    {
        player.evasion = evasion;
    }
    
    #endregion
    
    #region Enemy Ship
    [SerializeField] private Ship enemy;
    
    [HideInInspector] public List<ShipData> baseEnemyShips;
    [HideInInspector] public List<ShipData> baseEliteShips;
    [HideInInspector] public List<ShipData> baseBossShips;
    
    /// <summary>
    /// Loads all ships, then filters to just ships that can appear as enemy ships,
    /// sorting into Enemy, Elite, and Boss ship lists.
    /// </summary>
    private void LoadEnemyShips()
    {
        baseEnemyShips = new List<ShipData>();
        baseEliteShips = new List<ShipData>();
        baseBossShips = new List<ShipData>();
        var allShips = Resources.LoadAll<ShipData>("Ships");
        foreach (var ship in allShips)
        {
            switch (ship.shipClass)
            {
                case ShipData.ShipClass.Enemy:
                    baseEnemyShips.Add(ship);
                    break;
                case ShipData.ShipClass.Elite:
                    baseEliteShips.Add(ship);
                    break;
                case ShipData.ShipClass.Boss:
                    baseBossShips.Add(ship);
                    break;
            }
        }
    }

    private void InitEnemyShip()
    {
        for (var i = 0; i < transform.childCount; i++)
        {
            if (transform.GetChild(i).TryGetComponent(out Weapon weapon) || transform.GetChild(i).TryGetComponent(out Reactor reactor))
            {
                Destroy(transform.GetChild(i).gameObject);
            }
        }
        // Debug.Log("InitEnemyShip");
        enemy = new Ship
        {
            name = "Enemy ship",
            maxHull = 10 + 5 * CombatManager.Instance.fightLevel,
            currentHull = 10 + 5 * CombatManager.Instance.fightLevel,
            shield = 10 * CombatManager.Instance.fightLevel,
            weapons = new List<Weapon>()
        };
        var numWeapons = Random.Range(1, 2);
        if (Random.value < (float)CombatManager.Instance.fightLevel / 10) numWeapons++;
        for (var i = 0; i < numWeapons; i++)
        {
            var newWeapon = new GameObject();
            newWeapon.transform.SetParent(transform);
            newWeapon.name = "Enemy Weapon";
            var weapon = newWeapon.AddComponent<Weapon>();
            weapon.enemySystem = true;
            weapon.baseWeaponStats = new(Common.RandomEnemyWeaponStats(CombatManager.Instance.fightLevel));
            weapon.warming = true; // TODO: THIS IS TEMPORARY, THE WEAPONS SHOULD NOT ALL WARMUP AT ONCE
            var er = weapon.AddComponent<EnergyReservoir>();
            weapon.energyReservoir = er;
            er.maxStoredEnergy = 50;
            er.invisible = true;
            enemy.weapons.Add(weapon);
        }
        var newReactorObj = new GameObject();
        newReactorObj.transform.SetParent(transform);
        newReactorObj.name = "Enemy Reactor";
        var newReactor = newReactorObj.AddComponent<Reactor>();
        newReactor.health = newReactor.maxHealth;
        newReactor.enemySystem = true;
        enemy.reactor = newReactor;
        
        EventBus.Instance.enemyInitialized.Invoke();
        
        UIManager.Instance.InitEnemySystemsDisplay();
    }

    public Weapon[] EnemyWeapons()
    {
        return enemy.weapons.ToArray();
    }

    public Reactor EnemyReactor()
    {
        return enemy.reactor;
    }

    public float EnemyHull()
    {
        return enemy.currentHull;
    }

    public float EnemyMaxHull()
    {
        return enemy.maxHull;
    }
    
    #endregion
    
    #region Common Ship Methods

    public float PlayerEvasion()
    {
        return player.evasion;
    }

    public float EnemyEvasion()
    {
        return enemy.evasion;
    }

    /// <summary>
    /// Deals damage to enemy ship, and applies any associated status effects.
    /// </summary>
    /// <param name="weaponStats">put the lime in the coconut</param>
    public void DamagePlayer(IWeaponModule.WeaponStats weaponStats)
    {
        DamageShip(ref player, weaponStats);
    }

    /// <summary>
    /// Deals damage to enemy ship, and applies any associated status effects.
    /// </summary>
    /// <param name="weaponStats">weapon stats</param>
    public void DamageEnemy(IWeaponModule.WeaponStats weaponStats)
    {
        DamageShip(ref enemy, weaponStats);
    }

    /// <summary>
    /// Calculates actual damage received after shields, resistances, weaknesses, etc.
    /// done to target ship. Also applies the associated status effects.
    /// </summary>
    /// <param name="target">The ship to damage</param>
    /// <param name="weaponStats">weafweg statse</param>
    private void DamageShip(ref Ship target, IWeaponModule.WeaponStats weaponStats)
    {
        if (CombatManager.Instance.state != CombatManager.State.inCombat)
        {
            return;
        }
        
        // pick random system to target
        // the attack will deal some damage to the targeted system, and some damage to the hull
        var potentialSystemTargets = new List<ModuleRack>();
        potentialSystemTargets.Add(target.reactor);
        foreach (var weapon in target.weapons)
        {
            potentialSystemTargets.Add(weapon);
        }
        // potentialSystemTargets.Add(target.auxSystems);

        var systemTargets = new List<ModuleRack>
        {
            potentialSystemTargets[Random.Range(0, potentialSystemTargets.Count)]
        };
        
        // damage
        // hullDamage
        // systemDamage
        // heat
        // accuracy
        // soundType

        if (Random.value < 1 - weaponStats.Stats["accuracy"])
        {
            DisplayManager.Instance.Log("Miss!");
            return;
        }
        
        var hullDamage = .5f * weaponStats.Stats["damage"];
        var systemDamage = .5f * weaponStats.Stats["damage"];

        hullDamage *= 1 + weaponStats.Stats["hullDamage"];
        systemDamage *= 1 + weaponStats.Stats["systemDamage"];

        var stunAmount = 0f;
        var slowAmount = 0f;
        
        foreach (var effect in weaponStats.Effects)
        {
            if (effect.Value == 0) continue;
            
            switch (effect.Key)
            {
                case Common.Effect.None:
                    break;
                case Common.Effect.Stun:
                    stunAmount += effect.Value;
                    break;
                case Common.Effect.Slow:
                    slowAmount += effect.Value;
                    break;
                case Common.Effect.Skip:
                    //TODO: Implement shields
                    break;
                case Common.Effect.Sustain:
                    //TODO
                    break;
                case Common.Effect.Siphon:
                    if (target.Equals(enemy))
                    {
                        var energySiphonSum = effect.Value;
                        var energyToSteal = new Dictionary<Common.SoundType, float>();
                        foreach (var energyType in enemy.reactor.energyReservoir.storedEnergy)
                        {
                            if (energyType.Value > energySiphonSum)
                            {
                                energyToSteal[energyType.Key] = energySiphonSum;
                                energySiphonSum = 0;
                            }
                            else
                            {
                                energyToSteal[energyType.Key] = energyType.Value;
                                energySiphonSum -= energyType.Value;
                            }
                        }
                        
                        enemy.reactor.energyReservoir.TrySpendEnergy(energyToSteal);
                        player.reactor.energyReservoir.AddEnergy(energyToSteal);
                    }
                    else if (target.Equals(player))
                    {
                        var energySiphonSum = effect.Value;
                        var energyToSteal = new Dictionary<Common.SoundType, float>();
                        foreach (var energyType in player.reactor.energyReservoir.storedEnergy)
                        {
                            if (energyType.Value > energySiphonSum)
                            {
                                energyToSteal[energyType.Key] = energySiphonSum;
                                energySiphonSum = 0;
                            }
                            else
                            {
                                energyToSteal[energyType.Key] = energyType.Value;
                                energySiphonSum -= energyType.Value;
                            }
                        }
                        
                        player.reactor.energyReservoir.TrySpendEnergy(energyToSteal);
                        enemy.reactor.energyReservoir.AddEnergy(energyToSteal);
                    }
                    break;
                case Common.Effect.Scrap:
                    InventoryManager.Instance.scrap += effect.Value;
                    break;
                case Common.Effect.Splash:
                    // add additional targets
                    for (var i = 0; i < Mathf.Floor(effect.Value); i++)
                    {
                        systemTargets.Add(potentialSystemTargets[Random.Range(0, potentialSystemTargets.Count)]);
                    }
                    // divide damage (& other applicable effects) between targets
                    systemDamage /= Mathf.Floor(effect.Value);
                    stunAmount /= Mathf.Floor(effect.Value);
                    slowAmount /= Mathf.Floor(effect.Value);
                    break;
                case Common.Effect.SeekReactor:
                    for (var i = 0; i < systemTargets.Count; i++)
                    {
                        if (Random.value <= effect.Value)
                        {
                            systemTargets[i] = target.reactor;
                        }
                    }
                    break;
                case Common.Effect.SeekWeapon:
                    for (var i = 0; i < systemTargets.Count; i++)
                    {
                        if (Random.value <= effect.Value)
                        {
                            systemTargets[i] = target.reactor;
                        }
                    }
                    if (Random.value <= effect.Value)
                    {
                        systemTargets[0] = target.weapons[Random.Range(0, target.weapons.Count)];
                    }
                    break;
                case Common.Effect.SeekAux:
                    for (var i = 0; i < systemTargets.Count; i++)
                    {
                        if (Random.value <= effect.Value)
                        {
                            systemTargets[i] = target.auxSystems;
                        }
                    }
                    break;
            }
        }
        
        
        target.currentHull -= hullDamage;
        foreach (var systemTarget in systemTargets)
        {
            if (stunAmount > 0)
            {
                systemTarget.Stun(stunAmount);
            }
            if (slowAmount > 0)
            {
                systemTarget.Slow(slowAmount);
            }
            
            if (weaponStats.SoundType.Values.Sum() > 0)
            {
                var targetType = Common.SoundType.Pure;
                if (systemTarget is Weapon targetWeapon)
                {
                    
                    targetType = targetWeapon.WeaponStats().SoundType.OrderByDescending(kvp => kvp.Value).First().Key;
                }
                else if (systemTarget is Reactor targetReactor)
                {
                    // targetType = targetReactor.SoundType().OrderByDescending(kvp => kvp.Value).First().Key;
                }
                systemDamage *= Common.SoundTypeEffectMult(weaponStats.SoundType.OrderByDescending(kvp => kvp.Value).First().Key, targetType, weaponStats.SoundType.OrderByDescending(kvp => kvp.Value).First().Value);
            }
            
            systemTarget.health -= systemDamage;
            EventBus.Instance.systemHit.Invoke(systemTarget);
        }
        
        DisplayManager.Instance.Log($"{Math.Truncate(systemDamage)} dealt to {target.name}'s systems. {Math.Truncate(hullDamage)} damage dealt to hull.");
        
        // Debug.Log($"{target.name} was hit for {damage} damage. Hull is now {target.hull}.");
        
        if (target.currentHull <= 0)
        {
            Die(target);
        }
    }

    private IEnumerator DamageOverTime()
    {
        return null;
    }

    private void Die(Ship target)
    {
        if (target.Equals(player))
        {
            // check for Escape Modules
            if (player.reactor.ModulesOnRack().Exists(x => x is EscapeModule))
            {
                var escMod = player.reactor.ModulesOnRack().Find(x => x is EscapeModule);
                Destroy(escMod.gameObject);
                EventBus.Instance.playerEscaped.Invoke();
                InventoryManager.Instance.scrap += 15;
                EventBus.Instance.playerScrapValueChanged.Invoke();
                
                return;
            }
            EventBus.Instance.playerDefeated.Invoke();
        }
        else if (target.Equals(enemy))
        {
            EventBus.Instance.enemyDefeated.Invoke();
        }
    }
    
    #endregion

    private void OnPlayerHullRepairAttempted()
    {
        if (InventoryManager.Instance.scrap < hullRepairCost)
            return;
        
        InventoryManager.Instance.scrap -= hullRepairCost;
        player.currentHull = PlayerMaxHull();

        foreach (var weapon in player.weapons)
        {
            weapon.health = weapon.maxHealth;
        }
        player.reactor.health = player.reactor.maxHealth;
    }

    public void HealPlayerToFull()
    {
        player.currentHull = PlayerMaxHull();
        
        foreach (var weapon in player.weapons)
        {
            weapon.health = weapon.maxHealth;
        }
        player.reactor.health = player.reactor.maxHealth;
    }
}
