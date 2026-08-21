using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class DisplayManager : MonoBehaviour
{
    public static DisplayManager Instance { get; private set; }
    private void Awake()
    {
        if (Instance != null && Instance != this)
        {
            Destroy(gameObject);
        }
        else
        {
            Instance = this;
            // DontDestroyOnLoad(this);
        }
    }

    public TextMeshProUGUI displayLogText;
    
    public List<string> log { get; private set; } = new();

    public void Log(string text)
    {
        log.Add(text);
        if (log.Count > 256)
        {
            log.RemoveAt(0);
        }

        EventBus.Instance.displayLogUpdated.Invoke();
        
        displayLogText.text = string.Join("\n", log.ToArray());
    }
}
