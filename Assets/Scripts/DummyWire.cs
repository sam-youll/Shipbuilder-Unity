using UnityEngine;

public class DummyWire : MonoBehaviour
{
    LineRenderer lineRenderer;

    public int points = 7;
    public GameObject start;
    public GameObject end;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
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
                targetPositions[0] = start.transform.position;
            }
            else if (i == points - 1)
            {
                targetPositions[i] = end.transform.position;
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
        
        Vector3[] adjTargetPositions = new Vector3[points];
        for (int i = 0; i < points; i++)
        {
            adjTargetPositions[i] = targetPositions[i];
            adjTargetPositions[i].z = -.1f;
        }

        // apply points
        for (int i = 0; i < points; i++)
        {
            lineRenderer.SetPosition(i, adjTargetPositions[i]);
        }
    }
}
