using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using SaintsField;
using SaintsField.Playa;
using TMPro;
using UnityEngine;

public class CollapsibleValueBlock : MonoBehaviour
{
    [ShowInInspector] public Dictionary<string, GameObject> valueFields = new();
    private Dictionary<string, object> defaultValues = new();

    public void SetValuesFromShipData(ShipData shipData)
    {
        // get a list of all the fields in the shipData
        var fields = new List<FieldInfo>();
        foreach (var field in shipData.GetType().GetFields())
        {
            fields.Add(field);
        }
        
        // reset defaultValues to match new shipData
        defaultValues.Clear();
        
        // check to see if this CVB has that field, then set it
        foreach (var field in fields)
        {
            if (valueFields.ContainsKey(field.Name))
            {
                SetValue(valueFields[field.Name], field.GetValue(shipData));
                defaultValues.Add(field.Name, field.GetValue(shipData));
            }
        }
    }
    
    public void ResetValue(GameObject valueFieldObj)
    {
        foreach (var field in defaultValues)
        {
            SetValue(valueFields[field.Key], field.Value);
        }
    }

    public void SetValue(GameObject valueFieldObj, object value)
    {
        if (valueFieldObj.TryGetComponent(out TMP_InputField inputField))
        {
            switch (inputField.contentType)
            {
                case TMP_InputField.ContentType.Standard:
                    inputField.text = value.ToString();
                    break;
                case TMP_InputField.ContentType.DecimalNumber:
                    inputField.text = value.ToString();
                    break;
                case TMP_InputField.ContentType.IntegerNumber:
                    inputField.text = value.ToString();
                    break;
            }
            inputField.onEndEdit.Invoke(inputField.text);
        }
        else if (valueFieldObj.TryGetComponent(out TMP_Dropdown dropdown))
        {
            if (value is Enum e)
            {
                // dropdown.value = e.
            }
            else
            {
                dropdown.value = 0;
            }
            dropdown.onValueChanged.Invoke(dropdown.value);
        }
    }
}
