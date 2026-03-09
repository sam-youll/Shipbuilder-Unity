using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using UnityEngine;
using UnityEngine.Events;
using UnityEngine.SceneManagement;
#if UNITY_EDITOR
using UnityEditor;
#endif

#if UNITY_EDITOR
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
#endif

public class EventBus : MonoBehaviour
{

    public static EventBus Instance;

    private void Awake()
    {
        if (Instance != null && Instance != this)
        {
            Destroy(gameObject);
        }
        else
        {
            Instance = this;
            DontDestroyOnLoad(this);
        }
        
        SetEventLists();
    }

    // TODO: these should be grouped into more specific fields later, as we consolidate more events into the bus
    [Header("Events")]
    // a public dictionary exists so buttons and other scripts can connect to these events and invoke them programatically
    // this dictionary is automatically updated via OnValidate()
    public Dictionary<string, UnityEvent> eventsNoArgs;
    public Dictionary<string, UnityEvent<string>> eventsStringArg;
    public Dictionary<string, UnityEvent<GameObject>> eventsGameObjectArg;
    public Dictionary<string, UnityEvent<int>> eventsIntArg;
    public Dictionary<string, UnityEvent<float>> eventsFloatArg;
    
    // the following fields are the actual events themselves
    public UnityEvent combatStarted;
    public UnityEvent enemyDefeated;
    public UnityEvent playerDefeated;
    public UnityEvent newCombatEncounterStarted;
    public UnityEvent startedDialogue;
    public UnityEvent enteredShop;
    public UnityEvent playerHullRepairAttempted;
    
    // in combat events
    public UnityEvent enemyShieldBroken;
    public UnityEvent playerShieldBroken;
    public UnityEvent enemyEffectApplied; // effect applied to enemy
    public UnityEvent playerEffectApplied; //      ""       to player
    public UnityEvent enemyHullDamaged;
    public UnityEvent playerHullDamaged;
    
    // shop events
    public UnityEvent<GameObject> shopSlotPurchased;
    public UnityEvent leftShop;
    
    // rack layout editing
    public UnityEvent<GameObject> rackEditXUp;
    public UnityEvent<GameObject> rackEditXDown;
    public UnityEvent<GameObject> rackEditYUp;
    public UnityEvent<GameObject> rackEditYDown;
    public UnityEvent weaponAdded;
    public UnityEvent<GameObject> weaponDeleted;
    
    // player value changes
    public UnityEvent playerHullValueChanged;
    public UnityEvent playerScrapValueChanged;
    
    public UnityEvent<Weapon> weaponFired;
    public UnityEvent<float> playerHit; // technically this and the event below also get called on a miss, damage is just set to -1
    public UnityEvent<float> enemyHit;
    public UnityEvent<Wire> updateJackValidity;
    public UnityEvent displayLogUpdated;
    
    // scene changes
    
    private void OnValidate()
    {
        SetEventLists();
    }

    private void SetEventLists()
    {
        // Debug.Log("OnValidate");
        var fields= GetType().GetFields();
        // Debug.Log(fields.Length);
        eventsNoArgs = new();
        eventsStringArg = new();
        eventsGameObjectArg = new();
        eventsIntArg = new();
        foreach (var field in fields)
        {
            // Debug.Log(field.FieldType.Name + " " + field.Name);
            if (field.FieldType == typeof(UnityEvent))
            {
                eventsNoArgs.Add(field.Name, (UnityEvent)field.GetValue(this));
            }
            else if (field.FieldType == typeof(UnityEvent<string>))
            {
                eventsStringArg.Add(field.Name, (UnityEvent<string>)field.GetValue(this));
            }
            else if (field.FieldType == typeof(UnityEvent<GameObject>))
            {
                eventsGameObjectArg.Add(field.Name, (UnityEvent<GameObject>)field.GetValue(this));
            }
            // else if (field.FieldType == typeof(UnityEvent<int>))
            // {
            //     eventsIntArg.Add(field.Name, (UnityEvent<int>)field.GetValue(this));
            // }
            // else if (field.FieldType == typeof(UnityEvent<float>))
            // {
            //     eventsFloatArg.Add(field.Name, (UnityEvent<float>)field.GetValue(this));
            // }
        }
    }
}
