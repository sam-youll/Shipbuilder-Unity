using System.Collections.Generic;
using UnityEditor;
using UnityEngine;
using UnityEngine.Events;

public class Knob : MonoBehaviour
{
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
    
    public float rangeAngle = Mathf.PI;
    private List<GameObject> notchLRs = new();

    public float trueValue;
    public float value;

    private Vector3 startPos;
    
    public UnityEvent<float> valueChanged;
    
    private SpriteRenderer sr;

    private Sprite[] spriteSheet;
    public bool lightDark;
    
    public bool drawLRNotches = true;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        var pathString = lightDark ? "Spritesheets/knob sprite sheet light" : "Spritesheets/knob sprite sheet dark";
        spriteSheet = Resources.LoadAll<Sprite>(pathString);
        
        UpdateMaxValue(maxValue);
        startPos = transform.localPosition;
        sr = GetComponent<SpriteRenderer>();
    }

    // Update is called once per frame
    void Update()
    {
        // var results = Physics2D.RaycastAll(Camera.main.ScreenToWorldPoint(Input.mousePosition), Vector2.zero);
        
        // var isItMe = false;
        // foreach (var r in Global.Instance.raycastHits)
        // {
        //     if (r.collider.gameObject == gameObject)
        //     {
        //         isItMe = true;
        //     }
        // }

        var isItMe = Global.Instance.RaycastResultsContains(gameObject);

        sr.color = isItMe || grabbed ? new Color(.7f,.7f,.7f) : Color.white;
        
        if (drawLRNotches)
        {
            UpdateLRs();
        }
        
        transform.localPosition = startPos;
        
        if (Input.GetMouseButtonDown(0))
        {
            if (isItMe)
                grabbed = true;
        }

        if (Input.GetMouseButtonUp(0))
        {
            trueValue = (value - .5f * maxValue) / (maxValue * .5f);
            var adjustedValue = trueValue * rangeAngle / (4 * Mathf.PI);
            
            // Old rotation-based method, here for posterity
            // var rot = transform.localEulerAngles;
            // rot.z = -adjustedValue * 360;
            // transform.localEulerAngles = rot;
            
            var index = Mathf.RoundToInt(adjustedValue * spriteSheet.Length);
            // index = Mathf.Clamp(index, 0, spriteSheet.Length - 1);
            // index -= 16;
            if (index < 0)
            {
                index += 32;
            }
            else if (index >= spriteSheet.Length)
            {
                index -= 32;
            }
            sr.sprite = spriteSheet[index];
            
            grabbed = false;
            valueChanged.Invoke(value);
        }
        
        if (grabbed)
        {
            var dir = Input.mousePositionDelta;
            var change = dir.x + dir.y;
            change *= 1.2f * Time.deltaTime;
            change = Mathf.Clamp(change, -1, 1);
            trueValue += change;
            trueValue = Mathf.Clamp(trueValue, -1, 1);
            var adjustedValue = trueValue * rangeAngle / (4 * Mathf.PI);
            
            // Old rotation-based method, here for posterity
            // var rot = transform.localEulerAngles;
            // rot.z = -adjustedValue * 360;
            // transform.localEulerAngles = rot;
            
            var index = Mathf.RoundToInt(adjustedValue * spriteSheet.Length);
            // index -= 16;
            if (index < 0)
            {
                index += 32;
            }
            else if (index >= spriteSheet.Length)
            {
                index -= 32;
            }
            // index = Mathf.Clamp(index, 0, spriteSheet.Length - 1);
            sr.sprite = spriteSheet[index];
            
            value = Mathf.RoundToInt(trueValue * maxValue * .5f + .5f * maxValue);
        }
    }

    private void UpdateMaxValue(int value)
    {
        if (!drawLRNotches)
            return;
        
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
            newLR.startColor = Color.black;
            newLR.endColor = Color.black;
            newLR.material = new Material(Shader.Find("Sprites/Default"));
            newLR.material.color = Color.black;
            var newPos = transform.position;
            var angle = rangeAngle / (maxValue) * (i);
            angle += angleOffset;
            newPos.x += transform.localScale.x * .3f * Mathf.Cos(angle);
            newPos.y += transform.localScale.y * .3f * Mathf.Sin(angle);
            newPos.z = .01f;
            // newGO.transform.eulerAngles = new Vector3(0, 0, angle);
            newLR.positionCount = 2;
            newLR.numCapVertices = 0;
            newLR.widthMultiplier = 1f;
            // newLR.widthCurve = AnimationCurve.Constant(0, 1, .625f);
            var startPos = transform.position;
            startPos.z += .01f;
            newLR.SetPosition(0, startPos);
            newLR.SetPosition(1, newPos);
            notchLRs.Add(newGO);
        }
    }

    private void UpdateLRs()
    {
        var angleOffset = (Mathf.PI - rangeAngle) * .5f;
        for (var i = 0; i < notchLRs.Count; i++)
        {
            var newPos = transform.position;
            var angle = rangeAngle / (maxValue) * (i);
            angle += angleOffset;
            newPos.x += transform.localScale.x * .3f * Mathf.Cos(angle);
            newPos.y += transform.localScale.y * .3f * Mathf.Sin(angle);
            newPos.z = .01f;
            notchLRs[i].GetComponent<LineRenderer>().positionCount = 2;
            notchLRs[i].GetComponent<LineRenderer>().numCapVertices = 12;
            notchLRs[i].GetComponent<LineRenderer>().widthMultiplier = .1f;
            notchLRs[i].GetComponent<LineRenderer>().SetPosition(0, transform.position);
            notchLRs[i].GetComponent<LineRenderer>().SetPosition(1, newPos);
            // notchLRs[i].GetComponent<LineRenderer>().sortingOrder = 1;
        }
    }
}
