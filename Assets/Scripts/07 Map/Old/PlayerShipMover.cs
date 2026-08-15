using UnityEngine;

public class PlayerShipMover : MonoBehaviour
{

    public Vector3 location;
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        location = transform.position;
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void MovePlayerShip(Vector3 newLocation)
    {
        location = newLocation;
        transform.position = location;
    }
}
