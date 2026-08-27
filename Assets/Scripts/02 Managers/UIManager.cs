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
            return;
        }
        else
        {
            Instance = this;
            // DontDestroyOnLoad(gameObject);
        }
    }

    [Header("Properties")] 
    public Rect cameraBounds;
    public float cameraMinSize = 1.4375f;
    public float cameraMaxSize = 12.4375f;
    
    [SerializeField] private bool showBounds;
    
    [Header("Canvases")]
    public Canvas shipCanvas;
    public Canvas screenCanvas;
    public Canvas overlayCanvas;

    [Header("MFD Screen")]
    [SerializeField] private GameObject mfdScreen;
    [SerializeField] private Vector3 mfdScreenUpPos;
    [SerializeField] private Vector3 mfdScreenDownPos;
    
    [ShowInInspector] private bool mfdScreenUpDown = false;
    
    [Header("Shop Screen")]
    [SerializeField] private GameObject shopScreen;
    [SerializeField] private Vector3 shopScreenUpPos;
    [SerializeField] private Vector3 shopScreenDownPos;
    
    [ShowInInspector] private bool shopScreenUpDown = false;
    
    private readonly float screenMoveSpeed = 10f;
    
    [Header("Combat Display Elements")] 
    [SerializeField] private GameObject systemPanelPrefab;
    [SerializeField] private Image playerHullBar;
    [SerializeField] private Image enemyHullBar;
    [SerializeField] private GameObject playerSystems;
    [SerializeField] private GameObject enemySystems;
    [SerializeField] private TextMeshProUGUI combatReadyCheckText;
    [SerializeField] private TextMeshProUGUI warningMessage;
    
    [Header("Shop Display Elements")] 
    [SerializeField] private GameObject shopSlotPrefab;
    [SerializeField] private GridLayoutGroup shopSlotGrid;
    
    private readonly float rerollPrice = 1;

    [Header("Status Readout Elements")] 
    [SerializeField] private GameObject statusReadout;
    [SerializeField] private TextMeshProUGUI statusReadoutText;
    [SerializeField] private Sprite escapeModuleIcon;
    [SerializeField] private Transform escapeModuleCounterParent;
    [SerializeField] private TextMeshProUGUI scrapCounter;
    
    [Header("Constellation Tracker")]
    [SerializeField] private GameObject constellationTracker;
    [SerializeField] private Image constellationIcon;
    [SerializeField] private TextMeshProUGUI constellationTrackerLabel;
    
    [Header("Communicator Components")]
    [SerializeField] private GameObject communicator;
    [SerializeField] private TextMeshProUGUI communicatorText;
    [SerializeField] private Vector3 communicatorOutPos;
    [SerializeField] private Vector3 communicatorStowedPos;
    [ShowInInspector] private bool communicatorOut;
    
    [Header("Quest Log Components")] 
    [SerializeField] private GameObject questLog;
    [SerializeField] private TextMeshProUGUI questLogText;
    [SerializeField] private Vector3 questLogOutPos;
    [SerializeField] private Vector3 questLogStowedPos;

    [ShowInInspector] private bool questLogOut;
    
    [Header("Pause Menu")]
    [SerializeField] private GameObject pauseMenu;
    
    [Header("Overlay Elements")]
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
        
        EventBus.Instance.playerScrapValueChanged.AddListener(OnPlayerScrapValueChanged);
        EventBus.Instance.constellationAdvanced.AddListener(OnConstellationAdvanced);
        OnConstellationAdvanced();
        OnPlayerScrapValueChanged();



        ShowHideQuestLog();
    }

    private void Update()
    {
        UpdateCombatDisplay();
        HandleMouseInput();
        CursorStateMachine();
        HandleTooltip();
        UpdateCanvasRaycast();
        UpdateHoverList();
        UpdateEscapeModuleCounter();

        if (Input.GetKeyDown(KeyCode.Escape))
        {
            pauseMenu.SetActive(!pauseMenu.activeSelf);
        }
    }

    private void UpdateEscapeModuleCounter()
    {
        var escModCount = ShipManager.Instance.PlayerReactor().ModulesOnRack().FindAll(x => x is EscapeModule).Count;
        if (escapeModuleCounterParent.childCount > escModCount)
        {
            DestroyImmediate(escapeModuleCounterParent.transform.GetChild(0).gameObject);
            return;
        }
        else if (escapeModuleCounterParent.childCount < escModCount)
        {
            var newIcon = new GameObject("icon", typeof(Image));
            newIcon.transform.SetParent(escapeModuleCounterParent.transform);
            newIcon.GetComponent<Image>().sprite = escapeModuleIcon;
            newIcon.GetComponent<Image>().preserveAspect = true;
            newIcon.GetComponent<Image>().color = new Color(.7372f, .8666f, .5764f);
            newIcon.GetComponent<RectTransform>().sizeDelta = new Vector2(escapeModuleIcon.texture.width*2/32f, escapeModuleIcon.texture.height*2/32f);
            return;
        }
    }

    private void OnDrawGizmos()
    {
        if (showBounds)
        {
            var topLeft = new Vector2(cameraBounds.x, cameraBounds.y);
            var topRight = new Vector2(cameraBounds.x + cameraBounds.width, cameraBounds.y);
            var bottomRight = new Vector2(cameraBounds.x + cameraBounds.width, cameraBounds.y - cameraBounds.height);
            var bottomLeft = new Vector2(cameraBounds.x, cameraBounds.y - cameraBounds.height);
            Gizmos.DrawLine(topLeft, topRight);
            Gizmos.DrawLine(topRight, bottomRight);
            Gizmos.DrawLine(bottomRight, bottomLeft);
            Gizmos.DrawLine(bottomLeft, topLeft);
        }
    }

    private void OnPlayerScrapValueChanged()
    {
        scrapCounter.text = InventoryManager.Instance.scrap.ToString();
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
    
    public void ShowHideQuestLog()
    {
        StopAllCoroutines();
        StartCoroutine(ShowHideQuestLogCoroutine());
    }

    public void ShowHideCommunicator()
    {
        StopAllCoroutines();
        StartCoroutine(ShowHideCommunicatorCoroutine());
    }

    private IEnumerator ShowHideCommunicatorCoroutine()
    {
        var targetPos = !communicatorOut ? communicatorOutPos : communicatorStowedPos;
        communicatorOut = !communicatorOut;

        while (communicator.transform.position != targetPos)
        {
            communicator.transform.localPosition = Vector3.Lerp(communicator.transform.localPosition, targetPos, screenMoveSpeed * Time.deltaTime);
            
            yield return null;
        }
    }
    private IEnumerator ShowHideScreenCoroutine()
    {
        var targetPos = !mfdScreenUpDown ? mfdScreenUpPos : mfdScreenDownPos;
        mfdScreenUpDown = !mfdScreenUpDown;

        while (mfdScreen.transform.localPosition != targetPos)
        {
            mfdScreen.transform.localPosition = Vector3.Lerp(mfdScreen.transform.localPosition, targetPos, screenMoveSpeed * Time.deltaTime);

            yield return null;
        }
    }
    
    private IEnumerator ShowHideShopScreenCoroutine()
    {
        var targetPos = !shopScreenUpDown ? shopScreenUpPos : shopScreenDownPos;
        shopScreenUpDown = !shopScreenUpDown;

        while (shopScreen.transform.localPosition != targetPos)
        {
            shopScreen.transform.localPosition = Vector3.Lerp(shopScreen.transform.localPosition, targetPos, screenMoveSpeed * Time.deltaTime);

            yield return null;
        }
    }
    
    private IEnumerator ShowHideQuestLogCoroutine()
    {
        var targetPos = questLogOut ? questLogStowedPos : questLogOutPos;
        questLogOut = !questLogOut;

        while (questLog.transform.localPosition != targetPos)
        {
            questLog.transform.localPosition = Vector3.Lerp(questLog.transform.localPosition, targetPos, screenMoveSpeed * Time.deltaTime);

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
        
        combatReadyCheckText.text = ShipManager.Instance.PlayerReadyForCombat()
            ? "READY FOR COMBAT"
            : "Not ready for combat";
        warningMessage.gameObject.SetActive(!ShipManager.Instance.PlayerReadyForCombat());
        
        enemySystems.transform.parent.gameObject.SetActive(CombatManager.Instance.state == CombatManager.State.inCombat);
    }
    
    public void UpdateQuestLog(List<QuestData> activeQuests, List<string> stepsCompleted)
    {
        var text = "";
        foreach (var quest in activeQuests)
        {
            text += quest.questName + "\n";

            foreach (var step in quest.questSteps)
            {
                if (quest.DependenciesCompleted(step.stepName, x => stepsCompleted.Contains(x.stepName)))
                {
                    if (stepsCompleted.Contains(step.stepName))
                    {
                        text += "[x] ";
                    }
                    else
                    {
                        text += "[ ] ";
                    }
                    text += step.objectiveText + "\n";
                }
            }

            text += "\n";
        }
        questLogText.text = text;
        var rt = questLogText.gameObject.GetComponent<RectTransform>();
        rt.sizeDelta = new Vector2(rt.sizeDelta.x, questLogText.textInfo.lineCount * .43f);
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
        for (var i = 0; i < 10; i++)
        {
            var newShopSlot = Instantiate(shopSlotPrefab, shopSlotGrid.transform);
            GameObject moduleToLoad = null;
            if (i == 0 && Random.value < .7f)
            {
                var powerMods = Array.FindAll(modulesList, x => x.TryGetComponent(out PowerModule _));
                moduleToLoad = powerMods[Random.Range(0, powerMods.Length)];
            }
            else if (i == 1 && Random.value < .7f)
            {
                moduleToLoad = Array.Find(modulesList, x => x.TryGetComponent(out ClockModule _));
            }
            else if (i is 2 && Random.value < .7f)
            {
                var converterMods = Array.FindAll(modulesList, x => x.TryGetComponent(out ConverterModule _));
                moduleToLoad = converterMods[Random.Range(0, converterMods.Length)];
            }
            else if (i is 3 && Random.value < .7f)
            {
                var catMods = Array.FindAll(modulesList, x => x.TryGetComponent(out CatalystModule _));
                moduleToLoad = catMods[Random.Range(0, catMods.Length)];
            }
            else if (i is 4 && Random.value < .7f)
            {
                var ventMods = Array.FindAll(modulesList, x => x.TryGetComponent(out VentModule _));
                moduleToLoad = ventMods[Random.Range(0, ventMods.Length)];
            }
            else if (i is 5 && Random.value < .7f)
            {
                var armorMods = Array.FindAll(modulesList, x => x.TryGetComponent(out ArmorModule _));
                moduleToLoad = armorMods[Random.Range(0, armorMods.Length)];
            }
            else
            {
                moduleToLoad = modulesList[Random.Range(0, modulesList.Length)];
                while (!moduleToLoad.GetComponent<Module>().purchasable)
                {
                    moduleToLoad = modulesList[Random.Range(0, modulesList.Length)];
                }
            }
            newShopSlot.GetComponent<ShopSlotPanel>().Setup(moduleToLoad);
        }
    }

    public void RerollShop()
    {
        if (InventoryManager.Instance.scrap < rerollPrice)
        {
            return;
        }

        InventoryManager.Instance.scrap -= rerollPrice;
        EventBus.Instance.playerScrapValueChanged.Invoke();
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
        else if (DidIHitAnythingClickable(out var result))
        {
            target = result;
        }
        /*
        else
        {
            target = HoverList().Find(x => x.gameObject != null && x.gameObject.TryGetComponent(out ITooltipInfo _));
        }
        */
        
        if (target != null)
        {
            tooltipTimer -= Time.deltaTime;
            // Debug.Log("tooltipTimer: " + tooltipTimer);
        }
        else
        {
            tooltipTimer = .5f;
        }
        
        if (tooltipTimer <= 0 && target != null)
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

            var pos = panOriginCam - delta;
            
            // clamp to cameraBounds
            pos.x = Mathf.Clamp(pos.x, cameraBounds.x + cam.orthographicSize * cam.aspect, cameraBounds.x + cameraBounds.width - cam.orthographicSize * cam.aspect);
            pos.y = Mathf.Clamp(pos.y, cameraBounds.y - cameraBounds.height + cam.orthographicSize, cameraBounds.y - cam.orthographicSize);
            
            Global.Instance.cam.transform.position = pos;
        }

        if (Input.mouseScrollDelta.y != 0 &&
            cam.rect.Contains(cam.ScreenToViewportPoint(Input.mousePosition)) &&
            AmIOnlyHittingShipCanvas()) 
        {
            var mousePosBeforeZoom = cam.ScreenToWorldPoint(Input.mousePosition);
            
            cam.orthographicSize = Mathf.Clamp(cam.orthographicSize - Input.mouseScrollDelta.y, cameraMinSize, cameraMaxSize);

            var mousePosAfterZoom = cam.ScreenToWorldPoint(Input.mousePosition);
            
            var pos = Global.Instance.cam.transform.position;
            
            pos += mousePosBeforeZoom - mousePosAfterZoom;
            
            pos.x = Mathf.Clamp(pos.x, cameraBounds.x + cam.orthographicSize * cam.aspect, cameraBounds.x + cameraBounds.width - cam.orthographicSize * cam.aspect);
            pos.y = Mathf.Clamp(pos.y, cameraBounds.y - cameraBounds.height + cam.orthographicSize, cameraBounds.y - cam.orthographicSize);
            Global.Instance.cam.transform.position = pos;
        }
    }
    
    private void CursorStateMachine()
    {
        switch (cursor.state)
        {
            case GameCursor.State.Point:
                // if hit(s), switch to open hand
                if (DidIHitAnythingClickable(out _))
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
                if (!DidIHitAnythingClickable(out _))
                {
                    cursor.SetState(GameCursor.State.Point);
                }
                // if left click, grab
                if (Input.GetMouseButtonDown(0))
                {
                    cursor.SetState(GameCursor.State.Close);
                    if (DidIHitAnythingClickable(out var result))
                    {
                        cursor.heldObject = result;
                    }
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
                    if (HoverList().Count > 0 && DidIHitAnythingClickable(out var result))
                    {
                        if (result.TryGetComponent(out Wire wire))
                        {
                            cursor.heldObject = wire.gameObject;
                        }
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
    [ShowInInspector] private List<GameObject> hoverList = new();
    private void UpdateHoverList()
    {
        var resultsLayer1 = new List<GameObject>();
        var resultsLayer2 = new List<GameObject>();
        var resultsLayer3 = new List<GameObject>();
        CanvasRaycast(out var canvasResults);
        foreach (var hit in canvasResults)
        {
            // if (hit.gameObject.TryGetComponent(out ISelectable _) ||
            //     hit.gameObject.TryGetComponent(out Selectable _) ||
            //     hit.gameObject.TryGetComponent())
            // {
            //     results.Add(hit.gameObject);
            // }
            if (hit.gameObject.GetComponentInParent<Canvas>().sortingOrder == -1)
            {
                resultsLayer1.Add(hit.gameObject);
            }
            else if (hit.gameObject.GetComponentInParent<Canvas>().sortingOrder == 1)
            {
                resultsLayer2.Add(hit.gameObject);
            }
        }
        var physCastResults = Physics2D.RaycastAll(Camera.main.ScreenToWorldPoint(Input.mousePosition), Vector2.zero);
        foreach (var hit in physCastResults)
        {
            // if (canvasResults.Exists(x => x.gameObject.GetComponentInParent<Canvas>() == screenCanvas))
            // {
            //     break;
            // }
            // results.Add(hit.collider.gameObject);
            if (hit.collider.gameObject.TryGetComponent(out ISelectable _))
            {
                if (hit.collider.gameObject.GetComponentInParent<Canvas>() == null)
                {
                    resultsLayer3.Add(hit.collider.gameObject);
                }
                else if (hit.collider.gameObject.GetComponentInParent<Canvas>().sortingOrder == -1)
                {
                    resultsLayer1.Add(hit.collider.gameObject);
                }
                else if (hit.collider.gameObject.GetComponentInParent<Canvas>().sortingOrder == 1)
                {
                    resultsLayer2.Add(hit.collider.gameObject);
                }
            }
            else if (hit.collider.gameObject.TryGetComponent(out ModuleRack _))
            {
                if (hit.collider.gameObject.GetComponentInParent<Canvas>() == null)
                {
                    resultsLayer3.Add(hit.collider.gameObject);
                }
                else if (hit.collider.gameObject.GetComponentInParent<Canvas>().sortingOrder == -1)
                {
                    resultsLayer1.Add(hit.collider.gameObject);
                }
                else if (hit.collider.gameObject.GetComponentInParent<Canvas>().sortingOrder == 1)
                {
                    resultsLayer2.Add(hit.collider.gameObject);
                }
            }
        }
        resultsLayer1.Sort((a, b) => a.transform.position.z > b.transform.position.z ? 1 : -1);
        resultsLayer2.Sort((a, b) => a.transform.position.z > b.transform.position.z ? 1 : -1);
        var results = resultsLayer3;
        resultsLayer2.ForEach(x => results.Add(x));
        resultsLayer1.ForEach(x => results.Add(x));
        // results.Sort((a, b) => a.GetComponentInParent<Canvas>() != null && b.GetComponentInParent<Canvas>() != null && a.GetComponentInParent<Canvas>().sortingOrder < b.GetComponentInParent<Canvas>().sortingOrder ? 1 : -1);
        raycastResults = new();
        results.ForEach(x => raycastResults.Add(x.gameObject));
        hoverList = results;
    }

    private bool CanvasRaycast(out List<RaycastResult> results)
    {
        results = canvasRaycast;
        return canvasRaycast.Count > 0;
    }
    [ShowInInspector] private List<RaycastResult> canvasRaycast = new();
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
                results.Add(result);
                continue;
                
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

    private bool DidIHitAnythingClickable(out GameObject hit)
    {
        if (TopRaycastResult() != null)
        {
            var result = TopRaycastResult();
            if (result.TryGetComponent(out Collider2D _))
            {
                hit = result;
                return true;
            }
            else if (result.TryGetComponent(out UIBehaviour ui))
            {
                if (ui is Selectable _)
                {
                    hit = result;
                    return true;
                }
                else if (result.GetComponentInParent<Selectable>() != null)
                {
                    hit = result.GetComponentInParent<Selectable>().gameObject;
                    return true;
                }
                else if (result.CompareTag("Selectable"))
                {
                    hit = result;
                    return true;
                }
                if (result.name == "bg")
                {
                    hit = HoverList().Find(x => x.CompareTag("Selectable"));
                    if (hit == null) return false;
                    if (hit.name == "Item Panel") hit = hit.transform.parent.gameObject;
                    return true;
                }
            }
        }

        hit = null;
        return false;
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
        SceneManager.LoadScene("MainMenu", LoadSceneMode.Single);
        AudioManager.Instance.ReleaseFMODInstances();
    }

    public void ResetScene()
    {
        SceneManager.LoadScene(SceneManager.GetActiveScene().name);
    }

    public void CreativeMode()
    {
        InventoryManager.Instance.creativeMode = true;
        InventoryManager.Instance.LoadCreativeModeModules();
        pauseMenu.SetActive(false);
    }

    private void OnConstellationAdvanced()
    {
        var constellationName = Enum.GetName(typeof(GameStateManager.Constellation),
            GameStateManager.Instance.currentConstellation);
        // Debug.Log(constellationName);
        constellationIcon.sprite = Resources.Load<Sprite>("Sprites/" + constellationName);
        constellationTrackerLabel.text = constellationName;
    }
    
    #endregion
}
