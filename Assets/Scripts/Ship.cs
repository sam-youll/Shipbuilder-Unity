using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class Ship : MonoBehaviour
{
    public GameObject healthBar;
    public float maxHealth = 100f;
    private float health;
    public List<GameObject> weapons;
    private bool allWeaponsWarmed = false;
    
    public GameObject floatingDamageNumberPrefab;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        health = maxHealth;
    }

    // Update is called once per frame
    void Update()
    {
        // warm up weapons one by one
        if (!allWeaponsWarmed)
        {
            for (var i = 0; i < weapons.Count; i++)
            {
                var weapon = weapons[i].GetComponent<Weapon>();
                
                // weapons warm themselves up, we only need to know when to turn them on
                if (!weapon.warming)
                {
                    // first weapon warms up
                    if (i == 0)
                    {
                        weapon.warming = true;
                    }
                    // check if last weapon is done warming up
                    else if (weapons[i - 1].GetComponent<Weapon>().warmup >= 1)
                    {
                        weapon.warming = true;
                    }
                    // if it isn't the first and the previous one isn't done, don't bother checking the rest
                    else
                    {
                        break;
                    }
                }
            }
        }
        
    }

    public void TakeDamage(float damage)
    {
        health -= damage;
        healthBar.GetComponent<StatBar>().value = health / maxHealth;
        var playerHitNumber = Instantiate(floatingDamageNumberPrefab, transform.position, Quaternion.identity);
        playerHitNumber.GetComponent<TextMeshPro>().text = "-" + damage.ToString();
    }
}
