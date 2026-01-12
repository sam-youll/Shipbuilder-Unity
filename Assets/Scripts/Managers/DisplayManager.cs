using System.Collections.Generic;
using UnityEngine;

public class DisplayManager : MonoBehaviour
{
    public static DisplayManager Instance { get; private set; }
    private void Awake()
    {
        if (Instance != null && Instance != this)
        {
            Destroy(this);
        }
        else
        {
            Instance = this;
        }
    }

    public List<string> log { get; private set; } = new();

    public void Log(string text)
    {
        log.Add(text);
        if (log.Count > 6)
        {
            log.RemoveAt(0);
        }

        EventBus.Instance.displayLogUpdated.Invoke();
    }
}
