using UnityEngine;

public class ScopeDraw : MonoBehaviour
{
    public LineRenderer lineRenderer;
    public GameObject module;
    public int points;
    public float frequency;
    public float amplitude;
    public Vector2 xLimits = new Vector2(0, 1);

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        lineRenderer = GetComponent<LineRenderer>();
    }

    // Update is called once per frame
    void Update()
    {
        Draw();
    }

    void Draw()
    {
        //if (module.GetComponent<Module>().source = 2)
        //{
            float xStart = 0;
            float Tau = 2 * Mathf.PI * frequency;
            float xFinish = Tau;

            lineRenderer.positionCount = points;

            for (int currentPoint = 0; currentPoint < points; currentPoint++)
            {
                float progress = (float)currentPoint / (points - 1);
                float x = Mathf.Lerp(xStart, xFinish, progress);
                float y = amplitude * Mathf.Sin(x);
                lineRenderer.SetPosition(currentPoint, new Vector3(x, y, 0));
            }
        //}

    }
}
