using System;
using System.Collections.Generic;
using UnityEngine;

public class WeaponManager : MonoBehaviour
{
    public static WeaponManager Instance;

    private void Awake()
    {
        Instance = this;
    }

    public List<GameObject> weapons;
    public List<GameObject> shipWeapons;
    public int weaponActive;
    
    public GameObject playerShip;

    public GameObject shipWeaponPrefab;

    public GameObject weaponMenu;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        playerShip = CombatManager.Instance.playerShip.gameObject;
        
        var newShipWeapon = Instantiate(shipWeaponPrefab, playerShip.transform);
        var pos = newShipWeapon.transform.localPosition;
        pos.y = weaponActive - 1;
        newShipWeapon.transform.localPosition = pos;
        weapons[weaponActive].GetComponent<Weapon>().statBar = newShipWeapon.transform.GetComponentInChildren<StatBar>();
        weapons[weaponActive].GetComponent<Weapon>().myShip = playerShip;
        weapons[weaponActive].GetComponent<Weapon>().myShipWeapon = newShipWeapon;
        PatchManager.Instance.weapons.Add(weapons[weaponActive].GetComponent<Weapon>());
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void AddWeapon()
    {
        weaponActive++;
        weapons[weaponActive].SetActive(true);
        var newShipWeapon = Instantiate(shipWeaponPrefab, playerShip.transform);
        var pos = newShipWeapon.transform.localPosition;
        pos.y = weaponActive - 1;
        newShipWeapon.transform.localPosition = pos;
        weapons[weaponActive].GetComponent<Weapon>().statBar = newShipWeapon.transform.GetComponentInChildren<StatBar>();
        weapons[weaponActive].GetComponent<Weapon>().myShip = playerShip;
        weapons[weaponActive].GetComponent<Weapon>().myShipWeapon = newShipWeapon;
        PatchManager.Instance.weapons.Add(weapons[weaponActive].GetComponent<Weapon>());
    }
}
