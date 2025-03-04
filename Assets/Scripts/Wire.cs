using System;
using UnityEngine;
using UnityEngine.Serialization;

public class Wire : MonoBehaviour
{
    public int points = 7;

    public GameObject previousModule;
    public GameObject previousModuleJack;
    public GameObject nextModule;
    public GameObject nextModuleJack;
    private GameObject sourceModule;
    
    private LineRenderer lineRenderer;

    private bool connectedToModule = false;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        previousModuleJack = transform.parent.gameObject;
        previousModule = previousModuleJack.transform.parent.gameObject;
        sourceModule = previousModule.GetComponent<Module>().sourceModule;
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
                if (hit.collider.gameObject.transform.parent.gameObject.CompareTag("OutputRack"))
                {
                    var outputRack = hit.collider.gameObject.transform.parent.gameObject.GetComponent<OutputRack>();
                    int index = -1;
                    for (int i = 0; i < 6; i++)
                    {
                        if (hit.collider.gameObject == outputRack.weaponOutputs[i])
                        {
                            index = i;
                        }
                    }
                    for (int i = 6; i < 12; i++)
                    {
                        if (hit.collider.gameObject == outputRack.shieldOutputs[i-6])
                        {
                            index = i;
                        }
                    }
                    nextModuleJack = hit.collider.gameObject;
                    nextModule = nextModuleJack.transform.parent.gameObject;
                    previousModule.GetComponent<Module>().nextModule = nextModule;
                    if (index == -1)
                    {
                        Debug.Log("Couldn't find output.");
                    }
                    else if (index < 6 && outputRack.previousModsWeapons[index] != null)
                    {
                        outputRack.previousModsWeapons[index].GetComponent<Module>().outputJack.transform.GetChild(0).gameObject.GetComponent<Wire>().DeleteSelf();
                    }
                    else if (index >= 6 && outputRack.previousModsShields[index-6] != null)
                    {
                        outputRack.previousModsShields[index-6].GetComponent<Module>().outputJack.transform.GetChild(0).gameObject.GetComponent<Wire>().DeleteSelf();
                    }
                    else if (index < 6)
                    {
                        outputRack.previousModsWeapons[index] = previousModule;
                    }
                    else if (index < 12)
                    {
                        outputRack.previousModsShields[index-6] = previousModule;
                    }
                    connectedToModule = true;
                    PatchManager.Instance.UpdateAllPatches();
                }
                else if (hit.collider.gameObject.CompareTag("InputJack"))
                {
                    nextModuleJack = hit.collider.gameObject;
                    nextModule = nextModuleJack.transform.parent.gameObject;
                    previousModule.GetComponent<Module>().nextModule = nextModule;
                    if (nextModule.GetComponent<Module>().previousModule != null)
                    {
                        nextModule.GetComponent<Module>().previousModule.GetComponent<Module>().outputJack.transform.GetChild(0).gameObject.GetComponent<Wire>().DeleteSelf();
                    }
                    nextModule.GetComponent<Module>().previousModule = previousModule;
                    connectedToModule = true;
                    PatchManager.Instance.UpdateAllPatches();
                }
                else
                {
                    DeleteSelf();
                }
            }
            else
            {
                DeleteSelf();
            }
        }
    }

    private void FixedUpdate()
    {
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
                pos = Vector2.Lerp(pos, targetPos, .6f);
                targetPositions[i] = pos;
            }
        }

        // apply points
        for (int i = 0; i < points; i++)
        {
            lineRenderer.SetPosition(i, targetPositions[i]);
        }
    }

    public void DeleteSelf()
    {
        if (connectedToModule)
        {
            if (nextModule.CompareTag("OutputRack"))
            {
                var outputRack = nextModule.GetComponent<OutputRack>();
                for (int i = 0; i < 6; i++)
                {
                    if (previousModule == outputRack.previousModsWeapons[i])
                    {
                        outputRack.previousModsWeapons[i] = null;
                    }
                }
                for (int i = 6; i < 12; i++)
                {
                    if (previousModule == outputRack.previousModsShields[i-6])
                    {
                        outputRack.previousModsShields[i-6] = null;
                    }
                }
            }
            else
            {
                nextModule.GetComponent<Module>().previousModule = null;
            }
        }
        previousModule.GetComponent<Module>().nextModule = null;
        PatchManager.Instance.UpdateAllPatches();
        Destroy(gameObject);
    }
}
