using System.Collections;
using System.Collections.Generic;
using UnityEditor.Overlays;
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
    
    private struct Ship
    {
        public ShipData baseShip;
        public string name;
        public float hull;
        public float shield;
        public List<Weapon> weapons;
        public float evasion;
    }

    void Start()
    {
        // InitEnemyShip();
        // InitPlayerShip();

        SceneManager.sceneLoaded += OnSceneLoaded;
    }

    void Update()
    {
        // Debug.Log(enemy.hull);
        // enemy.hull -= 1f;
    }

    private bool playerShipInitialized = false;
    public void OnSceneLoaded(Scene scene, LoadSceneMode mode)
    {
        if (scene.name == "Cockpit" && !playerShipInitialized)
        {
            InitPlayerShip();
            InitEnemyShip();
            playerShipInitialized = true;
        }
    }
    
    #region Player Ship
    [HideInInspector] public List<ShipData> basePlayerShips;
    [Header("Player Ship")] 
    private Ship player;

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
    private void InitPlayerShip(ShipData baseShip)
    {
        player.hull = baseShip.maxHull;
    }

    private void InitPlayerShip()
    {
        Debug.Log("InitPlayerShip");
        player = new Ship
        {
            name = "Player ship",
            hull = 100,
            shield = 20,
            weapons = new()
        };
        var weaponRacks = GameObject.FindGameObjectsWithTag("Weapon");
        foreach (var weapon in weaponRacks)
        {
            player.weapons.Add(weapon.GetComponent<Weapon>());
        }
    }

    public Weapon[] PlayerWeapons()
    {
        return player.weapons.ToArray();
    }

    public float PlayerHull()
    {
        return player.hull;
    }

    public float PlayerMaxHull()
    {
        return 100;
    }
    #endregion
    
    #region Enemy Ship
    private Ship enemy;
    
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
        Debug.Log("InitEnemyShip");
        enemy = new Ship
        {
            name = "Enemy ship",
            hull = 50,
            shield = 10,
            weapons = new List<Weapon>()
        };
        for (var i = 0; i < 3; i++)
        {
            var newWeapon = new GameObject();
            newWeapon.transform.SetParent(transform);
            var weapon = newWeapon.AddComponent<Weapon>();
            weapon.enemyWeapon = true;
            enemy.weapons.Add(weapon);
        }
    }

    public Weapon[] EnemyWeapons()
    {
        return enemy.weapons.ToArray();
    }

    public float EnemyHull()
    {
        return enemy.hull;
    }

    public float EnemyMaxHull()
    {
        return 50;
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
    public void DamagePlayer(float damage, Common.Effect effect, float effectStrength)
    {
        Damage(ref player, damage, effect, effectStrength);
    }

    /// <summary>
    /// Deals damage to enemy ship, and applies any associated status effects.
    /// </summary>
    /// <param name="damage">Amount of damage dealt.</param>
    /// <param name="effect">Status effect applied to projectile.</param>
    /// <param name="effectStrength">"Strength" of the effect. This might mean duration or some other parameter.</param>
    public void DamageEnemy(float damage, Common.Effect effect, float effectStrength)
    {
        Damage(ref enemy, damage, effect, effectStrength);
    }

    public void DamageEnemy(float damage)
    {
        Damage(ref enemy, damage, Common.Effect.None, 0);
    }

    /// <summary>
    /// Calculates actual damage received after shields, resistances, weaknesses, etc.
    /// done to target ship. Also applies the associated status effects.
    /// </summary>
    /// <param name="target">Player or enemy ship.</param>
    /// <param name="damage">Amount of damage dealt.</param>
    /// <param name="effect">Status effect applied to projectile.</param>
    /// <param name="effectStrength">"Strength" of the effect. This might mean duration or some other parameter.</param>
    private void Damage(ref Ship target, float damage, Common.Effect effect, float effectStrength)
    {
        if (CombatManager.Instance.state == CombatManager.State.outOfCombat)
        {
            return;
        }
        
        //TODO: Add overloads without effects and stuff
        
        target.hull -= damage;
        
        // Debug.Log($"{target.name} was hit for {damage} damage. Hull is now {target.hull}.");
        
        if (target.hull <= 0)
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
            DisplayManager.Instance.Log("WIN WIN WIN WIN WIN WIN WIN WIN WIN WIN WIN WIN WIN");
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
}
