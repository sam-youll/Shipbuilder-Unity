using UnityEngine;
using FMOD;
using FMODUnity;
using FMOD.Studio;
using System.Runtime.CompilerServices;
using System.IO;
using UnityEngine.EventSystems;
using UnityEngine.UI;
using System.Collections.Generic;
using static ShipStats;
using TMPro;
using System;
using UnityEngine.Animations;

public class ShipStats : MonoBehaviour
{
    [Header("Game Object References")]
    //audio manager reference
    public GameObject audioManager;
    //enemy reference
    public GameObject enemy;
    //ship reference
    public GameObject ship;
    //Sliders Reference
    public Slider shipAttackSourceSlider;
    public Slider shipDefenseSourceSlider;
    public Slider shipEvasionSourceSlider;
    public Slider shipAccuracySourceSlider;

    public Slider enemyAttackSourceSlider;
    public Slider enemyDefenseSourceSlider;
    public Slider enemyEvasionSourceSlider;
    public Slider enemyAccuracySourceSlider;

    //[Header("Stats")]
    //primary combat stats
    public float attack;
    public float defense;
    public float evasion;
    public float accuracy;


    //[Header("Secondary Stats")]
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


    //[Header("Pitch Type Ultility")]
    //pitch type utility
    public enum pitchTypes
    {
        high,
        med,
        low
    };

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

    [Header("Display")]
    //display
    public TMP_Text displayText;

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
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
        SetAttack();
        SetDefense();
        SetEvasion();
        SetAccuracy();



        displayText.SetText("Attack: " + attack + "<br>Defense: " + defense +
                            "<br>Evasion: " + evasion + "<br>Accuracy: " + accuracy);
            
    }

    public void PitchUpdate()
    {
        var currentSlider = EventSystem.current.currentSelectedGameObject;
        if (CompareTag("Player"))
        {
            if (currentSlider.CompareTag("ShipAttack"))
            {
                attackPitch = currentSlider.GetComponent<Slider>().value;
            }
            if (currentSlider.CompareTag("ShipDefense"))
            {
                defensePitch = currentSlider.GetComponent<Slider>().value;
            }
            if (currentSlider.CompareTag("ShipEvasion"))
            {
                evasionPitch = currentSlider.GetComponent<Slider>().value;
            }
            if (currentSlider.CompareTag("ShipAccuracy"))
            {
                accuracyPitch = currentSlider.GetComponent<Slider>().value;
            }
        } 
        else
        {
            if (currentSlider.CompareTag("EnemyAttack"))
            {
                attackPitch = currentSlider.GetComponent<Slider>().value;
            }
            if (currentSlider.CompareTag("EnemyDefense"))
            {
                defensePitch = currentSlider.GetComponent<Slider>().value;
            }
            if (currentSlider.CompareTag("EnemyEvasion"))
            {
                evasionPitch = currentSlider.GetComponent<Slider>().value;
            }
            if (currentSlider.CompareTag("EnemyAccuracy"))
            {
                accuracyPitch = currentSlider.GetComponent<Slider>().value;
            }
        }
    }

    public void SourceUpdate()
    {
        var currentSlider = EventSystem.current.currentSelectedGameObject;

        if (CompareTag("Player"))
        {
            if (currentSlider.GetComponent<Slider>().transform.parent.CompareTag("Player"))
            {
                UnityEngine.Debug.Log("ship slider move");
                //set self
                if (currentSlider.CompareTag("ShipAttackSource"))
                {
                    sourceList[0] = shipAttackSourceSlider.GetComponent<Slider>().value;
                }
                if (currentSlider.CompareTag("ShipDefenseSource"))
                {
                    sourceList[1] = shipDefenseSourceSlider.GetComponent<Slider>().value;
                }
                if (currentSlider.CompareTag("ShipEvasionSource"))
                {
                    sourceList[2] = shipEvasionSourceSlider.GetComponent<Slider>().value;
                }
                if (currentSlider.CompareTag("ShipAccuracySource"))
                {
                    sourceList[3] = shipAccuracySourceSlider.GetComponent<Slider>().value;
                }
            }

            //set opponent source
            if (currentSlider.CompareTag("EnemyAttackSource"))
            {
                opponentSourceList[0] = enemyAttackSourceSlider.GetComponent<Slider>().value;
            }
            if (currentSlider.CompareTag("EnemyDefenseSource"))
            {
                opponentSourceList[1] = enemyDefenseSourceSlider.GetComponent<Slider>().value;
            }
            if (currentSlider.CompareTag("EnemyEvasionSource"))
            {
                opponentSourceList[2] = enemyEvasionSourceSlider.GetComponent<Slider>().value;
            }
            if (currentSlider.CompareTag("EnemyAccuracySource"))
            {
                opponentSourceList[3] = enemyAccuracySourceSlider.GetComponent<Slider>().value;
            }

        }
    }

    public void EnemySourceUpdate()
    {
        var currentSlider = EventSystem.current.currentSelectedGameObject;

        if (CompareTag("Enemy"))
        {
            if (currentSlider.GetComponent<Slider>().transform.parent.CompareTag("Enemy"))
            {
                UnityEngine.Debug.Log("EnemySliderMove");
                //set self
                if (currentSlider.CompareTag("EnemyAttackSource"))
                {
                    sourceList[0] = enemyAttackSourceSlider.GetComponent<Slider>().value;
                    UnityEngine.Debug.Log(sourceList[0]);
                }
                if (currentSlider.CompareTag("EnemyDefenseSource"))
                {
                    sourceList[1] = enemyDefenseSourceSlider.GetComponent<Slider>().value;
                }
                if (currentSlider.CompareTag("EnemyEvasionSource"))
                {
                    sourceList[2] = enemyEvasionSourceSlider.GetComponent<Slider>().value;
                }
                if (currentSlider.CompareTag("EnemyAccuracySource"))
                {
                    sourceList[3] = enemyAccuracySourceSlider.GetComponent<Slider>().value;
                }
            }
           

            //set opponent source
            if (currentSlider.CompareTag("ShipAttackSource"))
            {
                opponentSourceList[0] = shipAttackSourceSlider.GetComponent<Slider>().value;
            }
            if (currentSlider.CompareTag("ShipDefenseSource"))
            {
                opponentSourceList[1] = shipDefenseSourceSlider.GetComponent<Slider>().value;
            }
            if (currentSlider.CompareTag("ShipEvasionSource"))
            {
                opponentSourceList[2] = shipEvasionSourceSlider.GetComponent<Slider>().value;
            }
            if (currentSlider.CompareTag("ShipAccuracySource"))
            {
                opponentSourceList[3] = shipAccuracySourceSlider.GetComponent<Slider>().value;
            }
        }
       
    }


    void PitchType()
    {
        //ATTACK
        //establishing low pitch
        if (attackPitch < 130.81)
        {
            attackPitchType = pitchTypes.low;
        } 
        //establishing medium pitch
        else if (attackPitch < 523.25)
        {
            attackPitchType = pitchTypes.med;
        }
        //establishing high pitch
        else if (attackPitch > 523.25)
        {
            attackPitchType = pitchTypes.high;
        }

        //DEFENSE
        //establishing low pitch
        if (defensePitch < 130.81)
        {
            defensePitchType = pitchTypes.low;
        }
        //establishing medium pitch
        else if (defensePitch < 523.25)
        {
            defensePitchType = pitchTypes.med;
        }
        //establishing high pitch
        else if (defensePitch > 523.25)
        {
            defensePitchType = pitchTypes.high;
        }

        //EVASION
        //establishing low pitch
        if (evasionPitch < 130.81)
        {
            evasionPitchType = pitchTypes.low;
        }
        //establishing medium pitch
        else if (evasionPitch < 523.25)
        {
            evasionPitchType = pitchTypes.med;
        }
        //establishing high pitch
        else if (evasionPitch > 523.25)
        {
            evasionPitchType = pitchTypes.high;
        }


        //ACCURACY
        //establishing low pitch
        if (accuracyPitch < 130.81)
        {
            accuracyPitchType = pitchTypes.low;
        }
        //establishing medium pitch
        else if (accuracyPitch < 523.25)
        {
            accuracyPitchType = pitchTypes.med;
        }
        //establishing high pitch
        else if (accuracyPitch > 523.25)
        {
            accuracyPitchType = pitchTypes.high;
        }

    }

    //RPS function for use between stats
    void RockPaperScissors()
    {
        PitchType();
        //this is so not a good way of doing it there's like a half baked better way in my mind but im overthinking shit
        //so we do this for now and change it later 
        if (CompareTag("Player"))
        {
            for (int i = 0; i < pitchTypesList.Count; i++)
            {
                //then this type against enemy type
                enemy.GetComponent<ShipStats>().pitchTypesList[i] = opponentPitchTypesList[i];

                //pitch 
                if (pitchTypesList[i] == pitchTypes.low)
                {
                    if (opponentPitchTypesList[i] == pitchTypes.low)
                    {
                        typeMultipliersList[i] = 1;
                    }
                    else if (opponentPitchTypesList[i] == pitchTypes.med)
                    {
                        typeMultipliersList[i] = weakMultiplier;
                    }
                    else if (opponentPitchTypesList[i] == pitchTypes.high)
                    {
                        typeMultipliersList[i] = strongMultiplier;
                    }
                }

                else if (pitchTypesList[i] == pitchTypes.med)
                {
                    if (opponentPitchTypesList[i] == pitchTypes.high)
                    {
                        typeMultipliersList[i] = weakMultiplier;
                    }
                    else if (opponentPitchTypesList[i] == pitchTypes.med)
                    {
                        typeMultipliersList[i] = 1;
                    }
                    else if (opponentPitchTypesList[i] == pitchTypes.low)
                    {
                        typeMultipliersList[i] = strongMultiplier;
                    }
                }

                else if (pitchTypesList[i] == pitchTypes.high)
                {
                    if (opponentPitchTypesList[i] == pitchTypes.low)
                    {
                        typeMultipliersList[i] = weakMultiplier;
                    }
                    else if (opponentPitchTypesList[i] == pitchTypes.high)
                    {
                        typeMultipliersList[i] = 1;
                    }
                    else if (opponentPitchTypesList[i] == pitchTypes.med)
                    {
                        typeMultipliersList[i] = strongMultiplier;
                    }
                }

            }
        }
        else
        {
            for (int i = 0; i < pitchTypesList.Count; i++)
            {
                //then this type against enemy type
                ship.GetComponent<ShipStats>().pitchTypesList[i] = opponentPitchTypesList[i];

                //pitch 
                if (pitchTypesList[i] == pitchTypes.low)
                {
                    if (opponentPitchTypesList[i] == pitchTypes.low)
                    {
                        typeMultipliersList[i] = 1;
                    }
                    else if (opponentPitchTypesList[i] == pitchTypes.med)
                    {
                        typeMultipliersList[i] = weakMultiplier;
                    }
                    else if (opponentPitchTypesList[i] == pitchTypes.high)
                    {
                        typeMultipliersList[i] = strongMultiplier;
                    }
                }

                else if (pitchTypesList[i] == pitchTypes.med)
                {
                    if (opponentPitchTypesList[i] == pitchTypes.high)
                    {
                        typeMultipliersList[i] = weakMultiplier;
                    }
                    else if (opponentPitchTypesList[i] == pitchTypes.med)
                    {
                        typeMultipliersList[i] = 1;
                    }
                    else if (opponentPitchTypesList[i] == pitchTypes.low)
                    {
                        typeMultipliersList[i] = strongMultiplier;
                    }
                }

                else if (pitchTypesList[i] == pitchTypes.high)
                {
                    if (opponentPitchTypesList[i] == pitchTypes.low)
                    {
                        typeMultipliersList[i] = weakMultiplier;
                    }
                    else if (opponentPitchTypesList[i] == pitchTypes.high)
                    {
                        typeMultipliersList[i] = 1;
                    }
                    else if (opponentPitchTypesList[i] == pitchTypes.med)
                    {
                        typeMultipliersList[i] = strongMultiplier;
                    }
                }

            }
        }
    }

    void TimbreMatch()
    {
        if (CompareTag("Player"))
        {
            for (int i = 0; i < sourceList.Count; i++)
            {
                //get enemy ship source
                enemy.GetComponent<ShipStats>().sourceList[i] = opponentSourceList[i];

                //match 
                if (sourceList[i] == opponentSourceList[i])
                {
                    timbreMatchMultipliersList[i] = matchMultiplier;
                }
                //1 apart 
                else if (Mathf.Abs(sourceList[i] - opponentSourceList[i]) == 1)
                {
                    timbreMatchMultipliersList[i] = nearMultiplier;
                }
                //2 apart
                else if (Mathf.Abs(sourceList[i] - opponentSourceList[i]) == 2)
                {
                    timbreMatchMultipliersList[i] = farMultiplier;
                }
            }
        }
        else
        {
            for (int i = 0; i < sourceList.Count; i++)
            {
                timbreMatchMultipliersList[i] = 1;
            }
                
        }
    }

    public void SetAttack()
    {
        RockPaperScissors();
        TimbreMatch();
        attack = typeMultipliersList[0] * timbreMatchMultipliersList[0] * 100;
    }

    public void SetDefense()
    {
        RockPaperScissors();
        TimbreMatch();
        defense = typeMultipliersList[1] * timbreMatchMultipliersList[1] * 100;
    }

    public void SetEvasion()
    {
        RockPaperScissors();
        TimbreMatch();
        evasion = typeMultipliersList[2] * typeMultipliersList[2] * 100;
    }

    public void SetAccuracy()
    {
        RockPaperScissors();
        TimbreMatch();
        accuracy = typeMultipliersList[3] * typeMultipliersList[3] * 100;
    }
    
}
