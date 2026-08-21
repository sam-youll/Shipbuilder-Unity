#if UNITY_EDITOR
using UnityEditor;
#endif
using UnityEngine;
using UnityEngine.Assertions.Must;
using UnityEngine.UI;

#if UNITY_EDITOR
[CustomEditor(typeof(BetterCSF))]
public class CSFEditor : Editor
{
    public override void OnInspectorGUI()
    {
        var csf = (BetterCSF)target;
        csf.maxWidth = EditorGUILayout.FloatField(csf.maxWidth);
    }
}
#endif

public class BetterCSF : ContentSizeFitter
{
    [SerializeField] public float maxWidth = 5;
    
    public override void SetLayoutHorizontal()
    {
        base.SetLayoutHorizontal();

        if (m_HorizontalFit == FitMode.PreferredSize)
        {
            var rt = GetComponent<RectTransform>();
            // rt.sizeDelta = new Vector2(Mathf.Clamp(rt.sizeDelta.x, widthClamp.x, widthClamp.y), rt.sizeDelta.y);
            rt.SetSizeWithCurrentAnchors(0, Mathf.Clamp(LayoutUtility.GetPreferredSize(rt, 0), 0, maxWidth));
        }
    }

    // public override void SetLayoutVertical()
    // {
    //     base.SetLayoutVertical();
    //     
    //     if (m_VerticalFit == FitMode.PreferredSize)
    //     {
    //         var rt = GetComponent<RectTransform>();
    //         rt.sizeDelta = new Vector2(rt.sizeDelta.x, Mathf.Clamp(rt.sizeDelta.y, heightClamp.x, heightClamp.y));
    //     }
    // }
}
