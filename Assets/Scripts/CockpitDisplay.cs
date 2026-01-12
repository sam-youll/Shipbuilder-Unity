using System.Collections;
using System.Collections.Generic;
using System.Globalization;
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
    public GameObject enemyShip;
    public GameObject enemyShield;
    public Transform playerDamageLabelTransform;
    public Transform enemyDamageLabelTransform;

    [Header("Display Properties")] 
    public Color defaultColor;
    public Color inactiveColor;
    public Color shieldColor;
    public Color stunColor;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        EventBus.Instance.displayLogUpdated.AddListener(SetLogText);
        EventBus.Instance.playerHit.AddListener(OnPlayerHit);
        EventBus.Instance.enemyHit.AddListener(OnEnemyHit);
    }

    private void SetLogText()
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
            logText.text += $"<alpha=#{opacity.ToString("X2")}>";
            logText.text += line;
            logText.text += "\n";
            opacity -= 255 / DisplayManager.Instance.log.Count;
        }
    }

    private void OnPlayerHit(float damage)
    {
        StartCoroutine(DamageLabelCoroutine(damage, false));
    }

    private void OnEnemyHit(float damage)
    {
        StartCoroutine(DamageLabelCoroutine(damage, true));
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
            textCom.alpha -= Time.deltaTime;
            var newPos = damageLabel.transform.position;
            newPos.y += Time.deltaTime * 1.5f;
            damageLabel.transform.position = newPos;
            yield return null;
        }
        
        Destroy(damageLabel);
    }
}
