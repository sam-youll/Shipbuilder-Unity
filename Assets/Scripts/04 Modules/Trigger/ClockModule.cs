using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Serialization;

public class ClockModule : TriggerModule
{
    [FormerlySerializedAs("frequency")] [SerializeField]
    int subdivision = 2;

    public int Frequency
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
        switch (subdivision)
        {
            case 0:
                info += "sixteenth note.";
                break;
            case 1:
                info += "eighth note.";
                break;
            case 2:
                info += "quarter note.";
                break;
            case 3:
                info += "half note.";
                break;
            case 4:
                info += "whole note.";
                break;
            case 5:
                info += "bar.";
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
