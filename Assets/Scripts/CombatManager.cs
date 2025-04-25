using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using TMPro;
using UnityEngine;
using UnityEngine.SceneManagement;

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
    public int fightLevel;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
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
            enemyShip.gameObject.SetActive(true);
            // if (Camera.main.transform.position != new Vector3(18, 0, -10))
            // {
            //     Camera.main.transform.position = Vector3.Lerp(Camera.main.transform.position, new Vector3(18, 0, -10), .3f);
            // }

            if (playerHealthBar.value <= 0 || enemyHealthBar.value <= 0)
            {
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
                    foreach (var weapon in enemyWeapons)
                    {
                        weapon.GetComponent<Weapon>().damage += 2;
                    }
                }
            }
        }
        else if (state == State.endScreen)
        {
            endScreenTimer -= Time.deltaTime;
            if (endScreenTimer <= 0)
            {
                endScreen.SetActive(false);
                SceneManager.LoadScene(SceneManager.GetActiveScene().name);
                state = State.outOfCombat;
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
        endScreen.SetActive(false);
        enemyHealthBar.value = 1;
        playerHealthBar.value = 1;
        enemyShip.health = enemyShip.maxHealth;
        
        state = State.inCombat;

        AudioManager.Instance.ResetPlayedList();
        AudioManager.Instance.StopEnemySong();
    }
}
