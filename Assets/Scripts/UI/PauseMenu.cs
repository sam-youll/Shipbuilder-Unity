using UnityEngine;

public class PauseMenu : MonoBehaviour
{
    bool paused = false;
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Escape))
        {
            paused = !paused;
            transform.GetChild(0).gameObject.SetActive(paused);
        }
    }
}
