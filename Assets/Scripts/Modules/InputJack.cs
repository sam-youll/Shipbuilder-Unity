using UnityEngine;

public class InputJack : Jack
{
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    protected void Start()
    {
        base.Start();
        var filepath = GetComponentInParent<Module>().darkTheme ? "Sprites/Jacks/jack dark in" : "Sprites/Jacks/jack light in";
        GetComponent<SpriteRenderer>().sprite = Resources.Load<Sprite>(filepath);
    }
}
