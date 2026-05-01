using UnityEngine;

public class ConverterModule : PrimaryModule
{
    public float rate = 1;
    protected override void Start()
    {
        base.Start();

        combatStats["power"] = 0;
        combatStats["rate"] = rate;
        combatStats["shields"] = 0;
    }
}
