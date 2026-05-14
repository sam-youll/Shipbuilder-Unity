using System;
using System.Collections.Generic;
using SaintsField;
using UnityEngine;
using UnityEngine.UI;

public class EnergyReservoirDisplay : MonoBehaviour
{
    private Dictionary<Common.SoundType, List<GameObject>> energy = new()
    {
        { Common.SoundType.None , new List<GameObject>() },
        { Common.SoundType.Izki , new List<GameObject>() },
        { Common.SoundType.Aubo , new List<GameObject>() },
        { Common.SoundType.Dwth , new List<GameObject>() }
    };
    [GetComponent] public GridLayoutGroup grid;
    public GameObject energyBarPrefab;

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

    public void UpdateDisplay(Dictionary<Common.SoundType, float> energyInReactor)
    {
        foreach (var kvp in energyInReactor)
        {
            var difference = kvp.Value - EnergyAmount(kvp.Key);
            ChangeEnergy(kvp.Key, difference);
        }
    }

    private void ChangeEnergy(Common.SoundType type, float amount)
    {
        // no change -> return
        if (amount == 0)
        {
            return;
        }
        
        // first time setup
        if (energy[type].Count == 0)
        {
            AddEnergyBar(type, 0);
        }
        
        // get the current fill of the last bar in the display
        var lastEnergyBar = energy[type][^1];
        var remainder = lastEnergyBar.transform.Find("Fill").GetComponent<Image>().fillAmount;
        // add the change amount to that bar
        remainder += amount;
        // if it overflows, make a new bar
        if (remainder > 1)
        {
            energy[type][^1].transform.Find("Fill").GetComponent<Image>().fillAmount = 1;
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
            energy[type][^1].transform.Find("Fill").GetComponent<Image>().fillAmount = remainder;
        }
    }

    private void AddEnergyBar(Common.SoundType type, float remainder)
    {
        // if the remainder is still more than 1 (unlikely), we need to call this function again
        var trueRemainder = remainder;
        if (remainder > 1)
        {
            remainder = 1;
        }
        var newEnergyBar = Instantiate(energyBarPrefab, grid.transform);

        switch (type)
        {
            case Common.SoundType.None:
                newEnergyBar.transform.Find("Fill").GetComponent<Image>().color = Color.white;
                break;
            case Common.SoundType.Izki:
                newEnergyBar.transform.Find("Fill").GetComponent<Image>().color = Color.yellow;
                break;
            case Common.SoundType.Aubo:
                newEnergyBar.transform.Find("Fill").GetComponent<Image>().color = Color.cyan;
                break;
            case Common.SoundType.Dwth:
                newEnergyBar.transform.Find("Fill").GetComponent<Image>().color = Color.magenta;
                break;
        }

        newEnergyBar.transform.Find("Fill").GetComponent<Image>().fillAmount = remainder % 1;
        
        if (energy[type].Count > 0)
        {
            newEnergyBar.transform.SetSiblingIndex(energy[type][^1].transform.GetSiblingIndex() + 1);
        }
        else
        {
            switch (type)
            {
                case Common.SoundType.None:
                    newEnergyBar.transform.SetSiblingIndex(1);
                    break;
                case Common.SoundType.Izki:
                    if (energy[Common.SoundType.None].Count > 0)
                    {
                        newEnergyBar.transform.SetSiblingIndex(energy[Common.SoundType.None][^1].transform.GetSiblingIndex() + 1);
                    }
                    else
                    {
                        newEnergyBar.transform.SetSiblingIndex(1);
                    }
                    break;
                case Common.SoundType.Aubo:
                    if (energy[Common.SoundType.Izki].Count > 0)
                    {
                        newEnergyBar.transform.SetSiblingIndex(energy[Common.SoundType.Izki][^1].transform.GetSiblingIndex() + 1);
                    }
                    else if (energy[Common.SoundType.None].Count > 0)
                    {
                        newEnergyBar.transform.SetSiblingIndex(energy[Common.SoundType.None][^1].transform.GetSiblingIndex() + 1);
                    }
                    else
                    {
                        newEnergyBar.transform.SetSiblingIndex(1);
                    }
                    break;
                case Common.SoundType.Dwth:
                    if (energy[Common.SoundType.Aubo].Count > 0)
                    {
                        newEnergyBar.transform.SetSiblingIndex(energy[Common.SoundType.Aubo][^1].transform.GetSiblingIndex() + 1);
                    }
                    else if (energy[Common.SoundType.Izki].Count > 0)
                    {
                        newEnergyBar.transform.SetSiblingIndex(energy[Common.SoundType.Izki][^1].transform.GetSiblingIndex() + 1);
                    }
                    else if (energy[Common.SoundType.None].Count > 0)
                    {
                        newEnergyBar.transform.SetSiblingIndex(energy[Common.SoundType.None][^1].transform.GetSiblingIndex() + 1);
                    }
                    else
                    {
                        newEnergyBar.transform.SetSiblingIndex(1);
                    }
                    break;
            }
        }

        energy[type].Add(newEnergyBar);

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
        // if (Mathf.Abs(remainder) < 1) remainder--;
        Debug.Log($"There was {energy[type].Count-1 + energy[type][^1].transform.Find("Fill").GetComponent<Image>().fillAmount} {type} energy. " +
                  $"Removing {amount}.");
        for (int i = 0; i < (int)Mathf.Abs(amount); i++)
        {
            var remainder = energy[type][^1].transform.Find("Fill").GetComponent<Image>().fillAmount;
            Destroy(energy[type][^1]);
            energy[type].RemoveAt(energy[type].Count - 1);
            energy[type][^1].transform.Find("Fill").GetComponent<Image>().fillAmount = remainder;
        }
        Debug.Log($"There is now {energy[type].Count-1 + energy[type][^1].transform.Find("Fill").GetComponent<Image>().fillAmount} {type} energy.");
        // Debug.Log($"The correct value should be {Reactor.Instance.storedEnergy[type]}.");
    }

    private float EnergyAmount(Common.SoundType type)
    {
        if (energy[type].Count == 0)
        {
            return 0;
        }

        return energy[type].Count - 1 + energy[type][^1].transform.Find("Fill").GetComponent<Image>().fillAmount;
    }
}
