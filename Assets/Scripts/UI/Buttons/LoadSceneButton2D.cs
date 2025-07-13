using UnityEngine;
using UnityEngine.SceneManagement;

public class LoadSceneButton2D : Button2D
{
    public bool loadThisScene = false;
    public string sceneToLoad;
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
        if (loadThisScene)
            SceneManager.LoadScene(SceneManager.GetActiveScene().name);
        else
        {
            SceneManager.LoadScene(sceneToLoad);
        }
    }
}
