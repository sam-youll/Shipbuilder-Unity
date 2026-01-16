using System;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

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
    
    public Sprite cursorDefault;
    public Sprite cursorGrabOpen;
    public Sprite cursorGrabClose;

    public enum CursorState
    {
        Default,
        GrabOpen,
        GrabClose
    }
    public CursorState cursorState = CursorState.Default;

    private SpriteRenderer sr;

    [Header("Object Lists")] 
    public List<GameObject> hoverList = new();
    public List<GameObject> allModules = new();
    public List<GameObject> allJacks = new();

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        cam = Camera.main;
        
        Cursor.visible = false;
        sr = gameObject.AddComponent<SpriteRenderer>();
        sr.sprite = cursorDefault;
        sr.sortingLayerName = "UI";

        SceneManager.sceneLoaded += OnSceneLoaded;
    }

    public void OnSceneLoaded(Scene scene, LoadSceneMode mode)
    {
        cam = Camera.main;
        
        Debug.Log(scene.name + " loaded");
    }

    // Update is called once per frame
    void Update()
    {
        mousePos = cam.ScreenToWorldPoint(Input.mousePosition);
        mousePos.z = -5;
        
        raycastHits = Physics2D.RaycastAll(mousePos, Vector2.zero);

        // Cursor
        transform.position = mousePos;
        var hitGrabbable = false;
        hoverList.Clear();
        foreach (var result in raycastHits)
        {
            var coll = result.collider;
            if (coll.compositeOperation == Collider2D.CompositeOperation.Merge)
            {
                coll = coll.composite;
            }
            hoverList.Add(coll.gameObject);
            if (coll.gameObject.CompareTag("Wire") ||
				coll.gameObject.CompareTag("Button") ||
                coll.gameObject.layer == LayerMask.NameToLayer("Rack Objects") ||
				coll.gameObject.layer == LayerMask.NameToLayer("Jacks") ||
                coll.gameObject.layer == LayerMask.NameToLayer("Module Components"))
            {
                hitGrabbable = true;
            }
        }
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
                }
                break;
            case CursorState.GrabClose:
                if (Input.GetMouseButtonUp(0))
                {
                    sr.sprite = cursorGrabOpen;
                    cursorState = CursorState.GrabOpen;
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
}
