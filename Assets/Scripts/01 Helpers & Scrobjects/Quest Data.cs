using System;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

/// <summary>
/// Name, objectives, and other data required for a quest.
/// </summary>
[CreateAssetMenu(fileName = "New Quest", menuName = "Scriptable Objects/Quest Data")]
public class QuestData : ScriptableObject
{
    public string questName;

    // list of all steps in this quest
    public List<QuestStep> questSteps;

    

    // returns true if exists
    public bool TryGetQuestStep(string qName, out QuestStep questStep)
    {
        foreach (QuestStep step in questSteps)
        {
            if (step.stepName == qName)
            {
                questStep = step;
                return true;
            }
        }
        questStep = new QuestStep();
        return false;
    }
    
    // unfortunately the quest steps can't directly reference other quest steps
    // so this function has to live up here
    public bool DependenciesCompleted(string stepToCheck, Predicate<QuestStep> isCompleted)
    {
        var completed = TryGetQuestStep(stepToCheck, out var step);
        foreach (var name in step.dependencies)
        {
            if (TryGetQuestStep(name, out var subStep))
            {
                if (isCompleted(subStep) == false) completed = false;
            }
        }
        return completed;
    }

    [System.Serializable]
    public struct QuestStep
    {
        // used for reference & comparison
        public string stepName;
        
        // what is displayed in the quest log
        public string objectiveText;
        
        // any other quest steps this step depends on
        // this quest step can not be active until dependencies are completed
        public List<string> dependencies;
    }
}
