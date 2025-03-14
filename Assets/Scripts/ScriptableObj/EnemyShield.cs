using FMOD.Studio;
using FMODUnity;
using UnityEngine;

[CreateAssetMenu(fileName = "EnemyShield", menuName = "Scriptable Objects/EnemyShield")]
public class EnemyShield : ScriptableObject
{
    public string enemy;

    [Header("Pitches and Source")]
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

    [Header("Stats")]
    public float extraHealth;
    public float incomingDamageMult;
    public float evasion;
    public float izki;
    public float aubo;
    public float dwth;

    [Header("FMODStuff")]
    public EventReference moduleRef;
    public EventInstance enemyShieldInst;
}
