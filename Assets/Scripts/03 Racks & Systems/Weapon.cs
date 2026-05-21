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
    public bool enemyWeapon; // set true if Weapon belongs to an enemy ship
    [ShowInInspector, SaintsDictionary] public Dictionary<string, float> baseWeaponStats = new();
    [ShowInInspector, SaintsDictionary] public Dictionary<Common.SoundType, float> baseEnergyCost = new();

    [Header("Components")]
    public Image heatOverlay;
    public SwitchComponent testFireSwitch;

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
        if (enemyWeapon)
        {
            Conductor.Instance.onSixteenth.AddListener(Fire);
        }
        else
        {
            heatOverlay.rectTransform.sizeDelta = GetComponent<ModuleRack>().dimensions + Vector2Int.one;
        }
    }

    // Update is called once per frame
    void Update()
    {
        // are we either testing or in combat? If yes to either, we're firing
        firing = (!enemyWeapon && testFireSwitch.on) || CombatManager.Instance.state == CombatManager.State.inCombat;
        // if we're facing right (only true if player ship) and the patch is not complete, turn it off
        if (!enemyWeapon && !CompletePatch())
        {
            // Debug.Log("Is patch complete? " + CompletePatch());
            firing = false;
        }
        
        // if (warming)
        // {
        //     if (warmup < 1)
        //     {
        //         if (enemyWeapon)
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
        
        if (!enemyWeapon && firing && stunTimer <= 0)
        {
            heat -= HeatDissipation();
            heatOverlay.fillAmount = heat;
        }
        else if (enemyWeapon && firing && stunTimer <= 0)
        {
            heat -= HeatDissipation();
        }
    }

    public float HeatDissipation()
    {
        return 1 * Time.deltaTime;
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
               foreach (var stat in weaponMod.WeaponStats())
               {
                   dict[stat.Key] += stat.Value;
               }

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

        // var myReactor = enemyWeapon ? ShipManager.Instance.EnemyReactor() : ShipManager.Instance.PlayerReactor();
        // dict["damage"] *= (1 + .5f * myReactor.strength);

        return dict;
    }

    public Dictionary<string, float> NoteInfo()
    {
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
        var dict = new Dictionary<Common.SoundType, float>(baseEnergyCost);

        foreach (var mod in ActivePatch())
        {
            if (mod is INeedEnergy energyMod)
            {
                foreach (var kvp in energyMod.EnergyCost())
                {
                    dict[kvp.Key] = kvp.Value;
                }
            }
        }
        
        return dict;
    }

    public void Fire()
    {
        var myReactor = enemyWeapon ? ShipManager.Instance.EnemyReactor() : ShipManager.Instance.PlayerReactor();
        // Debug.Log(name);
        if (!enemyWeapon && heatOverlay.fillAmount > 0)
        {
            // Debug.Log($"{name} needs to cool down.");
            return;
        }

        if (!enemyWeapon && !CompletePatch())
        {
            // Debug.Log($"{name} has an incomplete patch.");
            return;
        }

        if (!firing)
        {
            // Debug.Log($"{name} is not firing");
            return;
        }

        if (!myReactor.TrySpendEnergy(EnergyCost()))
        {
            // Debug.Log($"{name} didn't have enough energy to fire.");
            return;
        }

        if (!enemyWeapon)
        {
            heatOverlay.fillAmount = 1;
        }
        
        DisplayManager.Instance.Log("Fired " + name);
        
        // calculate hit/miss + damage
        if (CombatManager.Instance.state == CombatManager.State.inCombat)
        {
            if (enemyWeapon)
            {
                var hit = WeaponStats()["accuracy"] * (1 - ShipManager.Instance.PlayerEvasion());
                if (hit <= 0)
                {
                    // Debug.Log("miss");
                    ShipManager.Instance.DamagePlayer(hit, WeaponStats()["soundType"]); // TODO: add overloads so I don't have to call useless stuff
                    EventBus.Instance.playerHit.Invoke(hit);
                }
                else
                {
                    // Debug.Log("hit");
                    ShipManager.Instance.DamagePlayer(
                        WeaponStats()["damage"], WeaponStats()["soundType"]); // TODO: make it so that multiple effects can be sent
                    EventBus.Instance.playerHit.Invoke(WeaponStats()["damage"]);
                }
            }
            else
            {
                var hit = WeaponStats()["accuracy"] * (1 - ShipManager.Instance.EnemyEvasion());
                if (hit <= 0)
                {
                    // Debug.Log("miss");
                    ShipManager.Instance.DamageEnemy(hit, WeaponStats()["soundType"]); // TODO: add overloads so I don't have to call useless stuff
                    EventBus.Instance.enemyHit.Invoke(hit);
                }
                else
                {
                    // Debug.Log("hit");
                    ShipManager.Instance.DamageEnemy(
                        WeaponStats()["damage"], WeaponStats()["soundType"]); // TODO: make it so that multiple effects can be sent
                    EventBus.Instance.enemyHit.Invoke(WeaponStats()["damage"]);
                }
            }
        }
        
        EventBus.Instance.weaponFired.Invoke(this);
    }
}
