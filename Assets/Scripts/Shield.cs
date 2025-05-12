using System.Collections;
using UnityEngine;

public class Shield : MonoBehaviour
{
    public float maxHealth;
    public float health;
    public float defense;
    public float downtime;
    public float rechargeRate;
    private float defaultScale;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        defaultScale = transform.localScale.x;
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void TakeDamage(float damage)
    {
        if (CombatManager.Instance.state != CombatManager.State.inCombat)
        {
            return;
        }
        
        health -= damage;
        if (health <= 0)
        {
            StartCoroutine(RegenShield());
        }
    }
    
    IEnumerator RegenShield()
    {
        gameObject.GetComponent<PolygonCollider2D>().enabled = false;
        var sprite = gameObject.GetComponent<SpriteRenderer>();
        var col = sprite.color;
        var newCol = new Color(col.r, col.g, col.b, .1f);
        sprite.color = newCol;
        transform.localScale = Vector3.zero;
        yield return new WaitForSeconds(downtime);
        while (transform.localScale.x <= defaultScale)
        {
            transform.localScale += Vector3.one * (rechargeRate * Time.deltaTime);
            yield return null;
        }
        health = maxHealth;
        gameObject.GetComponent<PolygonCollider2D>().enabled = true;
        sprite.color = new Color(col.r, col.g, col.b, .2f);
    }
}
