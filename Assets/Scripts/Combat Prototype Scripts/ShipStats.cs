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

public class ShipStats : MonoBehaviour
{
    //audio manager reference
    public GameObject audioManager;
    //enemy reference
    public GameObject enemy;
    //ship reference
    public GameObject ship;

    //primary combat stats
    public float attack;
    public float defense;
    public float evasion;
    public float accuracy;

    //secondary combat stats
    //private float pitchType;
    public float attackSource;
    public float defenseSource;
    public float evasionSource;
    public float accuracySource;

    private float timbreMatch;

    private float ringmod;

    private float attackPitch;
    private float defensePitch;
    private float evasionPitch;
    private float accuracyPitch;

    //multipliers
    private float typeMultiplier;
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

    //source utility
    private List<float> sourceList = new List<float>();
    private List<float> opponentSourceList = new List<float>();

    private float opponentAttackSource;
    private float opponentDefenseSource;
    private float opponentEvasionSource;
    private float opponentAccuracySource;

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
            if (currentSlider.CompareTag("ShipAttack"))
            {
                attackSource = currentSlider.GetComponent<Slider>().value;
            }
            if (currentSlider.CompareTag("ShipDefense"))
            {
                defenseSource = currentSlider.GetComponent<Slider>().value;
            }
            if (currentSlider.CompareTag("ShipEvasion"))
            {
                evasionSource = currentSlider.GetComponent<Slider>().value;
            }
            if (currentSlider.CompareTag("ShipAccuracy"))
            {
                accuracySource = currentSlider.GetComponent<Slider>().value;
            }
        }
        else
        {
            if (currentSlider.CompareTag("EnemyAttack"))
            {
                attackSource = currentSlider.GetComponent<Slider>().value;
            }
            if (currentSlider.CompareTag("EnemyDefense"))
            {
                defenseSource = currentSlider.GetComponent<Slider>().value;
            }
            if (currentSlider.CompareTag("EnemyEvasion"))
            {
                evasionSource = currentSlider.GetComponent<Slider>().value;
            }
            if (currentSlider.CompareTag("EnemyAccuracy"))
            {
                accuracySource = currentSlider.GetComponent<Slider>().value;
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
                        typeMultiplier = 1;
                    }
                    else if (opponentPitchTypesList[i] == pitchTypes.med)
                    {
                        typeMultiplier = weakMultiplier;
                    }
                    else if (opponentPitchTypesList[i] == pitchTypes.high)
                    {
                        typeMultiplier = strongMultiplier;
                    }
                }

                else if (pitchTypesList[i] == pitchTypes.med)
                {
                    if (opponentPitchTypesList[i] == pitchTypes.high)
                    {
                        typeMultiplier = weakMultiplier;
                    }
                    else if (opponentPitchTypesList[i] == pitchTypes.med)
                    {
                        typeMultiplier = 1;
                    }
                    else if (opponentPitchTypesList[i] == pitchTypes.low)
                    {
                        typeMultiplier = strongMultiplier;
                    }
                }

                else if (pitchTypesList[i] == pitchTypes.high)
                {
                    if (opponentPitchTypesList[i] == pitchTypes.low)
                    {
                        typeMultiplier = weakMultiplier;
                    }
                    else if (opponentPitchTypesList[i] == pitchTypes.high)
                    {
                        typeMultiplier = 1;
                    }
                    else if (opponentPitchTypesList[i] == pitchTypes.med)
                    {
                        typeMultiplier = strongMultiplier;
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
                        typeMultiplier = 1;
                    }
                    else if (opponentPitchTypesList[i] == pitchTypes.med)
                    {
                        typeMultiplier = weakMultiplier;
                    }
                    else if (opponentPitchTypesList[i] == pitchTypes.high)
                    {
                        typeMultiplier = strongMultiplier;
                    }
                }

                else if (pitchTypesList[i] == pitchTypes.med)
                {
                    if (opponentPitchTypesList[i] == pitchTypes.high)
                    {
                        typeMultiplier = weakMultiplier;
                    }
                    else if (opponentPitchTypesList[i] == pitchTypes.med)
                    {
                        typeMultiplier = 1;
                    }
                    else if (opponentPitchTypesList[i] == pitchTypes.low)
                    {
                        typeMultiplier = strongMultiplier;
                    }
                }

                else if (pitchTypesList[i] == pitchTypes.high)
                {
                    if (opponentPitchTypesList[i] == pitchTypes.low)
                    {
                        typeMultiplier = weakMultiplier;
                    }
                    else if (opponentPitchTypesList[i] == pitchTypes.high)
                    {
                        typeMultiplier = 1;
                    }
                    else if (opponentPitchTypesList[i] == pitchTypes.med)
                    {
                        typeMultiplier = strongMultiplier;
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
                    timbreMatch = matchMultiplier;
                }
                //1 apart 
                else if (Mathf.Abs(sourceList[i] - opponentSourceList[i]) == 1)
                {
                    timbreMatch = nearMultiplier;
                }
                //2 apart
                else if (Mathf.Abs(sourceList[i] - opponentSourceList[i]) == 2)
                {
                    timbreMatch = farMultiplier;
                }
            }
        }
        else
        {
            timbreMatch = 1;
        }
    }

    public void SetAttack()
    {
        RockPaperScissors();
        TimbreMatch();
        attack = typeMultiplier * timbreMatch * 100;
    }

    public void SetDefense()
    {
        RockPaperScissors();
        TimbreMatch();
        defense = typeMultiplier * timbreMatch * 100;
    }

    public void SetEvasion()
    {
        RockPaperScissors();
        TimbreMatch();
        evasion = typeMultiplier * timbreMatch * 100;
    }

    public void SetAccuracy()
    {
        RockPaperScissors();
        TimbreMatch();
        accuracy = typeMultiplier * timbreMatch * 100;
    }
    
}
