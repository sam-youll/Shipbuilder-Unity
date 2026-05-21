using System.Collections.Generic;
using UnityEngine;

public class ClockModule : TriggerModule
{
    [SerializeField]
    int frequency = 2;

    public int Frequency
    {
        get => frequency;
        set
        {
            value = Mathf.Clamp(value, 0, 5);
            frequency = value;
            UpdateFrequency(frequency);
        }
    }
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    public override string Description()
    {
        return "Triggers output at a consistent interval, set to a division of the current tempo.";
    }

    protected override void Start()
    {
        base.Start();
        
        UpdateFrequency(frequency);
    }

    void UpdateFrequency(int value)
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
