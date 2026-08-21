using UnityEngine;

public class Managers : MonoBehaviour
{
    public static Managers Instance;

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
}
