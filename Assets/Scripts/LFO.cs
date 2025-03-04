using UnityEngine;

public class LFO : MonoBehaviour
{
    private Module module;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        module = gameObject.GetComponent<Module>();
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        module.parameterValue = Remap(Mathf.Sin(Time.time), -1, 1, 261.63f, 440);
        PatchManager.Instance.UpdateAllPatches();
    }
    
    public static float Remap (float value, float from1, float to1, float from2, float to2)
    {
        return (value - from1) / (to1 - from1) * (to2 - from2) + from2;
    }
}
