using System;
using System.Collections.Generic;
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

    [Header("Primary Stats")]
    //primary combat stats
    public float attack;
    public float defense;
    public float evasion;
    public float accuracy;

    [Header("Secondary Stats")]
    //secondary combat stats
    //private float pitchType;
    public float attackSource;
    public float defenseSource;
    public float evasionSource;
    public float accuracySource;
    private float ringmod;


    private float attackPitch;
    private float defensePitch;
    private float evasionPitch;
    private float accuracyPitch;

    [Header("Multipliers")]
    //multipliers
    private float attackTypeMultiplier;
    private float defenseTypeMultiplier;
    private float evasionTypeMultiplier;
    private float accuracyTypeMultiplier;

    private float attackTimbreMatch;
    private float defenseTimbreMatch;
    private float evasionTimbreMatch;
    private float accuracyTimbreMatch;

    [Header("Multiplier Variables")]
    public float strongMultiplier;
    public float weakMultiplier;
    public float matchMultiplier;
    public float nearMultiplier;
    public float farMultiplier;


    //pitch type utility
    public enum pitchTypes
    {
        high,
        med,
        low
    };

    [Header("Pitch Type Ultility")]
    public pitchTypes attackPitchType;
    public pitchTypes defensePitchType;
    public pitchTypes evasionPitchType;
    public pitchTypes accuracyPitchType;

    pitchTypes opponentAttackPitchType;
    pitchTypes opponentDefensePitchType;
    pitchTypes opponentEvasionPitchType;
    pitchTypes opponentAccuracyPitchType;

    private List<pitchTypes> pitchTypesList = new List<pitchTypes>();
    private List<pitchTypes> opponentPitchTypesList = new List<pitchTypes>();
    public List<float> typeMultipliersList = new List<float>();

    [Header("Source Utility")]
    //source utility
    public List<float> sourceList = new List<float>();
    public List<float> opponentSourceList = new List<float>();
    public List<float> timbreMatchMultipliersList = new List<float>();

    private float opponentAttackSource;
    private float opponentDefenseSource;
    private float opponentEvasionSource;
    private float opponentAccuracySource;

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
    private List<Dictionary<string, float>> playerShields = new List<Dictionary<string, float>>();
    private List<Dictionary<string, float>> playerWeapons = new List<Dictionary<string, float>>();
    private List<Dictionary<string, float>> playerThrusters = new List<Dictionary<string, float>>();

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
        
        //set pitchtype list
        pitchTypesList.Add(attackPitchType);
        pitchTypesList.Add(defensePitchType);
        pitchTypesList.Add(evasionPitchType);
        pitchTypesList.Add(accuracyPitchType);
        //set opponent pitchtype list
        opponentPitchTypesList.Add(opponentAttackPitchType);
        opponentPitchTypesList.Add(opponentDefensePitchType);
        opponentPitchTypesList.Add(opponentEvasionPitchType);
        opponentPitchTypesList.Add(opponentAccuracyPitchType);

        //set source list
        sourceList.Add(attackSource);
        sourceList.Add(defenseSource);
        sourceList.Add(evasionSource);
        sourceList.Add(accuracySource);
        //set opponent source list
        opponentSourceList.Add(opponentAttackSource);
        opponentSourceList.Add(opponentDefenseSource);
        opponentSourceList.Add(opponentEvasionSource);
        opponentSourceList.Add(opponentAccuracySource);

        //set pitchTypesMultipliers list 
        typeMultipliersList.Add(attackTypeMultiplier);
        typeMultipliersList.Add(defenseTypeMultiplier);
        typeMultipliersList.Add(evasionTypeMultiplier);
        typeMultipliersList.Add(accuracyTypeMultiplier);

        //set timbreMatchMultipliers list
        timbreMatchMultipliersList.Add(attackTimbreMatch);
        timbreMatchMultipliersList.Add(defenseTimbreMatch);
        timbreMatchMultipliersList.Add(evasionTimbreMatch);
        timbreMatchMultipliersList.Add(accuracyTimbreMatch);
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
        playerHitNumber.GetComponent<TextMeshPro>().text = EnemyAttackDamage().ToString();
        playerHitNumber.transform.SetParent(playerShip.transform);
        Debug.Log(playerHitNumber);
        playerHealthBar.value = Mathf.Clamp(playerHealthBar.value, 0, 1);
        enemyHealthBar.value -= PlayerAttackDamage();
        var enemyHitNumber = Instantiate(floatingDamageNumberPrefab, enemyShip.transform.position, Quaternion.identity);
        enemyHitNumber.GetComponent<TextMeshPro>().text = PlayerAttackDamage().ToString();
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
            result *= shield["incomingDamageMult"];
            result *= RPS(enemyWeaponSoundType, GetShieldType(shield));
        }
        return result;
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

    // Dictionary<string, float> CombinedStats(List<Dictionary<string, float>> stats)
    // {
    //     var result = new Dictionary<string, float>()
    //     {
    //         { "outputType", 0 },
    //         { "extraHealth", 0 },
    //         { "incomingDamageMult", 0 },
    //         { "damage", 0 },
    //         { "attackSpeed", 0 },
    //         { "accuracy", 0 },
    //         { "evasion", 0 },
    //         { "izki", 0 },
    //         { "aubo", 0 },
    //         { "dwth", 0 }
    //     };
    //     foreach (var stat in stats)
    //     {
    //         foreach (var pair in stat)
    //         {
    //             if (pair.Value > result[pair.Key])
    //             {
    //                 result[pair.Key] = pair.Value;
    //             }
    //         }
    //     }
    // }

    float AttackMod()
    {
        return 1;
    }
    
    float ModifiedPlayerAttack()
    {
        return 0;
    }

    float ModifiedPlayerDefense()
    {
        return 0;
    }

    float ModifiedEnemyAttack()
    {
        return 0;
    }

    float ModifiedEnemyDefense()
    {
        return 0;
    }

    public void SetStatsByDict(int index, Module.OutputType outputType, Dictionary<string, float> stats)
    {
        switch (outputType)
        {
            case Module.OutputType.None:
                break;
            case Module.OutputType.Weapon:
                if (index >= playerWeapons.Count)
                {
                    var newWeapon = new Dictionary<string, float>()
                    {
                        { "damage", 1 },
                        { "attackSpeed", 1 },
                        { "accuracy", 1 },
                        { "izki", 0 },
                        { "aubo", 0 },
                        { "dwth", 0 }
                    };
                    playerWeapons.Add(newWeapon);
                }
                playerWeapons[index] = stats;
                break;
            case Module.OutputType.Shield:
                if (index >= playerShields.Count)
                {
                    var newShield = new Dictionary<string, float>()
                    {
                        { "extraHealth", 0 },
                        { "incomingDamageMult", 1 },
                        { "damage", 1 },
                        { "attackSpeed", 1 },
                        { "accuracy", 1 },
                        { "izki", 1 },
                        { "aubo", 1 },
                        { "dwth", 1 }
                    };
                    playerShields.Add(newShield);
                }
                playerShields[index] = stats;
                break;
            case Module.OutputType.Thruster:
                if (index >= playerThrusters.Count)
                {
                    var newThruster = new Dictionary<string, float>()
                    {
                        { "evasion", 1 },
                        { "izki", 0 },
                        { "aubo", 0 },
                        { "dwth", 0 }
                    };
                    playerThrusters.Add(newThruster);
                }
                playerThrusters[index] = stats;
                break;
            case Module.OutputType.Sensor:
                break;
        }
        // if (index >= playerPatches.Count)
        // {
        //     var newPatch = new Dictionary<string, float>()
        //     {
        //         { "extraHealth", 0 },
        //         { "incomingDamageMult", 0 },
        //         { "damage", 0 },
        //         { "attackSpeed", 0 },
        //         { "accuracy", 0 },
        //         { "evasion", 0 },
        //         { "izki", 0 },
        //         { "aubo", 0 },
        //         { "dwth", 0 }
        //     };
        //     playerPatches.Add(newPatch);
        // }
        //
        // playerPatches[index] = stats;
    }

    public float ModifyAttack()
    {
        RockPaperScissors();
        TimbreMatch();
        return typeMultipliersList[0] * timbreMatchMultipliersList[0] * 100;
    }

    public float ModifyDefense()
    {
        RockPaperScissors();
        TimbreMatch();
        return typeMultipliersList[1] * timbreMatchMultipliersList[1] * 100;
    }

    public float ModifyEvasion()
    {
        RockPaperScissors();
        TimbreMatch();
        return typeMultipliersList[2] * typeMultipliersList[2] * 100;
    }

    public float ModifyAccuracy()
    {
        RockPaperScissors();
        TimbreMatch();
        return typeMultipliersList[3] * typeMultipliersList[3] * 100;
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
