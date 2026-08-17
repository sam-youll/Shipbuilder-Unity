using System;
using System.Collections.Generic;
using System.Linq;
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
    [ShowInInspector, SaintsDictionary] public Dictionary<string, float> baseWeaponStats = new(Common.BaseWeaponStats().Stats.ToDictionary(x => x.Key, x => x.Value));
    [ShowInInspector, SaintsDictionary] public Dictionary<Common.SoundType, float> baseEnergyCost = new(Common.EmptyEnergyCost());
    public float baseCoolingRate = .1f;
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

    public override string Info()
    {
        var info = base.Info();
        
        info += "Weapon Stats:\n";
        foreach (var kvp in WeaponStats().Stats)
        {
            if (kvp.Key == "bulletType")
            {
                info += Funcs.ConvertCamelCase(kvp.Key.ToString()) + ": " + Enum.GetName(typeof(Common.BulletType), (int)kvp.Value) + "\n";
            }
            else if (kvp.Key == "soundType")
            {
                info += Funcs.ConvertCamelCase(kvp.Key.ToString()) + ": " + Enum.GetName(typeof(Common.SoundType), (int)kvp.Value) + "\n";
            }
            else
            {
                info += Funcs.ConvertCamelCase(kvp.Key.ToString()) + ": " + kvp.Value + "\n";
            }
        }
        info += "Cooling at a rate of " + CoolingRate() + " per second\n";
        return info;
    }

    public override bool Warning(out string message)
    {
        message = "";
        var hasClock = false;
        var hasSource = false;
        var energyNeeds = new Dictionary<Common.SoundType, float>(Common.EmptyEnergyCost());
        foreach (var module in ActivePatch())
        {
            if (module is ClockModule) hasClock = true;
            if (module is SourceModule) hasSource = true;
            if (module is INeedEnergy eMod)
            {
                energyNeeds = eMod.ChangeEnergyCost(energyNeeds);
            }
        }

        
        if (!hasClock)
        {
            message += "No clock module present to trigger this weapon.\n";
        }

        if (!hasSource)
        {
            message += "No source module present to generate sound.\n";
        }

        if (!WeaponHasEnergyForYou(energyNeeds, out var missingEnergy))
        {
            message += "This weapon is missing the following energy types it needs to fire:\n";
            foreach (var energy in missingEnergy)
            {
                message += "- " + energy + "\n";
            }
        }
        
        return !hasClock || !hasSource || missingEnergy.Count > 0;
    }

    public bool WeaponHasEnergyForYou(Dictionary<Common.SoundType, float> energyNeeds, out List<Common.SoundType> missingEnergy)
    {
        missingEnergy = new List<Common.SoundType>();
        var theoreticalEnergyProduction = new Dictionary<Common.SoundType, float>(Common.EmptyEnergyCost());
        foreach (var mod in EnergyPatch())
        {
            if (mod is IReactorModule iReactorMod)
            {
                theoreticalEnergyProduction = iReactorMod.ChangeEnergy(theoreticalEnergyProduction);
            }
        }

        foreach (var kvp in energyNeeds)
        {
            if (kvp.Value > 0)
            {
                if (theoreticalEnergyProduction[kvp.Key] <= 0)
                {
                    missingEnergy.Add(kvp.Key);
                }
            }
        }

        return missingEnergy.Count == 0;
    }

    public float CoolingRate()
    {
        var rate = baseCoolingRate;
        foreach (var module in ModulesOnRack())
        {
            if (module is VentModule vMod)
            {
                rate += vMod.coolingRateBonus;
            }
        }

        return rate;
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

        if (EnergyPatch().Count > 0 || enemySystem)
        {
            GenerateEnergy(energyReservoir);
        }
    }

    public float HeatDissipation()
    {
        if (slowTimer > 0)
        {
            return .25f * CoolingRate() * Time.deltaTime;
        }
        return CoolingRate() * Time.deltaTime;
    }

    public IWeaponModule.WeaponStats WeaponStats()
    {
        var ws = new IWeaponModule.WeaponStats(Common.BaseWeaponStats())
        {
            Stats = baseWeaponStats.ToDictionary(x => x.Key, x => x.Value)
        };

        foreach (var mod in ActivePatch())
        {
           if (mod is IWeaponModule weaponMod)
           {
               ws = weaponMod.ChangeWeaponStats(ws);
           }
        }
        
        return ws;
    }

    public Dictionary<string, float> MusicParams()
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
        
        var dict = new Dictionary<string, float>(Common.NoteInfo.ToDictionary(x => x.Key, x => x.Value));
        
        foreach (var mod in ActivePatch())
        {
            if (mod is IMusicParams musicMod)
            {
                dict = musicMod.ChangeMusicParams(dict);
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
                dict = energyMod.ChangeEnergyCost(dict);
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
        
        // TODO: once a system for adding invisible modules to enemy ships is in place, delete this
        // the above code will work once that's all in place
        // This is a stopgap for enemy ships
        if (enemySystem)
        {
            targetReservoir.storedEnergy[Common.SoundType.Pure] += Time.deltaTime;
            return;
        }

        var newEnergy = new Dictionary<Common.SoundType, float>(Common.EmptyEnergyCost());

        foreach (var mod in EnergyPatch())
        {
            if (mod is IReactorModule iReactorMod)
            {
                newEnergy = iReactorMod.ChangeEnergy(newEnergy);
            }
        }

        targetReservoir.AddEnergy(newEnergy);

        EventBus.Instance.weaponPowered.Invoke();
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

        heat += WeaponStats().Stats["heat"];
        Debug.Log(heat);
        
        DisplayManager.Instance.Log("Fired " + name);
        
        // calculate hit/miss + damage
        if (CombatManager.Instance.state == CombatManager.State.inCombat)
        {
            if (enemySystem)
            {
                ShipManager.Instance.DamagePlayer(WeaponStats());
            }
            else
            {
                ShipManager.Instance.DamageEnemy(WeaponStats());
            }
        }
        
        EventBus.Instance.weaponFired.Invoke(this);
    }

    public override bool CompletePatch()
    {
        if (base.CompletePatch() &&
            ActivePatch().TrueForAll(x => x is IWeaponModule or SecondaryModule or TriggerModule) &&
            ActivePatch().Exists(x => x is ClockModule) &&
            ActivePatch().Exists(x => x is SourceModule))
        {
            EventBus.Instance.weaponModulesConnected.Invoke();
            return true;
        }

        return false;
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
