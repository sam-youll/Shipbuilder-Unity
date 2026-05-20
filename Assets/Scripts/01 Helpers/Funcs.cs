
using UnityEngine;

public static class Funcs
{
    public static float DLerp(float a, float b, float t, float dt)
    {
        return Mathf.Lerp(a, b, 1 - Mathf.Pow(t, dt));
    }
}
