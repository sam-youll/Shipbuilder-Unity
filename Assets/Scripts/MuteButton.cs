using System;
using UnityEngine;

public class MuteButton : MonoBehaviour
{
    public Color defaultColor;
    public Color hoverColor;
    public Color pressedColor;
    private Color currentColor;

    public bool isMuted = false;

    private bool timerRunning = false;
    private float targetTime;

    private SpriteRenderer sr;
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        sr = GetComponent<SpriteRenderer>();
        sr.color = defaultColor;
        currentColor = sr.color;
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        var col = sr.color;
        col = Color.Lerp(col, currentColor, .1f);
        sr.color = col;
    }

    private void Update()
    {
        if (timerRunning)
        {
            targetTime -= Time.deltaTime;
        }
        if (targetTime < 0)
        {
            timerEnded();
        }
    }

    private void OnMouseEnter()
    {
        sr.color = hoverColor;
        currentColor = hoverColor;
    }

    private void OnMouseExit()
    {
        sr.color = defaultColor;
        currentColor = defaultColor;
    }

    private void OnMouseDown()
    {
        sr.color = pressedColor;
        currentColor = hoverColor;

        if (!timerRunning)
        {
            if (isMuted)
            {
                AudioManager.Instance.UnmutePlayerVolume();
                Debug.Log("unmuting");
                sr.color = defaultColor;
                currentColor = defaultColor;
                isMuted = false;
            }
            else
            {
                timerStart();
                AudioManager.Instance.MutePlayerVolume();
                Debug.Log("muting");
                isMuted = true;
            }
        }
    }

    void timerStart()
    {
        targetTime = 1;
        timerRunning = true;
    }
    void timerEnded()
    {
        timerRunning = false;
    }
}
