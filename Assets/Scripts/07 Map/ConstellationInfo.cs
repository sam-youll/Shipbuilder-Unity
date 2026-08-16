using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "ConstellationInfo", menuName = "Scriptable Objects/ConstellationInfo")]
public class ConstellationInfo : ScriptableObject
{
    public GameStateManager.Constellation constellation;
    public float constellationParam;
    public Notes.MODE mode;

    public enum KeyRoot
    {
        C,
        C_SHARP,
        D_FLAT,
        D,
        D_SHARP,
        E_FLAT,
        E,
        F,
        F_SHARP,
        G_FLAT,
        G,
        G_SHARP,
        A_FLAT,
        A,
        A_SHARP,
        B_FLAT,
        B
    }
    
    public Dictionary<KeyRoot, float> keyRoots = new Dictionary<KeyRoot, float>()
    {
        {KeyRoot.C, Notes.C},
        {KeyRoot.C_SHARP, Notes.C_SHARP},
        {KeyRoot.D_FLAT, Notes.D_FLAT},
        {KeyRoot.D, Notes.D},
        {KeyRoot.D_SHARP, Notes.D_SHARP},
        {KeyRoot.E_FLAT, Notes.E_FLAT},
        {KeyRoot.E, Notes.E},
        {KeyRoot.F, Notes.F},
        {KeyRoot.F_SHARP, Notes.F_SHARP},
        {KeyRoot.G_FLAT, Notes.G_FLAT},
        {KeyRoot.G, Notes.G},
        {KeyRoot.G_SHARP, Notes.G_SHARP},
        {KeyRoot.A_FLAT, Notes.A_FLAT},
        {KeyRoot.A, Notes.A},
        {KeyRoot.A_SHARP, Notes.A_SHARP},
        {KeyRoot.B_FLAT, Notes.B_FLAT},
        {KeyRoot.B, Notes.B},
    };
    
    public KeyRoot keyRoot;
    public float tempo;
    
    public List<int> changes = new List<int>();
    
}
