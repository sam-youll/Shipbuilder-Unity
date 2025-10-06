using System.Collections.Generic;
using UnityEditor;
using UnityEngine;
using UnityEngine.Events;

public class Knob : MonoBehaviour
{
    private UnityEvent<int> onValueChanged;

    private bool grabbed = false;
    
    [SerializeField]
    private int maxValue = 0;
    public int MaxValue
    {
        get => maxValue;
        set
        {
            maxValue = value;
            UpdateMaxValue(value);
        }
    }
    
    public float rangeAngle = 1.5f *  Mathf.PI;
    private List<GameObject> notchLRs = new();

    public float trueValue;
    public float value;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        UpdateMaxValue(maxValue);
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetMouseButtonDown(0))
        {
            var results = Physics2D.RaycastAll(Camera.main.ScreenToWorldPoint(Input.mousePosition), Vector2.zero);
            foreach (var r in results)
            {
                if (r.collider.gameObject == gameObject)
                {
                    grabbed = true;
                }
            }
        }

        if (Input.GetMouseButtonUp(0))
        {
            trueValue = (value - .5f * maxValue) / (maxValue * .5f);
            var adjustedValue = trueValue * rangeAngle / (4 * Mathf.PI);
            var rot = transform.localEulerAngles;
            rot.z = -adjustedValue * 360;
            transform.localEulerAngles = rot;
            grabbed = false;
        }
        
        if (grabbed)
        {
            var dir = Input.mousePositionDelta;
            var change = dir.x + dir.y;
            change *= 1.5f * Time.deltaTime;
            change = Mathf.Clamp(change, -1, 1);
            trueValue += change;
            trueValue = Mathf.Clamp(trueValue, -1, 1);
            var adjustedValue = trueValue * rangeAngle / (4 * Mathf.PI);
            var rot = transform.localEulerAngles;
            rot.z = -adjustedValue * 360;
            transform.localEulerAngles = rot;
            value = Mathf.RoundToInt(trueValue * maxValue * .5f + .5f * maxValue);
        }
    }

    private void UpdateMaxValue(int value)
    {
        Debug.Log("Max value changed");
        for (int i = 0; i < notchLRs.Count; i++)
        {
            Destroy(notchLRs[i]);
        }
        notchLRs.Clear();
        var angleOffset = (Mathf.PI - rangeAngle) * .5f;
        for (var i = 0; i <= maxValue; i++)
        {
            var newGO = new GameObject();
            newGO.transform.parent = transform;
            var newLR = newGO.AddComponent<LineRenderer>();
            var newPos = transform.position;
            var angle = rangeAngle / (maxValue) * (i);
            angle += angleOffset;
            newPos.x += transform.localScale.x * .6f * Mathf.Cos(angle);
            newPos.y += transform.localScale.y * .6f * Mathf.Sin(angle);
            // newGO.transform.eulerAngles = new Vector3(0, 0, angle);
            newLR.positionCount = 2;
            newLR.numCapVertices = 12;
            newLR.widthMultiplier = .1f;
            newLR.SetPosition(0, transform.position);
            newLR.SetPosition(1, newPos);
            notchLRs.Add(newGO);
        }
    }
}
