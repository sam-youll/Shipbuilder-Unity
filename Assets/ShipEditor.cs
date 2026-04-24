using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.UI;

public class ShipEditor : MonoBehaviour
{
    public ShipData shipData;
    private List<ShipData> shipList = new();
    public TMP_Dropdown shipSelector;

    public GameObject verticalLayout;
    public GameObject weaponEditorPrefab;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        shipSelector.ClearOptions();
        foreach (var ship in Resources.LoadAll<ShipData>("Ships"))
        {
            shipList.Add(ship);
        }

        var nameList = new List<string>();
        foreach (var ship in shipList)
        {
            nameList.Add(ship.name);
        }
        shipSelector.AddOptions(nameList);
        
        RefreshLayoutGroupsImmediateAndRecursive(transform.parent.gameObject);
    }

    // Update is called once per frame
    void Update()
    {
        // Canvas.ForceUpdateCanvases();
        // LayoutRebuilder.ForceRebuildLayoutImmediate(GetComponent<RectTransform>());
        
    }

    public void LoadShipData(GameObject dropdownObj)
    {
        if (dropdownObj.TryGetComponent(out TMP_Dropdown dropdown))
        {
            shipData = shipList[dropdown.value];
        }

        ShipManager.Instance.InitPlayerShip(shipData);
        SetFieldsFromShipData();
    }

    private void SetFieldsFromShipData()
    {
        for (var i = 0; i < verticalLayout.transform.childCount; i++)
        {
            var child = verticalLayout.transform.GetChild(i);
            if (child.TryGetComponent(out CollapsibleValueBlock cvb))
            {
                
            }
        }
    }
    
    public void ResetValue(GameObject inputFieldObj)
    {
        if (inputFieldObj.TryGetComponent(out TMP_InputField inputField))
        {
            switch (inputField.contentType)
            {
                case TMP_InputField.ContentType.Standard:
                    inputField.text = "";
                    break;
                case TMP_InputField.ContentType.DecimalNumber:
                    inputField.text = "0";
                    break;
                case TMP_InputField.ContentType.IntegerNumber:
                    inputField.text = "0";
                    break;
            }
            inputField.onEndEdit.Invoke(inputField.text);
        }
        else if (inputFieldObj.TryGetComponent(out TMP_Dropdown dropdown))
        {
            dropdown.value = 0;
        }
    }

    public void AddWeapon()
    {
        var newWeapon = Instantiate(weaponEditorPrefab, verticalLayout.transform);
        newWeapon.name = "New Weapon";
        var headerButton = newWeapon.transform.Find("Header/Collapsible Header").GetComponent<Button>();
        headerButton.onClick.AddListener(() => ExpandCollapse(newWeapon));
        var deleteButton = newWeapon.transform.Find("Header/Delete Button").GetComponent<Button>();
        deleteButton.onClick.AddListener(() => DeleteCollapsibleBlock(newWeapon));
        
        verticalLayout.transform.Find("Add Weapon Button").SetAsLastSibling();
        
        RefreshLayoutGroupsImmediateAndRecursive(transform.parent.gameObject);
    }

    public void ExpandCollapse(GameObject self)
    {
        var content = self.transform.Find("Content").gameObject;
        content.SetActive(!content.activeSelf);
        
        var label = self.transform.Find("Header/Collapsible Header").gameObject.GetComponentInChildren<TextMeshProUGUI>();
        label.text = string.Join(" ", label.text.Split(" "), 1, label.text.Split(" ").Length-1);
        switch (content.activeSelf)
        {
            case true:
                label.text = label.text.Insert(0, "<rotate=\"-90\">></rotate> ");
                break;
            case false:
                label.text = label.text.Insert(0, "> ");
                break;
        }

        // LayoutRebuilder.ForceRebuildLayoutImmediate(GetComponent<RectTransform>());
        RefreshLayoutGroupsImmediateAndRecursive(transform.parent.gameObject);
    }

    public void DeleteCollapsibleBlock(GameObject block)
    {
        DestroyImmediate(block);
        RefreshLayoutGroupsImmediateAndRecursive(transform.parent.gameObject);
    }
    
    public static void RefreshLayoutGroupsImmediateAndRecursive(GameObject root)
    {
        foreach (var layoutGroup in root.GetComponentsInChildren<LayoutGroup>())
        {
            LayoutRebuilder.ForceRebuildLayoutImmediate(layoutGroup.GetComponent<RectTransform>());
        }
    }
    
    #region Input fields

    public void SetName(GameObject inputFieldObj)
    {
        if (inputFieldObj.TryGetComponent(out TMP_InputField inputField))
        {
            ShipManager.Instance.SetPlayerName(inputField.text);
        }
    }

    public void SetCurrentHull(GameObject inputFieldObj)
    {
        if (inputFieldObj.TryGetComponent(out TMP_InputField inputField))
        {
            ShipManager.Instance.SetPlayerHull(float.Parse(inputField.text), false);
        }
    }

    public void SetMaxHull(GameObject inputFieldObj)
    {
        if (inputFieldObj.TryGetComponent(out TMP_InputField inputField))
        {
            ShipManager.Instance.SetPlayerHull(float.Parse(inputField.text), true);
        }
    }

    public void SetEvasion(GameObject inputFieldObj)
    {
        if (inputFieldObj.TryGetComponent(out TMP_InputField inputField))
        {
            ShipManager.Instance.SetPlayerEvasion(float.Parse(inputField.text));
        }
    }
    
    #endregion
}
