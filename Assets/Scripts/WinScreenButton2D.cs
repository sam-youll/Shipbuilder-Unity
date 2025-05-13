using UnityEngine;
using UnityEngine.SceneManagement;

public class WinScreenButton2D : Button2D
{

    public enum Type
    {
        NewWeapon,
        NewModule,
        NoThanks,
        Tutorial
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
                WeaponManager.Instance.AddWeapon();
                break;
            case Type.NewModule:
                Inventory.Instance.AddNewRandomModule();
                break;
            case Type.NoThanks:
                break;
            case Type.Tutorial:
                SceneManager.LoadScene("SampleScene");
                break;
        }
        
        CombatManager.Instance.endScreen.SetActive(false);
        CombatManager.Instance.state = CombatManager.State.outOfCombat;
    }
}
