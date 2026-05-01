using DG.Tweening;
using UnityEngine;

public class SplitterModule : TriggerModule
{
    public float bulletSpeed = .75f;
    protected override void Start()
    {
        base.Start();
        combatStats["bulletSpeed"] = bulletSpeed;
    }
}
