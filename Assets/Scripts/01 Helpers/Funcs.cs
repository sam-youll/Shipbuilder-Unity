using System.Globalization;
using System.Text.RegularExpressions;
using UnityEngine;

public static class Funcs
{
    /// <summary>
    /// Framerate independent alternative to lerp.
    /// </summary>
    /// <param name="a">Starting value.</param>
    /// <param name="b">Target value.</param>
    /// <param name="lambda">Decay rate???.</param>
    /// <param name="dt">Frame time.</param>
    /// <returns></returns>
    public static float Damp(float a, float b, float lambda, float dt)
    {
        return Mathf.Lerp(a, b, 1 - Mathf.Exp(-lambda * dt));
    }
    
    public static string ConvertCamelCase(string input)
    {
        // Insert spaces before capital letters
        string spaced = Regex.Replace(input, @"(\p{Ll})(\p{Lu})", "$1 $2");

        // Capitalize the first letter of the result
        return CultureInfo.CurrentCulture.TextInfo.ToTitleCase(spaced);
    }
    
    public static float Remap(float value, float inMin, float inMax, float outMin, float outMax) 
    {
        return outMin + (value - inMin) * (outMax - outMin) / (inMax - inMin);
    }
}
