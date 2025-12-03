using System;
using UnityEngine;

public abstract class Jack : MonoBehaviour
{
    protected void Start()
    {
        Global.Instance.allJacks.Add(gameObject);
    }

    protected void OnDestroy()
    {
        Global.Instance.allJacks.Remove(gameObject);
    }
}
