using UnityEngine;

public class VentModule : AccessoryModule, IWeaponModule
{
    public float coolingRateBonus = .1f;
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    public override string Description()
    {
        return "Increases the rate at which the weapon this module is placed on cools itself.\n";
    }

    public override string Info()
    {
        var message = "";
        if (GetComponentInParent<Weapon>() !=null)
        {
            message += $"{GetComponentInParent<Weapon>()} cools down an extra {coolingRateBonus}/s faster.\n";
        }
        else
        {
            message += $"Will cool weapon down an extra {coolingRateBonus}/s faster.\n";
        }

        return message;
    }

    public override bool Warning(out string message)
    {
        var warn = base.Warning(out message);
        if (GetComponentInParent<Weapon>() == null)
        {
            message += "This module will only function on a weapon.\n";
            return true;
        }
        return warn;
    }
    public IWeaponModule.WeaponStats ChangeWeaponStats(IWeaponModule.WeaponStats input)
    {
        return input;
    }
}
