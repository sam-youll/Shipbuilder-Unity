using System;
using System.Collections.Generic;
using System.Linq;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Bullet : MonoBehaviour
{
    // public Vector2 dir;
    public float damage;
    public float hullDamage;
    public float shieldDamage;
    public GameObject myShip;
    public GameObject[] myShields;
    // public float speed;
    public List<Weapon.Effect> effects;
    public Combat.SoundType soundType;

    public GameObject explosionPrefab;
    
    private float lifeTime = 10;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        lifeTime /= GetComponent<Rigidbody2D>().linearVelocity.magnitude;
        
        if (SceneManager.GetActiveScene().name == "Cinematic Scene")
        {
            var pos = transform.position;
            pos.z -= 1;
            transform.position = pos;
        }
    }

    // Update is called once per frame
    void Update()
    {
        lifeTime -= Time.deltaTime;

        if (lifeTime <= 0)
        {
            Destroy(gameObject);
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
            
            var explosion = Instantiate(explosionPrefab, transform.position + new Vector3(0, 0, -.3f), Quaternion.identity);
            if (SceneManager.GetActiveScene().name == "Cinematic Scene")
            {
                explosion.transform.localScale = new Vector3(3, 3, 3);
            }
            //AudioManager.Instance.PlayExplosionSFX();
            ship.TakeDamage(damage);
            Destroy(gameObject);
        }
        else if (collision.gameObject.CompareTag("Shield") &&  !myShields.Contains(collision.gameObject))
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
