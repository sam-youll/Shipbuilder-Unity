using UnityEngine;

public class AddWeaponButton2D : Button2D
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
        // WeaponManager.Instance.AddWeapon();
    }
}
