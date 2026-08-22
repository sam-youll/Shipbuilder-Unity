using System.Collections.Generic;
using UnityEngine;

public class ConverterModule : PrimaryModule, IReactorModule
{
    public float energyLimit;
    public float ratioNone;
    public float ratioIzki;
    public float ratioAubo;
    public float ratioDwth;
    
    public override string Description()
    {
        return "Converts pure energy to typed energy.";
    }

    public override string Info()
    {
        var info = $"Converts up to {energyLimit} pure energy per second, at a ratio of:\n";
        if (ratioNone > 0)
        {
            info += $"{ratioNone:P0} pure energy.\n";
        }
        if (ratioIzki > 0)
        {
            info += $"{ratioIzki:P0} izki energy.\n";
        }
        if (ratioAubo > 0)
        {
            info += $"{ratioAubo:P0} aubo energy.\n";
        }
        if (ratioDwth > 0)
        {
            info += $"{ratioDwth:P0} dwth energy.\n";
        }
        return info;
    }
    
    public override bool Warning(out string message)
    {
        var warn = base.Warning(out message);
        var rack = GetComponentInParent<ModuleRack>();
        if (rack != null)
        {
            if (rack is Reactor)
            {
                if (warn)
                {
                    return true;
                }
                return false;
            }
        }
        message += "This module will not convert power at maximum efficiency unless placed in reactor.\n";
        return true;
    }

    public List<KeyValuePair<Common.SoundType, float>> ConversionRatios()
    {
        var conversionList = new List<KeyValuePair<Common.SoundType, float>>();
        
        if (ratioNone > 0)
        {
            conversionList.Add(new(Common.SoundType.Pure, ratioNone));
        }
        if (ratioIzki > 0)
        {
            conversionList.Add(new(Common.SoundType.Izki, ratioIzki));
        }
        if (ratioAubo > 0)
        {
            conversionList.Add(new(Common.SoundType.Aubo, ratioAubo));
        }
        if (ratioDwth > 0)
        {
            conversionList.Add(new(Common.SoundType.Dwth, ratioDwth));
        }

        return conversionList;
    }

    public Dictionary<Common.SoundType, float> ChangeEnergy(Dictionary<Common.SoundType, float> energy)
    {
        var conversionAmount = Mathf.Min(energyLimit, energy[Common.SoundType.Pure]);
        
        var rack = GetComponentInParent<ModuleRack>();
        if (rack == null || rack.stunTimer > 0)
        {
            return energy;
        }

        if (rack is not Reactor) conversionAmount *= .25f;
        
        energy[Common.SoundType.Pure] -= conversionAmount;

        foreach (var kvp in ConversionRatios())
        {
            energy[kvp.Key] += conversionAmount * kvp.Value;
        }

        return energy;
    }

    public override Dictionary<string, float> ChangeMusicParams(Dictionary<string, float> musicParams)
    {
        throw new System.NotImplementedException();
    }
}
