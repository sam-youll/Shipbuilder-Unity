using System.Collections.Generic;
using UnityEngine;

public class OutputRack : MonoBehaviour
{
    [Header("Weapon Outputs")]
    public GameObject[] weaponOutputs = new GameObject[6];
    public GameObject[] previousModsWeapons = new GameObject[6];
    
    [Header("Shield Outputs")]
    public GameObject[] shieldOutputs = new GameObject[6];
    public GameObject[] previousModsShields = new GameObject[6];

    private GameObject objUnderMouse;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {

    }

    void OnMouseOver()
    {
        Vector2 mousePos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
        
        RaycastHit2D hit = Physics2D.Raycast(mousePos, Vector2.zero, Mathf.Infinity, LayerMask.GetMask("Jacks"));
        RaycastHit2D bodyHit = Physics2D.Raycast(mousePos, Vector2.zero);
        
        if (hit)
        {
            // compare against outputs
            for (int i = 0; i < 6; i++)
            {
                if (hit.collider.gameObject == weaponOutputs[i])
                {
                    objUnderMouse = hit.collider.gameObject;
                }
                else if (hit.collider.gameObject == shieldOutputs[i])
                {
                    objUnderMouse = hit.collider.gameObject;
                }
            }
        }
        else
        {
            objUnderMouse = null;
        }
    }
}
