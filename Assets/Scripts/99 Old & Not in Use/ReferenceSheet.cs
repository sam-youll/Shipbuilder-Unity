using UnityEngine;

public class ReferenceSheet : MonoBehaviour
{
    //position of the sheet
    private Vector3 position;
    //how far she go up
    public float moveAmount;
    //where she will go when open
    private float onScreenXPos = -0.57f; 
    private float onScreenYPos = 0.03f;
    //where she will go when closed
    private float defaultXPos = -4.99f;
    private float defaultYPos = -9.66f;
    //whether she is open
    public bool isOpen;



    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        //setting position variable
        position = transform.position;
    }

    // Update is called once per frame
    void Update()
    {

    }

    private void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(0))
        {
            //if she's closed, open her when you click
            if (!isOpen)
            {
                position.x = onScreenXPos;
                position.y = onScreenYPos;
                transform.position = position;
                isOpen = true;
            }
            else
            {
                //if she's open, close her when you click
                ////NOTE : maybe we should find a way to do this when mouse is off of the paper too? idk
                position.x = defaultXPos;
                position.y = defaultYPos;
                transform.position = position;
                isOpen = false;
            }
        }
        if (Input.GetKeyDown(KeyCode.Space))
        {
            if (isOpen)
            {
                position.x = defaultXPos;
                position.y = defaultYPos;
                transform.position = position;
                isOpen = false;
            }
        }
    }

    private void OnMouseEnter()
    {
        //if she's closed, she'll move up when you mouseover
        if (!isOpen)
        {
            position.y += moveAmount;
            transform.position = position;
        }
    }

    private void OnMouseExit()
    {
        //if she's closed, she'll drop back down to default when you un-mouseover
        if (!isOpen)
        {
            position.x = defaultXPos;
            position.y = defaultYPos;
            transform.position = position;
        }
    }

}
