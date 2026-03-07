using System;
using SaintsField;
using TMPro;
using UnityEngine;

public class UIOverlay : MonoBehaviour
{
    public static UIOverlay Instance { get; private set; }
    private void Awake()
    {
        if (Instance != null && Instance != this)
        {
            Destroy(gameObject);
        }
        else
        {
            Instance = this;
            DontDestroyOnLoad(gameObject);
        }
    }

    public TextMeshPro hullText;
    public TextMeshPro scrapText;

    private void Start()
    {
        EventBus.Instance.playerHullValueChanged.AddListener(OnPlayerHullValueChanged);
        EventBus.Instance.playerScrapValueChanged.AddListener(OnPlayerScrapValueChanged);
    }

    private void OnPlayerHullValueChanged()
    {
        hullText.text = Mathf.RoundToInt(ShipManager.Instance.PlayerHull()) + "/" + ShipManager.Instance.PlayerMaxHull();
    }

    private void OnPlayerScrapValueChanged()
    {
        scrapText.text = Inventory.Instance.scrap.ToString();
    }
}
