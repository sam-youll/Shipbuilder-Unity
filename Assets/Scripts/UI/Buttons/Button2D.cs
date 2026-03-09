using System.Collections.Generic;
using System.Linq;
using UnityEngine;
using UnityEngine.Events;
using System.Reflection;
#if UNITY_EDITOR
using UnityEditor;
#endif

#if UNITY_EDITOR
[CustomEditor(typeof(Button2D))]
public class Button2DEditor : Editor
{
    public override void OnInspectorGUI()
    {
        var button = target as Button2D;
        Undo.RecordObject(button, "Button");
        var eventBus = button.eventBus;
        if (eventBus == null)
        {
            EditorGUILayout.HelpBox("No event bus assigned", MessageType.Error);
            DrawDefaultInspector();
            return;
        }
        EditorGUILayout.BeginVertical();
        EditorGUILayout.LabelField("Event");
        if (EditorGUILayout.DropdownButton(new GUIContent(button.eventString), FocusType.Passive,GUILayout.ExpandWidth(true)))
        {
            GenericMenu menu = new();
            for (int i = 0; i < eventBus.eventsNoArgs.Count; i++)
            {
                var text = eventBus.eventsNoArgs.ElementAt(i).Key;
                menu.AddItem(new GUIContent(text), false, ConnectEvent, text);
            }

            for (int i = 0; i < eventBus.eventsStringArg.Count; i++)
            {
                var text = eventBus.eventsStringArg.ElementAt(i).Key;
                menu.AddItem(new GUIContent(text), false, ConnectEvent, text);
            }

            for (int i = 0; i < eventBus.eventsGameObjectArg.Count; i++)
            {
                var text = eventBus.eventsGameObjectArg.ElementAt(i).Key;
                menu.AddItem(new GUIContent(text), false, ConnectEvent, text);
            }
            
            menu.ShowAsContext();
        }
        if (eventBus.eventsStringArg.ContainsKey(button.eventString))
        {
            button.eventStringArg = EditorGUILayout.TextField("String argument: ", button.eventStringArg);
        }

        // if (eventBus.eventsIntArg.ContainsKey(button.eventString))
        // {
        //     button.eventIntArg = EditorGUILayout.IntField("Int argument: ", button.eventIntArg);
        // }
        //
        // if (eventBus.eventsFloatArg.ContainsKey(button.eventString))
        // {
        //     button.eventFloatArg = EditorGUILayout.FloatField("Float argument: ", button.eventFloatArg);
        // }
        
        if (eventBus.eventsGameObjectArg.ContainsKey(button.eventString))
        {
            button.eventStringArg = null;
            // button.eventGameObjectArg = EditorGUILayout.ObjectField("GameObject argument: ", button.eventGameObjectArg, typeof (GameObject), true) as GameObject;
        }
        
        EditorGUILayout.EndVertical();
        DrawDefaultInspector();
    }

    private void ConnectEvent(object obj)
    {
        var button = target as Button2D;
        button.eventString = obj as string;
    }
    
    private static bool IsSceneInProject(string named)
    {
        
        return EditorBuildSettings.scenes.Any(scene => scene.enabled && scene.path.Contains("/" + named + ".unity"));

    }
}
#endif

public class Button2D : MonoBehaviour
{
    public EventBus eventBus;
    
    public Sprite defaultSprite;
    public Sprite pressedSprite;

    private SpriteRenderer sr;

    [HideInInspector] public string eventString = "Select event";
    [HideInInspector] public string eventStringArg;
    public GameObject eventGameObjectArg;
    [HideInInspector] public int eventIntArg;
    [HideInInspector] public float eventFloatArg;
    
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
        if (!string.IsNullOrEmpty(eventStringArg))
        {
            EventBus.Instance.eventsStringArg[eventString].Invoke(eventStringArg);
        }
        else if (eventGameObjectArg != null)
        {
            EventBus.Instance.eventsGameObjectArg[eventString].Invoke(eventGameObjectArg);
        }
        else
        {
            EventBus.Instance.eventsNoArgs[eventString].Invoke();
        }
    }
}
