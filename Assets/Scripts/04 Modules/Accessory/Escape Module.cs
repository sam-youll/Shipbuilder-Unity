using System.Collections.Generic;
using UnityEngine;

public class EscapeModule : AccessoryModule, IReactorModule
{
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    public override string Description()
    {
        return "When the player loses a battle, an escape module will be shattered to allow the player to retreat and live to fight another battle.";
    }

    public override string Info()
    {
        return "";
    }

    public override bool Warning(out string message)
    {
        var warn = base.Warning(out message);
        if (GetComponentInParent<ModuleRack>() is not Reactor)
        {
            message += "Put this module in Reactor to allow it to function.";
            warn = true;
        }

        return warn;
    }

    public Dictionary<Common.SoundType, float> ChangeEnergy(Dictionary<Common.SoundType, float> energy)
    {
        return energy;
    }
}
