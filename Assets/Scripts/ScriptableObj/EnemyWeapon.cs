using FMOD.Studio;
using FMODUnity;
using UnityEngine;

[CreateAssetMenu(fileName = "EnemyWeapon", menuName = "Scriptable Objects/EnemyWeapon")]
public class EnemyWeapon : ScriptableObject
{
    public string enemy;

    [Header("Pitch and Source")]
    public float pitch;
    public float source;

    [Header("AM LFO")]
    public float AM;
    public float AMSource;
    public float AMFreq;
    public float AMDepth;

    [Header("FM LFO")]
    public float FM;
    public float FMSource;
    public float FMFreq;
    public float FMDepth;

    [Header("ADSR")]
    public float attack;
    public float decay;
    public float sustain;
    public float release;

    [Header("Notes on/off")]
    public float metro;
    public float note1;
    public float note2;
    public float note3;
    public float note4;

    [Header("Arp Pitches")]
    public float apitch1;
    public float apitch2;
    public float apitch3;
    public float apitch4;

    [Header("Stats")]
    public float damage;
    public float attackSpeed;
    public float accuracy;
    public float izki;
    public float aubo;
    public float dwth;

    [Header("FMODStuff")]
    public EventReference moduleRef;
    public EventInstance enemyWeaponInst;
}
