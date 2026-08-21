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
using UnityEngine.Serialization;
using static UnityEngine.Rendering.DebugUI;
using Random = UnityEngine.Random;

public class CombatManager : MonoBehaviour
{
    public static CombatManager Instance { get; private set; }
    private void Awake()
    {
        if (Instance != null && Instance != this)
        {
            Destroy(gameObject);
        }
        else
        {
            Instance = this;
            // DontDestroyOnLoad(this);
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

    public int fightLevel = 1; // i think this is doing the same thing as battleNumber

    public TextMeshPro battleNumberLabel; // displays what battle you're on
    private int battleNumber;

    // public GameObject geomagneticPulse;
    // public GameObject pulseTooltip;
    // private bool pulsarEventActive;
    // public float pulseTimer = 4; // time between pulses

    // public UnityEvent playerShipImpact;

    // public bool combatOverride;

    private int newWeapon = 1;
    private int newShield = 0;

    public int weaponChance = 33;
    public int shieldChance = 66;

    public GameObject shop;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        // Call OnMainSceneLoaded when the scene (re)loads
        // I'm doing this because singletons aren't going to call Start again on reload
        SceneManager.sceneLoaded += OnMainSceneLoaded;
        
        // geomagneticPulse.transform.parent.gameObject.SetActive(false);
        
        EventBus.Instance.combatStarted.AddListener(OnCombatStarted);
        EventBus.Instance.enemyDefeated.AddListener(OnEnemyDefeated);
        EventBus.Instance.playerEscaped.AddListener(OnPlayerEscaped);
        EventBus.Instance.playerDefeated.AddListener(OnPlayerDefeated);
    }

    /// <summary>
    /// void Start(): the squeakquel
    /// </summary>
    void OnMainSceneLoaded(Scene scene, LoadSceneMode mode)
    {
        state = State.outOfCombat;
        // enemyShip.gameObject.SetActive(false);
        
    }

    // Update is called once per frame
    void Update()
    {
        // set values of health & shield bars
        // playerHealthBar.value = playerShip.health / playerShip.maxHealth;
        // enemyHealthBar.value = enemyShip.health / enemyShip i = 0; i < 4; i++)
                                                                      // {
                                                                      //     playerShieldBars[i].gameObject.SetActive(playerShip.shields[i].activeSelf);
                                                                      //     playerShieldBars[i].value = playerShip.shields[i].GetComponent<Shield>().health / playerShip.shields[i].GetComponent<Shield>().maxHealth;
                                                                      //     enemyShieldBars[i].gameObject.SetActive(enemyShip.shields[i].activeSelf);
                                                                      //     enemyShieldBars[i].value = enemyShip.shields[i].GetComponent<Shield>().health / enemyShip.shields[i].GetComponent<Shield>().maxHealth;
                                                                      // }.maxHealth;
        // for (var

        // GEOMAGNETIC STORM TIME
        // if (fightLevel == 4 && state == State.outOfCombat) 
        // {
        //     geomagneticPulse.transform.parent.gameObject.SetActive(true);
        //     pulseTooltip.SetActive(true);
        // }
        
        #region Combat State Machine
        if (state == State.inCombat)
        {
            // On fight 4, start firing pulsar/geomagnetic storm
            // if (fightLevel == 4)
            // {
            //     // geomagneticPulse.SetActive(true);
            //    
            //     pulseTooltip.SetActive(false);
            //
            //     // countdown timer to pulse
            //     pulseTimer -= Time.deltaTime;
            //     if (pulseTimer <= 0)
            //     {
            //         StartCoroutine(Pulsar()); // the actual pulse is a coroutine
            //         pulseTimer += 6; // timer starts at 4 seconds, then resets to 6 seconds between pulses. this can be changed if need be
            //     }
            //     
            //
            // }
            // else
            // {
            //     geomagnetic storm is not active anywhere else
            //     geomagneticPulse.transform.parent.gameObject.SetActive(false);
            // }

            // if one of the ships dies, combat ends
            // if (playerHealthBar.value <= 0 || enemyHealthBar.value <= 0)
            // {
            //     ReactorSounds.Instance.StopEnemyReactor();
            //     state = State.endScreen;
            //     endScreen.SetActive(true);
            //     endScreenTimer = 3f; // close end screen in 3 seconds
            //
            //     // if player health is less than 0, player lost
            //     if (playerHealthBar.value <= 0)
            //     {
            //         endScreen.GetComponentInChildren<TextMeshPro>().text = "YOU LOSE";
            //         if (SceneManager.GetActiveScene() != SceneManager.GetSceneByName("Spring Showcase Tutorial"))
            //         {
            //             Invoke(nameof(GoToMainMenu), 2);
            //         }
            //     }
            //     // otherwise, the enemy lost and the player won
            //     else if (enemyHealthBar.value <= 0)
            //     {
            //         endScreen.GetComponentInChildren<TextMeshPro>().text = "YOU WIN";
            //         // endScreenTimer = 999f; // set the timer to 999 (basically turning it off) so the player has time to choose their reward
            //         
            //         fightLevel++;
            //         Inventory.Instance.credits += Random.Range(5, 9);
            //         battleNumberLabel.text = fightLevel.ToString();
            //         EnemyBeShopping();
            //
            //         // increase health cause why not
            //         // this is also something that could be good to change
            //         // theoretically we'll eventually have some actual mechanic for increasing health
            //         // enemyShipData.maxHealth += 5;
            //         // playerShipData.maxHealth += 5;
            //         
            //         if (SceneManager.GetActiveScene() != SceneManager.GetSceneByName("Spring Showcase Tutorial"))
            //         {
            //             Invoke(nameof(GoToShop), 1);
            //         }
            //     }
            //     
            // }
        }
        else if (state == State.endScreen)
        {
            // once the timer runs out, just close the damn game
            // TODO: don't quit the game, just go to the main menu or something
            // endScreenTimer -= Time.deltaTime;
            if (endScreenTimer <= 0)
            {
                endScreen.SetActive(false);
                state = State.outOfCombat;
                // SceneManager.LoadScene(SceneManager.GetActiveScene().name);
                // Application.Quit();
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

    private void OnCombatStarted()
    {
        state = State.inCombat;
        ShipManager.Instance.HealPlayerToFull();
    }

    private void OnEnemyDefeated()
    {
        state = State.outOfCombat;
        
        DisplayManager.Instance.Log("Enemy defeated!");
        var scrapWon = Random.Range(5, 10);
        InventoryManager.Instance.scrap += scrapWon;
        EventBus.Instance.playerScrapValueChanged.Invoke();
        EventBus.Instance.constellationAdvanced.Invoke();
        DisplayManager.Instance.Log($"Found {scrapWon} scrap.");
        ShipManager.Instance.HealPlayerToFull();
        fightLevel++;
        
    }

    private void OnPlayerEscaped()
    {
        state = State.outOfCombat;
        DisplayManager.Instance.Log("Player escaped!");
        DisplayManager.Instance.Log("Received 10 scrap from spent escape module.");
        EventBus.Instance.constellationAdvanced.Invoke();
        ShipManager.Instance.HealPlayerToFull();
        fightLevel++;

    }

    private void OnPlayerDefeated()
    {
        EventBus.Instance.constellationReset.Invoke();
    }

    // public IEnumerator Pulsar()
    // {
    //     // play audio
    //     AudioManager.Instance.StartStorm();
    //     
    //     // reset scale of pulse
    //     geomagneticPulse.transform.localScale = Vector3.one;
    //     // turn pulse on
    //     geomagneticPulse.SetActive(true);
    //     
    //     // get sprite renderer component
    //     var sr = geomagneticPulse.GetComponent<SpriteRenderer>();
    //     // reset color/alpha of sprite
    //     var colcol = sr.color;
    //     colcol.a = .6f;
    //     sr.color = colcol;
    //     
    //     // increase scale of pulse until it's at least 30
    //     while (geomagneticPulse.transform.localScale.x < 30)
    //     {
    //         // grow
    //         geomagneticPulse.transform.localScale *= 1 + (Time.deltaTime * 7);
    //         // pause for one frame
    //         yield return null;
    //     }
    //     // once it's grown, randomly stun weapons
    //     foreach (var weapon in playerShip.weapons)
    //     {
    //         // 80% chance to stun each weapon
    //         // feel free to change this number
    //         // TODO: player weapons don't turn yellow when stunned?
    //         // that should probably be a bug in the backlog
    //         var roll = Random.value;
    //         if (roll < 0.8f)
    //         {
    //             // we stun the weapon in a sort of roundabout way by just increasing its stun timer
    //             weapon.GetComponent<Weapon>().stunTimer += 3;
    //         }
    //     }
    //     // same as above, but for the enemy ship
    //     foreach (var weapon in enemyShip.weapons)
    //     {
    //         var roll = Random.value;
    //         if (roll < 0.8f)
    //         {
    //             weapon.GetComponent<Weapon>().stunTimer += 3;
    //         }
    //     }
    //     // once all that's finished, we fade out
    //     while (sr.color.a > 0)
    //     {
    //         // fade a bit
    //         var col = sr.color;
    //         col.a -= Time.deltaTime;
    //         sr.color = col;
    //         // wait one frame
    //         yield return null;
    //     }
    //     // once it's faded all the way out, deactivate it
    //     geomagneticPulse.SetActive(false);
    //
    //     // pause for 2.5 seconds, then stop audio
    //     yield return new WaitForSeconds(2.5f);
    //     AudioManager.Instance.StopStorm();
    //     
    // }

    void GoToShop()
    {
        state = State.outOfCombat;
        endScreen.SetActive(false);
        shop.SetActive(true);
        shop.GetComponent<Shop>().Reroll();
    }

    void GoToMainMenu()
    {
        state = State.outOfCombat;
        SceneManager.LoadScene("MainMenu");
    }
    
    /// <summary>
    /// Adds shields or weapons to the enemy
    /// </summary>
    private void EnemyBeShopping()
    {
        int roll = Random.Range(0,100);

        if (roll < weaponChance)
        {
            // if (newWeapon < enemyShipData.weapons.Count)
            // {
            //     enemyShipData.weapons[newWeapon].SetActive(true);
            //     newWeapon++;
            // } else
            // {
            //     weaponChance = 0;
            // }
        } 
        else if (roll < shieldChance)
        {
            // if (newShield < enemyShipData.shields.Length)
            // {
            //     enemyShipData.shields[newShield].SetActive(true);
            //     //enemyShip.shields[newShield].gameObject.transform.localScale = Vector3.one;
            //     //StartCoroutine(enemyShip.shields[newShield].GetComponent<Shield>().RegenShield());
            //     enemyShipData.shields[newShield].GetComponent<Shield>().StartCoroutine("RegenShield");
            //     Debug.Log("Adding shield to enemy: " + newShield);
            //     newShield++;
            // } 
            // else
            // {
            //     shieldChance = 0;
            // }
        } else
        {
            if (shieldChance > 0)
            {
                shieldChance += 5;
            }
            if (weaponChance > 0)
            {
                weaponChance += 5;
            }
        }

        
    }
}
