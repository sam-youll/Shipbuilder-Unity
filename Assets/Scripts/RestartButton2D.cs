using UnityEngine;
using UnityEngine.SceneManagement;

public class RestartButton2D : Button2D
{
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    protected override void OnClick()
    {
        base.OnClick();
        Debug.Log("RestartButton2D.OnClick");
        AudioManager.Instance.ResetModuleInstances();
        SceneManager.LoadScene(SceneManager.GetActiveScene().name);
    }
}
