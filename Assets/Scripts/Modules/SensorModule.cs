using System.Collections.Generic;
using System.Linq;
#if UNITY_EDITOR
using UnityEditor;
#endif
using UnityEngine;

// #if UNITY_EDITOR
// [CustomEditor(typeof(SensorModule))]
// public class SensorModuleEditor : Editor
// {
//     public override void OnInspectorGUI()
//     {
//         var module = target as SensorModule;
//         Undo.RecordObject(module, "Module");
//         var eventBus = module.eventBus;
//         if (eventBus == null)
//         {
//             EditorGUILayout.HelpBox("No event bus assigned", MessageType.Error);
//             DrawDefaultInspector();
//             return;
//         }
//         EditorGUILayout.BeginVertical();
//         EditorGUILayout.LabelField("Event");
//         if (EditorGUILayout.DropdownButton(new GUIContent("Select Available Events"), FocusType.Passive,GUILayout.ExpandWidth(true)))
//         {
//             GenericMenu menu = new();
//             for (int i = 0; i < eventBus.eventsNoArgs.Count; i++)
//             {
//                 var text = eventBus.eventsNoArgs.ElementAt(i).Key;
//                 menu.AddItem(new GUIContent(text), module.availableEventTriggers.Contains(text), ConnectEvent, text);
//             }
//             
//             menu.ShowAsContext();
//         }
//         // if (eventBus.eventsStringArg.ContainsKey(module.eventString))
//         // {
//         //     module.eventStringArg = EditorGUILayout.TextField("String argument: ", module.eventStringArg);
//         // }
//
//         EditorGUILayout.LabelField("Available Event Triggers:");
//         foreach (var eventString in module.availableEventTriggers)
//         {
//             EditorGUILayout.LabelField(eventString);
//         }
//         
//         EditorGUILayout.EndVertical();
//         DrawDefaultInspector();
//     }
//
//     private void ConnectEvent(object obj)
//     {
//         var module = target as SensorModule;
//
//         if (module.availableEventTriggers.Contains(obj.ToString()))
//         {
//             module.availableEventTriggers.Remove(obj.ToString());
//         }
//         else
//         {
//             module.availableEventTriggers.Add(obj.ToString());
//         }
//     }
//     
//     private static bool IsSceneInProject(string named)
//     {
//         
//         return EditorBuildSettings.scenes.Any(scene => scene.enabled && scene.path.Contains("/" + named + ".unity"));
//
//     }
// }
// #endif

public class SensorModule : Module, ITooltipInfo
{
    public List<string> availableEventTriggers = new();
    public string currentEventTrigger;
    
    public string Info()
    {
        var info = "Available Event Triggers:\n";
        foreach (var trigger in availableEventTriggers)
        {
            if (trigger == currentEventTrigger)
            {
                info += "> [" + trigger + "]\n";
            }
            else
            {
                info += trigger + "\n";
            }
        }
        return info;
    }
    
    protected override void Start()
    {
        base.Start();
        GetComponentInChildren<Knob>().valueChanged.AddListener(SetEventTrigger);
    }

    private void SetEventTrigger(float eventIndex)
    {
        EventBus.Instance.eventsNoArgs[currentEventTrigger].RemoveListener(Trigger);
        currentEventTrigger = availableEventTriggers[(int)eventIndex];
        EventBus.Instance.eventsNoArgs[currentEventTrigger].AddListener(Trigger);
    }
}
