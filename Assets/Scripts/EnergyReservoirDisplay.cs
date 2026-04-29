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

    public void ChangeEnergy(Common.SoundType type, float amount)
    {
        if (energy[type].Count == 0)
        {
            AddEnergyBar(type, 0);
        }
        
        var lastEnergyBar = energy[type][^1];
        var remainder = lastEnergyBar.transform.Find("Fill").GetComponent<Image>().fillAmount;
        remainder += amount;
        if (remainder > 1)
        {
            AddEnergyBar(type, remainder);
        }
        else if (remainder < 0)
        {
            RemoveEnergyBar(type, amount);
        }
        else
        {
            energy[type][^1].transform.Find("Fill").GetComponent<Image>().fillAmount = remainder;
        }
    }

    private void AddEnergyBar(Common.SoundType type, float remainder)
    {
        if (remainder < 1) remainder++;
        
        for (int i = 0; i < (int)remainder; i++)
        {
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
        }
    }

    private void RemoveEnergyBar(Common.SoundType type, float amount)
    {
        // if (Mathf.Abs(remainder) < 1) remainder--;
        Debug.Log($"There were {energy[type].Count-1 + energy[type][^1].transform.Find("Fill").GetComponent<Image>().fillAmount} energy blocks. " +
                  $"Removing {amount} energy of type {type}.");
        for (int i = 0; i < (int)Mathf.Abs(amount); i++)
        {
            var remainder = energy[type][^1].transform.Find("Fill").GetComponent<Image>().fillAmount;
            Destroy(energy[type][^1]);
            energy[type].RemoveAt(energy[type].Count - 1);
            energy[type][^1].transform.Find("Fill").GetComponent<Image>().fillAmount = remainder;
        }
        Debug.Log($"There are now {energy[type].Count-1 + energy[type][^1].transform.Find("Fill").GetComponent<Image>().fillAmount} energy blocks.");
        Debug.Log($"The correct value should be {Reactor.Instance.storedEnergy[type]}.");
    }
}
