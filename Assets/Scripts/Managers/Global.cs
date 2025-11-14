using UnityEngine;

public class Global : MonoBehaviour
{
    public static Global Instance { get; private set; }
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

    public RaycastHit2D[] raycastHits = new RaycastHit2D[0];
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

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        cam = Camera.main;
        
        Cursor.visible = false;
        sr = gameObject.AddComponent<SpriteRenderer>();
        sr.sprite = cursorDefault;
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
        foreach (var result in raycastHits)
        {
            if (result.collider.gameObject.CompareTag("Wire") ||
                result.collider.gameObject.layer == LayerMask.NameToLayer("Rack Objects") ||
                result.collider.gameObject.layer == LayerMask.NameToLayer("Module Components"))
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
