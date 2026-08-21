using UnityEngine;

public class AuxiliarySystems : ModuleRack
{

    public override string Description()
    {
        return "This rack holds any auxiliary systems, such as shields, cloaking, and escape patches.";
    }

    public override string Info()
    {
        throw new System.NotImplementedException();
    }

    public override bool Warning(out string message)
    {
        message = "";
        return false;
    }

    public override void Slow(float time)
    {
        throw new System.NotImplementedException();
    }
}
