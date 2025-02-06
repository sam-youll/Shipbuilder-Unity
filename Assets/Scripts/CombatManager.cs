using System;
using System.Collections.Generic;
using System.Runtime.InteropServices.WindowsRuntime;
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

    public StatBar playerHealthBar;
    public StatBar enemyHealthBar;

    public GameObject playerShip;
    public GameObject enemyShip;
    
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
        }
    }

    public void StartCombat()
    {
        timer = tickLength;
        inCombat = true;

        AudioManager.Instance.ResetPlayedList();
    }
    
    void CombatTick()
    {
        playerHealthBar.value -= .1f;
        playerHealthBar.value = Mathf.Clamp(playerHealthBar.value, 0, 1);
        enemyHealthBar.value -= .1f;
        enemyHealthBar.value = Mathf.Clamp(playerHealthBar.value, 0, 1);
    }

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

    public void SetStatsByDict()
    {
        return;
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
