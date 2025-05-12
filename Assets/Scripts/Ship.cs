using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class Ship : MonoBehaviour
{
    public float maxHealth = 100f;
    public float health;
    public List<GameObject> weapons;
    public bool allWeaponsWarmed;
    public GameObject[] shields;
    public bool cloaked = false;
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
        if (CombatManager.Instance.state != CombatManager.State.inCombat)
        {
            return;
        }
        
        CombatManager.Instance.playerShipImpact.Invoke();
        
        health -= damage;
        var playerHitNumber = Instantiate(floatingDamageNumberPrefab, transform.position, Quaternion.identity);
        var pos = transform.position;
        pos.z -= .1f;
        playerHitNumber.transform.position = pos;
        playerHitNumber.GetComponent<TextMeshPro>().text = "-" + damage;

        if (health <= 0)
        {
            gameObject.SetActive(false);
        }
    }
    
    public void ApplyStun(float duration)
    {
        // apply stun to a random weapon
        weapons[Random.Range(0, weapons.Count)].GetComponent<Weapon>().stunTimer = duration;
    }

    public void ApplySlow(float strength)
    {
        allWeaponsWarmed = false;
        foreach (var weapon in weapons)
        {
            weapon.GetComponent<Weapon>().warmup = .5f + .5f/strength; // TODO: Change this formula, it sucks
        }
    }
}
