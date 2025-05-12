using Unity.VisualScripting;
using UnityEngine;

public class TrailerManager : MonoBehaviour
{
    public GameObject weaponOne;

    //public SpriteRenderer enemyShipSprite;

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        Conductor.Instance.onEighth.AddListener(WeaponOne);
        Conductor.Instance.onHalf.AddListener(Pads);
        Conductor.Instance.onSixteenth.AddListener(WeaponTwo);
        Conductor.Instance.onQuarter.AddListener(WeaponThree);
        //Conductor.Instance.onQuarter.AddListener(EnemyWeaponOne);
        //Conductor.Instance.onEighth.AddListener(EnemyWeaponTwo);
        //Conductor.Instance.onSixteenth.AddListener(EnemyWeaponThree);
        Conductor.Instance.onHalf.AddListener(Perc);
        Conductor.Instance.onHalf.AddListener(TempoChanges);

        CombatManager.Instance.StartCombat();

        /*foreach (var weapon in CombatManager.Instance.enemyWeapons)
        {
            CombatManager.Instance.enemyShip.weapons.Remove(weapon);
        }*/

        // for (var i = 0; i < WeaponManager.Instance.weapons.Count; i++)
        // {
        //     var weapon = WeaponManager.Instance.weapons[i];
        //     WeaponManager.Instance.weapons.Remove(weapon);
        // }

        CombatManager.Instance.enemyShip.weapons[1].SetActive(false);
        CombatManager.Instance.enemyShip.weapons[2].SetActive(false);
        CombatManager.Instance.enemyShip.weapons[3].SetActive(false);
        
        //enemyShipSprite.enabled = false;
    }

    // Update is called once per frame
    void Update()
    {
        /*if (Conductor.Instance.bar == 9 && Conductor.Instance.half == 1)
        {
            CombatManager.Instance.geomagneticPulse.transform.parent.gameObject.SetActive(true);

            if (CombatManager.Instance.geomagneticPulse.transform.parent.gameObject == isActiveAndEnabled)
            {
                CombatManager.Instance.pulseTimer -= Time.deltaTime;
                if (CombatManager.Instance.pulseTimer <= 0)
                {
                    StartCoroutine(CombatManager.Instance.Pulsar());
                    CombatManager.Instance.pulseTimer += 6;
                }
            }
        }*/

    }

    void WeaponOne()
    {
        WeaponManager.Instance.weapons[0].GetComponent<Weapon>().bulletSpread = .1f;
        WeaponManager.Instance.weapons[0].GetComponent<Weapon>().myShipWeapon.transform.GetChild(1).GetComponent<SpriteRenderer>().enabled = false;
        WeaponManager.Instance.weapons[0].GetComponent<Weapon>().myShipWeapon.transform.GetChild(2).GetComponent<SpriteRenderer>().enabled = false;
        
        if (Conductor.Instance.bar == 0)
        {
            if (Conductor.Instance.eighth % 2 != 0)
            {
                WeaponManager.Instance.weapons[0].GetComponent<Weapon>().charge = 1;
                WeaponManager.Instance.weapons[0].GetComponent<Weapon>().Fire();
            }
        }

        if (Conductor.Instance.bar >= 1 && Conductor.Instance.bar < 9)
        {
            WeaponManager.Instance.weapons[0].GetComponent<Weapon>().charge = 1;
            WeaponManager.Instance.weapons[0].GetComponent<Weapon>().Fire();
        }

        
    }

    void WeaponTwo()
    {
        if (Conductor.Instance.bar == 1 && Conductor.Instance.sixteenth == 0)
        {
            WeaponManager.Instance.AddWeapon();
            WeaponManager.Instance.weapons[1].GetComponent<Weapon>().bulletSpread = .2f;
            WeaponManager.Instance.weapons[1].GetComponent<Weapon>().bulletSpeed = 3;
            WeaponManager.Instance.weapons[1].GetComponent<Weapon>().myShipWeapon.transform.GetChild(1).GetComponent<SpriteRenderer>().enabled = false;
            WeaponManager.Instance.weapons[1].GetComponent<Weapon>().myShipWeapon.transform.GetChild(2).GetComponent<SpriteRenderer>().enabled = false;
        }

        if (Conductor.Instance.bar >= 2 && Conductor.Instance.bar < 7)
        {
            
            WeaponManager.Instance.weapons[1].GetComponent<Weapon>().charge = 1;
            WeaponManager.Instance.weapons[1].GetComponent<Weapon>().Fire();
        }

        if (Conductor.Instance.bar == 7 && Conductor.Instance.sixteenth == 8)
        {
            WeaponManager.Instance.weapons[1].GetComponent<Weapon>().myShipWeapon.gameObject.SetActive(false);
        }

    }

    void WeaponThree()
    {
        if (Conductor.Instance.bar == 3 && Conductor.Instance.quarter == 0)
        {
            WeaponManager.Instance.AddWeapon();
            WeaponManager.Instance.weapons[2].GetComponent<Weapon>().myShipWeapon.transform.GetChild(1).GetComponent<SpriteRenderer>().enabled = false;
            WeaponManager.Instance.weapons[2].GetComponent<Weapon>().myShipWeapon.transform.GetChild(2).GetComponent<SpriteRenderer>().enabled = false;
        }

        if (Conductor.Instance.bar >= 4 && Conductor.Instance.bar < 8)
        {
            WeaponManager.Instance.weapons[2].GetComponent<Weapon>().charge = 1;
            WeaponManager.Instance.weapons[2].GetComponent <Weapon>().Fire();
        }

        if (Conductor.Instance.bar == 8 && Conductor.Instance.quarter == 2)
        {
            WeaponManager.Instance.weapons[2].GetComponent<Weapon>().myShipWeapon.gameObject.SetActive(false);
        }

    }

    void EnemyWeaponOne()
    {
        if (Conductor.Instance.bar == 1 && Conductor.Instance.bar < 9)
        {
            CombatManager.Instance.enemyShip.weapons[0].GetComponent<Weapon>().charge = 1;
            CombatManager.Instance.enemyShip.weapons[0].GetComponent<Weapon>().Fire();
        }
        if (Conductor.Instance.bar == 9 && Conductor.Instance.quarter == 0)
        {
            CombatManager.Instance.enemyShip.weapons[0].SetActive(false);
        }
    }

    void EnemyWeaponTwo()
    {
        if (Conductor.Instance.bar == 2 && Conductor.Instance.eighth == 1)
        {
            CombatManager.Instance.enemyShip.weapons[1].SetActive(true);
        }

        if (Conductor.Instance.bar >= 2 && Conductor.Instance.bar < 7)
        {
            CombatManager.Instance.enemyShip.weapons[1].GetComponent<Weapon>().charge = 1;
            CombatManager.Instance.enemyShip.weapons[1].GetComponent<Weapon>().Fire();
        }

        if (Conductor.Instance.bar == 7 && Conductor.Instance.eighth == 0)
        {
            CombatManager.Instance.enemyShip.weapons[1].SetActive(false);
        }
    }

    void EnemyWeaponThree()
    {
        if (Conductor.Instance.bar == 3 && Conductor.Instance.sixteenth == 1)
        {
            CombatManager.Instance.enemyShip.weapons[2].SetActive(true);
        }

        if (Conductor.Instance.bar >= 3 && Conductor.Instance.bar < 8)
        {
            CombatManager.Instance.enemyShip.weapons[2].GetComponent<Weapon>().charge = 1;
            CombatManager.Instance.enemyShip.weapons[2].GetComponent <Weapon>().Fire();
        }

        if (Conductor.Instance.bar == 8 && Conductor.Instance.sixteenth == 1 )
        {
            CombatManager.Instance.enemyShip.weapons[2].SetActive(false);
        }
    }

    void Pads()
    {
        if (Conductor.Instance.bar == 2 && Conductor.Instance.half == 0)
        {
            ReactorSounds.Instance.AddPlayerPad(ReactorSounds.Instance.playerPad2);
        }
        if (Conductor.Instance.bar == 3 && Conductor.Instance.half == 0)
        {
            ReactorSounds.Instance.AddEnemyPad(ReactorSounds.Instance.enemyPad2);
        }
        if (Conductor.Instance.bar == 3 && Conductor.Instance.half == 1)
        {
            ReactorSounds.Instance.AddPlayerPad(ReactorSounds.Instance.playerPad3);
        }
        if (Conductor.Instance.bar == 4 && Conductor.Instance.half == 0)
        {
            ReactorSounds.Instance.AddEnemyPad(ReactorSounds.Instance.enemyPad3);
        }
        if (Conductor.Instance.bar == 4 && Conductor.Instance.half == 1)
        {
            ReactorSounds.Instance.AddPlayerPad(ReactorSounds.Instance.enemyPad4);
        }
        if (Conductor.Instance.bar == 5 && Conductor.Instance.half == 0)
        {
            ReactorSounds.Instance.AddEnemyPad(ReactorSounds.Instance.playerPad4);
        }
    }

    void Perc()
    {

    }

    void TempoChanges()
    {
        //Debug.Log("The tempo change function is called");
        Reactor.Instance.tempoOverride = true;
        Reactor.Instance.SetPatch();

        if (Conductor.Instance.bar >= 2)
        {
            Conductor.Instance.tempo = 240;
            //Debug.Log("The tempo should change here");
        }
    }

}
