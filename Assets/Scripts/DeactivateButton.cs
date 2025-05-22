using UnityEngine;

public class DeactivateButton : Button2D
{
    public GameObject deactivationTarget;

    protected override void OnClick()
    {
        deactivationTarget.SetActive(false);
    }
}
