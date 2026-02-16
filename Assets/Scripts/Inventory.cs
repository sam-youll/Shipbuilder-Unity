using System;
using System.Collections.Generic;
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

    public List<GameObject> modulePrefabs;

    public float credits;
    public TextMeshPro creditsLabel;

    public GameObject hotbar;
    
    public List<GameObject> modulesInInventory;
    
    void Start()
    {
        // sr = GetComponent<SpriteRenderer>();
        // sr.color = defaultColor;

        
        CreateHotbar();
    }

    private void CreateHotbar()
    {
        hotbar = Instantiate(Resources.Load<GameObject>("Prefabs/InventoryBackground"), transform);
        hotbar.transform.position = new Vector3(-9, 0, -2);
        hotbar.SetActive(false);
    }

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.E))
        {
            hotbar.SetActive(!hotbar.activeSelf);

            for (int i = 0; i < transform.childCount; i++)
            {
                if (transform.GetChild(i).TryGetComponent(out Module module))
                {
                    transform.GetChild(i).gameObject.SetActive(hotbar.activeSelf);
                }
            }
            
            ArrangeModules();
        }
        
        // if (creditsLabel != null)
        // {
        //     creditsLabel.text = "Credits: " + credits;
        // }
        // if (Input.GetMouseButtonDown(0) && sr.color == defaultColor) // if click when not over collider
        // {
        //     // close tray
        //     isPulledDown = false;
        // }
        //
        // Vector2 mousePos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
        // RaycastHit2D hit = Physics2D.Raycast(mousePos, Vector2.zero, Mathf.Infinity, LayerMask.GetMask("Inventory"));
        // if (hit)
        // {
        //     sr.color = highlightColor;
        //     if (Input.GetMouseButtonDown(0))
        //     {
        //         isPulledDown = true;
        //     }
        // }
        // else
        // {
        //     sr.color = defaultColor;
        // }
    }

    private void FixedUpdate()
    {
        // if (isPulledDown)
        // {
        //     if (transform.position.y > downPos.y)
        //     {
        //         var pos = transform.position;
        //         pos = Vector3.Lerp(pos, downPos, .2f);
        //         if (SceneManager.GetActiveScene() == SceneManager.GetSceneByName("Spring Showcase Tutorial"))
        //         {
        //             pos.z = -5;
        //         } else
        //         {
        //             pos.z = -2;
        //         }
        //         transform.position = pos;
        //     }
        // }
        // else
        // {
        //     if (transform.position.y < upPos.y)
        //     {
        //         var pos = transform.position;
        //         pos = Vector3.Lerp(pos, upPos, .2f);
        //         pos.z = -2;
        //         transform.position = pos;
        //     }
        // }
    }

    public void AddNewRandomModule()
    {
        var pos = new Vector3(-6.5f, -1f, -3f);
        var roll = UnityEngine.Random.Range(0, modulePrefabs.Count);
        var module = Instantiate(modulePrefabs[roll], transform);
        module.transform.localPosition = pos;
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
        if (modulesInInventory.Count == 0) return;
        
        Physics2D.SyncTransforms();
        var width = 9;
        var colls = new List<Collider2D>();
        modulesInInventory[0].transform.position = new Vector3(-14f, 4, -3);
        colls.Add(modulesInInventory[0].GetComponent<CompositeCollider2D>());
        if (modulesInInventory.Count > 1)
        {
            for (var i = 1; i < modulesInInventory.Count; i++)
            {
                Physics2D.SyncTransforms();
                var module = modulesInInventory[i];
                module.transform.position = new Vector3(-14.5f, 4, -3);
                var loopCount = 0;
                while (!colls.TrueForAll(coll => !coll.bounds.Intersects(module.GetComponent<CompositeCollider2D>().bounds)))
                {
                    Physics2D.SyncTransforms();
                    loopCount++;
                    if (loopCount > 999)
                    {
                        Debug.Log("too many loop");
                        break;
                    }
                    
                    var newPos = module.transform.position;
                    newPos.x += .5f;
                    if (newPos.x > width-14.5f)
                    {
                        newPos.x = -14.5f;
                        newPos.y -= .5f;
                    }
                    module.transform.position = newPos;
                }
                
                Physics2D.SyncTransforms();
                colls.Add(module.GetComponent<CompositeCollider2D>());
            }
        }
    }
    
    //
    // private void OnMouseEnter()
    // {
    //     sr.color = highlightColor;
    // }
    //
    // private void OnMouseExit()
    // {
    //     sr.color = defaultColor;
    // }
    //
    // private void OnMouseDown()
    // {
    //     isPulledDown = true;
    // }
}