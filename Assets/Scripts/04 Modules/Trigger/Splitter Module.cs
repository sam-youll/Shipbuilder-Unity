using System.Collections.Generic;
using System.Linq;
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

    public Dictionary<Common.SoundType, float> ChangeEnergy(Dictionary<Common.SoundType, float> energy)
    {
        foreach (var key in energy.Keys.ToList())
        {
            energy[key] *= .5f;
        }

        return energy;
    }
}
