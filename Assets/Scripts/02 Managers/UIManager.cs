using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using NUnit.Framework;
using SaintsField;
using SaintsField.Playa;
using TMPro;
using UnityEditor;
using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.SceneManagement;
using UnityEngine.UI;
using Random = UnityEngine.Random;

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
    
    [Header("Canvases")]
    public Canvas shipCanvas;
    public Canvas screenCanvas;
    public Canvas overlayCanvas;

    [Header("MFD Screen")]
    [SerializeField] private GameObject mfdScreen;
    [SerializeField] private Vector3 mfdScreenUpPos;
    [SerializeField] private Vector3 mfdScreenDownPos;
    
    private bool mfdScreenUpDown = false;
    
    [Header("Shop Screen")]
    [SerializeField] private GameObject shopScreen;
    [SerializeField] private Vector3 shopScreenUpPos;
    [SerializeField] private Vector3 shopScreenDownPos;
    
    private bool shopScreenUpDown = false;
    
    private readonly float screenMoveSpeed = 10f;
    
    [Header("Combat Display Elements")] 
    [SerializeField] private GameObject systemPanelPrefab;
    [SerializeField] private Image playerHullBar;
    [SerializeField] private Image enemyHullBar;
    [SerializeField] private GameObject playerSystems;
    [SerializeField] private GameObject enemySystems;
    [SerializeField] private TextMeshProUGUI weaponsReadyCheckText;
    [SerializeField] private TextMeshProUGUI reactorReadyCheckText;
    [SerializeField] private TextMeshProUGUI combatReadyCheckText;
    
    [Header("Shop Display Elements")] 
    [SerializeField] private GameObject shopSlotPrefab;
    [SerializeField] private GridLayoutGroup shopSlotGrid;
    
    private readonly float rerollPrice = 1;
    
    [Header("Pause Menu")]
    [SerializeField] private GameObject pauseMenu;
    
    [Header("Overlay Elements")] 
    [SerializeField] private TextMeshProUGUI scrapCounterLabel;
    [SerializeField] private GameObject cursorPrefab;
    [ReadOnly] public GameCursor cursor;
    [SerializeField] private GameObject tooltipPrefab;
    [SerializeField, ReadOnly] private Tooltip tooltip;
    private float tooltipTimer;
    
    // Mouse Input
    private bool panning;
    private Vector3 panOrigin;
    private Vector3 panOriginCam;
    
    [Header("Show me what you have")]
    [ShowInInspector] private List<GameObject> raycastResults;
    
    private void Start()
    {
        InitShopScreen();
        InitCursor();
        InitTooltip();
    }

    private void Update()
    {
        UpdateCombatDisplay();
        HandleMouseInput();
        CursorStateMachine();
        HandleTooltip();
        UpdateCanvasRaycast();
        UpdateHoverList();
        scrapCounterLabel.text = "Scrap: " + InventoryManager.Instance.scrap.ToString();

        if (Input.GetKeyDown(KeyCode.Escape))
        {
            pauseMenu.SetActive(!pauseMenu.activeSelf);
        }
    }
    
    public void ShowHideScreen()
    {
        StopAllCoroutines();
        StartCoroutine(ShowHideScreenCoroutine());
    }
    
    public void ShowHideShopScreen()
    {
        StopAllCoroutines();
        StartCoroutine(ShowHideShopScreenCoroutine());
    }

    private IEnumerator ShowHideScreenCoroutine()
    {
        var targetPos = mfdScreenUpDown ? mfdScreenUpPos : mfdScreenDownPos;
        mfdScreenUpDown = !mfdScreenUpDown;

        while (mfdScreen.transform.localPosition != targetPos)
        {
            mfdScreen.transform.localPosition = Vector3.Lerp(mfdScreen.transform.localPosition, targetPos, screenMoveSpeed * Time.deltaTime);

            yield return null;
        }
    }
    
    private IEnumerator ShowHideShopScreenCoroutine()
    {
        var targetPos = shopScreenUpDown ? shopScreenUpPos : shopScreenDownPos;
        shopScreenUpDown = !shopScreenUpDown;

        while (shopScreen.transform.localPosition != targetPos)
        {
            shopScreen.transform.localPosition = Vector3.Lerp(shopScreen.transform.localPosition, targetPos, screenMoveSpeed * Time.deltaTime);

            yield return null;
        }
    }

    public void StartCombatFromButton()
    {
        if (!ShipManager.Instance.PlayerReadyForCombat())
        {
            return;
        }
        
        if (!mfdScreenUpDown)
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

        weaponsReadyCheckText.text = ShipManager.Instance.PlayerWeapons().ToList().Exists(x => x.CompletePatch())
            ? "Weapons: Active"
            : "Weapons: Inactive";
        reactorReadyCheckText.text = ShipManager.Instance.PlayerReactor().CompletePatch()
            ? "Reactor: Powered"
            : "Reactor: Unpowered";
        combatReadyCheckText.text = ShipManager.Instance.PlayerReadyForCombat()
            ? "READY FOR COMBAT"
            : "Not ready for combat";
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

    public void InitEnemySystemsDisplay()
    {
        for (var i = 0; i < enemySystems.transform.childCount; i++)
        {
            Destroy(enemySystems.transform.GetChild(i).gameObject);
        }
        
        // create reactor
        var newReactor = Instantiate(systemPanelPrefab, enemySystems.transform);
        newReactor.GetComponent<UISystemPanel>().Setup(ShipManager.Instance.EnemyReactor());
        
        // create weapons
        foreach (var system in ShipManager.Instance.EnemyWeapons())
        {
            var newWeapon = Instantiate(systemPanelPrefab, enemySystems.transform);
            newWeapon.GetComponent<UISystemPanel>().Setup(system);
        }
    }

    public void InitShopScreen()
    {
        for (var i = 0; i < shopSlotGrid.transform.childCount; i++)
        {
            Destroy(shopSlotGrid.transform.GetChild(i).gameObject);
        }
        
        var modulesList = Resources.LoadAll<GameObject>("Prefabs/Modules");
        for (var i = 0; i < 8; i++)
        {
            var newShopSlot = Instantiate(shopSlotPrefab, shopSlotGrid.transform);
            newShopSlot.GetComponent<ShopSlotPanel>().Setup(modulesList[Random.Range(0, modulesList.Length)]);
        }
    }

    public void RerollShop()
    {
        if (InventoryManager.Instance.scrap < rerollPrice)
        {
            return;
        }

        InventoryManager.Instance.scrap -= rerollPrice;
        InitShopScreen();
    }
    
    #region Mouse & Cursor bullshit
    
    private void InitCursor()
    {
        cursor = Instantiate(cursorPrefab, overlayCanvas.transform).GetComponent<GameCursor>();
    }

    private void InitTooltip()
    {
        tooltip = Instantiate(tooltipPrefab, overlayCanvas.transform).GetComponent<Tooltip>();
    }

    private void HandleTooltip()
    {
        GameObject target = null;
        if (cursor.heldObject != null && cursor.heldObject.TryGetComponent(out ITooltipInfo _))
        {
            target = cursor.heldObject;
        }
        else
        {
            target = HoverList().Find(x => x.gameObject != null && x.gameObject.TryGetComponent(out ITooltipInfo _));
        }
        
        if (target != null)
        {
            tooltipTimer -= Time.deltaTime;
            // Debug.Log("tooltipTimer: " + tooltipTimer);
        }
        else
        {
            tooltipTimer = .5f;
        }
        
        if (tooltipTimer <= 0)
        {
            tooltip.gameObject.SetActive(true);
            tooltip.UpdateTooltip(target);
        }
        else
        {
            tooltip.gameObject.SetActive(false);
        }
    }

    private void HandleMouseInput()
    {
        var cam = Global.Instance.cam;
        
        if (Input.GetMouseButtonDown(2))
        {
            panning = true;
            panOrigin = Input.mousePosition;
            panOriginCam = Global.Instance.cam.transform.position;
            // leaving room for other potential checks down the line that may prevent panning
            // (e.g. being in a menu, cutscene, etc.)
        }

        if (panning)
        {
            var delta = Input.mousePosition - panOrigin;
            
            // convert coordinate space from screen to world
            delta.x *= 2 * cam.orthographicSize * cam.aspect;
            delta.y *= 2 * cam.orthographicSize;
            
            delta.x /= Screen.width;
            delta.y /= Screen.height;
            
            // we only want to move in 2D space
            delta.z = 0;

            Global.Instance.cam.transform.position = panOriginCam - delta;
            
        }

        if (Input.mouseScrollDelta.y != 0 &&
            AmIOnlyHittingShipCanvas()) 
        {
            cam.orthographicSize = Mathf.Clamp(cam.orthographicSize - Input.mouseScrollDelta.y, 1.4375f, 16.4375f);
        }
    }
    
    private void CursorStateMachine()
    {
        switch (cursor.state)
        {
            case GameCursor.State.Point:
                // if hit(s), switch to open hand
                if (DidIHitAnythingClickable())
                {
                    cursor.SetState(GameCursor.State.Open);
                }
                // if panning
                if (panning)
                {
                    cursor.SetState(GameCursor.State.Close);
                }
                break;
            case GameCursor.State.Open:
                // if no hits, return to default
                if (!DidIHitAnythingClickable())
                {
                    cursor.SetState(GameCursor.State.Point);
                }
                // if left click, grab
                if (Input.GetMouseButtonDown(0))
                {
                    cursor.SetState(GameCursor.State.Close);
                    cursor.heldObject = TopRaycastResult().gameObject;
                }
                // if panning
                if (panning)
                {
                    cursor.SetState(GameCursor.State.Close);
                }
                break;
            case GameCursor.State.Close:
                // if let go of left mouse button (presumed/possible drop of whatever is being held)
                if (Input.GetMouseButtonUp(0))
                {
                    cursor.SetState(GameCursor.State.Open);
                    cursor.heldObject = null; // TODO: Should this be moved to GameCursor.cs???
                }
                if (!panning && cursor.heldObject == null)
                {
                    cursor.SetState(GameCursor.State.Open);
                }
                else if (cursor.heldObject != null && cursor.heldObject.TryGetComponent(out Jack jack))
                {
                    if (HoverList().Count > 0 && TopRaycastResult().TryGetComponent(out Wire wire))
                    {
                        cursor.heldObject = wire.gameObject;
                    }
                }
                // if not panning anymore
                if (panning && !Input.GetMouseButton(2))
                {
                    cursor.SetState(GameCursor.State.Point);
                    panning = false;
                }
                break;
        }
    }
    
    public GameObject TopRaycastResult()
    {
        if (HoverList().Count > 0)
        {
            return HoverList()[0];
        }

        return null;
    }

    public bool RaycastResultsContains(GameObject go)
    {
        if (HoverList().Contains(go)) return true;
        
        if (CanvasRaycast(out var list))
        {
            if (list.Exists(x => x.gameObject == go)) return true;
        }

        return false;
    }

    public bool RaycastResultsContains(Predicate<GameObject> predicate)
    {
        foreach (var hit in HoverList())
        {
            if (predicate(hit.gameObject)) return true;
        }

        CanvasRaycast(out var list);
        foreach (var hit in list)
        {
            if (predicate(hit.gameObject)) return true;
        }

        return false;
    }
    public bool RaycastResultsContains(Predicate<GameObject> predicate, out GameObject match)
    {
        foreach (var hit in HoverList())
        {
            if (predicate(hit.gameObject))
            {
                match = hit.gameObject;
                return true;
            }
        }

        CanvasRaycast(out var list);
        foreach (var hit in list)
        {
            if (predicate(hit.gameObject))
            {
                match = hit.gameObject;
                return true;
            }
        }

        match = null;
        return false;
    }

    private List<GameObject> HoverList()
    {
        return hoverList;
    }
    private List<GameObject> hoverList = new();
    private void UpdateHoverList()
    {
        var results = new List<GameObject>();
        CanvasRaycast(out var canvasResults);
        foreach (var hit in canvasResults)
        {
            // if (hit.gameObject.TryGetComponent(out ISelectable _) ||
            //     hit.gameObject.TryGetComponent(out Selectable _) ||
            //     hit.gameObject.TryGetComponent())
            // {
            //     results.Add(hit.gameObject);
            // }
            results.Add(hit.gameObject);
        }
        var physCastResults = Physics2D.RaycastAll(Camera.main.ScreenToWorldPoint(Input.mousePosition), Vector2.zero);
        foreach (var hit in physCastResults)
        {
            // results.Add(hit.collider.gameObject);
            if (hit.collider.gameObject.TryGetComponent(out ISelectable _))
            {
                results.Add(hit.collider.gameObject);
            }
            else if (hit.collider.gameObject.TryGetComponent(out ModuleRack _))
            {
                results.Add(hit.collider.gameObject);
            }
        }
        results.Sort((a, b) => a.transform.position.z > b.transform.position.z ? 1 : -1);
        results.Sort((a, b) => a.GetComponentInParent<Canvas>() != null && a.GetComponentInParent<Canvas>().sortingOrder < b.GetComponentInParent<Canvas>().sortingOrder ? 1 : -1);
        raycastResults = new();
        results.ForEach(x => raycastResults.Add(x.gameObject));
        hoverList = results;
    }

    private bool CanvasRaycast(out List<RaycastResult> results)
    {
        results = canvasRaycast;
        return canvasRaycast.Count > 0;
    }
    private List<RaycastResult> canvasRaycast = new();
    private void UpdateCanvasRaycast()
    {
        var results = new List<RaycastResult>();
        
        var pointerEvent = new PointerEventData(EventSystem.current)
        {
            position = Input.mousePosition
        };
        
        var canvasList = new List<Canvas>
        {
            shipCanvas,
            screenCanvas,
            overlayCanvas
        };
        
        foreach (var canvas in canvasList)
        {
            var canvasResults = new List<RaycastResult>();
            canvas.GetComponent<GraphicRaycaster>().Raycast(pointerEvent, canvasResults);
            foreach (var result in canvasResults)
            {
                // TODO: check if result is interactable
                if (result.gameObject.TryGetComponent(out Selectable _))
                {
                    results.Add(result);
                }
                else if (result.gameObject.TryGetComponent(out ISelectable _))
                {
                    results.Add(result);
                }
                else if (result.gameObject.CompareTag("Selectable"))
                {
                    results.Add(result);
                }
            }
        }

        canvasRaycast = results;
    }

    private bool DidIHitAnythingClickable()
    {
        return CanvasRaycast(out _) || HoverList().Count > 0;
    }

    private bool AmIOnlyHittingShipCanvas()
    {
        var results = new List<RaycastResult>();
        
        var pointerEvent = new PointerEventData(EventSystem.current)
        {
            position = Input.mousePosition
        };
        
        var canvasList = new List<Canvas>
        {
            screenCanvas,
            overlayCanvas
        };
        
        foreach (var canvas in canvasList)
        {
            var canvasResults = new List<RaycastResult>();
            canvas.GetComponent<GraphicRaycaster>().Raycast(pointerEvent, canvasResults);
            foreach (var result in canvasResults)
            {
                return false;
            }
        }

        return true;
    }

    public void QuitGame()
    {
        Application.Quit();
    }

    public void ResetScene()
    {
        SceneManager.LoadScene(SceneManager.GetActiveScene().name);
    }

    public void CreativeMode()
    {
        InventoryManager.Instance.creativeMode = true;
        InventoryManager.Instance.LoadCreativeModeModules();
    }
    
    #endregion
}
