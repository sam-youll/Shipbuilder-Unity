using System.Collections.Generic;
using DG.Tweening;
using UnityEngine;

public class SplitterModule : TriggerModule, IReactorModule
{
    public float bulletSpeed = .75f;
    public override string Description()
    {
        return "When triggered, triggers all outputs simultaneously.";
    }

    public override string Info()
    {
        var info = "";
        if (parentWires.Count > 0)
        {
            var prevMod = parentWires[0].GetComponent<Wire>().previousModule;
            if (prevMod != null)
            {
                info += $"Triggered by:\n - {prevMod}.\n";
            }
        }
        else
        {
            info += "Not triggered by anything.\n";
        }
        info += "Triggers:\n";
        foreach (var wire in childWires)
        {
            var nextMod = wire.GetComponent<Wire>().nextModule;
            if (nextMod == null) continue;
            info += $" - {nextMod}";
        }

        return info;
    }

    public IReactorModule.ReactorStats MyReactorStats()
    {
        // this really doesn't need to do anything, the functionality is implemented in the GenerateEnergy() method over in Weapon.cs
        return new IReactorModule.ReactorStats();
    }
}
