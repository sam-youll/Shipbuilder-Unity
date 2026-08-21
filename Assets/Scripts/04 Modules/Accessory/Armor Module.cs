using UnityEngine;

public class ArmorModule : AccessoryModule
{
    public float armor = 20;
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    public override string Description()
    {
        return "Adds armor plating to the ship, increasing the maximum health of the attached system and the ship's hull.";
    }

    public override string Info()
    {
        return $"Armor value: {armor}";
    }
}
