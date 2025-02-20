using System;
using UnityEngine;

public class FakeButtonPress : MonoBehaviour
{
    public Color defaultColor;
    public Color hoverColor;
    public Color pressedColor;
    private Color currentColor;

    public bool isPlaying = false;

    public Sprite triangle;
    public Sprite square;

    public GameObject otherTriangle;

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
        // if (timerRunning)
        // {
        //   targetTime -= Time.deltaTime;
        // }
        // if (targetTime < 0)
        // {
        //     timerEnded();
        // }
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
        AudioManager.Instance.PlayEnemySong();

        // if (!timerRunning)
        // {
            if (isPlaying)
            {
                sr.sprite = triangle;
                otherTriangle.GetComponent<SpriteRenderer>().sprite = triangle;
                AudioManager.Instance.StopEnemySong();
                Debug.Log("stopping");
                isPlaying = false;
            }
            else
            {
                //a smol timer so it doesnt just spam play/pause while the mouse is held down
                // timerStart();
                sr.sprite = square;
                otherTriangle.GetComponent<SpriteRenderer>().sprite = square;
                Debug.Log("starting");
                isPlaying = true;
            }
        // }
    }

    // void timerStart()
    // {
    //     targetTime = 1;
    //     timerRunning = true;
    // }
    // void timerEnded()
    // {
    //     timerRunning = false;
    // }
}
