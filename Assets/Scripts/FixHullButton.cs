using UnityEngine;

public class FixHullButton : Button2D
{

    protected override void OnClick()
    {
        if (CombatManager.Instance.playerShip.health >= CombatManager.Instance.playerShip.maxHealth ||
            Inventory.Instance.credits < 3)
            return;
        
        Inventory.Instance.credits -= 3;
        CombatManager.Instance.playerShip.health = CombatManager.Instance.playerShip.maxHealth;
    }
}
