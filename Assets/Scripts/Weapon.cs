using System;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.Events;
using UnityEngine.SceneManagement;
using UnityEngine.Serialization;
using Random = UnityEngine.Random;
#if UNITY_EDITOR
using UnityEditor;
#endif

#if UNITY_EDITOR
[CustomEditor(typeof(Weapon))]
public class WeaponEditor : Editor
{
    public override void OnInspectorGUI()
    {
        var weapon = (Weapon)target;
        EditorGUILayout.BeginVertical();
        GUILayout.Label("Note Info",  EditorStyles.boldLabel);
        foreach (var kvp in weapon.noteInfo)
        {
            GUILayout.BeginHorizontal();
            GUILayout.Label(kvp.Key, GUILayout.Width(60));
            // GUILayout.FlexibleSpace();
            GUILayout.Label(kvp.Value.ToString());
            GUILayout.EndHorizontal();
        }
        EditorGUILayout.EndVertical();
        DrawDefaultInspector();
    }
}
#endif

public class Weapon : MonoBehaviour
{
    [Header("Weapon Stats")]
    public Common.SoundType soundType;
    public Dictionary<Common.SoundType, int> soundTypePoints = new();
    public List<Common.Effect> effects;
    
    [Header("Properties")]
    public bool warming = false;
    public float warmup = 0;
    public float charge = 0;
    public float stunTimer;
    public bool quantized;
    // public bool testing;
    public bool firing;
    public bool enemyWeapon; // set true if Weapon belongs to an enemy ship

    public GameObject previousModule;
    public GameObject parentWire;
    public SwitchComponent testFireSwitch;
    
    public Dictionary<string, float> noteInfo = new()
    {
        { "pitch", 440 },
        { "length", .17f },
        { "attack", 100 },
        { "decay", 70 },
        { "release", 100 },
    };

    public Dictionary<string, float> weaponStats = new()
    {
        { "warmupRate", 1 },
        { "fireRate", 1 },
        { "damage", 1 },
        { "hullDamage", 1 },
        { "shieldDamage", 1 },
        { "bulletSpeed", 1 },
        { "accuracy", 1 }
    };
    
    public int currentNoteMeter = 0;
    private int[] notes = new int[1];
    private int currentNote;
    
    public List<Module> myPatch = new();
    
    public void Start()
    {
        // Enemy weapons do not have actual modules behind them (for now)
        // so we just want them to attempt to fire as often as possible
        if (!enemyWeapon)
        {
            Conductor.Instance.onSixteenth.AddListener(Fire);
        }
        
        for (int i = 0; i < notes.Length; i++)
        {
            notes[i] = Random.Range(0, 7);
            // Debug.Log(notes[i]);
        }
        
        // TODO: this is temporary, maybe change it so that this is more tied to the modules or something idk
        noteInfo["pitch"] = Notes.RandomNoteInScale(Conductor.Instance.keyRoot, Conductor.Instance.mode);
    }

    // Update is called once per frame
    void Update()
    {
        // are we either testing or in combat? If yes to either, we're firing
        firing = (!enemyWeapon && testFireSwitch.on) || CombatManager.Instance.state == CombatManager.State.inCombat;
        // if we're facing right (only true if player ship) and the patch is not complete, turn it off
        if (!enemyWeapon && !CompletePatch())
        {
            // Debug.Log("Is patch complete? " + CompletePatch());
            firing = false;
        }
        
        if (warming)
        {
            if (warmup < 1)
            {
                warmup += weaponStats["warmupRate"] * .1f * Time.deltaTime;
            }
            else if (warmup > 1)
            {
                warmup = Mathf.Clamp(warmup, 0, 1);
            }
        }
        
        if (!enemyWeapon && firing && stunTimer <= 0)
        {
            charge += Reactor.Instance.rate * weaponStats["fireRate"] * warmup * Time.deltaTime;
        }
        else if (enemyWeapon && firing && stunTimer <= 0)
        {
            charge += weaponStats["fireRate"] * warmup * Time.deltaTime;
        }

        // TODO: This is temporary, we probably don't want to just turn the whole thing yellow
        // in the final version. We should make it a little fancier at least...
        
        // if (stunTimer > 0)
        // {
        //     stunTimer -= Time.deltaTime;
        //     if (gameObject.GetComponent<SpriteRenderer>().color == Color.white)
        //     {
        //         gameObject.GetComponent<SpriteRenderer>().color = Color.yellow;
        //     }
        // }
        // else if (gameObject.GetComponent<SpriteRenderer>().color == Color.yellow)
        // {
        //     gameObject.GetComponent<SpriteRenderer>().color = Color.white;
        // }
    }

    public void Fire()
    {
        SetPatch();
        
        foreach (var mod in myPatch)
        {
            // TODO: add logic for calculating a final value based on multiple input values,
            // not just the most recent value.
            
            foreach (var param in mod.MusicParams)
            {
                noteInfo[param.Key] = param.Value;
            }

            foreach (var stat in mod.CombatStats)
            {
                weaponStats[stat.Key] = stat.Value;
            }
            
        }
        
        if (charge < 1 || !firing || !CompletePatch())
        {
            return;
        }
        
        charge = 0;
        
        DisplayManager.Instance.Log("Fired " + name);
        // Debug.Log(name + " fired");
        EventBus.Instance.weaponFired.Invoke(this);
        
        // calculate hit/miss + damage
        if (CombatManager.Instance.state == CombatManager.State.inCombat)
        {
            var hit = weaponStats["accuracy"] * (1 - ShipManager.Instance.EnemyEvasion());
            if (hit <= 0)
            {
                // Debug.Log("miss");
                ShipManager.Instance.DamageEnemy(hit); // TODO: add overrides so I don't have to call useless stuff
                EventBus.Instance.enemyHit.Invoke(hit);
            }
            else
            {
                // Debug.Log("hit");
                ShipManager.Instance.DamageEnemy(weaponStats["damage"]); // TODO: make it so that multiple effects can be sent
                EventBus.Instance.enemyHit.Invoke(weaponStats["damage"]);
            }
        }
        
        // if hit, fire at enemy ship
        // if miss, fire above/below
        // need to calculate hit range/angle
        
        
        /*
        // create bullet
        var newBullet = Instantiate(bulletPrefab, myShipWeapon.transform.position + Vector3.right * (dir * .5f), Quaternion.identity);
        if (SceneManager.GetActiveScene() == SceneManager.GetSceneByName("Cinematic Scene"))
        {
            newBullet.transform.localScale = (Vector3.one * 0.3f);
        }
        if (dir == 1)
        {
            newBullet.GetComponent<Bullet>().damage = damage * Reactor.Instance.strength;
            newBullet.GetComponent<Bullet>().hullDamage = hullDamage * Reactor.Instance.strength;
            newBullet.GetComponent<Bullet>().shieldDamage = shieldDamage * Reactor.Instance.strength;
            if (SceneManager.GetActiveScene() == SceneManager.GetSceneByName("Cinematic Scene"))
            {
                newBullet.GetComponent<Bullet>().damage = damage * (Random.Range(1, 4));
            }
        }
        else if (dir == -1)
        {
            newBullet.GetComponent<Bullet>().damage = damage;
            newBullet.GetComponent<Bullet>().hullDamage = hullDamage;
            newBullet.GetComponent<Bullet>().shieldDamage = shieldDamage;
        }
        newBullet.GetComponent<Bullet>().myShip = myShip;
        newBullet.GetComponent<Bullet>().myShields = myShip.GetComponent<Ship>().shields;
        newBullet.GetComponent<Bullet>().effects = effects;
        newBullet.GetComponent<Bullet>().soundType = soundType;
        */


        // int currentChord = ReactorSounds.Instance.changesIndex;
        // var chord = ReactorSounds.Instance.changes[currentChord];
        // string chordString = ReactorSounds.Instance.chords[chord];

        // var sensorMod = 1f;
    }

    public void SetPatch()
    {
        if (enemyWeapon)
            return;
        
        // Debug.Log($"Setting patch for {gameObject.name}.");
        if (parentWire == null)
        {
            myPatch.Clear();
            return;
        }

        if (parentWire.GetComponent<Wire>().previousModule == null)
        {
            myPatch.Clear();
            return;
        }
        
        myPatch = new();
        var prev = parentWire.GetComponent<Wire>().previousModule.GetComponent<Module>();
        // Debug.Log($"{prev}'s previous module is {prev.PreviousModule()}");
        while (prev.PreviousModule() != null)
        {
            // Debug.Log(prev.name);
            myPatch.Add(prev);

            if (prev.PreviousModule().TryGetComponent(out Module mod))
            {
                prev = mod;
            }
            // The lines below can probably be deleted
            else if (prev.PreviousModule().TryGetComponent(out Weapon weapon))
            {
                break;
            }
        }
        // Debug.Log(prev.name);
        myPatch.Add(prev);
        // Debug.Log($"{gameObject.name}'s patch consists of the following modules:");
        // foreach (var mod in myPatch)
        // {
        //     Debug.Log(mod.gameObject.name);
        // }
    }

    private bool CompletePatch()
    {
        SetPatch();
        if (myPatch.Count == 0)
            return false;
        
        return true;
        // return myPatch[^1].PreviousModule();
    }
}
