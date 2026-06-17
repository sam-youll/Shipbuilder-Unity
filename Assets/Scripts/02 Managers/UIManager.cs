using System.Collections;
using System.Collections.Generic;
using SaintsField;
using UnityEngine;
using UnityEngine.UI;

public class UIManager : MonoBehaviour
{
    public static UIManager Instance;
    private void Awake()
    {
        if (Instance != null && Instance != this)
        {
            Destroy(gameObject);
        }
        else
        {
            Instance = this;
            DontDestroyOnLoad(this);
        }
    }
    
    public Canvas shipCanvas;
    public Canvas menuCanvas;
    public Canvas overlayCanvas;

    public GameObject cockpitScreen;
    public Vector3 screenUpPos;
    public Vector3 screenDownPos;
    [Range(10, 100)] public float screenMoveSpeed = 50f;
    private bool screenUpDown;

    [Header("Combat Display Elements")] 
    public GameObject systemPanelPrefab;
    public GameObject combatDisplayRoot;
    public Image playerHullBar;
    public Image enemyHullBar;
    public GameObject playerSystems;
    public GameObject enemySystems;
    
    private void Update()
    {
        UpdateCombatDisplay();
    }
    
    public void ShowHideScreen()
    {
        StopAllCoroutines();
        StartCoroutine(ShowHideScreenCoroutine());
    }

    private IEnumerator ShowHideScreenCoroutine()
    {
        var targetPos = screenUpDown ? screenUpPos : screenDownPos;
        screenUpDown = !screenUpDown;

        while (cockpitScreen.transform.localPosition != targetPos)
        {
            cockpitScreen.transform.localPosition = Vector3.Lerp(cockpitScreen.transform.localPosition, targetPos, screenMoveSpeed * Time.deltaTime);

            yield return null;
        }
    }

    public void StartCombatFromButton()
    {
        if (!screenUpDown)
        {
            ShowHideScreen();
        }
        
        EventBus.Instance.combatStarted.Invoke();
    }

    private void UpdateCombatDisplay()
    {
        for (var i = 0; i < playerSystems.transform.childCount; i++)
        {
        }
        
        playerHullBar.fillAmount = ShipManager.Instance.PlayerCurrentHull() / ShipManager.Instance.PlayerMaxHull();
        enemyHullBar.fillAmount = ShipManager.Instance.EnemyHull() / ShipManager.Instance.EnemyMaxHull();
    }

    private void InitCombatDisplay()
    {
        for (var i = 0; i < enemySystems.transform.childCount; i++)
        {
            Destroy(enemySystems.transform.GetChild(i).gameObject);
        }
    }

    public void InitPlayerSystemsDisplay()
    {
        for (var i = 0; i < playerSystems.transform.childCount; i++)
        {
            Destroy(playerSystems.transform.GetChild(i).gameObject);
        }
        
        // create reactor
        var newReactor = Instantiate(systemPanelPrefab, playerSystems.transform);
        newReactor.GetComponent<UISystemPanel>().Setup(ShipManager.Instance.PlayerReactor());
        
        // create weapons
        foreach (var system in ShipManager.Instance.PlayerWeapons())
        {
            var newWeapon = Instantiate(systemPanelPrefab, playerSystems.transform);
            newWeapon.GetComponent<UISystemPanel>().Setup(system);
        }
    }
}
