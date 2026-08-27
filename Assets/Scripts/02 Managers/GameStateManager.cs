using System;
using System.Collections.Generic;
using NUnit.Framework;
using TMPro;
using UnityEngine;
using UnityEngine.Events;
using UnityEngine.SceneManagement;

public class GameStateManager : MonoBehaviour
{
    public static GameStateManager Instance;

    private void Awake()
    {
        if (Instance != null && Instance != this)
        {
            Destroy(gameObject);
        }
        else
        {
            Instance = this;
            // DontDestroyOnLoad(this);
        }
    }
    
    //Not sure if this is best way to handle this, but it works for now
    public Dictionary<string, bool> Gamestate = new Dictionary<string, bool>();
    
    //TODO: move location stuff to map manager and have it set location based on where you are on the map
    //TODO: add more node types
    public enum Node
    {
        Base,
        Pallas,
        Pan,
        AsteroidBelt,
        Bailigh,
        Zea,
        Node
    }

    public enum Constellation
    {
        Aries,
        Taurus,
        Gemini,
        Cancer,
        Leo,
        Virgo,
        Libra,
        Scorpio,
        Sagittarius,
        Capricorn,
        Aquarius,
        Pisces
    }
    
    public Node currentNode;
    public Constellation currentConstellation;

    // WIP / placeholder, this enum should be where major linear game events go
    public enum Stage
    {
        Testing,
        Tutorial,
        Exposition,
        Pallas,
        Pan,
        AsteroidBelt,
        Bailigh,
        Zea
    }
    
    public Stage currentStage;
    
    public List<ConstellationInfo> constellationScrobjects = new List<ConstellationInfo>();
    
    public Dictionary<Constellation, string> ConstellationStrings = new Dictionary<Constellation, string>()
    {
        {Constellation.Aries, "aries"},
        {Constellation.Taurus, "taurus"},
        {Constellation.Gemini, "gemini"},
        {Constellation.Cancer, "cancer"},
        {Constellation.Leo, "leo"},
        {Constellation.Virgo, "virgo"},
        {Constellation.Libra, "libra"},
        {Constellation.Scorpio, "scorpio"},
        {Constellation.Sagittarius, "sagittarius"},
        {Constellation.Capricorn, "capricorn"},
        {Constellation.Aquarius, "aquarius"},
        {Constellation.Pisces, "pisces"},
    };

    public ConstellationInfo constellationInfo;
    

    /// <summary>
    /// Some ships require the player to reach a certain milestone to unlock.
    /// The Ship Manager will check these tags against the milestones that the
    /// player has reached, which will be recorded in the player's save file.
    /// </summary>
    public enum UnlockMilestones
    {
        None,
        GameEnd,
        TrueEnd,
        PanQuest,
        PallasQuest // TODO: add the ones that actually exist, delete the ones that don't
    }


    public void Start()
    {
        //Dummy gamestates, should add and test complexity and how to set moving forward.
        //This is just here to get the narrative stuff functioning
        Gamestate.Add("gameStarted", true);
        currentNode = Node.Base;
        currentConstellation = Constellation.Aries;
        currentStage = Stage.Testing;
        constellationInfo = constellationScrobjects[(int)currentConstellation];
        
        EventBus.Instance.playerDefeated.AddListener(OnPlayerDefeated);
        EventBus.Instance.leftShop.AddListener(OnPlayerLeftShop);
        EventBus.Instance.constellationAdvanced.AddListener(OnConstellationAdvanced);
        EventBus.Instance.constellationReset.AddListener(OnConstellationReset);
        
        //quest listeners
        EventBus.Instance.weaponPowered.AddListener(() => OnQuestStepCompleted("powerWeapon"));
        EventBus.Instance.weaponReady.AddListener(() => OnQuestStepCompleted("connectWeapon"));
        EventBus.Instance.combatStarted.AddListener(() => OnQuestStepCompleted("startCombat"));
        
        EventBus.Instance.modulePlaced.AddListener((x, y) => OnQuestStepCompleted(modulePlacedTypeCheck(x, y)));
        EventBus.Instance.wireConnected.AddListener((x, y) => OnQuestStepCompleted(modulesConnectedCheck(x, y)));
        
        EventBus.Instance.enemyDefeated.AddListener(() => OnQuestStepCompleted("winCombat"));
        EventBus.Instance.shopSlotPurchased.AddListener(() => OnQuestStepCompleted("purchaseShop"));
        
        // SceneManager.sceneLoaded += DeduplicateCameras;
        
        EventBus.Instance.questStepCompleted.AddListener(OnQuestStepCompleted);
        
        UIManager.Instance.UpdateQuestLog(activeQuests, stepsCompleted);
    }

    private readonly Func<Module, ModuleRack, string> modulePlacedTypeCheck = (mod, rack) =>
    {
        if (mod is PowerModule && rack is Reactor)
        {
            return "powerModule";
        }
        if (mod is ConverterModule && rack is Reactor)
        {
            return "converterModule";
        }
        if (mod is ClockModule && rack is Weapon)
        {
            return "clockModule";
        }
        if (mod is CatalystModule && rack is Weapon)
        {
            return "sourceModule";
        }

        return "";
    };

    private readonly Func<GameObject, GameObject, string> modulesConnectedCheck = (prev, next) =>
    {
        if (prev == null || next == null) return "";
        
        if (prev.TryGetComponent(out Module prevMod))
        {
            if (next.TryGetComponent(out Module nextMod))
            {
                if (prevMod is PowerModule && nextMod is ConverterModule) return "connectReactorModules";
                if (prevMod is ClockModule && nextMod is CatalystModule) return "connectModules";
            }
            else if (next.TryGetComponent(out ModuleRack rack))
            {
                if (prevMod is CatalystModule && rack is Weapon) return "connectWeapon";
            }
        }

        return "";
    };
        
    private void DeduplicateCameras(Scene scene, LoadSceneMode mode)
    {
        var cameras = FindObjectsByType<Camera>(FindObjectsSortMode.None);
        for (int i = 0; i < cameras.Length; i++)
        {
            if (cameras[i] != Global.Instance.cam)
            {
                Destroy(cameras[i].gameObject);
            }
        }
    }

    private void OnPlayerDefeated()
    {
        SceneManager.LoadScene("MainMenu");
        AudioManager.Instance.ReleaseFMODInstances();
    }

    private void OnPlayerLeftShop()
    {
    }

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Space))
        {
            EventBus.Instance.questStepCompleted.Invoke("pressSpace");
        }
        if (Input.GetKeyDown(KeyCode.Return) || Input.GetKeyDown(KeyCode.KeypadEnter))
        {
            EventBus.Instance.questStepCompleted.Invoke("pressEnter");
        }
    }
    
    #region Quest Manager
    
    public List<QuestData> activeQuests = new();
    public List<string> stepsCompleted = new();

    private void OnQuestStepCompleted(string stepName)
    {
        foreach (var quest in activeQuests)
        {
            // the quest has to exist and it has to be active (i.e. the steps before it have to be completed)
            if (quest.TryGetQuestStep(stepName, out var step) &&
                quest.DependenciesCompleted(stepName, x => stepsCompleted.Contains(x.stepName)))
            {
                Debug.Log("yayyy quest step completed");
                stepsCompleted.Add(stepName);
            }
        }
        
        QuestCompleteCheck();

        UIManager.Instance.UpdateQuestLog(activeQuests, stepsCompleted);
    }

    private void QuestCompleteCheck()
    {
        var indicesToRemove = new List<int>();
        for (var i = 0; i < activeQuests.Count; i++)
        {
            var quest = activeQuests[i];
            var complete = true;
            foreach (var step in quest.questSteps)
            {
                if (!stepsCompleted.Contains(step.stepName)) complete = false;
            }

            if (complete)
            {
                indicesToRemove.Add(i);
            }
        }

        if (indicesToRemove.Count > 0)
        {
            foreach (var i in indicesToRemove)
            {
                activeQuests.RemoveAt(i);
            }
        }
    }
    
    #endregion

    private void OnConstellationAdvanced()
    {
        OnQuestStepCompleted(ConstellationStrings[currentConstellation]);
        
        currentConstellation++;
        if ((int)currentConstellation > ConstellationStrings.Count)
        {
            EventBus.Instance.runComplete.Invoke();
        }
        constellationInfo = constellationScrobjects[(int)currentConstellation];
        Debug.Log("current constellation: " + currentConstellation);
    }

    private void OnConstellationReset()
    {
        currentConstellation = Constellation.Aries;
        constellationInfo = constellationScrobjects[(int)currentConstellation];
        
    }
    
}
