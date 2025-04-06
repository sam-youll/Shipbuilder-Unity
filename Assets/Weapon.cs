using System.Collections.Generic;
using UnityEngine;

public class Weapon : MonoBehaviour
{
    public StatBar statBar;
    public float fireRate;
    public float energyRate;
    public float damage;
    public float warmup = 0;
    public bool warming = false;
    public float bulletSpeed;
    public float bulletSpread;
    public GameObject bulletPrefab;
    public GameObject myShip;
    public float dir;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
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
        
        statBar.value += energyRate * fireRate * warmup * Time.deltaTime;
        if (statBar.value >= 1)
        {
            statBar.value = 0;
            Fire();
        }
    }

    void Fire()
    {
        var newBullet = Instantiate(bulletPrefab, myShip.transform.position, Quaternion.identity);
        newBullet.GetComponent<Bullet>().damage = damage;
        newBullet.GetComponent<Rigidbody2D>().linearVelocity = new Vector2(dir*1, Random.Range(-bulletSpread, bulletSpread)) * bulletSpeed;
        newBullet.GetComponent<Bullet>().myShip = myShip;
        var noteInfo = new Dictionary<string, float>{ {"length", 1.17f} };
        AudioManager.Instance.PlayNote(gameObject, noteInfo);
    }
}
