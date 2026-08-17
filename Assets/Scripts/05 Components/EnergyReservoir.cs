using System;
using System.Collections.Generic;
using System.Linq;
using SaintsField;
using SaintsField.Playa;
using UnityEngine;
using UnityEngine.UI;

public class EnergyReservoir : MonoBehaviour
{
    private Dictionary<Common.SoundType, List<GameObject>> energyCells = new()
    {
        { Common.SoundType.Pure , new List<GameObject>() },
        { Common.SoundType.Izki , new List<GameObject>() },
        { Common.SoundType.Aubo , new List<GameObject>() },
        { Common.SoundType.Dwth , new List<GameObject>() }
    };
    [ShowInInspector] public Dictionary<Common.SoundType, float> storedEnergy = new()
    {
        { Common.SoundType.Pure, 0 },
        { Common.SoundType.Izki, 0 },
        { Common.SoundType.Aubo, 0 },
        { Common.SoundType.Dwth, 0 }
    };
    [GetComponent] public GridLayoutGroup grid;
    public GameObject energyBarPrefab;
    public float maxStoredEnergy;
    public bool invisible;
    private bool full;

    // private void Update()
    // {
    //     if (energy[Common.SoundType.None].Count == 0)
    //     {
    //         Debug.Log($"There is currently {energy[Common.SoundType.None].Count} None energy in display.");
    //     }
    //     else
    //     {
    //         Debug.Log(
    //             $"There is currently {energy[Common.SoundType.None].Count - 1 + energy[Common.SoundType.None][^1].transform.Find("Fill").GetComponent<Image>().fillAmount}" +
    //             $"None energy in display.");
    //     }
    // }

    private void Start()
    {
        EventBus.Instance.combatStarted.AddListener(OnCombatStarted);
    }
    
    public bool Full()
    {
        if (full)
        {
            return true;
        }
        
        float totalEnergy = 0;
        foreach (var type in storedEnergy.Values)
        {
            totalEnergy += type;
        }

        var overFull = totalEnergy > maxStoredEnergy;

        if (overFull)
        {
            full = true;
            foreach (var key in storedEnergy.Keys.ToList())
            {
                storedEnergy[key] = Mathf.Round(storedEnergy[key]);
            }
            UpdateDisplay(storedEnergy);
        }
        
        return full;
    }

    public void UpdateDisplay(Dictionary<Common.SoundType, float> energyInReactor)
    {
        if (invisible) return;
        
        // Debug.Log("Updating display cells");
        foreach (var kvp in energyInReactor)
        {
            var difference = kvp.Value - EnergyAmount(kvp.Key);
            ChangeEnergy(kvp.Key, difference);
        }
    }
    
    public bool TrySpendEnergy(Dictionary<Common.SoundType, float> cost)
    {
        // if (health <= 0)
        // {
        //     return false;
        // }
        
        // before we start actually removing any energy, make sure we have enough of each type
        foreach (var key in cost.Keys)
        {
            if (storedEnergy.ContainsKey(key) && storedEnergy[key] >= cost[key])
            {
                continue;
            }

            return false;
        }
        
        full = false;

        // ok now we actually remove the energy
        foreach (var key in cost.Keys)
        {
            storedEnergy[key] -= cost[key];
            UpdateDisplay(storedEnergy);
            
            // Debug.Log($"Removed {cost[key]} energy of type {key}.");
        }

        return true;
    }

    private void ChangeEnergy(Common.SoundType type, float amount)
    {
        if (invisible) return;

        if (full)
        {
            var emptyModules = new List<GameObject>();
            for (var i = 0; i < grid.transform.childCount; i++)
            {
                if (grid.transform.GetChild(i).Find("Fill").gameObject.GetComponent<Image>().fillAmount < .1f)
                {
                    emptyModules.Add(grid.transform.GetChild(i).gameObject);
                }
            }
            emptyModules.ForEach(DestroyImmediate);

            foreach (var list in energyCells)
            {
                var indices = new List<int>();
                for (int i = 0; i < list.Value.Count; i++)
                {
                    if (list.Value[i] == null)
                    {
                        indices.Add(i);
                    }
                }

                foreach (var i in indices)
                {
                    list.Value.RemoveAt(i);
                }
            }
        }
        
        // no change -> return
        if (amount == 0)
        {
            return;
        }
        
        // first time setup
        if (energyCells[type].Count == 0)
        {
            AddEnergyBar(type, 0);
        }
        
        // get the current fill of the last bar in the display
        var lastEnergyBar = energyCells[type][^1];
        var remainder = lastEnergyBar.transform.Find("Fill").GetComponent<Image>().fillAmount;
        // add the change amount to that bar
        remainder += amount;
        // if it overflows, make a new bar
        if (remainder > 1)
        {
            energyCells[type][^1].transform.Find("Fill").GetComponent<Image>().fillAmount = 1;
            AddEnergyBar(type, remainder - 1);
        }
        // and vice versa if we're subtracting energy
        else if (remainder < 0)
        {
            RemoveEnergyBar(type, amount);
        }
        // otherwise reapply the new amount to the last bar
        else
        {
            energyCells[type][^1].transform.Find("Fill").GetComponent<Image>().fillAmount = remainder;
        }
    }

    public void AddEnergy(Dictionary<Common.SoundType, float> energyToAdd)
    {
        if (!Full())
        {
            // Debug.Log("Adding energy for real now");
            foreach (var kvp in energyToAdd)
            {
                storedEnergy[kvp.Key] += kvp.Value * Time.deltaTime;
                // Debug.Log($"Added {kvp.Value * Time.deltaTime} {kvp.Value} energy");
            }
        }
        else
        {
            // Debug.Log("Energy full");
            foreach (var kvp in energyToAdd)
            {
                var totalEnergy = storedEnergy.Values.Sum();
                for (var i = 0; i < storedEnergy.Count; i++)
                {
                    var key = storedEnergy.ElementAt(i).Key;
                    storedEnergy[key] -= kvp.Value * (storedEnergy.ElementAt(i).Value / totalEnergy) * Time.deltaTime;
                }
                storedEnergy[kvp.Key] += kvp.Value * Time.deltaTime;
            }
        }
        
        UpdateDisplay(storedEnergy);
    }

    private void AddEnergyBar(Common.SoundType type, float remainder)
    {
        if (invisible) return;
        
        // if the remainder is still more than 1 (unlikely), we need to call this function again
        var trueRemainder = remainder;
        if (remainder > 1)
        {
            remainder = 1;
        }
        var newEnergyBar = Instantiate(energyBarPrefab, grid.transform);

        switch (type)
        {
            case Common.SoundType.Pure:
                newEnergyBar.transform.Find("Fill").GetComponent<Image>().sprite =
                    Resources.Load<Sprite>("Sprites/NormalBall");
                break;
            case Common.SoundType.Izki:
                newEnergyBar.transform.Find("Fill").GetComponent<Image>().sprite =
                    Resources.Load<Sprite>("Sprites/IzkiBall");
                break;
            case Common.SoundType.Aubo:
                newEnergyBar.transform.Find("Fill").GetComponent<Image>().sprite =
                    Resources.Load<Sprite>("Sprites/AuboBall");
                break;
            case Common.SoundType.Dwth:
                newEnergyBar.transform.Find("Fill").GetComponent<Image>().sprite =
                    Resources.Load<Sprite>("Sprites/DwthBall");
                break;
        }

        newEnergyBar.transform.Find("Fill").GetComponent<Image>().fillAmount = remainder % 1;
        
        if (energyCells[type].Count > 0)
        {
            newEnergyBar.transform.SetSiblingIndex(energyCells[type][^1].transform.GetSiblingIndex() + 1);
        }
        else
        {
            switch (type)
            {
                case Common.SoundType.Pure:
                    newEnergyBar.transform.SetSiblingIndex(1);
                    break;
                case Common.SoundType.Izki:
                    if (energyCells[Common.SoundType.Pure].Count > 0)
                    {
                        newEnergyBar.transform.SetSiblingIndex(energyCells[Common.SoundType.Pure][^1].transform.GetSiblingIndex() + 1);
                    }
                    else
                    {
                        newEnergyBar.transform.SetSiblingIndex(1);
                    }
                    break;
                case Common.SoundType.Aubo:
                    if (energyCells[Common.SoundType.Izki].Count > 0)
                    {
                        newEnergyBar.transform.SetSiblingIndex(energyCells[Common.SoundType.Izki][^1].transform.GetSiblingIndex() + 1);
                    }
                    else if (energyCells[Common.SoundType.Pure].Count > 0)
                    {
                        newEnergyBar.transform.SetSiblingIndex(energyCells[Common.SoundType.Pure][^1].transform.GetSiblingIndex() + 1);
                    }
                    else
                    {
                        newEnergyBar.transform.SetSiblingIndex(1);
                    }
                    break;
                case Common.SoundType.Dwth:
                    if (energyCells[Common.SoundType.Aubo].Count > 0)
                    {
                        newEnergyBar.transform.SetSiblingIndex(energyCells[Common.SoundType.Aubo][^1].transform.GetSiblingIndex() + 1);
                    }
                    else if (energyCells[Common.SoundType.Izki].Count > 0)
                    {
                        newEnergyBar.transform.SetSiblingIndex(energyCells[Common.SoundType.Izki][^1].transform.GetSiblingIndex() + 1);
                    }
                    else if (energyCells[Common.SoundType.Pure].Count > 0)
                    {
                        newEnergyBar.transform.SetSiblingIndex(energyCells[Common.SoundType.Pure][^1].transform.GetSiblingIndex() + 1);
                    }
                    else
                    {
                        newEnergyBar.transform.SetSiblingIndex(1);
                    }
                    break;
            }
        }

        energyCells[type].Add(newEnergyBar);

        // part 2 of the bit at the start, we stored the true remainder, and now we're decrementing
        // the remainder by 1 (the amount we set this time) before calling it again
        // I know recursion is bad but trust
        if (trueRemainder > 1)
        {
            Debug.Log("REcuRSION COWABUNFGA !!! dude");
            AddEnergyBar(type, trueRemainder - 1);
        }
    }

    private void RemoveEnergyBar(Common.SoundType type, float amount)
    {
        if (invisible) return;
        
        // if (Mathf.Abs(remainder) < 1) remainder--;
        // Debug.Log($"There was {energy[type].Count-1 + energy[type][^1].transform.Find("Fill").GetComponent<Image>().fillAmount} {type} energy. " +
        //           $"Removing {amount}.");
        for (int i = 0; i < (int)Mathf.Abs(amount); i++)
        {
            var remainder = energyCells[type][^1].transform.Find("Fill").GetComponent<Image>().fillAmount;
            Destroy(energyCells[type][^1]);
            energyCells[type].RemoveAt(energyCells[type].Count - 1);
            if (energyCells[type].Count == 0) break;
            energyCells[type][^1].transform.Find("Fill").GetComponent<Image>().fillAmount = remainder;
        }
        // Debug.Log($"There is now {energy[type].Count-1 + energy[type][^1].transform.Find("Fill").GetComponent<Image>().fillAmount} {type} energy.");
        // Debug.Log($"The correct value should be {Reactor.Instance.storedEnergy[type]}.");
    }

    private float EnergyAmount(Common.SoundType type)
    {
        if (energyCells[type].Count == 0)
        {
            return 0;
        }

        var amt = energyCells[type].Count - 1 +
              energyCells[type][^1].transform.Find("Fill").GetComponent<Image>().fillAmount;
        return amt;
    }
    
    private void OnCombatStarted()
    {
        // Debug.Log($"{name} has {storedEnergy[Common.SoundType.None]} stored energy.");
        var allEnergy = new Dictionary<Common.SoundType, float>(storedEnergy);
        TrySpendEnergy(allEnergy);
        // Debug.Log($"After TrySpendEnergy(), {name} has {storedEnergy[Common.SoundType.None]} stored energy.");
    }
}
