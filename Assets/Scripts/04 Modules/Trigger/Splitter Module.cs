using System.Collections.Generic;
using DG.Tweening;
using UnityEngine;

public class SplitterModule : TriggerModule
{
    public float bulletSpeed = .75f;
    public override string Description()
    {
        return "When triggered, triggers all outputs simultaneously.";
    }
}
