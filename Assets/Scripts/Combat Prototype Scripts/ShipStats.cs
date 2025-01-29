using UnityEngine;
using FMOD;
using FMODUnity;
using FMOD.Studio;
using System.Runtime.CompilerServices;
using System.IO;

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
    private float timbreMatch;
    private float ringmod;
    private float pitch;

    //multipliers
    private float typeMultiplier;

    //utility variables lol
    enum pitchTypes
    {
        high,
        med,
        low
    };

    pitchTypes pitchType;
    pitchTypes opponentPitchType;
    public float source;
    public float opponentSource;

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
       

    }

    // Update is called once per frame
    void Update()
    {
        
    }

    void PitchType()
    {
        //getting player pitch
        if (CompareTag("Player"))
        {
            pitch = audioManager.GetComponent<CombatPrototypeAudioManager>().pitch;
        }
        //getting enemy pitch
        else
        {
            pitch = 440;
        }

        //establishing low pitch
        if (pitch < 130.81)
        {
            pitchType = pitchTypes.low;
        } 
        //establishing medium pitch
        else if (pitch < 523.25)
        {
            pitchType = pitchTypes.med;
        }
        //establishing high pitch
        else if (pitch > 523.25)
        {
            pitchType = pitchTypes.high;
        }

    }

    void SetAccuracy()
    {
        RockPaperScissors();
        TimbreMatch();
        accuracy = typeMultiplier * timbreMatch * 100;
    }

    void SetDefense()
    {
        RockPaperScissors();
        TimbreMatch();
        defense = typeMultiplier * timbreMatch * 100;
    }

    //RPS function for use between stats
    void RockPaperScissors()
    {
        PitchType();
        //this is so not a good way of doing it there's like a half baked better way in my mind but im overthinking shit
        //so we do this for now and change it later 
        if (CompareTag("Player"))
        {
            //then this type against enemy type
            enemy.GetComponent<ShipStats>().pitchType = opponentPitchType;
            //pitch 
            if (pitchType == pitchTypes.low)
            {
                if (opponentPitchType == pitchTypes.low)
                {
                    typeMultiplier = 1;
                }
                if (opponentPitchType == pitchTypes.med)
                {
                    typeMultiplier = 1;
                }
                if (opponentPitchType == pitchTypes.high)
                {
                    typeMultiplier = 2;
                }
            }
            if (pitchType == pitchTypes.med)
            {
                if (opponentPitchType == pitchTypes.high)
                {
                    typeMultiplier = 1;
                }
                if (opponentPitchType == pitchTypes.med)
                {
                    typeMultiplier = 1;
                }
                if (opponentPitchType == pitchTypes.low)
                {
                    typeMultiplier = 2;
                }
            }
            if (pitchType == pitchTypes.high)
            {
               if (opponentPitchType == pitchTypes.low)
               {
                   typeMultiplier = 1;
               }
               if (opponentPitchType == pitchTypes.high)
               {
                   typeMultiplier = 1;
               }
               if (opponentPitchType == pitchTypes.med)
               {
                   typeMultiplier = 2;
               }
            }
        }
        else
        {
            //then this type against player type
            ship.GetComponent<ShipStats>().pitchType = opponentPitchType;
            //pitch 
            if (pitchType == pitchTypes.low)
            {
                if (opponentPitchType == pitchTypes.low)
                {
                    typeMultiplier = 1;
                }
                if (opponentPitchType == pitchTypes.med)
                {
                    typeMultiplier = 1;
                }
                if (opponentPitchType == pitchTypes.high)
                {
                    typeMultiplier = 2;
                }
            }
            if (pitchType == pitchTypes.med)
            {
                if (opponentPitchType == pitchTypes.high)
                {
                    typeMultiplier = 1;
                }
                if (opponentPitchType == pitchTypes.med)
                {
                    typeMultiplier = 1;
                }
                if (opponentPitchType == pitchTypes.low)
                {
                    typeMultiplier = 2;
                }
            }
            if (pitchType == pitchTypes.high)
            {
                if (opponentPitchType == pitchTypes.low)
                {
                    typeMultiplier = 1;
                }
                if (opponentPitchType == pitchTypes.high)
                {
                    typeMultiplier = 1;
                }
                if (opponentPitchType == pitchTypes.med)
                {
                    typeMultiplier = 2;
                }
            }
        }
    }

    void TimbreMatch()
    {
        audioManager.GetComponent<CombatPrototypeAudioManager>().source = source;
        if (CompareTag("Player"))
        {
            //get enemy ship source
            enemy.GetComponent<ShipStats>().source = opponentSource;

            if(source == opponentSource)
            {
                timbreMatch = 2;
            }
        }
        else
        {
            //get player ship source
            ship.GetComponent<ShipStats>().source = opponentSource;
            if (source == opponentSource)
            {
                timbreMatch = 2;
            }
            if (Mathf.Abs(source - opponentSource) == 1)
            {
                timbreMatch = 1.5f;
            }
            if (Mathf.Abs(source - opponentSource) == 2)
            {
                timbreMatch = 1;
            }
        }
    }
}
