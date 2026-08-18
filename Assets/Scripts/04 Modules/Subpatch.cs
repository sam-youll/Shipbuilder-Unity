using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using SaintsField;
using UnityEngine;

#region Dictionary serialization bullshit
[System.Serializable] public class ModuleOutputsPair
{
    [Tooltip("GameObjects should exist on children of the Subpatch GameObject, then be referenced here.")]
    public GameObject module;
    [Tooltip("These ints correspond to the indices of the subpatchDict this module outputs to.")]
    public List<int> outputIndices;
}
#endregion

public class Subpatch : Module
{
    public string myDescription;
    public List<ModuleOutputsPair> subpatchDict = new();
    private List<GameObject> wires = new();
    
    void CompileSubpatch()
    {
        Debug.Log("Compiling subpatch.");
        
        foreach (GameObject wire in childWires)
        {
            wire.GetComponent<Wire>().connected.RemoveListener(CompileSubpatch);
        }
        
        // clear wires
        foreach (var wire in wires)
        {
            Destroy(wire);
        }
        wires.Clear();

        for (var i = 0; i < subpatchDict.Count; i++)
        {
            var myMod = subpatchDict[i].module.GetComponent<Module>();
            // myMod.ClearWires();
            if (parentWires.Count > 0)
            {
                if (i != 0)
                {
                    for (var index = 0; index < myMod.parentWires.Count; index++)
                    {
                        myMod.parentWires[index].GetComponent<Wire>().DeleteSelf();
                    }
                
                    myMod.parentWires.Clear();
                }
            }
            if (childWires.Count > 0)
            {
                if (i != subpatchDict.Count - 1)
                {
                    for (var index = 0; index < myMod.childWires.Count; index++)
                    {
                        myMod.childWires[index].GetComponent<Wire>().DeleteSelf();
                    }
                
                    myMod.childWires.Clear();
                }
            }
        }
        
        // loop through modules in subpatch
        for (var i = 0; i < subpatchDict.Count; i++)
        {
            if (i < subpatchDict.Count)
            {
                // loop through output indices of current module
                for (var j = 0; j < subpatchDict[i].outputIndices.Count; j++)
                {
                    // create a GameObject to hold the wire
                    var newWireObj = new GameObject();
                    newWireObj.transform.SetParent(subpatchDict[i].module.transform);
                    
                    // add a wire to the GameObject
                    var newWire = newWireObj.AddComponent<Wire>();
                    
                    // subpatch wires should be invisible
                    newWire.invisible = true;
                    
                    // set the nextModule and previousModule of the new wire based on the current output index and the current module
                    newWire.nextModule = subpatchDict[subpatchDict[i].outputIndices[j]].module;
                    newWire.previousModule = subpatchDict[i].module;
                    
                    // add the new wire to childWires of the current module
                    subpatchDict[i].module.GetComponent<Module>().childWires.Add(newWireObj);
                    
                    // add the new wire to parentWires of the module indicated by the current output index
                    subpatchDict[subpatchDict[i].outputIndices[j]].module.GetComponent<Module>().parentWires.Add(newWireObj);
                    
                    // set input index if connected to pitch module
                    // TODO: THIS IS TEMPORARY. MAKE A BETTER SYSTEM FOR DETERMINING INPUT INDEX
                    if (subpatchDict[i].module.TryGetComponent(out SecondaryModule mod))
                    {
                        if (subpatchDict[subpatchDict[i].outputIndices[j]].module
                            .TryGetComponent(out PitchModule pitchMod))
                        {
                            mod.myInputIndex = 1;
                        }
                    }
                    
                    // add new wire to list of all managed invisible wires on this subpatch
                    wires.Add(newWireObj);
                    
                    // set name of wire for easy reference in inspector
                    newWireObj.name = $"Wire to {subpatchDict[subpatchDict[i].outputIndices[j]].module.name}";
                    
                    // tell the module it's connected so it doesn't delete itself
                    newWire.isConnected = true;
                    // Debug.Log($"(i,j):({i},{j})\nCreated a new wire targeting {subpatchDict[subpatchDict[i].outputIndices[j]]} as a child of {subpatchDict[i].module.name}.");
                }
            }
            // if this is the last module in the list
            else
            {
                // the child wires should be set equal to the (non-invisible) child wires of the subpatch itself
                // this also gets set later in case the subpatch doesn't have any child wires when we get here
                // subpatchDict[i].module.GetComponent<Module>().childWires = childWires;
            }
        }
    }
    
    // void CheckActiveState()
    // {
    //     activeState = SecondaryModule.ActiveState.Triggered;
    //     foreach (var module in modules)
    //     {
    //         if (module.GetComponent<SecondaryModule>() != null)
    //         {
    //             if (module.GetComponent<SecondaryModule>().activeState == SecondaryModule.ActiveState.Always)
    //             {
    //                 activeState = SecondaryModule.ActiveState.Always;
    //             }
    //         }
    //     }
    // }
    
    public override void Trigger(float value, int inputIndex)
    {
        // Debug.Log($"{gameObject.name} triggered {subpatchDict[0].module.name} with a value of {value} at inputIndex {inputIndex}.");
        // subpatchDict[^1].module.GetComponent<Module>().childWires = childWires;
        // subpatchDict[0].module.GetComponent<Module>().parentWires = parentWires;
        // subpatchDict[0].module.GetComponent<Module>().Trigger(value, inputIndex);
    }
    
    public override void Trigger(float value)
    {
        // Debug.Log($"{gameObject.name} triggered {subpatchDict[0].module.name} with a value of {value}.");
        // subpatchDict[^1].module.GetComponent<Module>().childWires = childWires;
        // subpatchDict[0].module.GetComponent<Module>().parentWires = parentWires;
        // subpatchDict[0].module.GetComponent<Module>().Trigger(value);
    }

    public override string Description()
    {
        return myDescription;
    }

    public override string Info()
    {
        var desc = "This subpatch contains:\n";
        
        foreach (var mod in subpatchDict)
        {
            desc += "- " + mod.module.name + ", which connects to ";
            for (var i = 0; i < mod.outputIndices.Count; i++)
            {
                var output = mod.outputIndices[i];
                if (i == mod.outputIndices.Count - 1)
                {
                    desc += subpatchDict[output].module.name + "\n";
                }
                else
                {
                    desc += subpatchDict[output].module.name + ", ";
                }
            }
        }

        return desc;
    }

    public override void Trigger()
    {
        // Debug.Log($"{gameObject.name} triggered {subpatchDict[0].module.name} with no arguments.");
        subpatchDict[^1].module.GetComponent<Module>().childWires = new List<GameObject>(childWires);
        subpatchDict[0].module.GetComponent<Module>().parentWires = new List<GameObject>(parentWires);
        subpatchDict[0].module.GetComponent<Module>().Trigger();
    }

    public void OnJackClick()
    {
        // We want CompileSubpatch to be triggered when the child wire is connected to its output.
        // Doing it sooner means the last module in the subpatch doesn't know what it's output is.
        foreach (var wire in childWires)
        {
            wire.GetComponent<Wire>().connected.AddListener(CompileSubpatch);
            Debug.Log("Added wire connection listener.");
        }
    }

    public override Dictionary<Common.SoundType, float> EnergyCost()
    {
        var cost = new Dictionary<Common.SoundType, float>
        {
            { Common.SoundType.Pure, energyNoneCost },
            { Common.SoundType.Izki, energyIzkiCost },
            { Common.SoundType.Aubo, energyAuboCost },
            { Common.SoundType.Dwth, energyDwthCost }
        };
        foreach (var pair in subpatchDict)
        {
            foreach (var type in pair.module.GetComponent<Module>().EnergyCost())
            {
                cost[type.Key] += type.Value;
            }
        }

        return cost;
    }

    public override Dictionary<Common.SoundType, float> ChangeEnergyCost(Dictionary<Common.SoundType, float> input)
    {
        foreach (var pair in subpatchDict)
        {
            foreach (var type in pair.module.GetComponent<Module>().EnergyCost())
            {
                input[type.Key] += type.Value;
            }
        }
        return input;
    }
}
