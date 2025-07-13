using UnityEngine;

public class PowerModule : PrimaryModule
{
    public float power = 1;
    protected override void Start()
    {
        base.Start();

        CombatStats["power"] = power;
        CombatStats["rate"] = 0;
        CombatStats["shields"] = 0;
    }
}
