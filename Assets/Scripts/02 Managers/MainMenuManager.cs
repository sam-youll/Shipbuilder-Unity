using System;
using UnityEngine;
using UnityEngine.SceneManagement;

public class MainMenuManager : MonoBehaviour
{
    private void Start()
    {
        Cursor.visible = true;
    }

    public void StartGame()
    {
        SceneManager.LoadScene("Cockpit", LoadSceneMode.Single);
    }
    
    public void Quit()
    {
        Application.Quit();
    }
}
