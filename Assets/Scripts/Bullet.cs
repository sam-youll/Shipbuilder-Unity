using System;
using System.Collections.Generic;
using System.Linq;
using Unity.VisualScripting;
using UnityEngine;

public class Bullet : MonoBehaviour
{
    // public Vector2 dir;
    public float damage;
    public float hullDamage;
    public float shieldDamage;
    public GameObject myShip;
    public GameObject myShield;
    // public float speed;
    public List<Weapon.Effect> effects;
    public Combat.SoundType soundType;

    public float lifeTime = 3;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        lifeTime -= Time.deltaTime;

        if (lifeTime <= 0)
        {
            Destroy(this.gameObject);
        }
    }

    void OnCollisionEnter2D(Collision2D collision)
    {
        // Debug.Log(collision.gameObject.name);
        if (collision.gameObject.CompareTag("Ship") && collision.gameObject != myShip)
        {
            var ship = collision.gameObject.GetComponent<Ship>();
            
            if (effects.Contains(Weapon.Effect.Stun))
            {
                ship.ApplyStun(damage);
            }
            if (effects.Contains(Weapon.Effect.Slow))
            {
                ship.ApplySlow(damage);
            }
            if (effects.Contains(Weapon.Effect.Splash))
            {
                
            }
            if (effects.Contains(Weapon.Effect.Skip))
            {
                
            }
            if (effects.Contains(Weapon.Effect.Sustain))
            {
                
            }
            
            ship.TakeDamage(damage);
            Destroy(gameObject);
        }
        else if (collision.gameObject.CompareTag("Shield") && collision.gameObject != myShield)
        {
            var shield = collision.gameObject.GetComponent<Shield>();
            
            if (effects.Contains(Weapon.Effect.Stun))
            {
                
            }
            if (effects.Contains(Weapon.Effect.Slow))
            {
                
            }
            if (effects.Contains(Weapon.Effect.Splash))
            {
                
            }
            if (effects.Contains(Weapon.Effect.Skip))
            {
                return;
            }
            if (effects.Contains(Weapon.Effect.Sustain))
            {
                
            }
            
            shield.TakeDamage(damage);
            Destroy(gameObject);
        }
    }

    private void OnTriggerExit2D(Collider2D other)
    {
        if (other.gameObject.name == "Viewport")
        {
            Destroy(gameObject);
        }
    }
}
