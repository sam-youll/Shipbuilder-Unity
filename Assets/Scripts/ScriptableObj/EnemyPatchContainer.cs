using UnityEngine;

[CreateAssetMenu(fileName = "EnemyPatchContainer", menuName = "Scriptable Objects/EnemyPatchContainer")]
public class EnemyPatchContainer : ScriptableObject
{
    public ScriptableObject weapon1;
    public ScriptableObject weapon2;
    public ScriptableObject shield1;
    public ScriptableObject shield2;

}
