using SaintsField;
using TMPro;
using UnityEngine;
using UnityEngine.Events;

public class RackEditPanel : MonoBehaviour
{
    [OnValueChanged(nameof(nameChanged))] public TextMeshPro label;
    [OnValueChanged(nameof(nameChanged))] public GameObject targetRack;
    private void nameChanged() { if (label == null || targetRack == null) return; label.text = targetRack.name;}
    
    public GameObject xUpButton;
    public GameObject xDownButton;
    public GameObject yUpButton;
    public GameObject yDownButton;
    public GameObject deleteButton;

    public TextMeshPro xDisplay;
    public TextMeshPro yDisplay;
    
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        xUpButton.GetComponent<Button2D>().eventGameObjectArg = targetRack;
        xDownButton.GetComponent<Button2D>().eventGameObjectArg = targetRack;
        yUpButton.GetComponent<Button2D>().eventGameObjectArg = targetRack;
        yDownButton.GetComponent<Button2D>().eventGameObjectArg = targetRack;
        
        deleteButton.GetComponent<Button2D>().eventGameObjectArg = targetRack;
        deleteButton.GetComponent<Button2D>().eventString = "weaponDeleted";
        
        nameChanged();
    }

    void Update()
    {
        xDisplay.text = targetRack.GetComponent<ModuleRack>().dimensions.x.ToString();
        yDisplay.text = targetRack.GetComponent<ModuleRack>().dimensions.y.ToString();

        GetComponentInChildren<SpriteRenderer>().color = targetRack.activeSelf ? Color.black : Color.gray;
    }
}
