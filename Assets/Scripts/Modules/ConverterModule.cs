using UnityEngine;

public class ConverterModule : PrimaryModule
{
    public float rate = 1;
    protected override void Start()
    {
        base.Start();

        CombatStats["power"] = 0;
        CombatStats["rate"] = rate;
        CombatStats["shields"] = 0;
    }
}
