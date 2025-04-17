using System;
using System.Collections.Generic;
using Random = UnityEngine.Random;

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
    public const float DIMINISHED_SEVENTH = 1.681793f;
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

    // these arrays contain the scale degrees that are present in the given triad
    public static readonly int[] I = { 0, 2, 4 };
    public static readonly int[] II = { 1, 3, 5 };
    public static readonly int[] III = { 2, 4, 6 };
    public static readonly int[] IV = { 3, 5, 0 };
    public static readonly int[] V = { 4, 6, 1 };
    public static readonly int[] VI = { 5, 0, 2 };
    public static readonly int[] VII = { 6, 1, 3 };
    // here is an example of a chord that's not just a triad, though it's not being used anywhere yet
    public static readonly int[] I7 = { 0, 2, 4, 6 };
    // do not ask me how we're gonna handle diminished chords and other shit like that
    // public static readonly int[] Io = { ??? };
    // purely interval based (non scale based) chords could look like this:
    public static readonly float[] MAJ = { UNISON, MAJOR_THIRD, PERFECT_FIFTH };
    public static readonly float[] MIN = { UNISON, MINOR_THIRD, PERFECT_FIFTH };
    public static readonly float[] DIM = { UNISON, MINOR_THIRD, TRITONE };
    public static readonly float[] DIM7 = { UNISON, MINOR_THIRD, TRITONE, DIMINISHED_SEVENTH };
    // feel free to add more if you need them
    
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

    /// <summary>
    /// SCALE_CHORD contains the various chord arrays. More chords can be added later.
    /// </summary>
    public enum SCALE_CHORD
    {
        I,
        II,
        III,
        IV,
        V,
        VI,
        VII
    };

    // 
    public enum CHORD
    {
        MAJ,
        MIN,
        DIM,
        DIM7
    };
    
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

    /// <summary>
    /// Function for getting the frequency of a given interval in a given scale.
    /// </summary>
    /// <param name="root">Base frequency of the scale.</param>
    /// <param name="mode">Mode of the scale.</param>
    /// <param name="interval">Interval of the note within the scale.</param>
    /// <returns>Returns the frequency as a float.</returns>
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
    
    /// <summary>
    /// Gets an array of pitches based on root note and chord.
    /// </summary>
    /// <param name="root">Root note of chord.</param>
    /// <param name="chord">Use Notes.CHORD.</param>
    /// <returns>Returns an array of pitches as floats.</returns>
    public static float[] GetChord(float root, float[] chord)
    {
        // multiply the root frequency by the interval for each note
        for (var i = 0; i < chord.Length; i++)
        {
            chord[i] *= root;
        }

        return chord;
    }

    /// <summary>
    /// Gets an array of pitches based on the degree of chord in a scale.
    /// </summary>
    /// <param name="root">Root note of scale.</param>
    /// <param name="mode">Mode of scale.</param>
    /// <param name="chord">Which degree of chord. Use Notes.SCALE_CHORD.</param>
    /// <returns>Returns an array of pitches as floats.</returns>
    public static float[] GetChordInScale(float root, MODE mode, int[] chord)
    {
        float[] result = new float[chord.Length];
        for (var i = 0; i < chord.Length; i++)
        {
            result[i] = GetPitch(root, mode, chord[i]);
        }

        return result;
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="root"></param>
    /// <param name="mode"></param>
    /// <returns>Returns pitch as float.</returns>
    public static float RandomNoteInScale(float root, MODE mode)
    {
        var step = Random.Range(0, 8);
        return GetPitch(root, mode, step);
    }

    /// <summary>
    /// Function for getting a random pitch in a given chord.
    /// </summary>
    /// <param name="root">Root note of key.</param>
    /// <param name="mode">Mode of the scale.</param>
    /// <param name="chord">Which degree of chord in the key. Use Notes.SCALE_CHORD.</param>
    /// <returns>Returns frequency of pitch as a float.</returns>
    public static float RandomNoteInChord(float root, MODE mode, int[] chord)
    {
        var i = Random.Range(0, chord.Length);
        return GetPitch(root, mode, i);
    }
}
