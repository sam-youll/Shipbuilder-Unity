using System;
using Unity.VisualScripting;
using UnityEngine;

public class Bullet : MonoBehaviour
{
    // public Vector2 dir;
    public float damage;
    public GameObject myShip;
    // public float speed;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    void OnCollisionEnter2D(Collision2D collision)
    {
        // Debug.Log(collision.gameObject.name);
        if (collision.gameObject.CompareTag("Ship") && collision.gameObject != myShip)
        {
            collision.gameObject.GetComponent<Ship>().TakeDamage(damage);
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
