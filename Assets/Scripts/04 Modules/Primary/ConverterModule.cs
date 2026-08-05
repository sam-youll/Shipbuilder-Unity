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
        return "Converts untyped energy to typed energy, though not with perfect efficiency.";
    }

    public override string Info()
    {
        var info = $"Converts up to {energyLimit} untyped energy per second, at a ratio of:\n";
        if (ratioNone > 0)
        {
            info += $"{ratioNone * 100}% untyped energy.\n";
        }
        if (ratioIzki > 0)
        {
            info += $"{ratioIzki * 100}% izki energy.\n";
        }
        if (ratioAubo > 0)
        {
            info += $"{ratioAubo * 100}% aubo energy.\n";
        }
        if (ratioDwth > 0)
        {
            info += $"{ratioDwth * 100}% dwth energy.\n";
        }
        return info;
    }

    public override Dictionary<string, float> MusicParams()
    {
        return new Dictionary<string, float>();
    }

    

    public IReactorModule.ReactorStats MyReactorStats()
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
        
        return new IReactorModule.ReactorStats
        {
            EnergyConversion = new()
            {
                EnergyLimit = energyLimit,
                ConversionRatios = conversionList
            }
        };
    }
}
