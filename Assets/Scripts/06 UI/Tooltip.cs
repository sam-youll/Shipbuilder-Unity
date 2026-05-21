using TMPro;
using UnityEngine;
using UnityEngine.UI;

public interface ITooltipInfo
{
    public string Description();
    public string Info();
}

public class Tooltip : MonoBehaviour
{
    private Vector2 panelSize;
    private SpriteRenderer sr;
    private TextMeshPro tmp;
    private BetterCSF csf;
    public float maxWidth = 5;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        sr = GetComponent<SpriteRenderer>();
        tmp = GetComponentInChildren<TextMeshPro>();
        csf = GetComponentInChildren<BetterCSF>();
        csf.maxWidth = maxWidth;
    }

    public void SetText(string text)
    {
        tmp.text = text;
        sr.size = new Vector2(tmp.bounds.size.x + .5f, tmp.bounds.size.y + .5f);
    }

    /// <summary>
    /// Update all parameters of tooltip.
    /// </summary>
    /// <param name="target">GameObject the tooltip will display info about.</param>
    public void UpdateTooltip(GameObject target)
    {
        tmp.text = target.name + "\n";
        if (target.TryGetComponent(out ITooltipInfo tooltip))
        {
            tmp.text += tooltip.Description() + "\n";
            tmp.text += "~~~\n" + tooltip.Info();
        }

        // csf.horizontalFit = ContentSizeFitter.FitMode.PreferredSize;
        
        sr.size = new Vector2(tmp.bounds.size.x + .5f, tmp.bounds.size.y + .5f);

        var coll = target.GetComponent<Collider2D>();
        
        // position tooltip just outside (top right) of target's collider
        var pos = coll.bounds.center;
        pos.x += .5f * coll.bounds.size.x;
        pos.x += .5f * sr.bounds.size.x + .5f;
        pos.y += .5f * coll.bounds.size.y + .39f;
        pos.y -= .5f * sr.bounds.size.y;
        pos.z = target.transform.position.z;
        pos.z -= 1;
        // make sure collider is visible (within bounds of camera)
        var cam = Global.Instance.cam;
        var height = cam.orthographicSize;
        var width = cam.aspect * height;
        pos.x = Mathf.Clamp(pos.x, -width + .5f * sr.bounds.size.x + .25f, width - .5f * sr.bounds.size.x - .25f);
        pos.y = Mathf.Clamp(pos.y, -height + .5f * sr.bounds.size.y + .25f, height - .5f * sr.bounds.size.y - .25f);
        transform.position = pos;
        
        // Debug.Log($"Coll pos = {coll.transform.position}. Coll size = {coll.bounds.size}. SR size = {sr.size}. Final pos = {pos}.");
        
        // TODO: check to make sure tooltip doesn't go off screen
        
    }
    
    // void DrawBounds(Bounds b, Color color)
    // {
    //     Vector3 min = b.min;
    //     Vector3 max = b.max;
    //
    //     Vector3[] corners = new Vector3[8];
    //     // Bottom
    //     corners[0] = new Vector3(min.x, min.y, min.z);
    //     corners[1] = new Vector3(max.x, min.y, min.z);
    //     corners[2] = new Vector3(max.x, min.y, max.z);
    //     corners[3] = new Vector3(min.x, min.y, max.z);
    //     // Top
    //     corners[4] = new Vector3(min.x, max.y, min.z);
    //     corners[5] = new Vector3(max.x, max.y, min.z);
    //     corners[6] = new Vector3(max.x, max.y, max.z);
    //     corners[7] = new Vector3(min.x, max.y, max.z);
    //
    //     // Bottom rectangle
    //     Debug.DrawLine(corners[0], corners[1], color);
    //     Debug.DrawLine(corners[1], corners[2], color);
    //     Debug.DrawLine(corners[2], corners[3], color);
    //     Debug.DrawLine(corners[3], corners[0], color);
    //
    //     // Top rectangle
    //     Debug.DrawLine(corners[4], corners[5], color);
    //     Debug.DrawLine(corners[5], corners[6], color);
    //     Debug.DrawLine(corners[6], corners[7], color);
    //     Debug.DrawLine(corners[7], corners[4], color);
    //
    //     // Vertical edges
    //     Debug.DrawLine(corners[0], corners[4], color);
    //     Debug.DrawLine(corners[1], corners[5], color);
    //     Debug.DrawLine(corners[2], corners[6], color);
    //     Debug.DrawLine(corners[3], corners[7], color);
    // }
}
