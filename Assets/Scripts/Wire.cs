using System;
using UnityEngine;
using UnityEngine.Serialization;

public class Wire : MonoBehaviour
{
    public int points = 7;

    private GameObject previousModule;
    private GameObject previousModuleJack;
    private GameObject nextModule;
    private GameObject nextModuleJack;
    private GameObject sourceModule;
    
    private LineRenderer lineRenderer;

    private bool connectedToModule = false;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        previousModuleJack = transform.parent.gameObject;
        previousModule = previousModuleJack.transform.parent.gameObject;
        sourceModule = previousModule.GetComponent<BaseModule>().sourceModule;
        lineRenderer = GetComponent<LineRenderer>();
        lineRenderer.positionCount = points;
        for (int i = 0; i < points; i++)
        {
            lineRenderer.SetPosition(i, transform.position);
        }
    }

    // Update is called once per frame
    void Update()
    {
        // either connect or destroy wire
        if (Input.GetMouseButtonUp(0) && !connectedToModule)
        {
            Vector2 mousePos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
            RaycastHit2D hit = Physics2D.Raycast(mousePos, Vector2.zero, Mathf.Infinity, LayerMask.GetMask("Jacks"));
            if (hit)
            {
                nextModuleJack = hit.collider.gameObject;
                nextModule = nextModuleJack.transform.parent.gameObject;
                previousModule.GetComponent<BaseModule>().nextModule = nextModule;
                connectedToModule = true;
                PatchManager.Instance.UpdatePatch(sourceModule);
            }
            else
            {
                previousModule.GetComponent<BaseModule>().nextModule = null;
                PatchManager.Instance.UpdatePatch(sourceModule);
                Destroy(gameObject);
            }
        }
        
        UpdatePoints();
    }

    private void UpdatePoints()
    {
        // calculate points
        Vector2[] targetPositions = new Vector2[points];
        for (int i = 0; i < points; i++)
        {
            if (i == 0)
            {
                targetPositions[0] = previousModuleJack.transform.position;
            }
            else if (i == points - 1)
            {
                if (connectedToModule)
                {
                    targetPositions[i] = nextModuleJack.transform.position;
                }
                else
                {
                    targetPositions[i] = Camera.main.ScreenToWorldPoint(Input.mousePosition);
                }
            }
            else
            {
                Vector2 pos = lineRenderer.GetPosition(i);
                Vector2 targetPos = (lineRenderer.GetPosition(i + 1) + lineRenderer.GetPosition(i - 1))*.5f;
                targetPos += .1f * Vector2.down;
                pos = Vector2.Lerp(pos, targetPos, .2f);
                targetPositions[i] = pos;
            }
        }

        // apply points
        for (int i = 0; i < points; i++)
        {
            lineRenderer.SetPosition(i, targetPositions[i]);
        }
    }
}
