using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using UnityEditor;
using UnityEngine;
using UnityEngine.Events;

[CustomEditor(typeof(EventBus))]
public class EventBusEditor : Editor
{
    public override void OnInspectorGUI()
    {
        EditorGUILayout.BeginVertical();
        var eventBus = target as EventBus;
        EditorGUILayout.LabelField($"Events with no arguments ({eventBus.eventsNoArgs.Count})");
        foreach (var key in eventBus.eventsNoArgs.Keys)
        {
            EditorGUILayout.LabelField(key);
        }
        EditorGUILayout.EndVertical();
        DrawDefaultInspector();
    }
}

public class EventBus : MonoBehaviour
{
    public static EventBus Instance;

    private void Awake()
    {
        if (Instance != null && Instance != this)
        {
            Destroy(this);
        }
        else
        {
            Instance = this;
        }
    }

    // TODO: these should be grouped into more specific fields later, as we consolidate more events into the bus
    [Header("Events")] 
    // a public dictionary exists so buttons and other scripts can connect to these events and invoke them programatically
    // this dictionary is automatically updated via OnValidate()
    public Dictionary<string, UnityEvent> eventsNoArgs = new();
    // the following fields are the actual events themselves
    public UnityEvent combatStarted;
    public UnityEvent combatEnded;
    public UnityEvent enemyDefeated;
    public UnityEvent playerDefeated;
    
    public UnityEvent<Weapon> weaponFired;
    public UnityEvent<float> playerHit; // technically this and the event below also get called on a miss, damage is just set to -1
    public UnityEvent<float> enemyHit;
    public UnityEvent<Wire> updateJackValidity;
    public UnityEvent displayLogUpdated;
    
    private void OnValidate()
    {
        // Debug.Log("OnValidate");
        var fields= GetType().GetFields();
        // Debug.Log(fields.Length);
        eventsNoArgs = new Dictionary<string, UnityEvent>();
        foreach (var field in fields)
        {
            // Debug.Log(field.FieldType.Name + " " + field.Name);
            if (field.FieldType== typeof(UnityEvent))
            {
                eventsNoArgs.Add(field.Name, (UnityEvent)field.GetValue(this));
            }
        }
    }
}
