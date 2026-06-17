using System;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.InputSystem;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class Global : MonoBehaviour
{
    public static Global Instance { get; private set; }
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

    public RaycastHit2D[] raycastHits = Array.Empty<RaycastHit2D>();
    public Vector3 mousePos = Vector3.zero;
    public Camera cam;
    
    [Header("UI Sprites")]
    public Sprite cursorDefault;
    public Sprite cursorGrabOpen;
    public Sprite cursorGrabClose;
    public Sprite selectionReticleSprite;
    private GameObject cursor;
    private GameObject selectionReticle;
    private GameObject tooltip;

    public enum CursorState
    {
        Default,
        GrabOpen,
        GrabClose
    }
    public CursorState cursorState = CursorState.Default;
    private bool cursorLocked;
    private float tooltipPopupTimer;
    private GameObject currentTooltipTarget;
    private GameObject grabbedObject;

    [Header("Object Lists")] 
    public List<GameObject> hoverList = new();
    public List<GameObject> allModules = new();
    public List<GameObject> allJacks = new();

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        cam = Camera.main;
        
        Cursor.visible = false;

        cursor = new GameObject("Cursor", typeof(SpriteRenderer))
        {
            transform =
            {
                parent = transform
            },
            layer = LayerMask.NameToLayer("UI")
        };
        cursor.GetComponent<SpriteRenderer>().sprite = cursorDefault;
        cursor.GetComponent<SpriteRenderer>().sortingLayerName = "UI";
        
        selectionReticle = new GameObject("Selection Reticle", typeof(SpriteRenderer))
        {
            transform =
            {
                parent = transform
            },
            layer = LayerMask.NameToLayer("UI")
        };
        selectionReticle.GetComponent<SpriteRenderer>().sprite = selectionReticleSprite;
        selectionReticle.GetComponent<SpriteRenderer>().drawMode = SpriteDrawMode.Tiled;
        selectionReticle.GetComponent<SpriteRenderer>().sortingLayerName = "UI";
        
        tooltip = Instantiate(Resources.Load<GameObject>("Prefabs/TooltipCanvas"), transform).transform.GetChild(0).gameObject;
        // tooltip.GetComponent<SpriteRenderer>().sortingLayerName = "UI";
        // tooltip.GetComponentInChildren<MeshRenderer>().sortingLayerName = "UI";

        SceneManager.sceneLoaded += OnSceneLoaded;
        
        EventBus.Instance.loadScene.AddListener(OnLoadScene);
        EventBus.Instance.gameExit.AddListener(OnGameExit);
    }

    private void OnLoadScene(string sceneName)
    {
        SceneManager.LoadScene(sceneName);
    }

    private void OnGameExit()
    {
        Application.Quit();
    }

    public void OnSceneLoaded(Scene scene, LoadSceneMode mode)
    {
        cam = Camera.main;
        
        Debug.Log(scene.name + " loaded");
    }

    // Update is called once per frame
    void Update()
    {
        // Cursor
        UpdateCursor();
        
        // Debug.Log(TopRaycastResult().name);
        
        // I'm tired of not being able to see the cursor when I'm trying to click on stuff in the
        // hierarchy or the inspector while the game is running, so this is a fix for that.
        Cursor.visible = !cam.rect.Contains(cam.ScreenToViewportPoint(Input.mousePosition));
    }

    private void LateUpdate()
    {
        // Selection Reticle & Tooltip
        var tooltipUnderMouse = false;
        if (hoverList.Count > 0)
        {
            foreach (var item in hoverList)
            {
                if (item.TryGetComponent(out ITooltipInfo tooltipInfo))
                {
                    tooltipUnderMouse = true;
                }
            }
        }

        if (grabbedObject != null)
        {
            tooltipUnderMouse = true;
        }

        if (tooltipUnderMouse)
        {
            tooltipPopupTimer -= Time.deltaTime;
        }
        else
        {
            tooltipPopupTimer = 1f;
        }

        var tooltipsActive = tooltipPopupTimer <= 0;
        
        selectionReticle.SetActive(false);
        tooltip.SetActive(tooltipsActive);
        if (tooltipsActive)
        {
            GameObject selectedItem;
            if (grabbedObject != null)
            {
                selectedItem = grabbedObject;
            }
            else
            {
                selectedItem = hoverList[0];
                foreach (var itemm in hoverList)
                {
                    if (itemm.TryGetComponent(out ITooltipInfo tooltipInfo))
                    {
                        selectedItem = itemm;
                    }
                }

                foreach (var item in hoverList)
                {
                    if (selectedItem.TryGetComponent(out ITooltipInfo tooltipInfo) &&
                        selectedItem.transform.position.z >= item.transform.position.z)
                    {
                        selectedItem = item;
                        selectionReticle.GetComponent<SpriteRenderer>().size = new Vector2(
                            item.GetComponent<Collider2D>().bounds.size.x + 1,
                            item.GetComponent<Collider2D>().bounds.size.y + 1);
                        selectionReticle.transform.position = item.GetComponent<Collider2D>().bounds.center;
                        var vector3 = selectionReticle.transform.position;
                        vector3.z = item.transform.position.z - .1f;
                        selectionReticle.transform.position = vector3;
                    }
                }
            }
            
            tooltip.GetComponent<Tooltip>().UpdateTooltip(selectedItem);
        }
    }

    private void UpdateCursor()
    {
        if (cursorLocked)
            return;
        
        // move cursor to mouse position
        mousePos = cam.ScreenToWorldPoint(Input.mousePosition);
        mousePos.z = -5;
        cursor.transform.position = mousePos;
        
        // test for colliders under mouse
        raycastHits = Physics2D.RaycastAll(mousePos, Vector2.zero);
        //Set up the new Pointer Event
        var m_EventSystem = EventSystem.current;
        var m_PointerEventData = new PointerEventData(m_EventSystem);
        //Set the Pointer Event Position to that of the mouse position
        m_PointerEventData.position = Input.mousePosition;
        var graphicRaycastHits = new List<RaycastResult>();
        var gRaycaster = UIManager.Instance.shipCanvas.GetComponent<GraphicRaycaster>();
        gRaycaster.Raycast(m_PointerEventData, graphicRaycastHits);
        
        // test if colliders are grabbable
        var hitGrabbable = false;
        hoverList.Clear();
        foreach (var result in raycastHits)
        {
            var coll = result.collider;
            if (coll.compositeOperation == Collider2D.CompositeOperation.Merge)
            {
                coll = coll.composite;
            }
            if (coll.gameObject.layer == LayerMask.NameToLayer("Particles"))
                continue;
            hoverList.Add(coll.gameObject);
            if (TopRaycastResult().CompareTag("Wire") ||
                TopRaycastResult().CompareTag("Button") ||
                TopRaycastResult().layer == LayerMask.NameToLayer("Rack Objects") ||
                TopRaycastResult().layer == LayerMask.NameToLayer("Jacks") ||
                TopRaycastResult().layer == LayerMask.NameToLayer("Module Components"))
            {
                hitGrabbable = true;
            }
        }
        foreach (var result in graphicRaycastHits)
        {
            var obj = result.gameObject;
            if (obj.TryGetComponent(out Button button))
            {
                hoverList.Add(obj.gameObject);
                hitGrabbable = true;
            }
        }
        
        // set cursor visual state
        var sr = cursor.GetComponent<SpriteRenderer>();
        switch (cursorState)
        {
            case CursorState.Default:
                if (hitGrabbable)
                {
                    sr.sprite = cursorGrabOpen;
                    cursorState = CursorState.GrabOpen;
                }
                break;
            case CursorState.GrabOpen:
                if (!hitGrabbable)
                {
                    sr.sprite = cursorDefault;
                    cursorState = CursorState.Default;
                }
                if (Input.GetMouseButtonDown(0))
                {
                    sr.sprite = cursorGrabClose;
                    cursorState = CursorState.GrabClose;
                    grabbedObject = TopRaycastResult().gameObject;
                }
                break;
            case CursorState.GrabClose:
                if (grabbedObject == null)
                {
                    sr.sprite = cursorGrabOpen;
                    cursorState = CursorState.GrabOpen;
                }
                else if (grabbedObject.TryGetComponent(out Jack jack))
                {
                    if (TopRaycastResult().TryGetComponent(out Wire wire))
                    {
                        grabbedObject = wire.gameObject;
                    }
                }
                if (Input.GetMouseButtonUp(0))
                {
                    sr.sprite = cursorGrabOpen;
                    cursorState = CursorState.GrabOpen;
                    grabbedObject = null;
                }
                break;
        }
    }

    public bool RaycastResultsContains(GameObject obj)
    {
        if (raycastHits.Length == 0)
            return false;
        
        var containsObj = false;

        foreach (var result in  raycastHits)
        {
            if (result.collider == null)
                continue;
            
            if (result.collider.gameObject == obj)
            {
                containsObj = true;
            }
        }

        return containsObj;
    }

    public GameObject TopRaycastResult()
    {
        if (hoverList.Count == 0) return null;

        if (hoverList.Count == 1) return hoverList[0];

        var topObj = hoverList[0];
        foreach (var result in hoverList)
        {
            // TODO: fix left click + right click bug
            // vvv this didn't really work vvv
            // if (result == null) continue;
            
            if (result.transform.position.z <= topObj.transform.position.z)
            {
                topObj = result;
            }
        }
        return topObj;
    }

    /// <summary>
    /// Instantiates a tooltip at the desired position.
    /// </summary>
    /// <param name="position">Position to instantiate the tooltip.</param>
    /// <param name="text">Content of the tooltip.</param>
    public GameObject InstantiateTooltip(Vector2 position, string text)
    {
        var tooltip = Instantiate(Resources.Load<GameObject>("Prefabs/Tooltip"), transform);
        tooltip.transform.position = position;
        tooltip.name = text;
        tooltip.GetComponent<Tooltip>().SetText(text);
        return tooltip;
    }

    public void LockCursor(bool locked)
    {
        cursorLocked = locked;

        if (!locked)
        {
            Mouse.current.WarpCursorPosition(cam.WorldToScreenPoint(cursor.transform.position));
            // Debug.Log($"Returning actual cursor ({Mouse.current}) to {cursor.transform.position}");
        }
    }
}
