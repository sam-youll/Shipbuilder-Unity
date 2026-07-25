using UnityEngine;

public class CombinerModule : TriggerModule
{
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    public override string Description()
    {
        return "Passes along trigger from either input. Be careful not to trigger both at once.";
    }

    public override string Info()
    {
        var info = "";
        info += "Triggered by:\n";
        foreach (var wire in childWires)
        {
            var prevMod = wire.GetComponent<Wire>().previousModule;
            if (prevMod == null) continue;
            info += $" - {prevMod}";
        }
        if (childWires.Count > 0)
        {
            var nextMod = childWires[0].GetComponent<Wire>().nextModule;
            if (nextMod != null)
            {
                info += $"Triggers:\n - {nextMod}.\n";
            }
        }
        else
        {
            info += "Not triggering anything.\n";
        }
        
        return info;
    }
}
