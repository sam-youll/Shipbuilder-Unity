using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Rendering.Universal;

public class CameraMovement : MonoBehaviour
{
    private Vector3 startPos;

    private float startSize;

    public List<Vector2Int> resolutions = new List<Vector2Int>();
    private int resIndex;
    
    private Camera cam;
    private PixelPerfectCamera ppCam;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        startPos = transform.position;
        cam = GetComponent<Camera>();
        startSize = cam.orthographicSize;
        ppCam = GetComponent<PixelPerfectCamera>();
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.UpArrow))
        {
            resIndex++;
        }
        else if (Input.GetKeyDown(KeyCode.DownArrow))
        {
            resIndex--;
        }
        resIndex = Mathf.Clamp(resIndex, 0, resolutions.Count - 1);
        
        ppCam.refResolutionX = resolutions[resIndex].x;
        ppCam.refResolutionY = resolutions[resIndex].y;
    }
}
