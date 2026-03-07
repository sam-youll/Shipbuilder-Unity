using System;
using System.Collections.Generic;
using System.Linq;
using TMPro;
using UnityEngine;
using UnityEngine.SceneManagement;
using Random = System.Random;

public class Inventory : MonoBehaviour
{
    public static Inventory Instance;
    private void Awake()
    {
        if (Instance != null && Instance != this)
        {
            Destroy(this);
        }
        else
        {
            Instance = this;
        }
    }

    public Color defaultColor;
    public Color highlightColor;
    public Vector2 upPos;
    public Vector2 downPos;
    public bool isPulledDown = false;
    public SpriteRenderer sr;

    public float scrap;
    public TextMeshPro creditsLabel;

    public GameObject inventoryOverlay;

    public bool creativeMode;

    public GameObject moduleContainer;

    public GameObject triggerModulesLabel;
    public GameObject primaryModulesLabel;
    public GameObject secondaryModulesLabel;
    public List<GameObject> triggerModules = new();
    public List<GameObject> primaryModules = new();
    public List<GameObject> secondaryModules = new();
    
    void Start()
    {
        SceneManager.sceneLoaded += OnSceneLoaded;
        OnSceneLoaded(SceneManager.GetActiveScene(), LoadSceneMode.Single);
        
        
        CreateHotbar();
        
        if (creativeMode)
        {
            LoadCreativeModeModules();
        }

    }

    private void LoadCreativeModeModules()
    {
        triggerModules = Resources.LoadAll<GameObject>("Prefabs/Modules/Trigger Modules").ToList();
        for (var i = 0; i < triggerModules.Count; i++)
        {
            triggerModules[i] = Instantiate(triggerModules[i]);
            triggerModules[i].SetActive(gameObject.activeSelf);
            triggerModules[i].transform.SetParent(triggerModulesLabel.transform);
        }
        primaryModules = Resources.LoadAll<GameObject>("Prefabs/Modules/Primary Modules").ToList();
        for (var i = 0; i < primaryModules.Count; i++)
        {
            primaryModules[i] = Instantiate(primaryModules[i]);
            primaryModules[i].SetActive(gameObject.activeSelf);
            primaryModules[i].transform.SetParent(primaryModulesLabel.transform);
        }
        secondaryModules = Resources.LoadAll<GameObject>("Prefabs/Modules/Secondary Modules").ToList();
        for (var i = 0; i < secondaryModules.Count; i++)
        {
            secondaryModules[i] = Instantiate(secondaryModules[i]);
            secondaryModules[i].SetActive(gameObject.activeSelf);
            secondaryModules[i].transform.SetParent(secondaryModulesLabel.transform);
        }
    }

    private void OnSceneLoaded(Scene scene, LoadSceneMode mode)
    {
        if (scene.name == "Creative Mode")
        {
            creativeMode = true;
        }
        else
        {
            creativeMode = false;
        }
    }

    private void CreateHotbar()
    {
        inventoryOverlay = Instantiate(Resources.Load<GameObject>("Prefabs/InventoryOverlay"), transform);
        inventoryOverlay.transform.position = new Vector3(-9, 0, -2.5f);
        triggerModulesLabel = inventoryOverlay.transform.Find("Sprite Mask/Module Container/Trigger Modules").gameObject;
        primaryModulesLabel = inventoryOverlay.transform.Find("Sprite Mask/Module Container/Primary Modules").gameObject;
        secondaryModulesLabel = inventoryOverlay.transform.Find("Sprite Mask/Module Container/Secondary Modules").gameObject;
        inventoryOverlay.SetActive(false);
    }

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.E))
        {
            inventoryOverlay.SetActive(!inventoryOverlay.activeSelf);

            for (int i = 0; i < transform.childCount; i++)
            {
                if (transform.GetChild(i).TryGetComponent(out Module module))
                {
                    transform.GetChild(i).gameObject.SetActive(inventoryOverlay.activeSelf);
                }
            }
            
            ArrangeModules();
        }
    }

    public void AddModule(GameObject module)
    {
        Debug.Log("Added " + module.name);
        var pos = Vector3.zero;
        for (int i = 0; i < 36; i++)
        {
            var pos1 = Vector2.zero;
            var pos2 = Vector2.zero;
            
            var empty = true;
            for (int j = 0; j < transform.childCount - 6; j++)
            {
                pos1 = new Vector2(transform.GetChild(5).GetChild(i).position.x, transform.GetChild(5).GetChild(i).position.y);
                pos2 = new Vector2(transform.GetChild(6 + j).position.x, transform.GetChild(6 + j).position.y);
                if (pos1 == pos2)
                {
                    empty = false;
                }
            }

            if (empty)
            {
                pos = new Vector3(pos1.x, pos1.y, -3);
                break;
            }
        }
        var newMod = Instantiate(module, pos, Quaternion.identity);
        newMod.transform.SetParent(gameObject.transform);
    }

    public void ArrangeModules()
    {
        var triggerPos = triggerModulesLabel.transform.position;
        triggerPos.x -= triggerModulesLabel.GetComponent<RectTransform>().rect.width;
        ArrangeModulesOfType(triggerModules, triggerPos);
        if (triggerModules.Count > 0)
        {
            primaryModulesLabel.transform.position = new Vector3(-9,
                triggerModules[^1].transform.position.y - 1 -
                triggerModules[^1].GetComponent<Module>().dimensions.y * .5f, -3);
        }
        var primaryPos = primaryModulesLabel.transform.position;
        primaryPos.x -= primaryModulesLabel.GetComponent<RectTransform>().rect.width;
        ArrangeModulesOfType(primaryModules, primaryPos);
        if (primaryModules.Count > 0)
        {
            secondaryModulesLabel.transform.position = new Vector3(-9,
                primaryModules[^1].transform.position.y - 1 -
                primaryModules[^1].GetComponent<Module>().dimensions.y * .5f, -3);
        }
        var secondaryPos = secondaryModulesLabel.transform.position;
        secondaryPos.x -= secondaryModulesLabel.GetComponent<RectTransform>().rect.width;
        ArrangeModulesOfType(secondaryModules, secondaryPos);
    }

    public void ArrangeModulesOfType(List<GameObject> modulesInInventory, Vector3 headerPos)
    {
        // don't bother if inventory is empty
        if (modulesInInventory.Count == 0) return;
        
        // deactivate modules, so we can activate them one at a time and avoid overlaps
        foreach (var module in modulesInInventory)
        {
            module.SetActive(false);
        }
        
        // force update of all colliders
        Physics2D.SyncTransforms();
        
        // width of allowed space in inventory before moving down a row
        var width = 10;

        for (var i = 0; i < modulesInInventory.Count; i++)
        {
            // initial setup & placement of module
            var module = modulesInInventory[i];
            module.SetActive(true);
            var startPos = new Vector3(-5, -1 - module.GetComponent<Module>().dimensions.y + 1, -.5f);
            module.transform.localPosition = startPos;
            
            Debug.Log($"===== CHECKING {module.name} ======");
            
            // loop through items that have already been placed
            for (var j = 0; j < i; j++)
            {
                Physics2D.SyncTransforms();
                
                // do the modules overlap?
                var otherModule = modulesInInventory[j];
                var myBounds = module.GetComponent<CompositeCollider2D>().bounds;
                var otherBounds = otherModule.GetComponent<CompositeCollider2D>().bounds;
                otherBounds.size += Vector3.one * .5f;
                var loops = 0;
                while (myBounds.Intersects(otherBounds))
                {
                    Debug.Log($"{module.name} is overlapping {otherModule.name}");
                    var newPos = module.transform.localPosition;
                    newPos.x += 1f;
                    if (newPos.x > width * .5f - myBounds.size.x + 1)
                    {
                        newPos.x = -width * .5f;
                        newPos.y -= 1;
                    }
                    module.transform.localPosition = newPos;
                    Physics2D.SyncTransforms();
                    myBounds = module.GetComponent<CompositeCollider2D>().bounds;
                    
                    // this might be really stupid, it might be really smart
                    j = -1;

                    loops++;
                    if (loops > 100) break;
                }
            }
        }
        // set first module to starting position
        // modulesInInventory[0].transform.localPosition = new Vector3(-5, -1 - modulesInInventory[0].GetComponent<Module>().dimensions.y + 1, -.5f);
        //
        // if (modulesInInventory.Count > 1)
        // {
        //     for (var i = 1; i < modulesInInventory.Count; i++)
        //     {
        //         Physics2D.SyncTransforms();
        //         var module = modulesInInventory[i];
        //         Debug.Log($"Placing {module.name}.");
        //         module.transform.localPosition = new Vector3(-5, -1 - module.GetComponent<Module>().dimensions.y + 1, -.5f);
        //         var loopCount = 0;
        //         while (!colls.TrueForAll(coll => !coll.bounds.Intersects(module.GetComponent<CompositeCollider2D>().bounds)))
        //         {
        //             
        //             Physics2D.SyncTransforms();
        //             loopCount++;
        //             if (loopCount > 999)
        //             {
        //                 Debug.Log("too many loop");
        //                 break;
        //             }
        //             
        //             var newPos = module.transform.position;
        //             newPos.x += .5f;
        //             if (newPos.x > width - 5)
        //             {
        //                 newPos.x = startPos.x;
        //                 newPos.y -= .5f;
        //             }
        //             module.transform.localPosition = newPos;
        //         }
        //
        //         for (var j = 0; j < i; j++)
        //         {
        //             
        //         }
        //         
        //         Physics2D.SyncTransforms();
        //         colls.Add(module.GetComponent<CompositeCollider2D>());
        //     }
        // }
    }
    
    public void SendToInventory(GameObject moduleObj)
    {
        var module = moduleObj.GetComponent<Module>();
        var moduleMov = moduleObj.GetComponent<RackMovement>();
        
        if (moduleMov.isInInventory) return;

        if (module is TriggerModule)
        {
            triggerModules.Add(moduleObj);
            moduleObj.transform.SetParent(triggerModulesLabel.transform);
        }
        else if (module is PrimaryModule)
        {
            primaryModules.Add(moduleObj);
            moduleObj.transform.SetParent(primaryModulesLabel.transform);
        }
        else if (module is SecondaryModule)
        {
            secondaryModules.Add(moduleObj);
            moduleObj.transform.SetParent(secondaryModulesLabel.transform);
        }
        
        transform.localPosition = Vector3.zero;
        moduleMov.isInInventory = true;
        moduleMov.inventoryEnter.Invoke();
        moduleMov.lastParent = transform.parent;
        ArrangeModules();
    }

    public void RemoveModule(GameObject module)
    {
        if (creativeMode)
        {
            var replacement = Instantiate(module, module.transform.parent);
            if (module.GetComponent<Module>() is TriggerModule)
            {
                triggerModules[triggerModules.FindIndex(x => x == module)] = replacement;
            }
            else if (module.GetComponent<Module>() is PrimaryModule)
            {
                primaryModules[primaryModules.FindIndex(x => x == module)] = replacement;
            }
            else if (module.GetComponent<Module>() is SecondaryModule)
            {
                secondaryModules[secondaryModules.FindIndex(x => x == module)] = replacement;
            }
        }
        else
        {
            if (module.GetComponent<Module>() is TriggerModule)
            {
                triggerModules.Remove(module);
            }
            else if (module.GetComponent<Module>() is PrimaryModule)
            {
                primaryModules.Remove(module);
            }
            else if (module.GetComponent<Module>() is SecondaryModule)
            {
                secondaryModules.Remove(module);
            }
        }
        
        ArrangeModules();
        
        inventoryOverlay.SetActive(false);
    }
}