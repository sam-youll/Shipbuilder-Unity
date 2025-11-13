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

    public RaycastHit2D[] raycastHits;
    public Vector3 mousePos;
    public Camera cam;

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        cam = Camera.main;
    }

    // Update is called once per frame
    void Update()
    {
        mousePos = cam.ScreenToWorldPoint(Input.mousePosition);
        mousePos.z = -5;
        
        raycastHits = Physics2D.RaycastAll(mousePos, Vector2.zero);
    }
}
