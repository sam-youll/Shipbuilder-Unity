using System;
using System.Collections.Generic;
using UnityEngine;
using Random = UnityEngine.Random;

public class Weapon : MonoBehaviour
{
    [Header("Components")]
    public StatBar statBar;
    public GameObject bulletPrefab;
    public GameObject myShip;
    public GameObject myShipWeapon;
    public GameObject output;
    public List<StatBar> noteMeters = new();
    
    [Header("Properties")]
    public bool warming = false;
    public float warmup = 0;
    public float charge = 0;
    public float fireRate;
    public float energyRate;
    public float damage;
    public float hullDamage;
    public float shieldDamage;
    public float bulletSpeed;
    public float bulletSpread;
    public float dir;
    public float stunTimer;
    public Combat.SoundType soundType;
    public Dictionary<Combat.SoundType, int> soundTypePoints = new();
    public bool quantized;
    public bool inCombat;
    public bool testing;
    public bool firing;

    public GameObject previousModule;
    
    public Dictionary<string, float> noteInfo = new()
    {
        { "pitch", 440 },
        { "length", .17f },
        { "attack", 100 },
        { "decay", 70 },
        { "sustain", 0 },
        { "release", 100 },
    };
    
    public int currentNoteMeter = 0;
    
    public List<Module> myPatch = new();
    
    public enum Effect
    {
        Stun, // disables weapons/systems
        Slow, // slows weapons
        Splash, // hits multiple systems
        Skip, // ignores shields
        Sustain // damage over time
    }
    public List<Effect> effects;
    
    void Start()
    {
        Conductor.Instance.onSixteenth.AddListener(Fire);
    }

    // Update is called once per frame
    void Update()
    {
        inCombat = CombatManager.Instance.state == CombatManager.State.inCombat;
        firing = testing || inCombat;
        if (dir == 1 && (previousModule == null || !SourceModuleConnected()))
        {
            firing = false;
        }
        
        if (warming)
        {
            if (warmup < 1)
            {
                warmup += energyRate * .1f * Time.deltaTime;
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

        if (quantized)
        {
            charge = Mathf.Clamp(charge, 0, 1);
        }
        else
        {
            if (charge >= 1)
            {
                Fire();
            }
        }

         statBar.value = charge;
        // Debug.Log(currentNoteMeter);
        if (noteMeters.Count > 0)
            noteMeters[currentNoteMeter].value = charge;


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

    void Fire()
    {
        if (charge < 1)
        {
            return;
        }

        charge = 0;
        currentNoteMeter++;
        if (currentNoteMeter >= noteMeters.Count)
        {
            foreach (var n in noteMeters)
            {
                n.value = 0;
            }
            currentNoteMeter = 0;
        }
        
        // create bullet
        var newBullet = Instantiate(bulletPrefab, myShipWeapon.transform.position + Vector3.right * (dir * .5f), Quaternion.identity);
        if (dir == 1)
        {
            newBullet.GetComponent<Bullet>().damage = damage * Reactor.Instance.strength;
            newBullet.GetComponent<Bullet>().hullDamage = hullDamage * Reactor.Instance.strength;
            newBullet.GetComponent<Bullet>().shieldDamage = shieldDamage * Reactor.Instance.strength;
        }
        else if (dir == -1)
        {
            newBullet.GetComponent<Bullet>().damage = damage;
            newBullet.GetComponent<Bullet>().hullDamage = hullDamage;
            newBullet.GetComponent<Bullet>().shieldDamage = shieldDamage;
        }
        newBullet.GetComponent<Rigidbody2D>().linearVelocity = new Vector2(dir*1, Random.Range(-bulletSpread, bulletSpread)) * bulletSpeed;
        newBullet.GetComponent<Bullet>().myShip = myShip;
        newBullet.GetComponent<Bullet>().myShield = myShip.GetComponent<Ship>().shield;
        newBullet.GetComponent<Bullet>().effects = effects;
        newBullet.GetComponent<Bullet>().soundType = soundType;

        int currentChord = ReactorSounds.Instance.currentChord;
        var chord = ReactorSounds.Instance.changes[currentChord];
        string chordString = ReactorSounds.Instance.chords[chord];
        
        SetPatch();
        foreach (var mod in myPatch)
        {
            if (noteInfo.ContainsKey(mod.parameter))
            {
                noteInfo[mod.parameter] = mod.parameterValue;
            }
            else
            {
                noteInfo.Add(mod.parameter, mod.parameterValue);
            }
        }
        
        noteInfo["pitch"] = Notes.RandomNoteInChord(Notes.A, Notes.MODE.IONIAN, Notes.SCALE_CHORD[chordString]);
        AudioManager.Instance.PlayNote(gameObject, noteInfo);
    }

    private void OnMouseDown()
    {
        if (inCombat)
            return;
        
        testing = !testing;
    }

    public void SetPatch()
    {
        if (previousModule == null)
            return;
        
        myPatch = new();
        var prev = previousModule.GetComponent<Module>();
        while (prev.previousModule != null)
        {
            // Debug.Log(prev.name);
            myPatch.Add(prev);
            prev = prev.previousModule.GetComponent<Module>();
        }
        // Debug.Log(prev.name);
        myPatch.Add(prev);
    }

    private bool SourceModuleConnected()
    {
        var result = false;
        foreach (var module in myPatch)
        {
            if (module.isSourceModule)
            {
                result = true;
            }
        }

        return result;
    }
}
