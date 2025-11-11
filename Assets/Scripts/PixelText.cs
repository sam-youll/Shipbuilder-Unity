using UnityEngine;
using Nothke.Utils;
using TMPro;

[RequireComponent(typeof(TextMeshPro))]
[RequireComponent(typeof(RectTransform))]
[RequireComponent(typeof(MeshRenderer))]
public class PixelText : MonoBehaviour
{
    private Material mat;
    private RenderTexture rt;
    private TextMeshPro text;
    private MeshRenderer mr;
    public SpriteRenderer sr;
    [Tooltip("Pixels per unit.")]
    public int ppu;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        mr =  GetComponent<MeshRenderer>();
        // mr.enabled = false;
        mat = Material.Instantiate(mr.material);
        mat.name = "Pixel Text Material";
        mr.material = mat;
        text = GetComponent<TextMeshPro>();
        var rectTransform = GetComponent<RectTransform>();
        var width = (int)(rectTransform.rect.width * ppu);
        var height = (int)(rectTransform.rect.height * ppu);
        Debug.Log($"Width = {width}, Height = {height}");
        rt = new RenderTexture(width, height, 24);
        mr.material.mainTexture = rt;
        
        rt.BeginPixelRendering();
        GL.Clear(true, true, Color.black);
        rt.DrawTMPText(text, new Vector2(.5f, .5f), .2f);
        rt.EndRendering();
        
        Texture2D tex = new Texture2D(width, height);
        RenderTexture.active = rt;
        tex.ReadPixels(new Rect(0, 0, width, height), 0, 0);
        tex.Apply();
        RenderTexture.active = null;
        
        sr.sprite = Sprite.Create(tex, new Rect(transform.position.x, transform.position.y, width, height), Vector2.zero);
        mr.material = mat;
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
