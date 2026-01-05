using UnityEngine;
using UnityEngine.Events;

public class EventBus : MonoBehaviour
{
    public static EventBus Instance;

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

    // TODO: these should be grouped into more specific fields later, as we consolidate more events into the bus
    [Header("Events")] 
    public UnityEvent combatStarted;
    public UnityEvent combatEnded;
    public UnityEvent<Weapon> weaponFired;
    public UnityEvent<Wire> updateJackValidity;
}
