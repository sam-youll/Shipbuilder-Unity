using System.Collections.Generic;
using System.Linq;
using UnityEditor;
using UnityEngine;
using UnityEngine.Events;
using System.Reflection;

[CustomEditor(typeof(Button2D))]
public class Button2DEditor : Editor
{
    public override void OnInspectorGUI()
    {
        var button = target as Button2D;
        var eventBus = button.eventBus;
        if (eventBus == null)
        {
            EditorGUILayout.HelpBox("No event bus assigned", MessageType.Error);
            DrawDefaultInspector();
            return;
        }
        EditorGUILayout.LabelField("Event");
        if (EditorGUILayout.DropdownButton(new GUIContent(button.eventString), FocusType.Passive,GUILayout.ExpandWidth(true)))
        {
            GenericMenu menu = new();
            for (int i = 0; i < eventBus.eventsNoArgs.Count; i++)
            {
                var text = eventBus.eventsNoArgs.ElementAt(i).Key;
                menu.AddItem(new GUIContent(text), false, ConnectEvent, text);
            }
            menu.ShowAsContext();
        }
        DrawDefaultInspector();
    }

    private void ConnectEvent(object obj)
    {
        var button = target as Button2D;
        button.eventString = obj as string;
    }
}

public class Button2D : MonoBehaviour
{
    public EventBus eventBus;
    
    public Sprite defaultSprite;
    public Sprite pressedSprite;

    private SpriteRenderer sr;

    [HideInInspector] public string eventString = "Select event";
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        sr = GetComponent<SpriteRenderer>();
        sr.sprite = defaultSprite;
    }
    protected virtual void OnMouseEnter()
    {
        // sr.color = new Color(.9f, .9f, .9f, 1);
    }

    protected virtual void OnMouseExit()
    {
        // sr.color = Color.white;
        sr.sprite = defaultSprite;
    }

    protected virtual void OnMouseDown()
    {
        sr.sprite = pressedSprite;
        // sr.color = Color.white;
        // click.Invoke();

        OnClick();
    }

    protected virtual void OnMouseUp()
    {
        sr.sprite = defaultSprite;
        // sr.color = Color.white;
    }

    protected virtual void OnClick()
    {
        EventBus.Instance.eventsNoArgs[eventString].Invoke();
    }
}
