using System;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.Events;
using UnityEngine.SceneManagement;
using UnityEngine.Serialization;
using Random = UnityEngine.Random;

public class Weapon : MonoBehaviour
{
    [Header("Weapon Stats")]
    public float fireRate;
    [FormerlySerializedAs("energyRate")] public float warmupRate;
    public float damage;
    public float hullDamage;
    public float shieldDamage;
    public float bulletSpeed;
    public float bulletSpread;
    public float dir;
    public float stunTimer;
    public Combat.SoundType soundType;
    public Dictionary<Combat.SoundType, int> soundTypePoints = new();
    
    public enum Effect
    {
        Stun, // disables weapons/systems
        Slow, // slows weapons
        Splash, // hits multiple systems
        Skip, // ignores shields
        Sustain // damage over time
    }
    public List<Effect> effects;
    
    [Header("Properties")]
    public bool warming = false;
    public float warmup = 0;
    public float charge = 0;
    public bool quantized;
    public bool inCombat;
    public bool testing;
    public bool firing;

    public GameObject previousModule;
    public GameObject parentWire;
    
    public Dictionary<string, float> noteInfo = new()
    {
        { "pitch", 440 },
        { "length", .17f },
        { "attack", 100 },
        { "decay", 70 },
        { "release", 100 },
    };
    
    public int currentNoteMeter = 0;
    private int[] notes = new int[1];
    private int currentNote;
    
    public List<Module> myPatch = new();
    
    public void Start()
    {
        // Enemy weapons do not have actual modules behind them (for now)
        // so we just want them to attempt to fire as often as possible
        if (dir == -1)
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
        // is the CombatManager in combat?
        inCombat = CombatManager.Instance.state == CombatManager.State.inCombat;
        // are we either testing or in combat? If yes to either, we're firing
        firing = testing || inCombat;
        // if we're facing right (only true if player ship) and the patch is not complete, turn it off
        if (dir == 1 && !CompletePatch())
        {
            // Debug.Log("Is patch complete? " + CompletePatch());
            firing = false;
        }
        
        if (warming)
        {
            if (warmup < 1)
            {
                warmup += warmupRate * .1f * Time.deltaTime;
            }
            else if (warmup > 1)
            {
                warmup = Mathf.Clamp(warmup, 0, 1);
            }
        }
        
        if (dir == 1 && firing && stunTimer <= 0)
        {
            charge += Reactor.Instance.rate * fireRate * warmup * Time.deltaTime;
        }
        else if (dir == -1 && firing && stunTimer <= 0)
        {
            charge += fireRate * warmup * Time.deltaTime;
        }

        // TODO: This is temporary, we probably don't want to just turn the whole thing yellow
        // in the final version. We should make it a little fancier at least...
        if (stunTimer > 0)
        {
            stunTimer -= Time.deltaTime;
            if (gameObject.GetComponent<SpriteRenderer>().color == Color.white)
            {
                gameObject.GetComponent<SpriteRenderer>().color = Color.yellow;
            }
        }
        else if (gameObject.GetComponent<SpriteRenderer>().color == Color.yellow)
        {
            gameObject.GetComponent<SpriteRenderer>().color = Color.white;
        }
    }

    public void Fire()
    {
        if (dir == 1)
        {
            // Debug.Log($"Attempting to fire {gameObject.name}.");
        }
        
        if (charge < 1)
        {
            return;
        }

        if (dir == 1)
        {
            // Debug.Log($"Firing {gameObject.name}.");
        }
        charge = 0;
        
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
        
        SetPatch();
        
        foreach (var mod in myPatch)
        {
            foreach (var param in mod.MusicParams)
            {
                noteInfo[param.Key] = param.Value;
            }

            foreach (var stat in mod.CombatStats)
            {
                // fireRate
                // damage
                // bullet speed
                // spread
                // effects
                // type
            }
            
        }
        // newBullet.GetComponent<Rigidbody2D>().linearVelocity = new Vector2(dir*1, Random.Range(-bulletSpread, bulletSpread)*sensorMod) * bulletSpeed;
        
        
        //noteInfo["pitch"] = Notes.RandomNoteInChord(Conductor.Instance.keyRoot, Conductor.Instance.mode, Notes.SCALE_CHORD[chordString]);
        // noteInfo["pitch"] = Notes.GetPitch(Notes.A, Notes.MODE.IONIAN, notes[currentNote]);
        // currentNote++;
        // currentNote = (int)Mathf.Repeat(currentNote, notes.Length);
        // Debug.Log("current note is " + currentNote + " which is " + notes[currentNote]);
        
        
        // AudioManager.Instance.PlayNote(gameObject, noteInfo);
        EventBus.Instance.weaponFired.Invoke(this);
    }

    private void OnMouseDown()
    {
        if (inCombat)
            return;
        
        testing = !testing;
    }

    public void SetPatch()
    {
        if (dir == -1)
            return;
        
        // Debug.Log($"Setting patch for {gameObject.name}.");
        if (previousModule == null)
            return;
        
        myPatch = new();
        var prev = previousModule.GetComponent<Module>();
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
        if (myPatch.Count == 0)
            return false;
        
        return true;
        // return myPatch[^1].PreviousModule();
    }
}
