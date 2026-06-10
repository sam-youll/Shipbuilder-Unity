using UnityEngine;

public class AuxiliarySystems : ModuleRack
{
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    public override string Description()
    {
        return "This rack holds any auxiliary systems, such as shields, cloaking, and escape patches.";
    }

    public override void Slow(float time)
    {
        throw new System.NotImplementedException();
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
