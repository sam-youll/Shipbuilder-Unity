using System;
using System.Collections.Generic;
using System.Numerics;
using TMPro;
using UnityEngine;
using UnityEngine.Serialization;
using UnityEngine.UIElements;
using Vector2 = UnityEngine.Vector2;
using Vector3 = UnityEngine.Vector3;
#if UNITY_EDITOR
using UnityEditor;
#endif


#if UNITY_EDITOR
[CustomEditor(typeof(Module), true)]
public class ModuleInspector : Editor
{
    Module.ModuleComponent paletteSelection = Module.ModuleComponent.Body;
    
    public override void OnInspectorGUI()
    {
        Undo.RecordObject(target, "Module Inspector");
        
        var module = (Module)target;
        
        EditorGUILayout.BeginVertical();
        
        #region Palette buttons
        GUILayout.Label("Palette");
        
        EditorGUILayout.BeginHorizontal();
        
        // EMPTY
        if (paletteSelection == Module.ModuleComponent.Empty)
        {
            GUI.color = Color.white;
        }
        else
        {
            GUI.color = Color.gray;
        }
        if (GUILayout.Button("Empty", GUILayout.Width(50), GUILayout.Height(20)))
        {
            paletteSelection = Module.ModuleComponent.Empty;
        }
        
        // BODY
        if (paletteSelection == Module.ModuleComponent.Body)
        {
            GUI.color = Color.white;
        }
        else
        {
            GUI.color = Color.gray;
        }
        if (GUILayout.Button("Body", GUILayout.Width(40), GUILayout.Height(20)))
        {
            paletteSelection = Module.ModuleComponent.Body;
        }
        
        // INPUT
        if (paletteSelection == Module.ModuleComponent.Input)
        {
            GUI.color = Color.white;
        }
        else
        {
            GUI.color = Color.gray;
        }
        if (GUILayout.Button("Input", GUILayout.Width(40), GUILayout.Height(20)))
        {
            paletteSelection = Module.ModuleComponent.Input;
        }
        
        // OUTPUT
        if (paletteSelection == Module.ModuleComponent.Output)
        {
            GUI.color = Color.white;
        }
        else
        {
            GUI.color = Color.gray;
        }
        if (GUILayout.Button("Output", GUILayout.Width(50), GUILayout.Height(20)))
        {
            paletteSelection = Module.ModuleComponent.Output;
        }
        
        // SWITCH
        if (paletteSelection == Module.ModuleComponent.Switch)
        {
            GUI.color = Color.white;
        }
        else
        {
            GUI.color = Color.gray;
        }
        if (GUILayout.Button("Switch", GUILayout.Width(50), GUILayout.Height(20)))
        {
            paletteSelection = Module.ModuleComponent.Switch;
        }
        
        // KNOB
        if (paletteSelection == Module.ModuleComponent.Knob)
        {
            GUI.color = Color.white;
        }
        else
        {
            GUI.color = Color.gray;
        }
        if (GUILayout.Button("Knob", GUILayout.Width(40), GUILayout.Height(20)))
        {
            paletteSelection = Module.ModuleComponent.Knob;
        }
        
        // LABEL
        if (paletteSelection == Module.ModuleComponent.Label)
        {
            GUI.color = Color.white;
        }
        else
        {
            GUI.color = Color.gray;
        }
        if (GUILayout.Button("Label", GUILayout.Width(40), GUILayout.Height(20)))
        {
            paletteSelection = Module.ModuleComponent.Label;
        }
        
        GUI.color = Color.red;
        if (GUILayout.Button("CLEAR", GUILayout.Width(50), GUILayout.Height(20)))
        {
            module.moduleShape = new Module.ModuleComponent[module.dimensions.x, module.dimensions.y];
        }
        GUILayout.EndHorizontal();
        GUI.color = Color.white;
        #endregion
        
        #region Module shape
        GUILayout.Label("Module Shape");

        for (int y = module.dimensions.y - 1; y >= 0; y--)
        {
            GUILayout.BeginHorizontal();
            for (int x = 0; x < module.dimensions.x; x++)
            {
                switch (module.moduleShape[x, y])
                {
                    case Module.ModuleComponent.Empty:
                        GUI.color = Color.gray;
                        if (GUILayout.Button("", GUILayout.Width(40), GUILayout.Height(40)))
                        {
                            module.moduleShape[x, y] = paletteSelection;
                        }
                        
                        break;
                    case Module.ModuleComponent.Body:
                        GUI.color = Color.white;
                        if (GUILayout.Button("", GUILayout.Width(40), GUILayout.Height(40)))
                        {
                            module.moduleShape[x, y] = paletteSelection;
                        }

                        break;
                    case Module.ModuleComponent.Input:
                        GUI.color = Color.cyan;
                        if (GUILayout.Button("In", GUILayout.Width(40), GUILayout.Height(40)))
                        {
                            module.moduleShape[x, y] = paletteSelection;
                        }

                        break;
                    case Module.ModuleComponent.Output:
                        GUI.color = Color.cyan;
                        if (GUILayout.Button("Out", GUILayout.Width(40), GUILayout.Height(40)))
                        {
                            module.moduleShape[x, y] = paletteSelection;
                        }

                        break;
                    case Module.ModuleComponent.Switch:
                        GUI.color = Color.cyan;
                        if (GUILayout.Button("S", GUILayout.Width(40), GUILayout.Height(40)))
                        {
                            module.moduleShape[x, y] = paletteSelection;
                        }

                        break;
                    case Module.ModuleComponent.Knob:
                        GUI.color = Color.cyan;
                        if (GUILayout.Button("K", GUILayout.Width(40), GUILayout.Height(40)))
                        {
                            module.moduleShape[x, y] = paletteSelection;
                        }

                        break;
                    case Module.ModuleComponent.Label:
                        GUI.color = Color.cyan;
                        if (GUILayout.Button("L", GUILayout.Width(40), GUILayout.Height(40)))
                        {
                            module.moduleShape[x, y] = paletteSelection;
                        }

                        break;
                }
                
            }
            GUILayout.EndHorizontal();
        }
        GUI.color = Color.white;
        #endregion

        GUI.color = Color.red;
        if (GUILayout.Button("Clear Module"))
        {
            module.ClearModule();
        }
        GUI.color = Color.green;
        if (GUILayout.Button("Build Module"))
        {
            module.BuildModule();
            module.OnBeforeSerialize();
        }
        GUI.color = Color.white;
        
        EditorGUILayout.EndVertical();
        
        DrawDefaultInspector();
    }
}
#endif

[SelectionBase]
public abstract class Module : MonoBehaviour, ISerializationCallbackReceiver
{
    #region Module Builder
    public enum ModuleComponent
    {
        Empty,
        Body,
        Input,
        Output,
        Switch,
        Knob,
        Label
    }
    
    [Header("Changing dimensions will reset grid.\nDimensions can be between 1 and 8.")]
    public Vector2Int dimensions = new(3, 3);
    public ModuleComponent[,] moduleShape = new ModuleComponent[3, 3];
    [SerializeField] private List<Package<ModuleComponent>> moduleShapeSerialized = new();
    
    public enum Theme
    {
        White,
        CarbonFiber,
        BlueMetal
    }
    private readonly string[] tilesheetPaths = 
    {
        "Spritesheets/tilesheet white",
        "Spritesheets/tilesheet carbon fiber",
        "Spritesheets/tilesheet blue metal"
    };
    public Theme theme = Theme.CarbonFiber;
    public bool darkTheme;
    private string tilesheetPath;
    
    #if UNITY_EDITOR
    private void OnValidate()
    {
        dimensions.x = Mathf.Clamp(dimensions.x, 1, 8);
        dimensions.y = Mathf.Clamp(dimensions.y, 1, 8);
        if (moduleShape.GetLength(0) != dimensions.x || moduleShape.GetLength(1) != dimensions.y)
        {
            moduleShape = new ModuleComponent[dimensions.x, dimensions.y];
        }
        
        tilesheetPath = tilesheetPaths[(int)theme];
    }
    
    public void BuildModule()
    {
        Undo.RecordObject(gameObject, "Build Module");
        // EditorUtility.SetDirty(gameObject);
        ClearModule();
        
        gameObject.layer = LayerMask.NameToLayer("Rack Objects");
        
        #region Module body sprites & collision
        var tilesheet = Resources.LoadAll<Sprite>(tilesheetPath);
        // We're using a dual-grid system here, so we're spawning
        // one extra row & column of tiles and offsetting them by .5
        for (int x = 0; x <= dimensions.x; x++)
        {
            for (int y = 0; y <= dimensions.y; y++)
            {
                var newComponent = new GameObject($"Body ({x}, {y})");
                newComponent.transform.SetParent(transform);
                newComponent.transform.localPosition = new Vector3(x - .5f, y - .5f, 0);
                var sr = newComponent.AddComponent<SpriteRenderer>();

                // with the dual-grid system, we only check the corners of a tile
                // for the purposes of checking against moduleShape, top right is (0,0)
                // this means we subtract 1 to get the other corners
                var topRight = false;
                if (x < dimensions.x && y < dimensions.y)
                {
                    topRight = moduleShape[x, y] != ModuleComponent.Empty;
                }
                
                var topLeft = false;
                if (x > 0 && y < dimensions.y)
                {
                    topLeft = moduleShape[x - 1, y] != ModuleComponent.Empty;
                }

                var bottomRight = false;
                if (x < dimensions.x && y > 0)
                {
                    bottomRight = moduleShape[x, y - 1] != ModuleComponent.Empty;
                }

                var bottomLeft = false;
                if (x > 0 && y > 0)
                {
                    bottomLeft = moduleShape[x - 1, y - 1] != ModuleComponent.Empty;
                }

                if (topRight)
                {
                    if (topLeft)
                    {
                        if (bottomLeft)
                        {
                            if (bottomRight)
                            {
                                // all 4 corners are filled with module
                                sr.sprite = tilesheet[6];
                            }
                            else
                            {
                                // bottom right is missing, all others are filled
                                sr.sprite = tilesheet[7];
                            }
                        }
                        else
                        {
                            if (bottomRight)
                            {
                                // bottom left is missing, all others are filled
                                sr.sprite = tilesheet[10];
                            }
                            else
                            {
                                // bottom missing, top filled
                                sr.sprite = tilesheet[9];
                            }
                        }
                    }
                    else
                    {
                        // yes top right, no top left
                        if (bottomRight)
                        {
                            if (bottomLeft)
                            {
                                // top left is missing, all others are filled
                                sr.sprite = tilesheet[5];
                            }
                            else
                            {
                                // left side missing, right side filled
                                sr.sprite = tilesheet[1];
                            }
                        }
                        else
                        {
                            if (bottomLeft)
                            {
                                // top right and bottom left filled, others missing
                                sr.sprite = tilesheet[13];
                            }
                            else
                            {
                                // top right only
                                sr.sprite = tilesheet[8];
                            }
                        }
                    }
                }
                else
                {
                    // no top right
                    if (topLeft)
                    {
                        if (bottomRight)
                        {
                            if (bottomLeft)
                            {
                                // top right missing, all others filled
                                sr.sprite = tilesheet[2];
                            }
                            else
                            {
                                // top left and bottom right only
                                sr.sprite = tilesheet[4];
                            }
                        }
                        else
                        {
                            // no bottom right
                            if (bottomLeft)
                            {
                                // left side only
                                sr.sprite = tilesheet[11];
                            }
                            else
                            {
                                // top left only
                                sr.sprite = tilesheet[14];
                            }
                        }
                    }
                    else
                    {
                        // no top
                        if (bottomRight)
                        {
                            if (bottomLeft)
                            {
                                // bottom only
                                sr.sprite = tilesheet[3];
                            }
                            else
                            {
                                // bottom right only
                                sr.sprite = tilesheet[12];
                            }
                        }
                        else
                        {
                            if (bottomLeft)
                            {
                                // bottom left only
                                sr.sprite = tilesheet[0];
                            }
                            else
                            {
                                // all empty
                                DestroyImmediate(newComponent);
                            }
                        }
                    }
                }
            }
        }
        
        // for collision, we're adding a composite collider, so we can place
        // a box collider on each tile of the module, then combine them
        gameObject.AddComponent<CompositeCollider2D>();
        gameObject.GetComponent<CompositeCollider2D>().geometryType = CompositeCollider2D.GeometryType.Polygons;
        gameObject.GetComponent<Rigidbody2D>().bodyType = RigidbodyType2D.Kinematic;
        for (int x = 0; x < dimensions.x; x++)
        {
            for (int y = 0; y < dimensions.y; y++)
            {
                if (x == dimensions.x || y == dimensions.y || moduleShape[x, y] == ModuleComponent.Empty)
                    continue;
                
                var newCollObj = new GameObject($"Coll ({x}, {y})");
                newCollObj.transform.SetParent(transform);
                newCollObj.transform.localPosition = new Vector3(x, y, 0);
                var newColl = newCollObj.AddComponent<BoxCollider2D>();
                newColl.compositeOperation = Collider2D.CompositeOperation.Merge; 
            }
        }
        #endregion

        #region Module components
        for (int x = 0; x < dimensions.x; x++)
        {
            for (int y = 0; y < dimensions.y; y++)
            {
                switch (moduleShape[x, y])
                {
                    case ModuleComponent.Input:
                        // var newInputJack = new GameObject($"Input Jack ({x}, {y})");
                        var newInputJack = Instantiate(Resources.Load<GameObject>("Module Components/Input Jack"), transform);
                        newInputJack.transform.SetParent(transform);
                        newInputJack.transform.localPosition = new Vector3(x, y, -.1f);
                        newInputJack.GetComponent<Jack>().darkTheme = darkTheme;
                        inputJacks.Add(newInputJack);
                        break;
                    case ModuleComponent.Output:
                        var newOutputJack = Instantiate(Resources.Load<GameObject>("Module Components/Output Jack"), transform);
                        newOutputJack.transform.SetParent(transform);
                        newOutputJack.transform.localPosition = new Vector3(x, y, -.1f);
                        newOutputJack.GetComponent<Jack>().darkTheme = darkTheme;
                        outputJacks.Add(newOutputJack);
                        break;
                    case ModuleComponent.Switch:
                        var newSwitch = Instantiate(Resources.Load<GameObject>("Module Components/Switch"), transform);
                        newSwitch.transform.SetParent(transform);
                        newSwitch.transform.localPosition = new Vector3(x, y, -.1f);
                        break;
                    case ModuleComponent.Knob:
                        var newKnob = Instantiate(Resources.Load<GameObject>("Module Components/Knob"), transform);
                        newKnob.transform.SetParent(transform);
                        newKnob.transform.localPosition = new Vector3(x, y, -.1f);
                        break;
                    case ModuleComponent.Label:
                        var newTypeIcon = new GameObject($"Label ({x}, {y})");
                        newTypeIcon.transform.SetParent(transform);
                        newTypeIcon.transform.localPosition = new Vector3(x, y, -.1f);
                        newTypeIcon.AddComponent<MeshRenderer>();
                        var textComponent = newTypeIcon.AddComponent<TextMeshPro>();
                        textComponent.fontSize = 5;
                        textComponent.rectTransform.sizeDelta = new Vector2(.75f, .75f);
                        textComponent.font = Resources.Load<TMP_FontAsset>("Fonts/mythic-pixels");
                        textComponent.alignment = TextAlignmentOptions.BottomLeft;
                        textComponent.text = gameObject.name.Split(" ")[0];
                        textComponent.color = darkTheme ? new Color(.56f, .78f, .78f) : new Color(.2f, .2f, .2f);
                        break;
                }
            }
        }
        #endregion
        
        #region Rack movement and snap square
        var rackMovement = gameObject.AddComponent<RackMovement>();
        rackMovement.oddSizeX = dimensions.x % 2 == 1;
        rackMovement.oddSizeY = dimensions.y % 2 == 1;
        
        var snapSquare = new GameObject("Snap Square");
        snapSquare.transform.parent = gameObject.transform;
        snapSquare.transform.localPosition = new Vector3(0, 0, .05f);
        snapSquare.AddComponent<CompositeCollider2D>();
        snapSquare.GetComponent<CompositeCollider2D>().geometryType = CompositeCollider2D.GeometryType.Polygons;
        snapSquare.GetComponent<Rigidbody2D>().bodyType = RigidbodyType2D.Kinematic;
        rackMovement.snapSquare = snapSquare;
        for (int x = 0; x < dimensions.x; x++)
        {
            for (int y = 0; y < dimensions.y; y++)
            {
                if (moduleShape[x, y] == ModuleComponent.Empty)
                    continue;
                
                var snapSquareComponent = new GameObject($"Snap Square Component ({x},{y})");
                snapSquareComponent.transform.parent = snapSquare.transform;
                snapSquareComponent.transform.localPosition = new Vector3(x, y, -.01f);
                snapSquareComponent.AddComponent<SpriteRenderer>();
                snapSquareComponent.GetComponent<SpriteRenderer>().sprite = Resources.Load<Sprite>("Sprites/Square");
                snapSquareComponent.GetComponent<SpriteRenderer>().color = new Color(0, 0, 0, 0.7f);
                var coll = snapSquareComponent.AddComponent<BoxCollider2D>();
                coll.compositeOperation = Collider2D.CompositeOperation.Merge;
                coll.size = new Vector2(.9f, .9f);
            }
        }
        #endregion
    }

    public void ClearModule()
    {
        while (transform.childCount > 0)
        {
            DestroyImmediate(transform.GetChild(0).gameObject);
        }

        DestroyImmediate(GetComponent<CompositeCollider2D>());
        var components = GetComponents<Component>();
        for (int i = 0; i < components.Length; i++)
        {
            if (components[i] == this || components[i] == transform)
                continue;

            DestroyImmediate(components[i]);
        }
        
        inputJacks.Clear();
        outputJacks.Clear();
    }

    #endif
    
    [Serializable]
    private struct Package<TElement>
    {
        public int x;
        public int y;
        public TElement element;

        public Package(int x, int y, TElement element)
        {
            this.x = x;
            this.y = y;
            this.element = element;
        }
    }
    
    public void OnBeforeSerialize()
    {
        moduleShapeSerialized = new();
        for (int x = 0; x < dimensions.x; x++)
        {
            for (int y = 0; y < dimensions.y; y++)
            {
                moduleShapeSerialized.Add(new Package<ModuleComponent>(x, y, moduleShape[x, y]));
            }
        }
    }

    public void OnAfterDeserialize()
    {
        moduleShape = new ModuleComponent[dimensions.x, dimensions.y];
        for (int i = 0; i < moduleShapeSerialized.Count; i++)
        {
            var x = moduleShapeSerialized[i].x;
            var y = moduleShapeSerialized[i].y;
            moduleShape[x, y] = moduleShapeSerialized[i].element;
        }
    }
    #endregion
    
    [Header("Values")] 
    [Tooltip("The amount charged for this module in the shop.")]
    public float price;
    public float izki;
    public float aubo;
    public float dwth;
    public Dictionary<string, float> MusicParams = new();
    public Dictionary<string, float> CombatStats = new();
    
    [Header("Connections")] 
    [Tooltip("Make sure the primary input jack is index 0 in the list. The rest should be left to right.")]
    public List<GameObject> inputJacks = new();
    public List<GameObject> outputJacks = new();
    public List<GameObject> parentWires = new();
    public List<GameObject> childWires = new();
    public GameObject wirePrefab;

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    protected virtual void Start()
    {
        // assign delegates to unity events from rack movement script
        if (GetComponent<RackMovement>() != null)
        {
            GetComponent<RackMovement>().bodyClick.AddListener(OnBodyClick);
            GetComponent<RackMovement>().jackClick.AddListener(OnJackClick);
            GetComponent<RackMovement>().inventoryEnter.AddListener(OnInventoryEnter);
            GetComponent<RackMovement>().inventoryExit.AddListener(OnInventoryExit);
            GetComponent<RackMovement>().destroyed.AddListener(OnDestroyed);
        }
    }
    
    #region Trigger Method + Overloads
    /// <summary>
    /// Calls Trigger() on each child wire, which in turn will call Trigger() on any attached modules.
    /// </summary>
    public virtual void Trigger()
    {
        // Debug.Log($"Attempting to call Trigger() from base Module class on {gameObject.name}");
        foreach (GameObject wire in childWires)
        {
            // Debug.Log($"Base Module class on {gameObject.name} triggered {wire.name} without arguments.");
            wire.GetComponent<Wire>().Trigger();
        }
        // Other behavior should be extended in inherited classes
    }

    // TODO: is this overload ever *actually* used?
    /// <summary>
    /// Calls Trigger() on each child wire, which in turn will call Trigger() on any attached modules.
    /// Calling Trigger() with a value is typically used for secondary modules.
    /// </summary>
    /// <param name="value">The value to pass to the next module.</param>
    public virtual void Trigger(float value)
    {
        foreach (GameObject wire in childWires)
        {
            // Debug.Log($"Base Module class on {gameObject.name} triggered {wire.name} with a value of {value}.");
            wire.GetComponent<Wire>().Trigger(value);
        }
    }

    /// <summary>
    /// Calls Trigger() on each child wire, which in turn will call Trigger() on any attached modules.
    /// Any secondary modules triggering primary modules, as well as some secondary modules triggering some
    /// secondary modules will require passing a value and input index.
    /// </summary>
    /// <param name="value"></param>
    /// <param name="inputIndex"></param>
    public virtual void Trigger(float value, int inputIndex)
    {
        foreach (GameObject wire in childWires)
        {
            // Debug.Log($"Base Module class on {gameObject.name} triggered {wire.name} with a value of {value}.");
            wire.GetComponent<Wire>().Trigger(value, inputIndex);
        }
    }
    
    // public virtual void Trigger(Dictionary<string, float> musicParams, Dictionary<string, float> combatStats)
    // {
    //     foreach (GameObject wire in childWires)
    //     {
    //         Debug.Log($"Base Module class on {gameObject.name} triggered {wire.name} with primary (dictionary) arguments.");
    //         wire.GetComponent<Wire>().Trigger(musicParams, combatStats);
    //     }
    // }
    #endregion
    
    #region Event Handlers
    private void OnBodyClick()
    {
        
    }

    private void OnDestroyed()
    {
        foreach (var wire in parentWires)
        {
            wire.GetComponent<Wire>().DeleteSelf();
        }

        foreach (var wire in childWires)
        {
            wire.GetComponent<Wire>().DeleteSelf();
        }
    }

    protected virtual void OnJackClick(GameObject jack)
    {
        return;
        
        // Debug.Log("module jack clicked");
        if (transform.parent == Inventory.Instance.transform)
            return;

        // input jacks are not allowed to spawn new wires
        // this may change in the future depending on wire behavior
        // if (inputJacks.Contains(jack) || jack.CompareTag("InputJack"))
        //     return;
        //
        // update: they're allowed
        
        // is there already a wire there?
        if (outputJacks.Contains(jack) && childWires.Count > 0 ||
            inputJacks.Contains(jack) && parentWires.Count > 0)
        {
            return;
        }
        
        // make a new wire
        GameObject newWire = Instantiate(Resources.Load<GameObject>("Module Components/Wire"), jack.transform);
        if (jack.CompareTag("InputJack"))
        {
            parentWires.Add(newWire);
        }
        else if (jack.CompareTag("OutputJack"))
        {
            childWires.Add(newWire);
        }
    }

    private void OnInventoryEnter()
    {
        ClearWires();
    }

    private static void OnInventoryExit()
    {
        
    }
    #endregion

    public GameObject PreviousModule()
    {
        GameObject result = null;

        foreach (GameObject wire in parentWires)
        {
            if (wire.GetComponent<Wire>().previousModule != null &&
                wire.GetComponent<Wire>().previousModule.TryGetComponent(out Module module))
            {
                if (module is not SecondaryModule)
                {
                    result = wire.GetComponent<Wire>().previousModule;
                }
            }
        }

        return result;
    }

    protected virtual void Update()
    {
        
    }

    public void ClearWires()
    {
        if (parentWires.Count > 0)
        {
            for (var i = 0; i < parentWires.Count; i++)
            {
                parentWires[i].GetComponent<Wire>().DeleteSelf();
            }

            parentWires.Clear();
        }
        if (childWires.Count > 0)
        {
            for (var i = 0; i < childWires.Count; i++)
            {
                childWires[i].GetComponent<Wire>().DeleteSelf();
            }

            childWires.Clear();
        }
    }

    public void GenerateModuleShape(Vector2Int bounds, int numTiles)
    {
        var shape = new bool[bounds.x, bounds.y];
        
        Debug.Log("Generated new shape");
    }
}
