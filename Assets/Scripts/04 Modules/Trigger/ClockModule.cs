using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Serialization;

public class ClockModule : TriggerModule
{
    [FormerlySerializedAs("frequency")] [SerializeField]
    int subdivision = 2;

    public int Subdivision
    {
        get => subdivision;
        set
        {
            value = Mathf.Clamp(value, 0, 5);
            subdivision = value;
            UpdateSubdivision(subdivision);
        }
    }
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    public override string Description()
    {
        return "Triggers output at a consistent interval, set to a division of the current tempo.";
    }

    public override string Info()
    {
        var info = "Triggers every ";
        var tempo = GameStateManager.Instance.constellationInfo.tempo / 120;
        switch (subdivision)
        {
            case 0:
                info += $"1/16 note. ({1/16f * tempo}s)";
                break;
            case 1:
                info += $"1/8 note. ({1/8f * tempo}s)";
                break;
            case 2:
                info += $"1/4 note. ({1/4f * tempo}s)";
                break;
            case 3:
                info += $"1/2 note. ({1/2f * tempo}s)";
                break;
            case 4:
                info += $"whole note. ({tempo}s)";
                break;
            case 5:
                info += $"bar.";
                break;
        }

        return info;
    }

    protected override void Start()
    {
        base.Start();
        
        UpdateSubdivision(subdivision);
    }

    void UpdateSubdivision(int value)
    {
        Conductor.Instance.onSixteenth.RemoveListener(Trigger);
        Conductor.Instance.onEighth.RemoveListener(Trigger);
        Conductor.Instance.onQuarter.RemoveListener(Trigger);
        Conductor.Instance.onHalf.RemoveListener(Trigger);
        Conductor.Instance.onWhole.RemoveListener(Trigger);
        Conductor.Instance.onBar.RemoveListener(Trigger);
        
        switch (value)
        {
            case 0:
                Conductor.Instance.onSixteenth.AddListener(Trigger);
                break;
            case 1:
                Conductor.Instance.onEighth.AddListener(Trigger);
                break;
            case 2:
                Conductor.Instance.onQuarter.AddListener(Trigger);
                break;
            case 3:
                Conductor.Instance.onHalf.AddListener(Trigger);
                break;
            case 4:
                Conductor.Instance.onWhole.AddListener(Trigger);
                break;
            case 5:
                Conductor.Instance.onBar.AddListener(Trigger);
                break;
        }
    }
}
