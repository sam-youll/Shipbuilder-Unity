using System.Globalization;
using System.Text.RegularExpressions;
using UnityEngine;

public static class Funcs
{
    public static float DLerp(float a, float b, float t, float dt)
    {
        return Mathf.Lerp(a, b, 1 - Mathf.Pow(t, dt));
    }
    
    public static string ConvertCamelCase(string input)
    {
        // Insert spaces before capital letters
        string spaced = Regex.Replace(input, @"(\p{Ll})(\p{Lu})", "$1 $2");

        // Capitalize the first letter of the result
        return CultureInfo.CurrentCulture.TextInfo.ToTitleCase(spaced);
    }
}
