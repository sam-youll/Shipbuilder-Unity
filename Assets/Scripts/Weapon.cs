using System;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.SceneManagement;
using Random = UnityEngine.Random;

public class Weapon : MonoBehaviour
{
    [Header("Components")] 
    private GameObject startJack;
    private GameObject endJack;
    public StatBar statBar;
    public GameObject bulletPrefab;
    public GameObject myShip;
    public GameObject myShipWeapon;
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

    public GameObject wirePrefab;
    
    public Dictionary<string, float> noteInfo = new()
    {
        { "pitch", 440 },
        { "length", .17f },
        { "attack", 100 },
        { "decay", 70 },
        { "release", 100 },
    };
    
    public int currentNoteMeter = 0;
    private int[] notes;
    private int currentNote;
    
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
    
    public void Start()
    {
        Conductor.Instance.onSixteenth.AddListener(Fire);
        notes = new int[noteMeters.Count];
        for (int i = 0; i < notes.Length; i++)
        {
            notes[i] = Random.Range(0, 7);
            // Debug.Log(notes[i]);
        }
        
        for (int i = 0; i < transform.childCount; i++)
        {
            if (transform.GetChild(i).CompareTag("InputJack"))
            {
                endJack = transform.GetChild(i).gameObject;
            }
            else if (transform.GetChild(i).CompareTag("OutputJack"))
            {
                startJack = transform.GetChild(i).gameObject;
            }
        }
        
        // TODO: this is temporary, maybe change it so that this is more tied to the modules or something idk
        noteInfo["pitch"] = Notes.RandomNoteInScale(Conductor.Instance.keyRoot, Conductor.Instance.mode);
    }

    // Update is called once per frame
    void Update()
    {
        // we don't have RackMovement.cs on the weapons, so we just do the same code to check for a jack click here
        // we can maybe refactor this later into just being a UnityEvent sent by the jack itself, but this works for now
        if (Input.GetMouseButtonDown(0))
        {
            // we do a lil raycast
            var results = Physics2D.RaycastAll(Camera.main.ScreenToWorldPoint(Input.mousePosition), Vector2.zero);

            var isItMe = false;
            foreach (var r in results)
            {
                if (r.collider.gameObject == startJack)
                {
                    isItMe = true;
                }
            }

            if (isItMe)
            {
                foreach (var result in results)
                {
                    // if we hit a jack, invoke that unity event
                    if (result.collider.gameObject.layer == LayerMask.NameToLayer("Jacks"))
                    {
                        OnJackClick(startJack);
                        break;
                    }
                }
            }
        }

        inCombat = CombatManager.Instance.state == CombatManager.State.inCombat;
        firing = testing || inCombat;
        if (dir == 1 && !CompletePatch())
        {
            // Debug.Log("Is patch complete? " + CompletePatch());
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

        // Debug.Log(charge);
        // Debug.Log(statBar.value);
        statBar.value = charge;
        // Debug.Log(currentNoteMeter);
        if (noteMeters.Count > 0)
        {
            noteMeters[currentNoteMeter].value = charge;
        }


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

        if (charge < 1)
        {
            return;
        }
        
        if (dir == 1)
        {
            for (int i = 0; i < startJack.transform.childCount; i++)
            {
                if (startJack.transform.GetChild(i).CompareTag("Wire"))
                {
                    Debug.Log($"Weapon script on {gameObject.name} triggering {startJack.transform.GetChild(i).name}");
                    startJack.transform.GetChild(i).GetComponent<Wire>().Trigger();
                }
            }
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



        int currentChord = ReactorSounds.Instance.currentChord;
        var chord = ReactorSounds.Instance.changes[currentChord];
        string chordString = ReactorSounds.Instance.chords[chord];

        var sensorMod = 1f;
        
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
        newBullet.GetComponent<Rigidbody2D>().linearVelocity = new Vector2(dir*1, Random.Range(-bulletSpread, bulletSpread)*sensorMod) * bulletSpeed;
        
        
        //noteInfo["pitch"] = Notes.RandomNoteInChord(Conductor.Instance.keyRoot, Conductor.Instance.mode, Notes.SCALE_CHORD[chordString]);
        // noteInfo["pitch"] = Notes.GetPitch(Notes.A, Notes.MODE.IONIAN, notes[currentNote]);
        // currentNote++;
        // currentNote = (int)Mathf.Repeat(currentNote, notes.Length);
        // Debug.Log("current note is " + currentNote + " which is " + notes[currentNote]);
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
        while (prev.PreviousModule() != null)
        {
            // Debug.Log(prev.name);
            myPatch.Add(prev);
            
            if (prev.PreviousModule().TryGetComponent(out Module mod))
            {
                prev = mod;
            }
            else if (prev.PreviousModule().TryGetComponent(out Weapon weapon))
            {
                break;
            }
        }
        // Debug.Log(prev.name);
        myPatch.Add(prev);
    }

    private bool CompletePatch()
    {
        if (myPatch.Count == 0)
            return false;
        
        return myPatch[^1].PreviousModule() == gameObject;
    }
    
    private void OnJackClick(GameObject jack)
    {
        if (transform.parent == Inventory.Instance.transform)
        {
            return;
        }
        
        // is there already a wire there?
        if (jack.transform.childCount > 0)
        {
            // get rid of it, unless you're holding left control
            // this way, left control + drag creates a second wire on top of the first
            // same as VCV rack
            // TODO: allow dragging wires from either end and don't just automatically delete to create new
            if (!Input.GetKey(KeyCode.LeftControl))
            {
                jack.transform.GetChild(0).gameObject.GetComponent<Wire>().DeleteSelf();
            }
        }
        // make a new wire
        GameObject newWire = Instantiate(wirePrefab, jack.transform);
    }
}
