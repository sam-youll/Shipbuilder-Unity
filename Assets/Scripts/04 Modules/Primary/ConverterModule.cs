using System.Collections.Generic;
using UnityEngine;

public class ConverterModule : PrimaryModule, IReactorModule
{
    public float conversionRatio = 1;
    public Common.SoundType conversionType;
    
    public override string Description()
    {
        return "Converts energy or something.";
    }

    public override Dictionary<string, float> MusicParams()
    {
        return new Dictionary<string, float>();
    }

    public Dictionary<string, float> ReactorStats()
    {
        return new Dictionary<string, float>
        {
            { "conversionType", (float)conversionType },
            { "conversionRatio", conversionRatio }
        } ;
    }
}
