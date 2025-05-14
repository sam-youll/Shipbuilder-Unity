using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using TMPro;
using UnityEngine;
using UnityEngine.Events;
using UnityEngine.Rendering;
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
    private float endScreenTimer = 3f; // time before endScreen disappears

    public StatBar playerHealthBar;
    public StatBar[] playerShieldBars;
    public StatBar enemyHealthBar;
    public StatBar[] enemyShieldBars;

    public Ship playerShip;
    public Ship enemyShip;
    public List<GameObject> enemyWeapons; // probably redundant with enemyShip.weapons
    public int fightLevel = 1; // i think this is doing the same thing as battleNumber

    public TextMeshPro battleNumberLabel; // displays what battle you're on
    private int battleNumber;

    public GameObject geomagneticPulse;
    public GameObject pulseTooltip;
    private bool pulsarEventActive;
    public float pulseTimer = 4; // time between pulses

    public UnityEvent playerShipImpact;

    public bool combatOverride;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        // Call OnMainSceneLoaded when the scene (re)loads
        // I'm doing this because singletons aren't going to call Start again on reload
        SceneManager.sceneLoaded += OnMainSceneLoaded;
        
        geomagneticPulse.transform.parent.gameObject.SetActive(false);
    }

    /// <summary>
    /// void Start(): the squeakquel
    /// </summary>
    void OnMainSceneLoaded(Scene scene, LoadSceneMode mode)
    {
        state = State.outOfCombat;
        enemyShip.gameObject.SetActive(false);
        
    }

    // Update is called once per frame
    void Update()
    {
        // set values of health & shield bars
        playerHealthBar.value = playerShip.health / playerShip.maxHealth;
        enemyHealthBar.value = enemyShip.health / enemyShip.maxHealth;
        for (var i = 0; i < 4; i++)
        {
            playerShieldBars[i].gameObject.SetActive(playerShip.shields[i].activeSelf);
            playerShieldBars[i].value = playerShip.shields[i].GetComponent<Shield>().health / playerShip.shields[i].GetComponent<Shield>().maxHealth;
            enemyShieldBars[i].gameObject.SetActive(enemyShip.shields[i].activeSelf);
            enemyShieldBars[i].value = enemyShip.shields[i].GetComponent<Shield>().health / enemyShip.shields[i].GetComponent<Shield>().maxHealth;
        }

        // GEOMAGNETIC STORM TIME
        if (fightLevel == 4 && state == State.outOfCombat) 
        {
            geomagneticPulse.transform.parent.gameObject.SetActive(true);
            pulseTooltip.SetActive(true);
            // Debug.Log("showing tooltip");
        }
        
        #region Combat State Machine
        if (state == State.inCombat)
        {
            // On fight 4, start firing pulsar/geomagnetic storm
            if (fightLevel == 4)
            {
                // Debug.Log("hiding tooltip");
                pulseTooltip.SetActive(false);

                // countdown timer to pulse
                pulseTimer -= Time.deltaTime;
                if (pulseTimer <= 0)
                {
                    StartCoroutine(Pulsar()); // the actual pulse is a coroutine
                    pulseTimer += 6; // timer starts at 4 seconds, then resets to 6 seconds between pulses. this can be changed if need be
                }
                

            }
            else
            {
                // geomagnetic storm is not active anywhere else
                geomagneticPulse.transform.parent.gameObject.SetActive(false);
            }

            // if one of the ships dies, combat ends
            if (playerHealthBar.value <= 0 || enemyHealthBar.value <= 0)
            {
                ReactorSounds.Instance.StopEnemyReactor();
                state = State.endScreen;
                endScreen.SetActive(true);
                endScreenTimer = 3f; // close end screen in 3 seconds

                // if player health is less than 0, player lost
                if (playerHealthBar.value <= 0)
                {
                    endScreen.GetComponentInChildren<TextMeshPro>().text = "YOU LOSE";
                    
                }
                // otherwise, the enemy lost and the player won
                else if (enemyHealthBar.value <= 0)
                {
                    endScreen.GetComponentInChildren<TextMeshPro>().text = "YOU WIN";
                    endScreenTimer = 999f; // set the timer to 999 (basically turning it off) so the player has time to choose their reward
                    
                    fightLevel++;
                    battleNumberLabel.text = fightLevel.ToString();
                    
                    // increase damage of all enemy weapons
                    foreach (var weapon in enemyWeapons)
                    {
                        weapon.GetComponent<Weapon>().damage += 1;
                    }

                    // increase health cause why not
                    // this is also something that could be good to change
                    // theoretically we'll eventually have some actual mechanic for increasing health
                    enemyShip.maxHealth += 5;
                    playerShip.maxHealth += 5;
                }
                
            }
        }
        else if (state == State.endScreen)
        {
            // once the timer runs out, just close the damn game
            // TODO: don't quit the game, just go to the main menu or something
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
            // this only mattered when the camera moved
            // it doesn't move anymore
            // yet???
            // if (Camera.main.transform.position != new Vector3(0, 0, -10))
            // {
            //     Camera.main.transform.position = Vector3.Lerp(Camera.main.transform.position, new Vector3(0, 0, -10), .3f);
            // }
        }
        #endregion
    }

    public void StartCombat()
    {
        // endScreen.GetComponentInChildren<TextMeshPro>().text = "YOU LOSE";
        ReactorSounds.Instance.StartEnemyReactor();
        endScreen.SetActive(false);
        
        // reset enemy ship
        enemyShip.gameObject.SetActive(true);
        // reset enemy shields
        // TODO: set shields to starting scale, not Vector3.one
        // I'm also calling start coroutine here because it was an attempt to fix things
        // This may be causing problems
        foreach (var shield in enemyShip.GetComponent<Ship>().shields)
        {
            shield.transform.localScale = Vector3.one;
            shield.GetComponent<Shield>().health = shield.GetComponent<Shield>().maxHealth;
            shield.GetComponent<Shield>().StartCoroutine("RegenShield"); // this is probably not a great idea
        }
        
        // reset player & enemy health
        // setting the health bars is probably redundant
        enemyHealthBar.value = 1;
        playerHealthBar.value = 1;
        //playerShip.health = playerShip.maxHealth;
        enemyShip.health = enemyShip.maxHealth;

        // loop through all player weapons, then reset warmup status on all of them
        // this might not be happening for the enemy weapons
        playerShip.weapons = new List<GameObject>(); // wipe the weapons list and rebuild it every new combat
        foreach (var weapon in WeaponManager.Instance.weapons)
        {
            if (weapon.activeSelf)
            {
                playerShip.weapons.Add(weapon); // rebuilding the list based on what weapons are active
                weapon.GetComponent<Weapon>().warmup = 0;
                weapon.GetComponent<Weapon>().warming = false;
            }
        }
        playerShip.allWeaponsWarmed = false; // this is so Ship.cs can warm up the weapons one by one
        // this whole thing should probably be happening for the enemy weapons, too
        
        state = State.inCombat;

        AudioManager.Instance.ResetPlayedList();
        AudioManager.Instance.StopEnemySong();
    }

    public IEnumerator Pulsar()
    {
        // play audio
        AudioManager.Instance.StartStorm();
        
        // reset scale of pulse
        geomagneticPulse.transform.localScale = Vector3.one;
        // turn pulse on
        geomagneticPulse.SetActive(true);
        
        // get sprite renderer component
        var sr = geomagneticPulse.GetComponent<SpriteRenderer>();
        // reset color/alpha of sprite
        var colcol = sr.color;
        colcol.a = .6f;
        sr.color = colcol;
        
        // increase scale of pulse until it's at least 30
        while (geomagneticPulse.transform.localScale.x < 30)
        {
            // grow
            geomagneticPulse.transform.localScale *= 1 + (Time.deltaTime * 7);
            // pause for one frame
            yield return null;
        }
        // once it's grown, randomly stun weapons
        foreach (var weapon in playerShip.weapons)
        {
            // 80% chance to stun each weapon
            // feel free to change this number
            // TODO: player weapons don't turn yellow when stunned?
            // that should probably be a bug in the backlog
            var roll = Random.value;
            if (roll < 0.8f)
            {
                // we stun the weapon in a sort of roundabout way by just increasing its stun timer
                weapon.GetComponent<Weapon>().stunTimer += 3;
            }
        }
        // same as above, but for the enemy ship
        foreach (var weapon in enemyShip.weapons)
        {
            var roll = Random.value;
            if (roll < 0.8f)
            {
                weapon.GetComponent<Weapon>().stunTimer += 3;
            }
        }
        // once all that's finished, we fade out
        while (sr.color.a > 0)
        {
            // fade a bit
            var col = sr.color;
            col.a -= Time.deltaTime;
            sr.color = col;
            // wait one frame
            yield return null;
        }
        // once it's faded all the way out, deactivate it
        geomagneticPulse.SetActive(false);

        // pause for 2.5 seconds, then stop audio
        yield return new WaitForSeconds(2.5f);
        AudioManager.Instance.StopStorm();
        
    }
}
