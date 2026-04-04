using System;
using UnityEngine;

public class PauseMenu : MonoBehaviour
{
    private void Start()
    {
        transform.Find("Quit Button").GetComponent<Button2D>().eventString = "gameExit";
        transform.Find("Main Menu Button").GetComponent<Button2D>().eventString = "loadScene";
        transform.Find("Main Menu Button").GetComponent<Button2D>().eventStringArg = "MainMenu";
    }
}
