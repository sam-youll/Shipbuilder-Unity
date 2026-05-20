using UnityEngine;
using UnityEngine.SceneManagement;

public class WinScreenButton2D : Button2D
{

    public enum Type
    {
        NewWeapon,
        NewModule,
        NoThanks,
        Tutorial, 
        Start,
        Quit
    }
    public Type type;
    
    // Update is called once per frame
    void Update()
    {
        // if (type == Type.NewWeapon && WeaponManager.Instance.
    }

    protected override void OnClick()
    {
        base.OnClick();

        switch (type)
        {
            case Type.NewWeapon:
                if (InventoryManager.Instance.scrap < 10)
                    break;
                InventoryManager.Instance.scrap -= 10;
                WeaponManager.Instance.AddWeapon();
                break;
            case Type.NewModule:
                // Inventory.Instance.AddNewRandomModule();
                break;
            case Type.NoThanks:
                break;
            case Type.Start:
                SceneManager.LoadScene("SampleScene");
                break;
            case Type.Tutorial:
                SceneManager.LoadScene("Spring Showcase Tutorial");
                break;
            case Type.Quit:
                Application.Quit();
                break;

        }
        
        // CombatManager.Instance.endScreen.SetActive(false);
        // CombatManager.Instance.state = CombatManager.State.outOfCombat;
    }
}
