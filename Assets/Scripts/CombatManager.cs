using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using TMPro;
using UnityEngine;

public class CombatManager : MonoBehaviour
{
    public static CombatManager Instance { get; private set; }
    private void Awake()
    {
        if (Instance != null && Instance != this)
        {
            Destroy(this);
        }
        else
        {
            Instance = this;
        }
    }
    //
    // [Header("Primary Stats")]
    // //primary combat stats
    // public float attack;
    // public float defense;
    // public float evasion;
    // public float accuracy;
    //
    // [Header("Secondary Stats")]
    // //secondary combat stats
    // //private float pitchType;
    // public float attackSource;
    // public float defenseSource;
    // public float evasionSource;
    // public float accuracySource;
    // private float ringmod;
    //
    //
    //
    //
    // [Header("Multipliers")]
    // //multipliers
    // private float attackTypeMultiplier;
    // private float defenseTypeMultiplier;
    // private float evasionTypeMultiplier;
    // private float accuracyTypeMultiplier;
    //
    // private float attackTimbreMatch;
    // private float defenseTimbreMatch;
    // private float evasionTimbreMatch;
    // private float accuracyTimbreMatch;
    //
    // [Header("Multiplier Variables")]
    // public float strongMultiplier;
    // public float weakMultiplier;
    // public float matchMultiplier;
    // public float nearMultiplier;
    // public float farMultiplier;


    //pitch type utility
    public enum pitchTypes
    {
        high,
        med,
        low
    };

    private bool inCombat = false;
    public float tickLength = 2;
    private float timer;
    private int currentTick = 0;

    public StatBar playerHealthBar;
    public StatBar enemyHealthBar;

    public GameObject playerShip;
    public GameObject enemyShip;
    
    public GameObject floatingDamageNumberPrefab;
    
    [Header("Player Ship Stats")]
    public float playerHealth;
    public float playerEvasion;
    private Dictionary<string, float>[] playerShields = new Dictionary<string, float>[6];
    private Dictionary<string, float>[] playerWeapons = new Dictionary<string, float>[6];

    [Header("Enemy Ship Stats")] 
    public float enemyHealth = 1;
    public float enemyShieldMod = .9f;
    public float enemyWeaponDamage = .05f;
    public Module.SoundType enemyWeaponSoundType;
    public Module.SoundType enemyShieldSoundType;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        timer = tickLength;

        for (var i = 0; i < playerWeapons.Length; i++)
        {
            playerWeapons[i] = new Dictionary<string, float>()
            {
                { "damage", 0 },
                { "attackSpeed", 1 },
                { "accuracy", 1 },
                { "izki", 0 },
                { "aubo", 0 },
                { "dwth", 0 }
            };
        }

        for (var i = 0; i < playerShields.Length; i++)
        {
            playerShields[i] = new Dictionary<string, float>()
            {
                { "extraHealth", 0 },
                { "incomingDamageMult", 1 },
                // { "damage", 1 },
                { "attackSpeed", 1 },
                { "accuracy", 1 },
                { "izki", 0 },
                { "aubo", 0 },
                { "dwth", 0 }
            };
        }
    }

    // Update is called once per frame
    void Update()
    {
        if (inCombat)
        {
            timer -= Time.deltaTime;
            if (timer <= 0)
            {
                timer = tickLength;
                CombatTick();
            }
        }
        
    }

    private void FixedUpdate()
    {
        if (inCombat)
        {
            if (Camera.main.transform.position != new Vector3(18, 0, -10))
            {
                Camera.main.transform.position = Vector3.Lerp(Camera.main.transform.position, new Vector3(18, 0, -10), .3f);
            }

            if (playerHealthBar.value <= 0 || enemyHealthBar.value <= 0)
            {
                inCombat = false;
            }
        }
        else
        {
            if (Camera.main.transform.position != new Vector3(0, 0, -10))
            {
                Camera.main.transform.position = Vector3.Lerp(Camera.main.transform.position, new Vector3(0, 0, -10), .3f);
            }
        }
    }

    public void StartCombat()
    {
        enemyHealthBar.value = 1;
        playerHealthBar.value = 1;
        
        timer = tickLength;
        inCombat = true;

        AudioManager.Instance.ResetPlayedList();
        AudioManager.Instance.StopEnemySong();
    }
    
    void CombatTick()
    {
        playerHealthBar.value -= EnemyAttackDamage();
        var playerHitNumber = Instantiate(floatingDamageNumberPrefab, playerShip.transform.position, Quaternion.identity);
        playerHitNumber.GetComponent<TextMeshPro>().text = "-" + Mathf.Floor(EnemyAttackDamage()*100).ToString();
        playerHitNumber.transform.SetParent(playerShip.transform);
        Debug.Log(playerHitNumber);
        playerHealthBar.value = Mathf.Clamp(playerHealthBar.value, 0, 1);
        enemyHealthBar.value -= PlayerAttackDamage();
        var enemyHitNumber = Instantiate(floatingDamageNumberPrefab, enemyShip.transform.position, Quaternion.identity);
        enemyHitNumber.GetComponent<TextMeshPro>().text = "-" + Mathf.Floor(PlayerAttackDamage()*100).ToString();
        enemyHitNumber.transform.SetParent(enemyShip.transform);
        Debug.Log(enemyHitNumber);
        enemyHealthBar.value = Mathf.Clamp(enemyHealthBar.value, 0, 1);
        
        currentTick++;
    }

    float PlayerAttackDamage()
    {
        float result = 0;
        foreach (var weapon in playerWeapons)
        {
            if (weapon == null)
                continue;
            float dmg = 0;
            if (currentTick % weapon["attackSpeed"] == 0)
            {
                dmg = weapon["damage"];
                dmg *= RPS(GetWeaponType(weapon), enemyShieldSoundType);
            }

            result += dmg;
        }

        result *= enemyShieldMod;
        Debug.Log("Player weapon is type " + GetWeaponType(playerWeapons[0]) + ". Enemy shield is type " + enemyShieldSoundType);
        Debug.Log("Player did " + result + " damage! RPS result: " + RPS(GetWeaponType(playerWeapons[0]), enemyShieldSoundType));
        return result;
    }

    float EnemyAttackDamage()
    {
        float result = enemyWeaponDamage;
        foreach (var shield in playerShields)
        {
            if (shield == null)
                continue;
            result *= shield["incomingDamageMult"];
            result *= RPS(enemyWeaponSoundType, GetShieldType(shield));
        }
        Debug.Log("Player shield is type " + GetShieldType(playerShields[0]) + ". Enemy weapon is type " + enemyWeaponSoundType);
        Debug.LogFormat("Enemy did " + result + " damage! RPS result: " + RPS(enemyWeaponSoundType, GetShieldType(playerShields[0])));
        return result;
    }

    Module.SoundType GetSoundType(List<GameObject> patch)
    {
        Dictionary<Module.SoundType, float> result = new Dictionary<Module.SoundType, float>();

        foreach (var module in patch)
        {
            var mod = module.GetComponent<Module>();
            foreach (var type in mod.soundType)
            {
                result[type.Key] += type.Value;
            }
        }
        return result.Keys.Max();
    }

    Module.SoundType GetWeaponType(Dictionary<string, float> weapon)
    {
        var result = Module.SoundType.None;
        float val = 0;
        if (weapon["izki"] > val)
        {
            val = weapon["izki"];
            result = Module.SoundType.Izki;
        }
        if (weapon["aubo"] > val)
        {
            val = weapon["aubo"];
            result = Module.SoundType.Aubo;
        }
        if (weapon["dwth"] > val)
        {
            val = weapon["dwth"];
            result = Module.SoundType.Dwth;
        }
        // Debug.Log("weapon type: " + result);
        return result;
    }

    Module.SoundType GetShieldType(Dictionary<string, float> shield)
    {
        var result = Module.SoundType.None;
        float val = 0;
        if (shield["izki"] > val)
        {
            val = shield["izki"];
            result = Module.SoundType.Izki;
        }
        if (shield["aubo"] > val)
        {
            val = shield["aubo"];
            result = Module.SoundType.Aubo;
        }
        if (shield["dwth"] > val)
        {
            val = shield["dwth"];
            result = Module.SoundType.Dwth;
        }
        // Debug.Log("shield type: " + result);
        return result;
    }

    float RPS(Module.SoundType attacker, Module.SoundType defender)
    {
        switch (attacker)
        {
            case Module.SoundType.None:
                return 1;
            case Module.SoundType.Izki:
                switch (defender)
                {
                    case Module.SoundType.None:
                        return 1;
                    case Module.SoundType.Izki:
                        return 1;
                    case Module.SoundType.Aubo:
                        return .75f;
                    case Module.SoundType.Dwth:
                        return 1.5f;
                };
                break;
            case Module.SoundType.Aubo:
                switch (defender)
                {
                    case Module.SoundType.None:
                        return 1;
                    case Module.SoundType.Izki:
                        return 1.5f;
                    case Module.SoundType.Aubo:
                        return 1;
                    case Module.SoundType.Dwth:
                        return .75f;
                };
                break;
            case Module.SoundType.Dwth:
                switch (defender)
                {
                    case Module.SoundType.None:
                        return 1;
                    case Module.SoundType.Izki:
                        return .75f;
                    case Module.SoundType.Aubo:
                        return 1.5f;
                    case Module.SoundType.Dwth:
                        return 1f;
                };
                break;
        }

        return 1;
    }

    public void SetStatsByDict(int index, OutputRack.Type outputType, Dictionary<string, float> stats)
    {
        switch (outputType)
        {
            case OutputRack.Type.None:
                break;
            case OutputRack.Type.Weapon:
                playerWeapons[index] = stats;
                break;
            case OutputRack.Type.Shield:
                playerShields[index-6] = stats;
                break;
        }
    }

    private void RockPaperScissors()
    {
        Debug.Log("This is where rps will happen");
    }

    private void TimbreMatch()
    {
        Debug.Log("This is where timbrematch will happen");
    }

    private void PitchUpdate()
    {
        //get whether arp = 1 etc for the thing 
        
    }
}
