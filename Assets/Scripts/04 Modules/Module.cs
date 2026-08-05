using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using SaintsField;
using SaintsField.Playa;
using TMPro;
using UnityEngine;
using UnityEngine.Serialization;
using UnityEngine.UI;
using Vector2 = UnityEngine.Vector2;
using Vector3 = UnityEngine.Vector3;
#if UNITY_EDITOR
using UnityEditor;
using UnityEngine.U2D;
#endif


#if UNITY_EDITOR
[CustomEditor(typeof(Module), true)]
public class ModuleInspector : Editor
{
    Module.ModuleComponent paletteSelection = Module.ModuleComponent.Body;
    public string keyToAddToDict = "test";
    
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
        if (paletteSelection == Module.ModuleComponent.InputTrig)
        {
            GUI.color = Color.white;
        }
        else
        {
            GUI.color = Color.gray;
        }
        if (GUILayout.Button("InputTrig", GUILayout.Width(40), GUILayout.Height(20)))
        {
            paletteSelection = Module.ModuleComponent.InputTrig;
        }
        if (paletteSelection == Module.ModuleComponent.InputCtrl)
        {
            GUI.color = Color.white;
        }
        else
        {
            GUI.color = Color.gray;
        }
        if (GUILayout.Button("InputCtrl", GUILayout.Width(40), GUILayout.Height(20)))
        {
            paletteSelection = Module.ModuleComponent.InputCtrl;
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
        
        // SCREEN
        if (paletteSelection == Module.ModuleComponent.Screen)
        {
            GUI.color = Color.white;
        }
        else
        {
            GUI.color = Color.gray;
        }

        if (GUILayout.Button("Screen", GUILayout.Width(40), GUILayout.Height(20)))
        {
            paletteSelection = Module.ModuleComponent.Screen;
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
                    case Module.ModuleComponent.InputTrig:
                        GUI.color = Color.cyan;
                        if (GUILayout.Button("InT", GUILayout.Width(40), GUILayout.Height(40)))
                        {
                            module.moduleShape[x, y] = paletteSelection;
                        }

                        break;
                    case Module.ModuleComponent.InputCtrl:
                        GUI.color = Color.cyan;
                        if (GUILayout.Button("InC", GUILayout.Width(40), GUILayout.Height(40)))
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
                        if (GUILayout.Button("Sw", GUILayout.Width(40), GUILayout.Height(40)))
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
                    case Module.ModuleComponent.Screen:
                        GUI.color = Color.cyan;
                        if (GUILayout.Button("Sc", GUILayout.Width(40), GUILayout.Height(40)))
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
            Debug.Log("clicky button");
            module.BuildModule();
            module.OnBeforeSerialize();
        }
        GUI.color = Color.white;

        // for (var i = 0; i < module.combatStats.Keys.Count; i++)
        // {
        //     GUILayout.BeginHorizontal();
        //     var key = module.combatStats.Keys.ToArray()[i];
        //     GUILayout.Label(key);
        //     module.combatStats[key] = float.Parse(GUILayout.TextField(module.combatStats.Values.ToArray()[i].ToString()));
        //     GUILayout.EndHorizontal();
        // }
        //
        // GUILayout.BeginHorizontal();
        // keyToAddToDict = GUILayout.TextField(keyToAddToDict);
        // if (GUILayout.Button("Add Combat Stat"))
        // {
        //     module.combatStats.Add(keyToAddToDict, 0);
        // }
        // GUILayout.EndHorizontal();
        
        EditorGUILayout.EndVertical();
        
        DrawDefaultInspector();
    }
}
#endif

#region Interfaces
public interface INeedEnergy
{
    public Dictionary<Common.SoundType, float> EnergyCost();
}

public interface IMusicParams
{
    public Dictionary<string, float> MusicParams();
}

public interface IWeaponModule
{
    public struct WeaponStats
    {
        public Dictionary<string, float> Stats;

        public Dictionary<Common.SoundType, float> SoundType;

        public Dictionary<Common.Effect, float> Effect;
    }

    public WeaponStats MyWeaponStats();
}

public interface IReactorModule
{
    public struct EnergyConversion
    {
        public float EnergyLimit;
        public List<KeyValuePair<Common.SoundType, float>> ConversionRatios;
    }
    
    public struct ReactorStats
    {
        // power module
        public float PowerGenerated;
        
        // converter modules
        public EnergyConversion EnergyConversion;
        
        // system routing? energy discounts?
        public Dictionary<ModuleRack, float> SystemRouting;

        public Dictionary<Common.SoundType, float> SoundType;
    }
    
    public ReactorStats MyReactorStats();
}

public interface IAuxModule
{
    // TODO: idk yet
}
#endregion

[SelectionBase]
public abstract class Module : MonoBehaviour, ISerializationCallbackReceiver, ITooltipInfo, INeedEnergy, ISelectable
{
    #region Module Builder
    public enum ModuleComponent
    {
        Empty,
        Body,
        InputTrig,
        InputCtrl,
        Output,
        Switch,
        Knob,
        Label,
        Screen
    }
    
    [Header("Changing dimensions will reset grid.\nDimensions can be between 1 and 8.")]
    public Vector2Int dimensions = new(3, 3);
    public ModuleComponent[,] moduleShape = new ModuleComponent[3, 3];
    [SerializeField] private List<Package<ModuleComponent>> moduleShapeSerialized = new();

    public enum EdgeStyle
    {
        Spikes,
        Round,
        Flat
    }
    public EdgeStyle edgeStyle = EdgeStyle.Flat;

    public enum EdgeColor
    {
        White,
        Yellow,
        Cyan,
        Magenta
    }
    public EdgeColor edgeColor = EdgeColor.White;
    
    // public enum Theme
    // {
    //     White,
    //     CarbonFiber,
    //     BlueMetal
    // }
    // private readonly string[] tilesheetPaths = 
    // {
    //     "Spritesheets/tilesheet white",
    //     "Spritesheets/tilesheet carbon fiber",
    //     "Spritesheets/tilesheet blue metal"
    // };
    // public Theme theme = Theme.CarbonFiber;
    
    public bool darkTheme;
    public bool leyLines;
    
    [ShowInInspector] private string tilesheetPath;
    public string labelText;

    public Sprite overlayImage;
    
    #if UNITY_EDITOR
    private void OnValidate()
    {
        dimensions.x = Mathf.Clamp(dimensions.x, 1, 8);
        dimensions.y = Mathf.Clamp(dimensions.y, 1, 8);
        if (moduleShape.GetLength(0) != dimensions.x || moduleShape.GetLength(1) != dimensions.y)
        {
            moduleShape = new ModuleComponent[dimensions.x, dimensions.y];
        }

        tilesheetPath = "Spritesheets/tilesheet ";
        switch (edgeStyle)
        {
            case EdgeStyle.Spikes:
                tilesheetPath += "spikes ";
                break;
            case EdgeStyle.Round:
                tilesheetPath += "round ";
                break;
            case EdgeStyle.Flat:
                tilesheetPath += "flat ";
                break;
        }
        switch (edgeColor)
        {
            case EdgeColor.White:
                tilesheetPath += "white";
                break;
            case EdgeColor.Yellow:
                tilesheetPath += "yellow";
                break;
            case EdgeColor.Cyan:
                tilesheetPath += "cyan";
                break;
            case EdgeColor.Magenta:
                tilesheetPath += "magenta";
                break;
        }
    }
    
    public void BuildModule()
    {
        Undo.RecordObject(gameObject, "Build Module");
        // EditorUtility.SetDirty(gameObject);
        ClearModule();
        Debug.Log("module cleared :)");
        gameObject.layer = LayerMask.NameToLayer("Rack Objects");
        
        
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
                snapSquareComponent.transform.localPosition = new Vector3(x - .5f * dimensions.x + .5f, y - .5f * dimensions.y + .5f, -.01f);
                snapSquareComponent.AddComponent<SpriteRenderer>();
                snapSquareComponent.GetComponent<SpriteRenderer>().sprite = Resources.Load<Sprite>("Sprites/Square");
                snapSquareComponent.GetComponent<SpriteRenderer>().color = new Color(0, 0, 0, 0.7f);
                // snapSquareComponent.GetComponent<RectTransform>().sizeDelta = Vector2.one;
                var coll = snapSquareComponent.AddComponent<BoxCollider2D>();
                coll.compositeOperation = Collider2D.CompositeOperation.Merge;
                coll.size = new Vector2(.9f, .9f);
            }
        }
        #endregion
        
        #region Module body sprites & collision
        Debug.Log("loading tilesheet");
        var tilesheet = Resources.LoadAll<Sprite>(tilesheetPath);
        // We're using a dual-grid system here, so we're spawning
        // one extra row & column of tiles and offsetting them by .5
        Debug.Log("placing tiles");
        for (int x = 0; x <= dimensions.x; x++)
        {
            for (int y = 0; y <= dimensions.y; y++)
            {
                var newComponent = new GameObject($"Body ({x}, {y})");
                newComponent.transform.SetParent(transform);
                newComponent.transform.localPosition = new Vector3(x- .5f * dimensions.x, y - .5f * dimensions.y, 0);
                var img = newComponent.AddComponent<SpriteRenderer>();
                // newComponent.gameObject.GetComponent<RectTransform>().sizeDelta = Vector2.one;

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
                                img.sprite = tilesheet[6];
                            }
                            else
                            {
                                // bottom right is missing, all others are filled
                                img.sprite = tilesheet[7];
                            }
                        }
                        else
                        {
                            if (bottomRight)
                            {
                                // bottom left is missing, all others are filled
                                img.sprite = tilesheet[10];
                            }
                            else
                            {
                                // bottom missing, top filled
                                img.sprite = tilesheet[9];
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
                                img.sprite = tilesheet[5];
                            }
                            else
                            {
                                // left side missing, right side filled
                                img.sprite = tilesheet[1];
                            }
                        }
                        else
                        {
                            if (bottomLeft)
                            {
                                // top right and bottom left filled, others missing
                                img.sprite = tilesheet[13];
                            }
                            else
                            {
                                // top right only
                                img.sprite = tilesheet[8];
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
                                img.sprite = tilesheet[2];
                            }
                            else
                            {
                                // top left and bottom right only
                                img.sprite = tilesheet[4];
                            }
                        }
                        else
                        {
                            // no bottom right
                            if (bottomLeft)
                            {
                                // left side only
                                img.sprite = tilesheet[11];
                            }
                            else
                            {
                                // top left only
                                img.sprite = tilesheet[14];
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
                                img.sprite = tilesheet[3];
                            }
                            else
                            {
                                // bottom right only
                                img.sprite = tilesheet[12];
                            }
                        }
                        else
                        {
                            if (bottomLeft)
                            {
                                // bottom left only
                                img.sprite = tilesheet[0];
                            }
                            else
                            {
                                // all empty
                                DestroyImmediate(newComponent);
                                continue;
                            }
                        }
                    }
                }

                if (overlayImage != null)
                {
                    var mask = newComponent.AddComponent<SpriteMask>();
                    mask.sprite = img.sprite;
                    var overlay = new GameObject("Overlay Image", typeof(SpriteRenderer));
                    overlay.transform.SetParent(newComponent.transform, false);
                    overlay.transform.position = transform.position;
                    overlay.GetComponent<SpriteRenderer>().sprite = overlayImage;
                    overlay.GetComponent<SpriteRenderer>().maskInteraction = SpriteMaskInteraction.VisibleInsideMask;
                    // overlay.GetComponent<SpriteRenderer>().preserveAspect = true;
                    // overlay.GetComponent<SpriteRenderer>().material =
                    //     Resources.Load<Material>("Sprites/Materials/SpriteMultMaterial");
                    // overlay.GetComponent<RectTransform>().sizeDelta = overlayImage.rect.size / 32f;
                }
            }
        }
        
        // for collision, we're adding a composite collider, so we can place
        // a box collider on each tile of the module, then combine them
        Debug.Log("Adding Components");
        // if (!TryGetComponent(out RectTransform rt))
        // {
        //     rt = gameObject.AddComponent<RectTransform>();
        // }
        // rt.sizeDelta = new Vector2(dimensions.x, dimensions.y);
        // gameObject.AddComponent<Canvas>();
        // gameObject.AddComponent<CanvasScaler>();
        // gameObject.AddComponent<GraphicRaycaster>();
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
                newCollObj.transform.localPosition = new Vector3(x - .5f * dimensions.x + .5f, y - .5f * dimensions.y + .5f, 0);
                var newColl = newCollObj.AddComponent<BoxCollider2D>();
                newColl.compositeOperation = Collider2D.CompositeOperation.Merge; 
            }
        }
        
        // just like don't bother. idk it's staying for posterity
        /*
        Debug.Log("I'm about to do the sprite shape thing");
        var ssc = gameObject.AddComponent<SpriteShapeController>();
        var mask = gameObject.AddComponent<SpriteMask>();
        var spline = ssc.spline;
        ssc.splineDetail = 2; // Low I hope
        ssc.spriteShape = ScriptableObject.CreateInstance<SpriteShape>();
        var compositeCollider = gameObject.GetComponent<CompositeCollider2D>();
        var points = new List<Vector2>();
        Debug.Log("HELLLOOOOOo");
        for (int i = 0; i < compositeCollider.pathCount; i++)
        {
            Vector2[] pathPoints = new Vector2[compositeCollider.GetPathPointCount(i)];
            compositeCollider.GetPath(i, pathPoints);
            points.AddRange(pathPoints);
            foreach (var point in pathPoints) Debug.Log(point);
        }
        Debug.Log("=============");
        spriteShapePoints = new Vector2[points.Count];
        for (int i = 0; i < points.Count; i++)
        {
            spriteShapePoints[i] = points[i];
            spline.InsertPointAt(i, points[i]);
            spline.SetTangentMode(i, ShapeTangentMode.Linear);
            Debug.Log("added " + points[i]);
        }

        spriteShapePoints = new Vector2[spline.GetPointCount()];
        for (int i = 0; i < spline.GetPointCount(); i++)
        {
            spriteShapePoints[i] = spline.GetPosition(i);
        }

        while (spline.GetPointCount() > points.Count)
        {
            spline.RemovePointAt(spline.GetPointCount() - 1);
        }
        // for (int i = 1; i < 3; i++)
        // {
        //     spline.RemovePointAt(spline.GetPointCount()-i);
        //     spline.RemovePointAt(i-1);
        // }
        
        ssc.RefreshSpriteShape();
        
        var sprite = Sprite.Create(ssc.spriteShape.fillTexture, new Rect(0, 0, dimensions.x, dimensions.y), new Vector2(.5f, .5f), 32);
        mask.sprite = sprite;
        */
        
        
        if (leyLines)
        {
            var end = new Vector2Int();
            for (var i0 = 0; i0 < moduleShape.GetLength(0); i0++)
            for (var i1 = 0; i1 < moduleShape.GetLength(1); i1++)
            {
                var component = moduleShape[i0, i1];
                if (component is ModuleComponent.Output)
                {
                    end = new Vector2Int(i0, i1);
                }
            }
            for (var j0 = 0; j0 < moduleShape.GetLength(0); j0++)
            for (var j1 = 0; j1 < moduleShape.GetLength(1); j1++)
            {
                var component = moduleShape[j0, j1];
                if (component is ModuleComponent.InputTrig)
                {
                    var start = new Vector2Int(j0, j1);

                    var lineTiles = Resources.LoadAll<Sprite>("Spritesheets/leylines");

                    Debug.Log($"Pathing from {start} to {end}. Dimensions: {dimensions}.");
                    
                    var path = Funcs.AStar4Dir(start, end, dimensions.y, dimensions.x, v2I => moduleShape[v2I.x, v2I.y] != ModuleComponent.Empty);
                    
                    if (path.Count < 2) continue;

                    for (var i = 0; i < path.Count; i++)
                    {
                        var cell = path[i];
                        var newLineSegment = new GameObject("Line Segment " + cell, typeof(SpriteRenderer));
                        newLineSegment.transform.parent = transform;
                        // newLineSegment.GetComponent<RectTransform>().sizeDelta = Vector2.one;
                        newLineSegment.transform.localPosition = new Vector3(path[i].x - .5f * dimensions.x + .5f, path[i].y - .5f * dimensions.y + .5f, -.1f);
                        var lineSprite = lineTiles[0];
                        if (i == 0)
                        {
                            var dir = path[i + 1] - path[i];
                            if (dir == Vector2Int.up)
                            {
                                lineSprite = lineTiles[0];
                            }
                            else if (dir == Vector2Int.right)
                            {
                                lineSprite = lineTiles[1];
                            }
                            else if (dir == Vector2Int.down)
                            {
                                lineSprite = lineTiles[2];
                            }
                            else if (dir == Vector2Int.left)
                            {
                                lineSprite = lineTiles[3];
                            }
                        }
                        else if (i == path.Count - 1)
                        {
                            var dir = path[i - 1] - path[i];
                            if (dir == Vector2Int.up)
                            {
                                lineSprite = lineTiles[0];
                            }
                            else if (dir == Vector2Int.right)
                            {
                                lineSprite = lineTiles[1];
                            }
                            else if (dir == Vector2Int.down)
                            {
                                lineSprite = lineTiles[2];
                            }
                            else if (dir == Vector2Int.left)
                            {
                                lineSprite = lineTiles[3];
                            }
                        }
                        else
                        {
                            var prevDir = path[i - 1] - path[i];
                            var nextDir =  path[i + 1] - path[i];

                            if (prevDir == Vector2Int.up && nextDir == Vector2Int.right ||
                                nextDir == Vector2Int.up && prevDir == Vector2Int.right)
                            {
                                lineSprite = lineTiles[4];
                            }
                            else if (prevDir == Vector2Int.down && nextDir == Vector2Int.right ||
                                     nextDir == Vector2Int.down && prevDir == Vector2Int.right)
                            {
                                lineSprite = lineTiles[5];
                            }
                            else if (prevDir == Vector2Int.left && nextDir == Vector2Int.down ||
                                     nextDir == Vector2Int.left && prevDir == Vector2Int.down)
                            {
                                lineSprite = lineTiles[6];
                            }
                            else if (prevDir == Vector2Int.left && nextDir == Vector2Int.up ||
                                     nextDir == Vector2Int.left && prevDir == Vector2Int.up)
                            {
                                lineSprite = lineTiles[7];
                            }
                            else if (prevDir == Vector2Int.left && nextDir == Vector2Int.right ||
                                     nextDir == Vector2Int.left && prevDir == Vector2Int.right)
                            {
                                lineSprite = lineTiles[8];
                            }
                            else if (prevDir == Vector2Int.up && nextDir == Vector2Int.down ||
                                     nextDir == Vector2Int.up && prevDir == Vector2Int.down)
                            {
                                lineSprite = lineTiles[9];
                            }
                        }

                        newLineSegment.GetComponent<SpriteRenderer>().sprite = lineSprite;
                    }
                }
                else if (component is ModuleComponent.InputCtrl)
                {
                    var start = new Vector2Int(j0, j1);
                    
                    var lineTiles = Resources.LoadAll<Sprite>("Spritesheets/leylines");

                    var path = Funcs.AStar4Dir(start, end, dimensions.y, dimensions.x, v2I => moduleShape[v2I.x, v2I.y] != ModuleComponent.Empty);
                    
                    if (path.Count < 2) continue;

                    for (var i = 0; i < path.Count; i++)
                    {
                        var cell = path[i];
                        var newLineSegment = new GameObject("Line Segment " + cell, typeof(SpriteRenderer));
                        newLineSegment.transform.parent = transform;
                        // newLineSegment.GetComponent<RectTransform>().sizeDelta = Vector2.one;
                        newLineSegment.transform.localPosition = new Vector3(path[i].x - .5f * dimensions.x + .5f, path[i].y - .5f * dimensions.y + .5f, -.1f);
                        var lineSprite = lineTiles[0];
                        if (i == 0)
                        {
                            var dir = path[i + 1] - path[i];
                            if (dir == Vector2Int.up)
                            {
                                lineSprite = lineTiles[10];
                            }
                            else if (dir == Vector2Int.right)
                            {
                                lineSprite = lineTiles[11];
                            }
                            else if (dir == Vector2Int.down)
                            {
                                lineSprite = lineTiles[12];
                            }
                            else if (dir == Vector2Int.left)
                            {
                                lineSprite = lineTiles[13];
                            }
                        }
                        else if (i == path.Count - 1)
                        {
                            var dir = path[i - 1] - path[i];
                            if (dir == Vector2Int.up)
                            {
                                lineSprite = lineTiles[10];
                            }
                            else if (dir == Vector2Int.right)
                            {
                                lineSprite = lineTiles[11];
                            }
                            else if (dir == Vector2Int.down)
                            {
                                lineSprite = lineTiles[12];
                            }
                            else if (dir == Vector2Int.left)
                            {
                                lineSprite = lineTiles[13];
                            }
                        }
                        else
                        {
                            var prevDir = path[i - 1] - path[i];
                            var nextDir =  path[i + 1] - path[i];

                            if (prevDir == Vector2Int.up && nextDir == Vector2Int.right ||
                                nextDir == Vector2Int.up && prevDir == Vector2Int.right)
                            {
                                lineSprite = lineTiles[14];
                            }
                            else if (prevDir == Vector2Int.down && nextDir == Vector2Int.right ||
                                     nextDir == Vector2Int.down && prevDir == Vector2Int.right)
                            {
                                lineSprite = lineTiles[15];
                            }
                            else if (prevDir == Vector2Int.left && nextDir == Vector2Int.down ||
                                     nextDir == Vector2Int.left && prevDir == Vector2Int.down)
                            {
                                lineSprite = lineTiles[16];
                            }
                            else if (prevDir == Vector2Int.left && nextDir == Vector2Int.up ||
                                     nextDir == Vector2Int.left && prevDir == Vector2Int.up)
                            {
                                lineSprite = lineTiles[17];
                            }
                            else if (prevDir == Vector2Int.left && nextDir == Vector2Int.right ||
                                     nextDir == Vector2Int.left && prevDir == Vector2Int.right)
                            {
                                lineSprite = lineTiles[18];
                            }
                            else if (prevDir == Vector2Int.up && nextDir == Vector2Int.down ||
                                     nextDir == Vector2Int.up && prevDir == Vector2Int.down)
                            {
                                lineSprite = lineTiles[19];
                            }
                        }

                        newLineSegment.GetComponent<SpriteRenderer>().sprite = lineSprite;
                    }
                }
            }
        }
        
        #endregion

        #region Module components
        for (int x = 0; x < dimensions.x; x++)
        {
            for (int y = 0; y < dimensions.y; y++)
            {
                var pos = new Vector3(x - .5f * dimensions.x + .5f, y - .5f * dimensions.y + .5f, -.2f);
                
                switch (moduleShape[x, y])
                {
                    case ModuleComponent.InputTrig:
                        // var newInputJack = new GameObject($"Input Jack ({x}, {y})");
                        var newInputJack = Instantiate(Resources.Load<GameObject>("Module Components/Input Jack (Trigger)"), transform);
                        newInputJack.transform.SetParent(transform);
                        newInputJack.transform.localPosition = pos;
                        newInputJack.GetComponent<Jack>().darkTheme = darkTheme;
                        inputJacks.Add(newInputJack);
                        break;
                    case ModuleComponent.InputCtrl:
                        // var newInputJack = new GameObject($"Input Jack ({x}, {y})");
                        var newInputJackCtrl = Instantiate(Resources.Load<GameObject>("Module Components/Input Jack (Control)"), transform);
                        newInputJackCtrl.transform.SetParent(transform);
                        newInputJackCtrl.transform.localPosition = pos;
                        newInputJackCtrl.GetComponent<Jack>().darkTheme = darkTheme;
                        inputJacks.Add(newInputJackCtrl);
                        break;
                    case ModuleComponent.Output:
                        var newOutputJack = Instantiate(Resources.Load<GameObject>("Module Components/Output Jack"), transform);
                        newOutputJack.transform.SetParent(transform);
                        newOutputJack.transform.localPosition = pos;
                        newOutputJack.GetComponent<Jack>().darkTheme = darkTheme;
                        outputJacks.Add(newOutputJack);
                        break;
                    case ModuleComponent.Switch:
                        var newSwitch = Instantiate(Resources.Load<GameObject>("Module Components/Switch"), transform);
                        newSwitch.transform.SetParent(transform);
                        newSwitch.transform.localPosition = pos;
                        break;
                    case ModuleComponent.Knob:
                        var newKnob = Instantiate(Resources.Load<GameObject>("Module Components/Knob"), transform);
                        newKnob.transform.SetParent(transform);
                        newKnob.transform.localPosition = pos;
                        break;
                    case ModuleComponent.Label:
                        var newTypeIcon = new GameObject($"Label ({x}, {y})");
                        newTypeIcon.transform.SetParent(transform);
                        newTypeIcon.transform.localPosition = pos;
                        newTypeIcon.AddComponent<MeshRenderer>();
                        var textComponent = newTypeIcon.AddComponent<TextMeshPro>();
                        textComponent.fontSize = 5f;
                        textComponent.rectTransform.sizeDelta = new Vector2(1f, .75f);
                        textComponent.font = Resources.Load<TMP_FontAsset>("Fonts/CutePixel Bitmap");
                        textComponent.alignment = TextAlignmentOptions.Midline;
                        textComponent.textWrappingMode = TextWrappingModes.NoWrap;
                        textComponent.text = String.IsNullOrEmpty(labelText) ? gameObject.name.Split(" ")[0] : labelText;
                        textComponent.color = darkTheme ? new Color(.56f, .78f, .78f) : new Color(.2f, .2f, .2f);
                        break;
                    case ModuleComponent.Screen:
                        var newScreen = Instantiate(Resources.Load<GameObject>("Module Components/Screen"), transform);
                        newScreen.transform.SetParent(transform);
                        newScreen.transform.localPosition = pos;
                        break;
                }
            }
        }
        #endregion
        
    }

    public void ClearModule()
    {
        if (TryGetComponent(out SpriteShapeController ssc)) DestroyImmediate(ssc);
        
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

    [Header("Components")] 
    public ModuleScreen screen;
    
    [Header("Connections")] 
    [Tooltip("Make sure the primary input jack is index 0 in the list. The rest should be left to right.")]
    public List<GameObject> inputJacks = new();
    public List<GameObject> outputJacks = new();
    public List<GameObject> parentWires = new();
    public List<GameObject> childWires = new();
    
    [Header("Values")] 
    [Tooltip("The amount charged for this module in the shop.")]
    public float price;
    public float heat;
    public float energyNoneCost;
    public float energyIzkiCost;
    public float energyAuboCost;
    public float energyDwthCost;

    public Sprite icon;

    #region Tooltip Info
    public abstract string Description();

    public abstract string Info();

    public virtual bool Warning(out string message)
    {
        message = "";
        var missingEnergy = new List<Common.SoundType>();
        if (GetComponentInParent<Weapon>() != null)
        {
            if (!GetComponentInParent<Weapon>().WeaponHasEnergyForYou(EnergyCost(), out missingEnergy))
            {
                message += "This module is missing the following energy types it needs to trigger:\n";
                foreach (var energy in missingEnergy)
                {
                    message += "- " + energy + "\n";
                }
            }
        }

        return missingEnergy.Count > 0;
    }

    #endregion
    
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
        Debug.Log("boutta die, lemme clear my wires");
        ClearWires();
        
        Destroy(gameObject);
    }

    protected virtual void OnJackClick(GameObject jack)
    {
        return;
        
        // Debug.Log("module jack clicked");
        if (transform.parent == InventoryManager.Instance.transform)
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

    protected virtual void UpdateScreen(string content)
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

    public virtual Dictionary<Common.SoundType, float> EnergyCost()
    {
        return new Dictionary<Common.SoundType, float>
        {
            { Common.SoundType.Pure, energyNoneCost },
            { Common.SoundType.Izki, energyIzkiCost },
            { Common.SoundType.Aubo, energyAuboCost },
            { Common.SoundType.Dwth, energyDwthCost }
        };
    }

    public void Select()
    {
        
    }

    public void SetRenderers(SpriteMaskInteraction smi, int order)
    {
        foreach (var sr in gameObject.GetComponentsInChildren<SpriteRenderer>())
        {
            sr.sortingOrder = order;
            sr.maskInteraction = smi;
        }

        foreach (var tmp in gameObject.GetComponentsInChildren<TextMeshPro>())
        {
            tmp.sortingOrder = order;
        }
    }
}
