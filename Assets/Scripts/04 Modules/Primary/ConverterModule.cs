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
        return "Converts energy or something.";
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
            conversionList.Add(new(Common.SoundType.None, ratioNone));
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
