using UnityEngine;

public static class Notes
{
    // CONSTANTS
    public const float UNISON = 1;
    public const float MINOR_SECOND = 1.059463f;
    public const float MAJOR_SECOND = 1.122462f;
    public const float MINOR_THIRD = 1.189207f;
    public const float MAJOR_THIRD = 1.259921f;
    public const float PERFECT_FOURTH = 1.334840f;
    public const float TRITONE = 1.414214f;
    public const float PERFECT_FIFTH = 1.498307f;
    public const float MINOR_SIXTH = 1.587401f;
    public const float MAJOR_SIXTH = 1.681793f;
    public const float MINOR_SEVENTH = 1.781797f;
    public const float MAJOR_SEVENTH = 1.887749f;
    public const float OCTAVE = 2f;

    public const float C = 261.63f;
    public const float C_SHARP = 277.18f;
    public const float D_FLAT = 277.18f;
    public const float D = 293.67f;
    public const float D_SHARP = 311.13f;
    public const float E_FLAT = 311.13f;
    public const float E = 329.63f;
    public const float F = 349.23f;
    public const float F_SHARP = 369.99f;
    public const float G_FLAT = 369.99f;
    public const float G = 392.00f;
    public const float G_SHARP = 415.00f;
    public const float A_FLAT = 415.00f;
    public const float A = 440.00f;
    public const float A_SHARP = 466.16f;
    public const float B_FLAT = 466.16f;
    public const float B = 493.88f;
    
    

    public enum MODE
    {
        IONIAN,
        DORIAN,
        PHRYGIAN,
        LYDIAN,
        MIXOLYDIAN,
        AEOLIAN,
        LOCRIAN
    }
    
    public static readonly float[] IONIAN =
    {
        UNISON,
        MAJOR_SECOND,
        MAJOR_THIRD,
        PERFECT_FOURTH,
        PERFECT_FIFTH,
        MAJOR_SIXTH,
        MAJOR_SEVENTH,
        OCTAVE
    };

    public static readonly float[] DORIAN =
    {

    };
    
    public static readonly float[] LYDIAN =
    {
        UNISON,
        MAJOR_SECOND,
        MAJOR_THIRD,
        TRITONE,
        PERFECT_FIFTH,
        MAJOR_SIXTH,
        MAJOR_SEVENTH,
        OCTAVE
    };

    public static float GetPitch(float root, MODE mode, int interval)
    {
        switch (mode)
        {
            case MODE.IONIAN:
                return IONIAN[interval]*root;
            case MODE.DORIAN:
                break;
            case MODE.PHRYGIAN:
                break;
            case MODE.LYDIAN:
                return LYDIAN[interval]*root;
            case MODE.MIXOLYDIAN:
                break;
            case MODE.AEOLIAN:
                break;
            case MODE.LOCRIAN:
                break;
        }

        return root;
    }
}
