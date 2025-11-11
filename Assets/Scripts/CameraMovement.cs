using UnityEngine;

public class CameraMovement : MonoBehaviour
{
    private Vector3 startPos;

    private float startSize;

    private Camera cam;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        startPos = transform.position;
        cam = GetComponent<Camera>();
        startSize = cam.orthographicSize;
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Alpha0))
        {
            transform.position = startPos;
            GetComponent<Camera>().orthographicSize = startSize;
        }

        cam.orthographicSize -= Input.GetAxis("Mouse ScrollWheel")*4;
        cam.orthographicSize = Mathf.Clamp(cam.orthographicSize, 1f, startSize);
        
        var z = transform.position.z;
        var dir = (Vector2)transform.position + new Vector2(Input.GetAxis("Horizontal"), Input.GetAxis("Vertical"))*(cam.orthographicSize/startSize);
        var pos = new Vector3(Vector2.Lerp(transform.position, dir, .2f).x, Vector2.Lerp(transform.position, dir, .2f).y, z);
        transform.position = pos;
        
        
    }
}
