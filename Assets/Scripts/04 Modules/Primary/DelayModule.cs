using UnityEngine;

public class DelayModule : PrimaryModule
{
    public float fireRate = 2;
    public float damage = 2;
    public float delayTime = 0;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    protected override void Start()
    {
        combatStats["fireRate"] = fireRate;
        combatStats["damage"] = damage;
        musicParams["delayTime"] = delayTime;
    }
    public override void Trigger(float value, int inputIndex)
    {
        switch (inputIndex)
        {
            case 0:
                base.Trigger();
                break;
            case 1:
                musicParams["delaytime"] = value * 1000;
                // base.Trigger();
                break;
        }
    }
}
