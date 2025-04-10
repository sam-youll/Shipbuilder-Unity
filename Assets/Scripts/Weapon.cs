using System.Collections.Generic;
using UnityEngine;

public class Weapon : MonoBehaviour
{
    public StatBar statBar;
    public float charge = 0;
    public float fireRate;
    public float energyRate;
    public float damage;
    public float hullDamage;
    public float shieldDamage;
    public float warmup = 0;
    public bool warming = false;
    public float bulletSpeed;
    public float bulletSpread;
    public GameObject bulletPrefab;
    public GameObject myShip;
    public float dir;
    public float stunTimer;

    public enum Effect
    {
        Stun, // disables weapons/systems
        Slow, // slows weapons
        Splash, // hits multiple systems
        Skip, // ignores shields
        Sustain // damage over time
    }
    public List<Effect> effects;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        Conductor.Instance.onBeat.AddListener(Fire);
    }

    // Update is called once per frame
    void Update()
    {
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
        
        if (stunTimer <= 0)
        {
            charge += energyRate * fireRate * warmup * Time.deltaTime;
        }
        if (charge >= 1)
        {
            Fire();
        }
        // charge = Mathf.Clamp(charge, 0, 1);

        statBar.value = charge;


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
        
        // create bullet
        var newBullet = Instantiate(bulletPrefab, transform.GetChild(0).transform.position, Quaternion.identity);
        newBullet.GetComponent<Bullet>().damage = damage;
        newBullet.GetComponent<Bullet>().hullDamage = hullDamage;
        newBullet.GetComponent<Bullet>().shieldDamage = shieldDamage;
        newBullet.GetComponent<Rigidbody2D>().linearVelocity = new Vector2(dir*1, Random.Range(-bulletSpread, bulletSpread)) * bulletSpeed;
        newBullet.GetComponent<Bullet>().myShip = myShip;
        newBullet.GetComponent<Bullet>().myShield = myShip.GetComponent<Ship>().shield;
        newBullet.GetComponent<Bullet>().effects = effects;
        
        // play note
        var pitch = Notes.RandomNoteInScale(Notes.A, Notes.MODE.IONIAN);
        var noteInfo = new Dictionary<string, float>{ {"length", 1.17f}, {"pitch", pitch} };
        AudioManager.Instance.PlayNote(gameObject, noteInfo);
    }
}
