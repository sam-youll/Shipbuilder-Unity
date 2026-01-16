using System;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using TMPro;
using UnityEngine;

public class CockpitDisplay : MonoBehaviour
{
    [Header("Text Display")] 
    public TextMeshPro statText;
    public TextMeshPro logText;
    public GameObject damageLabelPrefab;
    
    [Header("Display Icons")] 
    public GameObject playerShip;
    public GameObject playerShield;
    public List<GameObject> playerWeapons;
    public StatBar playerHealthBar;
    public GameObject enemyShip;
    public GameObject enemyShield;
    public List<GameObject> enemyWeapons;
    public StatBar enemyHealthBar;
    public Transform playerDamageLabelTransform;
    public Transform enemyDamageLabelTransform;
    public GameObject questionMarks;

    [Header("Display Properties")] 
    public Color defaultColor;
    public Color inactiveColor;
    public Color shieldColor;
    public Color stunColor;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        EventBus.Instance.displayLogUpdated.AddListener(OnDisplayLogUpdated);
        EventBus.Instance.combatStarted.AddListener(OnCombatStarted);
        EventBus.Instance.playerHit.AddListener(OnPlayerHit);
        EventBus.Instance.enemyHit.AddListener(OnEnemyHit);
        EventBus.Instance.weaponFired.AddListener(OnWeaponFired);
        EventBus.Instance.enemyDefeated.AddListener(OnEnemyDefeated);
        
        DeactivateEnemyIcons();
    }

    void Update()
    {
        for (var i = 0; i < playerWeapons.Count; i++)
        {
            playerWeapons[i].GetComponentInChildren<StatBar>().value = ShipManager.Instance.PlayerWeapons()[i].charge;
        }

        for (var i = 0; i < enemyWeapons.Count; i++)
        {
            enemyWeapons[i].GetComponentInChildren<StatBar>().value = ShipManager.Instance.EnemyWeapons()[i].charge;
        }
        
        
    }

    private void OnDisplayLogUpdated()
    {
        if (DisplayManager.Instance.log.Count <= 0)
            return;
        
        // Log has room for 6 lines of text
        // 255 == FF
        logText.text = "";
        var opacity = 255;
        for (var i = DisplayManager.Instance.log.Count-1; i >= 0; i--)
        {
            var line = DisplayManager.Instance.log[i];
            logText.text += $"<alpha=#{opacity:X2}>"; // X2 converts to hexadecimal
            logText.text += line;
            logText.text += "\n";
            opacity -= 255 / DisplayManager.Instance.log.Count;
        }
    }

    private void OnCombatStarted()
    {
        questionMarks.SetActive(false);
        
        ActivateEnemyIcons();
    }

    private void OnPlayerHit(float damage)
    {
        StartCoroutine(DamageLabelCoroutine(damage, false));
        playerHealthBar.value = ShipManager.Instance.PlayerHull() / ShipManager.Instance.PlayerMaxHull();
    }

    private void OnEnemyHit(float damage)
    {
        // Debug.Log("enemy hit for " + damage);
        StartCoroutine(DamageLabelCoroutine(damage, true));
        enemyHealthBar.value = ShipManager.Instance.EnemyHull() / ShipManager.Instance.EnemyMaxHull();
    }

    private void OnEnemyDefeated()
    {
        DeactivateEnemyIcons();
    }

    private void ActivateEnemyIcons()
    {
        enemyShip.SetActive(true);
        enemyShield.SetActive(true);
        enemyHealthBar.gameObject.SetActive(true);
        enemyShield.SetActive(true);
        foreach (var w in enemyWeapons)
        {
            w.SetActive(true);
        }
    }

    private void DeactivateEnemyIcons()
    {
        enemyShip.SetActive(false);
        enemyShield.SetActive(false);
        enemyHealthBar.gameObject.SetActive(false);
        enemyShield.SetActive(false);
        foreach (var w in enemyWeapons)
        {
            w.SetActive(false);
        }
    }

    private IEnumerator DamageLabelCoroutine(float damage, bool isEnemy)
    {
        var damageLabel = Instantiate(damageLabelPrefab);
        if (isEnemy)
        {
            damageLabel.transform.position = enemyDamageLabelTransform.position;
        }
        else
        {
            damageLabel.transform.position = playerDamageLabelTransform.position;
        }
        
        var textCom = damageLabel.GetComponent<TextMeshPro>();
        if (damage < 0)
        {
            textCom.text = "MISS!";
        }
        else
        {
            textCom.text = "-" + damage;
        }

        textCom.alpha = 1;
        while (textCom.alpha > 0)
        {
            textCom.alpha -= Time.deltaTime * 1.5f;
            var newPos = damageLabel.transform.position;
            newPos.y += Time.deltaTime * .5f;
            damageLabel.transform.position = newPos;
            yield return null;
        }
        
        Destroy(damageLabel);
    }

    private void OnWeaponFired(Weapon weapon)
    {
        GameObject weaponGameObject = null;
        
        if (ShipManager.Instance.PlayerWeapons().Contains(weapon))
        {
            weaponGameObject = playerWeapons[Array.IndexOf(ShipManager.Instance.PlayerWeapons(), weapon)];
        }
        else if (ShipManager.Instance.EnemyWeapons().Contains(weapon))
        {
            weaponGameObject = enemyWeapons[Array.IndexOf(ShipManager.Instance.EnemyWeapons(), weapon)];
        }

        if (weaponGameObject == null)
        {
            Debug.Log("No weapon found in Cockpit Display");
            return;
        }
        
        StartCoroutine(FireWeaponAnimation(weaponGameObject));
    }

    private IEnumerator FireWeaponAnimation(GameObject weapon)
    {
        var sr = weapon.GetComponent<SpriteRenderer>();
        var mainCol = sr.color;
        sr.color = Color.white;
        while (sr.color != mainCol)
        {
            yield return new WaitForSeconds(.05f);
            sr.color = Color.Lerp(sr.color, mainCol, .1f);
        }
    }
}
