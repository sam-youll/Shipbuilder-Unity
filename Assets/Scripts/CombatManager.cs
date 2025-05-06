using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using TMPro;
using UnityEngine;
using UnityEngine.Events;
using UnityEngine.SceneManagement;
using Random = UnityEngine.Random;

public class CombatManager : MonoBehaviour
{
    public static CombatManager Instance { get; private set; }
    private void Awake()
    {
        if (Instance != null && Instance != this)
        {
            Destroy(this);
        }
        else
        {
            Instance = this;
        }
    }

    public enum State
    {
        outOfCombat,
        inCombat,
        endScreen
    }

    public State state = State.outOfCombat;
    public GameObject endScreen;
    private float endScreenTimer = 3f;

    public StatBar playerHealthBar;
    public StatBar playerShieldBar;
    public StatBar enemyHealthBar;
    public StatBar enemyShieldBar;

    public Ship playerShip;
    public Ship enemyShip;
    public List<GameObject> enemyWeapons;
    public int fightLevel = 1;

    public TextMeshPro battleNumberLabel;
    private int battleNumber;

    public GameObject geomagneticPulse;
    private bool pulsarEventActive;
    private float pulseTimer = 4;

    public UnityEvent playerShipImpact;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        SceneManager.sceneLoaded += OnMainSceneLoaded;
        
        // geomagneticPulse.SetActive(false);
        geomagneticPulse.transform.parent.gameObject.SetActive(false);
    }

    void OnMainSceneLoaded(Scene scene, LoadSceneMode mode)
    {
        state = State.outOfCombat;
        enemyShip.gameObject.SetActive(false);
        
    }

    // Update is called once per frame
    void Update()
    {
        playerHealthBar.value = playerShip.health / playerShip.maxHealth;
        enemyHealthBar.value = enemyShip.health / enemyShip.maxHealth;
        playerShieldBar.value = playerShip.transform.GetComponentInChildren<Shield>().health /
                                playerShip.transform.GetComponentInChildren<Shield>().maxHealth;
        enemyShieldBar.value = enemyShip.transform.GetComponentInChildren<Shield>().health /
                               enemyShip.transform.GetComponentInChildren<Shield>().maxHealth;
        
        if (state == State.inCombat)
        {
            if (fightLevel == 2)
            {
                // geomagneticPulse.SetActive(true);
                geomagneticPulse.transform.parent.gameObject.SetActive(true);
                
                pulseTimer -= Time.deltaTime;
                if (pulseTimer <= 0)
                {
                    StartCoroutine(Pulsar());
                    pulseTimer += 6;
                    foreach (var weapon in playerShip.weapons)
                    {
                        var roll = Random.value;
                        if (roll < 0.8f)
                        {
                            weapon.GetComponent<Weapon>().stunTimer += 3;
                        }
                    }

                    foreach (var weapon in enemyShip.weapons)
                    {
                        var roll = Random.value;
                        if (roll < 0.8f)
                        {
                            weapon.GetComponent<Weapon>().stunTimer += 3;
                        }
                    }
                }
                
            }
            else
            {
                // geomagneticPulse.SetActive(false);
                geomagneticPulse.transform.parent.gameObject.SetActive(false);
            }
            // if (Camera.main.transform.position != new Vector3(18, 0, -10))
            // {
            //     Camera.main.transform.position = Vector3.Lerp(Camera.main.transform.position, new Vector3(18, 0, -10), .3f);
            // }

            if (playerHealthBar.value <= 0 || enemyHealthBar.value <= 0)
            {
                ReactorSounds.Instance.StopEnemyReactor();
                state = State.endScreen;
                endScreen.SetActive(true);
                endScreenTimer = 3f;

                if (playerHealthBar.value <= 0)
                {
                    endScreen.GetComponentInChildren<TextMeshPro>().text = "YOU LOSE";
                    
                }
                else if (enemyHealthBar.value <= 0)
                {
                    endScreen.GetComponentInChildren<TextMeshPro>().text = "YOU WIN";
                    endScreenTimer = 999f;
                    fightLevel++;
                    battleNumberLabel.text = fightLevel.ToString();
                    foreach (var weapon in enemyWeapons)
                    {
                        weapon.GetComponent<Weapon>().damage += 1;
                    }

                    enemyShip.maxHealth += 5;
                    enemyShip.shield.GetComponent<Shield>().maxHealth += 2;
                    playerShip.maxHealth += 5;
                    playerShip.shield.GetComponent<Shield>().maxHealth += 2;
                }
                
            }
        }
        else if (state == State.endScreen)
        {
            endScreenTimer -= Time.deltaTime;
            if (endScreenTimer <= 0)
            {
                endScreen.SetActive(false);
                state = State.outOfCombat;
                // SceneManager.LoadScene(SceneManager.GetActiveScene().name);
                Application.Quit();
            }
        }
        else if (state == State.outOfCombat)
        {
            if (Camera.main.transform.position != new Vector3(0, 0, -10))
            {
                Camera.main.transform.position = Vector3.Lerp(Camera.main.transform.position, new Vector3(0, 0, -10), .3f);
            }
        }
    }

    public void StartCombat()
    {
        // endScreen.GetComponentInChildren<TextMeshPro>().text = "YOU LOSE";
        ReactorSounds.Instance.StartEnemyReactor();
        endScreen.SetActive(false);
        enemyShip.gameObject.SetActive(true);
        enemyShip.GetComponent<Ship>().shield.transform.localScale = Vector3.one;
        enemyShip.GetComponent<Ship>().shield.GetComponent<Shield>().health =
            enemyShip.GetComponent<Ship>().shield.GetComponent<Shield>().maxHealth;
        enemyShip.GetComponent<Ship>().shield.GetComponent<Shield>().StartCoroutine("RegenShield");
        enemyHealthBar.value = 1;
        playerHealthBar.value = 1;
        playerShip.health = playerShip.maxHealth;
        enemyShip.health = enemyShip.maxHealth;

        playerShip.weapons = new List<GameObject>();
        foreach (var weapon in WeaponManager.Instance.weapons)
        {
            if (weapon.activeSelf)
            {
                playerShip.weapons.Add(weapon);
                weapon.GetComponent<Weapon>().warmup = 0;
                weapon.GetComponent<Weapon>().warming = false;
            }
        }
        playerShip.allWeaponsWarmed = false;
        
        state = State.inCombat;

        AudioManager.Instance.ResetPlayedList();
        AudioManager.Instance.StopEnemySong();
    }

    IEnumerator Pulsar()
    {
        geomagneticPulse.transform.localScale = Vector3.one;
        geomagneticPulse.SetActive(true);
        var sr = geomagneticPulse.GetComponent<SpriteRenderer>();
        var colcol = sr.color;
        colcol.a = .6f;
        sr.color = colcol;
        while (geomagneticPulse.transform.localScale.x < 30)
        {
            geomagneticPulse.transform.localScale *= 1 + (Time.deltaTime * 7);
            yield return null;
        }
        while (sr.color.a > 0)
        {
            var col = sr.color;
            col.a -= Time.deltaTime;
            sr.color = col;
            yield return null;
        }
        colcol.a = .6f;
        sr.color = colcol;
        geomagneticPulse.SetActive(false);
    }
}
