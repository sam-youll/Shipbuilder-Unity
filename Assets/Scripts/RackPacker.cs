using System.Collections.Generic;
using SaintsField;
using TMPro;
using UnityEngine;

public class RackPacker : MonoBehaviour
{
    public static RackPacker Instance;
    
    // index 0 is always the reactor, the rest are weapons
    public List<GameObject> racks = new();
    public List<GameObject> panels = new();
    public GameObject addWeaponButton;
    
    // transform.position is top left
    public Vector2Int bounds = new(24, 12);

    // how much space should be left between racks
    public float margin = 1;

    private bool needsUpdate;
    
    private void Start()
    {
        EventBus.Instance.rackEditXUp.AddListener(NeedsUpdate);
        EventBus.Instance.rackEditXDown.AddListener(NeedsUpdate);
        EventBus.Instance.rackEditYUp.AddListener(NeedsUpdate);
        EventBus.Instance.rackEditYDown.AddListener(NeedsUpdate);
        
        var reactor = Instantiate(Resources.Load<GameObject>("Prefabs/Racks/Reactor"), transform, true);
        reactor.name = "Reactor";
        racks.Add(reactor);
        
        PackRacks();
        
        AddPanel();

        addWeaponButton = Instantiate(Resources.Load<GameObject>("Prefabs/Button"), transform, true);
        addWeaponButton.transform.position = new Vector3(-10, 7, -2);
        var button = addWeaponButton.GetComponent<Button2D>();
        button.eventBus = EventBus.Instance;
        button.eventString = "weaponAdded";
        
        EventBus.Instance.weaponAdded.AddListener(OnWeaponAdded);
        EventBus.Instance.weaponDeleted.AddListener(OnWeaponDeleted);
        
        ShipManager.Instance.SetPlayerReactor(reactor.GetComponent<Reactor>());
    }

    private void Update()
    {
        var tl = (Vector2)transform.position + new Vector2(-bounds.x*.5f, bounds.y*.5f);
        var tr = (Vector2)transform.position + new Vector2(bounds.x*.5f, bounds.y*.5f);
        var bl = (Vector2)transform.position + new Vector2(-bounds.x*.5f, -bounds.y*.5f);
        var br = (Vector2)transform.position + new Vector2(bounds.x*.5f, -bounds.y*.5f);
        Debug.DrawLine(tl, tr, Color.red);
        Debug.DrawLine(tr, br, Color.red);
        Debug.DrawLine(br, bl, Color.red);
        Debug.DrawLine(bl, tl, Color.red);

        if (needsUpdate)
        {
            needsUpdate = false;
            PackRacks();
        }
    }

    // I know this is stupid, don't worry about it.
    // I just need it to wait a frame before checking the dimensions of the rack.
    private void NeedsUpdate(GameObject go)
    {
        needsUpdate = true;
    }
    
    // NOTE: Module racks must be on a whole number position if the dimension is even, .5 if odd.
    // If they are misaligned, the modules will be misaligned to the grid.
    private void PackRacks()
    {
        foreach (var rack in racks)
        {
            rack.SetActive(true);
        }
        
        Debug.Log("Packing Racks");
        for (var i = 0; i < racks.Count; i++)
        {
            Debug.Log($"Packing {racks[i].name}.");
            var rack = racks[i].GetComponent<ModuleRack>();
            var pos = (Vector2)transform.position + 
                      new Vector2(-bounds.x*.5f, bounds.y*.5f) + 
                      new Vector2((rack.dimensions.x) * .5f + margin, -(rack.dimensions.y) * .5f - margin);
            var validPos = false;
            var counter = 0;
            Debug.Log($"Checking if {pos} is valid.");
            while (!validPos)
            {
                validPos = true;
                var halfMargin = Vector2.one * margin;
                Rect myRect;
                if (i > 0)
                {
                    for (var j = 0; j < i; j++)
                    {
                        var prevRect = new Rect(
                            (Vector2)racks[j].transform.position -
                            (Vector2)racks[j].GetComponent<ModuleRack>().dimensions * .5f - halfMargin,
                            racks[j].GetComponent<ModuleRack>().dimensions + Vector2.one * 2 * margin);
                        myRect = new Rect(pos - (Vector2)rack.dimensions * .5f - halfMargin,
                            rack.dimensions + Vector2.one * 2 * margin);

                        if (myRect.Overlaps(prevRect))
                        {
                            Debug.Log($"{pos} overlaps with {racks[j].name}. Checking new pos.");
                            // Debug.Log($"PrevMin: {prevRect.min.y}, MyMax: {myRect.max.y}");
                            validPos = false;
                            pos.y -= .5f;
                            break;
                        }
                    }
                }
                
                var boundsRect = new Rect((Vector2)transform.position + new Vector2(-bounds.x * .5f, -bounds.y * .5f), bounds);
                myRect = new Rect(pos - (Vector2)rack.dimensions * .5f - halfMargin, rack.dimensions + Vector2.one * margin);
                if (!boundsRect.Contains(myRect.min) ||
                    !boundsRect.Contains(myRect.max))
                {
                    // Debug.Log($"({myRect.min},{myRect.max}) is out of bounds ({boundsRect.min},{boundsRect.max}). Checking new pos.");
                    Debug.Log($"{pos} is out of bounds.");
                    validPos = false;
                    pos.x += .5f;
                    pos.y = transform.position.y + bounds.y * .5f - (rack.dimensions.y) * .5f - margin;
                }

                counter++;
                if (counter > 800)
                {
                    Debug.Log("No valid positions.");
                    racks[i].SetActive(false);
                    break;
                }
            }
            racks[i].transform.position = pos;
            Debug.Log($"{racks[i].name} packed successfully.");
        }
    }

    private void OnWeaponAdded()
    {
        var pos = addWeaponButton.transform.position;
        pos.x += 3;
        addWeaponButton.transform.position = pos;
        
        AddWeapon();
        AddPanel();
    }

    private void OnWeaponDeleted(GameObject target)
    {
        var pos = addWeaponButton.transform.position;
        pos.x -= 3;
        addWeaponButton.transform.position = pos;

        DeleteWeapon(target);
        DeletePanel();
    }
    
    private void AddWeapon()
    {
        var weapon = Instantiate(Resources.Load<GameObject>("Prefabs/Racks/Weapon"));
        weapon.name = "Weapon " + racks.Count;
        weapon.GetComponentInChildren<TextMeshPro>().text = weapon.name;
        weapon.GetComponent<Weapon>().warming = true;
        racks.Add(weapon);
        PackRacks();
    }

    private void AddPanel()
    {
        var panel = Instantiate(Resources.Load<GameObject>("Prefabs/Racks/Rack Edit Panel"), transform, true);
        panel.transform.position = new Vector3(-13 + 3 * panels.Count, 7, -2);
        panel.GetComponent<RackEditPanel>().targetRack = racks[panels.Count];
        panel.name = racks[panels.Count].name + " Editor";
        panel.GetComponentInChildren<TextMeshPro>().text = panel.name;
        panels.Add(panel);

        if (panels.Count == 1)
        {
            panel.transform.GetChild(panel.transform.childCount-1).gameObject.SetActive(false);
        }
    }

    private void DeleteWeapon(GameObject target)
    {
        racks.Remove(target);
        Destroy(target);
        PackRacks();
    }

    private void DeletePanel()
    {
        var foundMismatch = -1;
        for (var i = 0; i < panels.Count; i++)
        {
            var panel = panels[i];
            var hasMatch = false;
            foreach (var rack in racks)
            {
                if (panel.GetComponent<RackEditPanel>().targetRack == rack)
                {
                    hasMatch = true;
                }
            }

            if (!hasMatch)
            {
                Destroy(panel.gameObject);
                foundMismatch = i;
            }

            if (foundMismatch != -1)
            {
                var pos = panel.transform.position;
                pos.x -= 3;
                panel.transform.position = pos;
            }
        }
        panels.RemoveAt(foundMismatch);

        RenamePanels();
    }

    private void RenamePanels()
    {
        for (var i = 0; i < panels.Count; i++)
        {
            if (i == 0) continue;

            var name = "Weapon " + i;
            panels[i].name = name + " Editor";
            panels[i].GetComponentInChildren<TextMeshPro>().text = name + " Editor";
            racks[i].name = name;
            racks[i].GetComponentInChildren<TextMeshPro>().text = name;
        }
    }
}
