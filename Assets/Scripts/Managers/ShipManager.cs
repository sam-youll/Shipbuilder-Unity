using System.Collections;
using System.Collections.Generic;
using System.Linq;
using FMODUnity;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.Serialization;
    
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
    private struct Ship
    {
        public ShipData baseShip;
        public string name;
        public float currentHull;
        public float maxHull;
        public float shield;
        public List<Weapon> weapons;
        public Reactor reactor;
        public float evasion;
    }

    public float hullRepairCost = 15;

    void Start()
    {
        // InitPlayerShip();
        // InitEnemyShip();

        Debug.Log("hey im boutta add onsceneloaded");
        SceneManager.sceneLoaded += OnSceneLoaded;
        EventBus.Instance.newCombatEncounterStarted.AddListener(InitEnemyShip);
        EventBus.Instance.playerHullRepairAttempted.AddListener(OnPlayerHullRepairAttempted);
    }

    void Update()
    {
        // Debug.Log(enemy.hull);
        // enemy.hull -= 1f;
    }

    private bool playerShipInitialized = false;
    private void OnSceneLoaded(Scene scene, LoadSceneMode mode)
    {
        Debug.Log("OnSceneLoaded hi i'm shipmanager");
        if (scene.name == "Cockpit")// && !playerShipInitialized)
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
    }

    private void InitPlayerShip()
    {
        Debug.Log("InitPlayerShip");
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
            player.reactor = GameObject.FindGameObjectWithTag("Reactor").GetComponent<Reactor>();
        }
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
            maxHull = 50 + 5 * CombatManager.Instance.fightLevel,
            currentHull = 50 + 5 * CombatManager.Instance.fightLevel,
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
            weapon.enemyWeapon = true;
            weapon.weaponStats = new(Common.RandomEnemyWeaponStats(CombatManager.Instance.fightLevel));
            weapon.warming = true; // TODO: THIS IS TEMPORARY, THE WEAPONS SHOULD NOT ALL WARMUP AT ONCE
            enemy.weapons.Add(weapon);
        }
        var newReactorObj = new GameObject();
        newReactorObj.transform.SetParent(transform);
        newReactorObj.name = "Enemy Reactor";
        var newReactor = newReactorObj.AddComponent<Reactor>();
        enemy.reactor = newReactor;
        
        EventBus.Instance.enemyInitialized.Invoke();
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
        return 50 + 10 * CombatManager.Instance.fightLevel;
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
    /// Deals damage to player ship, and applies any associated status effects.
    /// </summary>
    /// <param name="damage">Amount of damage dealt.</param>
    /// <param name="effect">Status effect applied to projectile.</param>
    /// <param name="effectStrength">"Strength" of the effect. This might mean duration or some other parameter.</param>
    public void DamagePlayer(float damage, float soundType, Common.Effect effect, float effectStrength)
    {
        Damage(ref player, damage, soundType, effect, effectStrength);

        EventBus.Instance.playerHullValueChanged.Invoke();
    }

    public void DamagePlayer(float damage, float soundType)
    {
        Damage(ref player, damage, soundType, Common.Effect.None, 0);
        
        EventBus.Instance.playerHullValueChanged.Invoke();
    }

    /// <summary>
    /// Deals damage to enemy ship, and applies any associated status effects.
    /// </summary>
    /// <param name="damage">Amount of damage dealt.</param>
    /// <param name="soundType">Sound type of damage.</param>
    /// <param name="effect">Status effect applied to projectile.</param>
    /// <param name="effectStrength">"Strength" of the effect. This might mean duration or some other parameter.</param>
    public void DamageEnemy(float damage, float soundType, Common.Effect effect, float effectStrength)
    {
        Damage(ref enemy, damage, soundType, effect, effectStrength);
    }
 
    public void DamageEnemy(float damage, float soundType)
    {
        Damage(ref enemy, damage, soundType, Common.Effect.None, 0);
    }

    /// <summary>
    /// Calculates actual damage received after shields, resistances, weaknesses, etc.
    /// done to target ship. Also applies the associated status effects.
    /// </summary>
    /// <param name="target">Player or enemy ship.</param>
    /// <param name="damage">Amount of damage dealt.</param>
    /// <param name="soundType">idfhbvsiufbsiubn sound type!!! asawaawa</param>
    /// <param name="effect">Status effect applied to projectile.</param>
    /// <param name="effectStrength">"Strength" of the effect. This might mean duration or some other parameter.</param>
    private void Damage(ref Ship target, float damage, float soundType, Common.Effect effect, float effectStrength)
    {
        if (CombatManager.Instance.state == CombatManager.State.outOfCombat)
        {
            return;
        }
        
        //TODO: Add overloads without effects and stuff

        switch (soundType)
        {
            case (float)Common.SoundType.None:
                break;
            case (float)Common.SoundType.Izki:
                break;
            case (float)Common.SoundType.Aubo:
                break;
            case (float)Common.SoundType.Dwth:
                break;
            case (float)Common.SoundType.Hysh:
                break;
        }
        
        target.currentHull -= damage;
        
        // Debug.Log($"{target.name} was hit for {damage} damage. Hull is now {target.hull}.");
        
        if (target.currentHull <= 0)
        {
            Die(target);
        }
        
        // switch (effect)
        // {
        //     case Common.Effect.None:
        //         break;
        //     case Common.Effect.Stun:
        //         Stun(target, effectStrength);
        //         break;
        //     case Common.Effect.Slow:
        //         Slow(target, effectStrength);
        //         break;
        //     case Common.Effect.Splash:
        //         break;
        //     case Common.Effect.Skip:
        //         break;
        //     case Common.Effect.Sustain:
        //         break;
        //     case Common.Effect.Siphon:
        //         break;
        //     case Common.Effect.Scrap:
        //         break;
        // }
    }

    private IEnumerator DamageOverTime()
    {
        return null;
    }

    private void Die(Ship target)
    {
        if (target.Equals(player))
        {
            EventBus.Instance.playerDefeated.Invoke();
        }
        else if (target.Equals(enemy))
        {
            EventBus.Instance.enemyDefeated.Invoke();
        }
    }
    
    private void Stun(Ship target, float duration)
    {
        
    }

    private void Slow(Ship target, float duration)
    {
        
    }
    
    #endregion

    private void OnPlayerHullRepairAttempted()
    {
        if (InventoryManager.Instance.scrap < hullRepairCost)
            return;
        
        InventoryManager.Instance.scrap -= hullRepairCost;
        player.currentHull = PlayerMaxHull();
    }
}
