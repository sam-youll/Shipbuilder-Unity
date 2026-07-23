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

    public Camera cam;
    
    [Header("Object Lists")] 
    public List<GameObject> allModules = new();
    public List<GameObject> allJacks = new();

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        cam = Camera.main;
        
        Cursor.visible = false;

        
        // cursor = new GameObject("Cursor", typeof(SpriteRenderer))
        // {
        //     transform =
        //     {
        //         parent = transform
        //     },
        //     layer = LayerMask.NameToLayer("UI")
        // };
        // cursor.GetComponent<SpriteRenderer>().sprite = cursorDefault;
        // cursor.GetComponent<SpriteRenderer>().sortingLayerName = "UI";
        
        // selectionReticle = new GameObject("Selection Reticle", typeof(SpriteRenderer))
        // {
        //     transform =
        //     {
        //         parent = transform
        //     },
        //     layer = LayerMask.NameToLayer("UI")
        // };
        // selectionReticle.GetComponent<SpriteRenderer>().sprite = selectionReticleSprite;
        // selectionReticle.GetComponent<SpriteRenderer>().drawMode = SpriteDrawMode.Tiled;
        // selectionReticle.GetComponent<SpriteRenderer>().sortingLayerName = "UI";
        
        // tooltip = Instantiate(Resources.Load<GameObject>("Prefabs/TooltipCanvas"), transform).transform.GetChild(0).gameObject;
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
        // UpdateCursor();
        
        // Debug.Log(TopRaycastResult().name);
        
        // I'm tired of not being able to see the cursor when I'm trying to click on stuff in the
        // hierarchy or the inspector while the game is running, so this is a fix for that.
        Cursor.visible = !cam.rect.Contains(cam.ScreenToViewportPoint(Input.mousePosition));
        
        
    }

    private void LateUpdate()
    {
        return;
        /*
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
        // tooltip.SetActive(tooltipsActive);
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
        */
    }
}
