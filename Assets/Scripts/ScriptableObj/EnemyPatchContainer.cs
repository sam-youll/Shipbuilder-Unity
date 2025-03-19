using UnityEngine;

[CreateAssetMenu(fileName = "EnemyPatchContainer", menuName = "Scriptable Objects/EnemyPatchContainer")]
public class EnemyPatchContainer : ScriptableObject
{
    [Header("Weapons")]
    public EnemyWeapon[] weapons = new EnemyWeapon[6];
    
    [Header("Shields")]
    public EnemyShield[] shields = new EnemyShield[6];

}
