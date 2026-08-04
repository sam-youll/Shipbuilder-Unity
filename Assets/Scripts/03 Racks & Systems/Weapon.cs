using System;
using System.Collections.Generic;
using SaintsField;
using SaintsField.Playa;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.Events;
using UnityEngine.SceneManagement;
using UnityEngine.Serialization;
using UnityEngine.UI;
using Random = UnityEngine.Random;

public class Weapon : ModuleRack, ITooltipInfo
{
    [Header("Properties")] 
    public float heat;
    public bool warming = false;
    public float warmup = 0;
    public float stunTimer;
    public bool firing;
    [ShowInInspector, SaintsDictionary] public Dictionary<string, float> baseWeaponStats = new(Common.CombatStats);
    [ShowInInspector, SaintsDictionary] public Dictionary<Common.SoundType, float> baseEnergyCost = new();
    public bool overheated;

    [Header("Components")]
    public Image heatOverlay;
    public SwitchComponent testFireSwitch;
    public GameObject energyInJack;
    public GameObject parentEnergyWire;

    public override string Description()
    {
        return "Fires projectiles, playing a note with each one. " +
               "Musical parameters and combat stats are determined by the modules in the connected patch.";
    }

    protected override void Start()
    {
        base.Start();
        // Enemy weapons do not have actual modules behind them (for now)
        // so we just want them to attempt to fire as often as possible
        if (enemySystem)
        {
            switch (Random.Range(0, 2))
            {
                case 0:
                    Conductor.Instance.onSixteenth.AddListener(Fire);
                    break;
                case 1:
                    Conductor.Instance.onEighth.AddListener(Fire);
                    break;
                case 2:
                    Conductor.Instance.onQuarter.AddListener(Fire);
                    break;
            }
        }
    }

    // Update is called once per frame
    protected override void Update()
    {
        base.Update();
        // are we either testing or in combat? If yes to either, we're firing
        firing = (!enemySystem && testFireSwitch.on) || CombatManager.Instance.state == CombatManager.State.inCombat;
        // if we're facing right (only true if player ship) and the patch is not complete, turn it off
        if (!enemySystem && !CompletePatch())
        {
            // Debug.Log("Is patch complete? " + CompletePatch());
            firing = false;
        }
        
        // if (warming)
        // {
        //     if (warmup < 1)
        //     {
        //         if (enemySystem)
        //         {
        //             warmup += .2f * Time.deltaTime;
        //         }
        //         else
        //         {
        //             warmup += WeaponStats()["warmupRate"] * .1f * Time.deltaTime;
        //         }
        //     }
        //     else if (warmup > 1)
        //     {
        //         warmup = Mathf.Clamp(warmup, 0, 1);
        //     }
        // }
        
        if (!enemySystem && firing && stunTimer <= 0)
        {
            heat = Mathf.Max(0, heat - HeatDissipation());
            heatOverlay.fillAmount = heat;
        }
        else if (enemySystem && firing && stunTimer <= 0)
        {
            heat = Mathf.Max(0, heat - HeatDissipation());
        }

        if (heat >= 1)
        {
            overheated = true;
        }

        if (overheated)
        {
            if (heat <= 0)
            {
                overheated = false;
            }
        }

        if (EnergyPatch().Count > 0)
        {
            GenerateEnergy(energyReservoir);
        }
    }

    public float HeatDissipation()
    {
        if (slowTimer > 0)
        {
            return .025f * Time.deltaTime;
        }
        return .1f * Time.deltaTime;
    }

    public Dictionary<string, float> WeaponStats()
    {
        var dict = new Dictionary<string, float>(baseWeaponStats);

        // var izki = 0f;
        // var aubo = 0f;
        // var dwth = 0f;
        // var hysh = 0f;
        
        foreach (var mod in ActivePatch())
        {
           if (mod is IWeaponModule weaponMod)
           {
               if (weaponMod.MyWeaponStats().Stats != null)
               {
                   foreach (var stat in weaponMod.MyWeaponStats().Stats)
                   {
                       dict[stat.Key] += stat.Value;
                   }
               }
               
               dict["heat"] += mod.heat;

               // izki += mod.izki;
               // aubo += mod.aubo;
               // dwth += mod.dwth;
               // hysh += mod.hysh;
           }
        }

        // var soundTypeValue = 0f;
        // dict["soundType"] = (float)Common.SoundType.None;
        // if (izki > soundTypeValue)
        // {
        //     dict["soundType"] = (float)Common.SoundType.Izki;
        //     soundTypeValue = izki;
        // }
        // if (aubo > soundTypeValue)
        // {
        //     dict["soundType"] = (float)Common.SoundType.Aubo;
        //     soundTypeValue = aubo;
        // }
        // if (dwth > soundTypeValue)
        // {
        //     dict["soundType"] = (float)Common.SoundType.Dwth;
        //     soundTypeValue = dwth;
        // }
        // if (hysh > soundTypeValue)
        // {
        //     dict["soundType"] = (float)Common.SoundType.Hysh;
        //     soundTypeValue = hysh;
        // }

        // var myReactor = enemySystem ? ShipManager.Instance.EnemyReactor() : ShipManager.Instance.PlayerReactor();
        // dict["damage"] *= (1 + .5f * myReactor.strength);

        return dict;
    }

    public Dictionary<Common.Effect, float> WeaponEffects()
    {
        var dict = new Dictionary<Common.Effect, float>();
        foreach (var module in ActivePatch())
        {
            if (module.TryGetComponent(out IWeaponModule weaponModule))
            {
                if (weaponModule.MyWeaponStats().Effect == null) continue;
                
                foreach (var kvp in weaponModule.MyWeaponStats().Effect)
                {
                    dict.Add(kvp.Key, kvp.Value);
                }
            }
        }

        return dict;
    }

    public Dictionary<string, float> NoteInfo()
    {
        if (enemySystem)
        {
            var enemydict = new Dictionary<string, float>(Common.NoteInfo);
            var myPitch = Notes.GetPitch(
                Notes.C,
                Notes.MODE.IONIAN,
                Random.Range(0, 8));
            // Debug.Log($"pitch is {myPitch}");
            enemydict["pitch"] = myPitch;
            return enemydict;
        }
        
        var dict = new Dictionary<string, float>(Common.NoteInfo);
        
        foreach (var mod in ActivePatch())
        {
            if (mod is IMusicParams musicMod)
            {
                foreach (var param in musicMod.MusicParams())
                {
                    dict[param.Key] = param.Value;
                }
            }
        }

        return dict;
    }

    private Dictionary<Common.SoundType, float> EnergyCost()
    {
        if (enemySystem)
        {
            return Common.RandomEnergyCost();
        }
        
        var dict = new Dictionary<Common.SoundType, float>(baseEnergyCost);

        foreach (var mod in ActivePatch())
        {
            if (mod is INeedEnergy energyMod)
            {
                foreach (var kvp in energyMod.EnergyCost())
                {
                    if (!dict.ContainsKey(kvp.Key))
                    {
                        dict[kvp.Key] = kvp.Value;
                    }
                    else
                    {
                        dict[kvp.Key] += kvp.Value;
                    }
                }
            }
        }
        
        return dict;
    }
    
    private void GenerateEnergy(EnergyReservoir targetReservoir)
    {
        if (health <= 0)
        {
            return;
        }

        var newEnergy = new Dictionary<Common.SoundType, float>
        {
            { Common.SoundType.None, 0 },
            { Common.SoundType.Izki, 0 },
            { Common.SoundType.Aubo, 0 },
            { Common.SoundType.Dwth, 0 }
        };

        foreach (var mod in EnergyPatch())
        {
            if (mod is IReactorModule iReactorMod)
            {
                if (mod is PowerModule)
                {
                    // Add the energy amount as untyped energy (right now, this assumes a power module)
                    newEnergy[Common.SoundType.None] += iReactorMod.MyReactorStats().PowerGenerated;
                    // Debug.Log($"Added {iReactorMod.MyReactorStats().PowerGenerated} power");
                }

                if (mod is ConverterModule)
                {
                    // this is probably gonna throw errors, but I'm not sure exactly how
                    var enCon = iReactorMod.MyReactorStats().EnergyConversion;
                    var conAmt = Mathf.Min(enCon.EnergyLimit, newEnergy[Common.SoundType.None]);

                    newEnergy[Common.SoundType.None] -= conAmt;

                    foreach (var kvp in iReactorMod.MyReactorStats().EnergyConversion.ConversionRatios)
                    {
                        newEnergy[kvp.Key] += conAmt * kvp.Value;
                        // Debug.Log($"Converted {conAmt * kvp.Value} energy to {kvp.Key}");
                    }
                }
            }
        }

        targetReservoir.AddEnergy(newEnergy);


        // TODO: once a system for adding invisible modules to enemy ships is in place, delete this
        // the above code will work once that's all in place
        // This is a stopgap for enemy ships
        if (enemySystem)
        {
            targetReservoir.storedEnergy[Common.SoundType.None] += Time.deltaTime;
        }
    }

    public void Fire()
    {
        // if (!enemySystem)
        // {
        //     Debug.Log("yello");
        // }
        
        var myReactor = enemySystem ? ShipManager.Instance.EnemyReactor() : ShipManager.Instance.PlayerReactor();
        // Debug.Log(name);
        if (health <= 0)
        {
            return;
        }
        
        if (overheated)
        {
            // Debug.Log($"{name} needs to cool down.");
            return;
        }

        if (!enemySystem && !CompletePatch())
        {
            // Debug.Log($"{name} has an incomplete patch.");
            return;
        }

        if (!firing)
        {
            // Debug.Log($"{name} is not firing");
            return;
        }

        if (!energyReservoir.TrySpendEnergy(EnergyCost()))
        {
            // Debug.Log($"{name} didn't have enough energy to fire.");
            return;
        }

        heat += .125f * WeaponStats()["heat"];
        
        
        DisplayManager.Instance.Log("Fired " + name);
        
        // calculate hit/miss + damage
        if (CombatManager.Instance.state == CombatManager.State.inCombat)
        {
            if (enemySystem)
            {
                ShipManager.Instance.DamagePlayer(WeaponStats(), SoundType(), WeaponEffects());
            }
            else
            {
                ShipManager.Instance.DamageEnemy(WeaponStats(), SoundType(), WeaponEffects());
            }
        }
        
        EventBus.Instance.weaponFired.Invoke(this);
    }

    public override bool CompletePatch()
    {
        return base.CompletePatch() &&
               ActivePatch().TrueForAll(x => x is IWeaponModule or SecondaryModule or TriggerModule) &&
               ActivePatch().Exists(x => x is ClockModule) &&
               ActivePatch().Exists(x => x is SourceModule);
    }
    
    public Dictionary<Common.SoundType, float> SoundType()
    {
        var dict = new Dictionary<Common.SoundType, float>(Common.EmptySoundType);
        foreach (var mod in ActivePatch())
        {
            if (mod is IWeaponModule weaponModule)
            {
                foreach (var kvp in weaponModule.MyWeaponStats().SoundType)
                {
                    dict[kvp.Key] += kvp.Value;
                }
            }
        }
        return dict;
    }

    private List<Module> EnergyPatch()
    {
        if (enemySystem)
            return new List<Module>();

        if (parentEnergyWire == null)
            return new List<Module>();

        if (parentEnergyWire.GetComponent<Wire>().previousModule == null)
            return new List<Module>();

        var patch = new List<Module>();
        var prev = parentEnergyWire.GetComponent<Wire>().previousModule.GetComponent<Module>();
        var loopCount = 0;
        while (prev.PreviousModule() != null)
        {
            if (loopCount > 299)
            {
                parentWire.GetComponent<Wire>().DeleteSelf();
                Debug.Log("Wire privileges revoked because you made an infinite loop.\n>:(");
                break;
            }

            loopCount++;
            // Debug.Log(prev.name);
            patch.Add(prev);

            if (prev.PreviousModule().TryGetComponent(out Module mod))
            {
                prev = mod;
            }
            else
            {
                break;
            }
        }

        patch.Add(prev);
        patch.Reverse();
        return patch;
    }
}
