using UnityEngine;

public class OutputJack : Jack
{
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    protected void Start()
    {
        base.Start();
        var filepath = GetComponentInParent<Module>().darkTheme ? "Sprites/Jacks/jack dark out" : "Sprites/Jacks/jack light out";
        GetComponent<SpriteRenderer>().sprite = Resources.Load<Sprite>(filepath);
    }
}
