using System;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.Serialization;
using UnityEngine.UI;

public interface ITooltipInfo
{
    public string Description();
    public string Info();
    public bool Warning(out string message);
}

public class Tooltip : MonoBehaviour
{
    public TextMeshProUGUI nameLabel;
    public TextMeshProUGUI descriptionLabel;
    [FormerlySerializedAs("infoLabel")] public TextMeshProUGUI warningLabel;
    public LayoutElement layoutElement;
    public GameObject energyCostGroup;
    public GameObject pureEnergyCost;
    public GameObject izkiEnergyCost;
    public GameObject auboEnergyCost;
    public GameObject dwthEnergyCost;
    public float maxWidth = 5;

    public void SetText(string text)
    {
        return;
    }

    private void Update()
    {
        var gb = .325f + .125f * Mathf.Sin(5 * Time.time);
        warningLabel.color = new Color(1, gb, gb);
    }

    /// <summary>
    /// Update all parameters of tooltip.
    /// </summary>
    /// <param name="target">GameObject the tooltip will display info about.</param>
    public void UpdateTooltip(GameObject target)
    {
        if (target.TryGetComponent(out ShopSlotPanel ssp))
        {
            if (ssp.itemForSale != null)
            {
                target = ssp.itemForSale;
            }
        }
        nameLabel.text = target.name;
        descriptionLabel.text = "";
        warningLabel.text = "";
        if (target.TryGetComponent(out ITooltipInfo tooltip))
        {
            var labelText = tooltip.Description() + "\n~~~\n" + tooltip.Info();
            if (target.TryGetComponent(out Module mod))
            {
                if (mod.heat > 0)
                {
                    labelText += "\nGenerates " + mod.heat + " heat per trigger.";
                }
            }
            descriptionLabel.text = labelText;
            
            if (tooltip.Warning(out string message))
            {
                warningLabel.gameObject.SetActive(true);
                warningLabel.text = message;
            }
            else
            {
                warningLabel.gameObject.SetActive(false);
            }
        }

        if (target.TryGetComponent(out INeedEnergy energy))
        {
            var energyCost = energy.ChangeEnergyCost(new Dictionary<Common.SoundType, float>(Common.EmptyEnergyCost()));
            var energySum = 0f;
            foreach (var kvp in energyCost)
            {
                energySum += kvp.Value;
            }
            // Debug.Log(energySum);
            if (energySum > 0)
            {
                energyCostGroup.SetActive(true);
                // Debug.Log("Showing energy cost");
                
                if (energyCost[Common.SoundType.Pure] > 0)
                {
                    pureEnergyCost.SetActive(true);
                    pureEnergyCost.transform.GetChild(0).GetComponent<TextMeshProUGUI>().text =
                        energyCost[Common.SoundType.Pure].ToString();
                }
                else
                {
                    pureEnergyCost.SetActive(false);
                }
                if (energyCost[Common.SoundType.Izki] > 0)
                {
                    izkiEnergyCost.SetActive(true);
                    izkiEnergyCost.transform.GetChild(0).GetComponent<TextMeshProUGUI>().text =
                        energyCost[Common.SoundType.Izki].ToString();
                }
                else
                {
                    izkiEnergyCost.SetActive(false);
                }
                if (energyCost[Common.SoundType.Aubo] > 0)
                {
                    auboEnergyCost.SetActive(true);
                    auboEnergyCost.transform.GetChild(0).GetComponent<TextMeshProUGUI>().text =
                        energyCost[Common.SoundType.Aubo].ToString();
                }
                else
                {
                    auboEnergyCost.SetActive(false);
                }
                if (energyCost[Common.SoundType.Dwth] > 0)
                {
                    dwthEnergyCost.SetActive(true);
                    dwthEnergyCost.transform.GetChild(0).GetComponent<TextMeshProUGUI>().text =
                        energyCost[Common.SoundType.Izki].ToString();
                }
                else
                {
                    dwthEnergyCost.SetActive(false);
                }
            }
            else
            {
                energyCostGroup.SetActive(false);
                // Debug.Log("Hiding energy cost");
            }
        }
        else
        {
            energyCostGroup.SetActive(false);
        }
        
        if (target.TryGetComponent(out Weapon weapon))
        {
            var energySum = 0f;
            var energyCost = new Dictionary<Common.SoundType, float>(Common.EmptyEnergyCost());
            foreach (var mod in weapon.ActivePatch())
            {
                if (mod.TryGetComponent(out INeedEnergy eMod))
                {
                    energyCost = eMod.ChangeEnergyCost(energyCost);
                }
            }
            foreach (var kvp in energyCost)
            {
                energySum += kvp.Value;
            }
            if (energySum > 0)
            {
                energyCostGroup.SetActive(true);

                if (energyCost[Common.SoundType.Pure] > 0)
                {
                    pureEnergyCost.SetActive(true);
                    pureEnergyCost.transform.GetChild(0).GetComponent<TextMeshProUGUI>().text =
                        energyCost[Common.SoundType.Pure].ToString();
                }
                else
                {
                    pureEnergyCost.SetActive(false);
                }
                if (energyCost[Common.SoundType.Izki] > 0)
                {
                    izkiEnergyCost.SetActive(true);
                    izkiEnergyCost.transform.GetChild(0).GetComponent<TextMeshProUGUI>().text =
                        energyCost[Common.SoundType.Izki].ToString();
                }
                else
                {
                    izkiEnergyCost.SetActive(false);
                }
                if (energyCost[Common.SoundType.Aubo] > 0)
                {
                    auboEnergyCost.SetActive(true);
                    auboEnergyCost.transform.GetChild(0).GetComponent<TextMeshProUGUI>().text =
                        energyCost[Common.SoundType.Aubo].ToString();
                }
                else
                {
                    auboEnergyCost.SetActive(false);
                }
                if (energyCost[Common.SoundType.Dwth] > 0)
                {
                    dwthEnergyCost.SetActive(true);
                    dwthEnergyCost.transform.GetChild(0).GetComponent<TextMeshProUGUI>().text =
                        energyCost[Common.SoundType.Izki].ToString();
                }
                else
                {
                    dwthEnergyCost.SetActive(false);
                }
            }
            else
            {
                energyCostGroup.SetActive(false);
            }
        }

        // layoutElement.enabled = descriptionLabel.textBounds.size.x >= maxWidth || infoLabel.textBounds.size.x >= maxWidth;
        GetComponent<RectTransform>().sizeDelta = new Vector2(GetComponent<RectTransform>().sizeDelta.x, transform.GetChild(0).gameObject.GetComponent<RectTransform>().sizeDelta.y + .25f);

        
        // var coll = target.GetComponent<Collider2D>();
        //
        // // position tooltip just outside (top right) of target's collider
        // var pos = coll.bounds.center;
        // pos.x += .5f * coll.bounds.size.x;
        // pos.x -= 1f * GetComponent<RectTransform>().rect.x - .5f;
        // pos.y += .5f * coll.bounds.size.y + .39f;
        // pos.y += 1f * GetComponent<RectTransform>().rect.y - .5f;
        // pos.z = target.transform.position.z;
        // pos.z -= 1;
        // make sure collider is visible (within bounds of camera)
        // var cam = Global.Instance.cam;
        // var height = cam.orthographicSize;
        // var width = cam.aspect * height;
        // pos.x = Mathf.Clamp(pos.x, -width - 1f * GetComponent<RectTransform>().rect.x + .25f, width + 1f * GetComponent<RectTransform>().rect.x - .25f);
        // pos.y = Mathf.Clamp(pos.y, -height - 1f * GetComponent<RectTransform>().rect.y + .25f, height + 1f * GetComponent<RectTransform>().rect.y - .25f);
        // pos = Camera.main.WorldToScreenPoint(pos);
        transform.position = UIManager.Instance.cursor.transform.position + 10 * Vector3.right;

        // Debug.Log($"Coll pos = {coll.transform.position}. Coll size = {coll.bounds.size}. SR size = {sr.size}. Final pos = {pos}.");

        // TODO: check to make sure tooltip doesn't go off screen

    }
    
    // void DrawBounds(Bounds b, Color color)
    // {
    //     Vector3 min = b.min;
    //     Vector3 max = b.max;
    //
    //     Vector3[] corners = new Vector3[8];
    //     // Bottom
    //     corners[0] = new Vector3(min.x, min.y, min.z);
    //     corners[1] = new Vector3(max.x, min.y, min.z);
    //     corners[2] = new Vector3(max.x, min.y, max.z);
    //     corners[3] = new Vector3(min.x, min.y, max.z);
    //     // Top
    //     corners[4] = new Vector3(min.x, max.y, min.z);
    //     corners[5] = new Vector3(max.x, max.y, min.z);
    //     corners[6] = new Vector3(max.x, max.y, max.z);
    //     corners[7] = new Vector3(min.x, max.y, max.z);
    //
    //     // Bottom rectangle
    //     Debug.DrawLine(corners[0], corners[1], color);
    //     Debug.DrawLine(corners[1], corners[2], color);
    //     Debug.DrawLine(corners[2], corners[3], color);
    //     Debug.DrawLine(corners[3], corners[0], color);
    //
    //     // Top rectangle
    //     Debug.DrawLine(corners[4], corners[5], color);
    //     Debug.DrawLine(corners[5], corners[6], color);
    //     Debug.DrawLine(corners[6], corners[7], color);
    //     Debug.DrawLine(corners[7], corners[4], color);
    //
    //     // Vertical edges
    //     Debug.DrawLine(corners[0], corners[4], color);
    //     Debug.DrawLine(corners[1], corners[5], color);
    //     Debug.DrawLine(corners[2], corners[6], color);
    //     Debug.DrawLine(corners[3], corners[7], color);
    // }
}
