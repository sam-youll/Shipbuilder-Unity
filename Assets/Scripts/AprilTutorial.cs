using System.Collections;
using Unity.VisualScripting;
using UnityEngine;

public class AprilTutorial : MonoBehaviour
{
    //cursor variables
    public GameObject fakeCursor;
    private Vector3 fakeCursorPos;
    private Vector3 cursorStart;
    private Vector3 cursorTarget;
    public float cursorSpeed;
    public float step;
    private bool cursorSet;

    //tutorial variables
    private int currentStep;
    private bool isComplete;

    //module variables
    public GameObject funnel;
    public GameObject funnelOutput;
    public GameObject funnelInput;
    public GameObject fuel;
    public GameObject fuelOutput;
    public GameObject izkiModule;
    public GameObject izkiOutput;


    //highlight variables
    public GameObject inventoryHighlight;
    private Vector3 modulePlacePos;
    public GameObject modulePlaceHighlight;
    public GameObject startCombatHighlight;
    private Vector3 highlightScale;

    //rack variables
    public GameObject reactor;
    public GameObject weaponRack;
    public GameObject reactorInput;
    public GameObject weaponInput;

    //jack variables
    public GameObject jack1;
    public GameObject jack2;
    private Vector3 jack1Pos;
    private Vector3 jack2Pos;

    public GameObject startButton;

    public float timerLength = 0.2f;
    private bool timerStarted = false;

    // Start is called once before the first execution of Update after the MonoBehaviour is created

    void Start()
    {
        fakeCursorPos = new Vector3(fakeCursor.transform.position.x, fakeCursor.transform.position.y, -6f);
    }

    // Update is called once per frame
    void Update()
    {
        //timer for chime sound
        if (timerStarted)
        {
            timerLength -= Time.deltaTime;
        } else
        {
            timerLength = 0.2f;
        }
        if (timerLength <= 0)
        {
            EndTimer();
            timerStarted = false;
        }

        step = cursorSpeed * Time.deltaTime;
        fakeCursorPos = Vector3.MoveTowards(fakeCursor.transform.position, cursorTarget, step);
        if (fakeCursorPos == cursorTarget)
        {
            fakeCursorPos = cursorStart;
        }

        if (currentStep == 0)
        {
            //OPEN INVENTORY
            isComplete = false;
            inventoryHighlight.SetActive(true);
            cursorSpeed = 3;
            

            cursorStart = new Vector3(0, 5.84f, -6f);
            if (!cursorSet)
            {
                fakeCursorPos = cursorStart;
                cursorSet = true;
            }
            cursorTarget = new Vector3(-7, 7, -6f);
            fakeCursor.SetActive(true);


            if (Inventory.Instance.isPulledDown)
            {
                inventoryHighlight.SetActive(false);
                fakeCursor.SetActive(false);
                isComplete = true;
                CompleteStep();
            }
        }
        if (currentStep == 1)
        {
            //PLACE FUNNEL
            isComplete = false;
            cursorSpeed = 8;

            modulePlacePos = new Vector3(-12, -4, -3.4241f);
            highlightScale = new Vector3(9, 9, 9);
            modulePlaceHighlight.SetActive(true);

            cursorStart = new Vector3 (funnel.transform.position.x, funnel.transform.position.y, -6f);
            if (!cursorSet)
            {
                fakeCursorPos = cursorStart;
                cursorSet = true;
            }
            cursorTarget = new Vector3 (modulePlaceHighlight.transform.position.x, modulePlaceHighlight.transform.position.y, -6f);
            fakeCursor.SetActive(true);

            if (funnel.transform.parent == reactor.transform)
            {
                    fakeCursor.SetActive(false);
                    modulePlaceHighlight.SetActive(false);
                    isComplete = true;
                    CompleteStep();
            }

        }

        if (currentStep == 2)
        {
            //PLUG FUNNEL IN
            isComplete = false;
            cursorSpeed = 3;
            cursorStart = new Vector3 (funnelOutput.transform.position.x, funnelOutput.transform.position.y, -6f);
            if (!cursorSet)
            {
                fakeCursorPos = cursorStart;
                cursorSet = true;
            }
            cursorTarget = new Vector3 (reactorInput.transform.position.x, reactorInput.transform.position.y, -6f);
            fakeCursor.SetActive(true);

            jack1Pos = new Vector3(funnelOutput.transform.position.x, funnelOutput.transform.position.y, -4);
            jack2Pos = new Vector3(reactorInput.transform.position.x, reactorInput.transform.position.y, -.17f);
            jack1.SetActive(true);
            jack2.SetActive(true);

            if (Reactor.Instance.rate > 0)
            {
                fakeCursor.SetActive(false);
                jack1.SetActive(false);
                jack2.SetActive(false);
                isComplete = true;
                CompleteStep();
            }
        }

        if (currentStep == 3)
        {
            //OPEN INVENTORY
            isComplete = false;
            cursorSpeed = 3;
            inventoryHighlight.SetActive(true);
            cursorStart = new Vector3(0, 5.84f, -6f);
            if (!cursorSet)
            {
                fakeCursorPos = cursorStart;
                cursorSet = true;
            }
            cursorTarget = new Vector3(2.01f, 7.06f, -6f);
            fakeCursor.SetActive(true);

            if (Inventory.Instance.isPulledDown)
            {
                inventoryHighlight.SetActive(false);
                fakeCursor.SetActive(false);
                isComplete = true;
                CompleteStep();
            }
        }

        if (currentStep == 4)
        {
            //PLACE FUEL
            isComplete = false;
            cursorSpeed = 8;

            modulePlacePos = new Vector3(-12.5f, 0.5f, -3.4241f);
            highlightScale = new Vector3(18, 18, 18);
            modulePlaceHighlight.SetActive(true);

            cursorStart = new Vector3(fuel.transform.position.x, fuel.transform.position.y, -6f);
            if (!cursorSet)
            {
                fakeCursorPos = cursorStart;
                cursorSet = true;
            }
            cursorTarget = new Vector3(modulePlaceHighlight.transform.position.x, modulePlaceHighlight.transform.position.y, -6f);
            fakeCursor.SetActive(true);
            

            if (fuel.transform.parent == reactor.transform) 
            {
                fakeCursor.SetActive(false);
                modulePlaceHighlight.SetActive(false);
                isComplete = true;
                CompleteStep();
            }
        }

        if (currentStep == 5)
        {
            //PLUG IN FUEL
            isComplete = false;
            cursorSpeed = 2;
            cursorStart = new Vector3(fuelOutput.transform.position.x, fuelOutput.transform.position.y, -6f);
            if (!cursorSet)
            {
                fakeCursorPos = cursorStart;
                cursorSet = true;
            }
            cursorTarget = new Vector3(funnelInput.transform.position.x, funnelInput.transform.position.y, -6f);
            fakeCursor.SetActive(true);

            jack1Pos = new Vector3(fuelOutput.transform.position.x, fuelOutput.transform.position.y, -4);
            jack2Pos = new Vector3(funnelInput.transform.position.x, funnelInput.transform.position.y, -4);
            jack1.SetActive(true);
            jack2.SetActive(true);

            if (Reactor.Instance.strength > 0)
            {
                isComplete = true;
                jack1.SetActive(false);
                jack2.SetActive(false);
                fakeCursor.SetActive(false);
                CompleteStep();
            }
        }

        if (currentStep == 6)
        {
            //OPEN INVENTORY
            isComplete = false;
            cursorSpeed = 3;
            inventoryHighlight.SetActive(true);
            fakeCursor.SetActive(true);
            cursorStart = new Vector3(0, 5.84f, -3.4775f);
            if (!cursorSet)
            {
                fakeCursorPos = cursorStart;
                cursorSet = true;
            }
            cursorTarget = new Vector3(-7, 7, -3.4775f);

            if (Inventory.Instance.isPulledDown)
            {
                inventoryHighlight.SetActive(false);
                fakeCursor.SetActive(false);
                isComplete = true;
                CompleteStep();
            }
        }

        if (currentStep == 7)
        {
            //PLACE IZKI
            isComplete = false;
            cursorSpeed = 6;
            modulePlacePos = new Vector3(-7, -4, -3.4241f);
            modulePlaceHighlight.SetActive(true);
            highlightScale = new Vector3(9, 9, 9);

            cursorStart = new Vector3(izkiModule.transform.position.x, izkiModule.transform.position.y, -6f);
            if (!cursorSet)
            {
                fakeCursorPos = cursorStart;
                cursorSet = true;
            }
            cursorTarget = new Vector3(modulePlaceHighlight.transform.position.x, modulePlaceHighlight.transform.position.y, -6f); 
            fakeCursor.SetActive(true);

            if (izkiModule.transform.parent == weaponRack.transform) 
            {
                fakeCursor.SetActive(false);
                modulePlaceHighlight.SetActive(false);
                isComplete = true;
                CompleteStep();
            }
        }

        if (currentStep == 8)
        {
            //PLUG IN IZKI
            isComplete = false;
            cursorSpeed = 3;
            cursorStart = new Vector3(izkiOutput.transform.position.x, izkiOutput.transform.position.y, -6f);
            cursorTarget = new Vector3(weaponInput.transform.position.x, weaponInput.transform.position.y, -6f);
            fakeCursor.SetActive(true);

            jack1Pos = new Vector3(izkiOutput.transform.position.x, izkiOutput.transform.position.y, -4);
            jack2Pos = new Vector3(weaponInput.transform.position.x, weaponInput.transform.position.y, -4f);
            jack1.SetActive(true);
            jack2.SetActive(true);

            if (izkiModule.GetComponent<Module>().nextModule != null)
            {
                fakeCursor.SetActive(false);
                jack1.SetActive(false); 
                jack2.SetActive(false);
                isComplete = true;
                CompleteStep();
            }
        }

        if (currentStep == 9)
        {
            isComplete = false;
            startCombatHighlight.SetActive(true);
            cursorSpeed = 8;
            cursorStart = new Vector3(0, 0, -3.4775f);
            if (!cursorSet)
            {
                fakeCursorPos = cursorStart;
                cursorSet = true;
            }
            //change this to start combat
            cursorTarget = startCombatHighlight.transform.position;
            fakeCursor.SetActive(true);

            if (startButton.GetComponent<StartCombatButton>().Pressed)
            {
                fakeCursor.SetActive(false);
                startCombatHighlight.SetActive(false);
            }

        }


        fakeCursor.transform.position = fakeCursorPos;
        modulePlaceHighlight.transform.position = modulePlacePos;
        modulePlaceHighlight.transform.localScale = highlightScale;
        jack1.transform.position = jack1Pos;
        jack2.transform.position = jack2Pos;
    }

    void CompleteStep()
    {
        if (isComplete)
        {
            timerStarted = true;
            currentStep++;
            cursorSet = false;
        }
    }

    void EndTimer()
    {
        AudioManager.Instance.PlayDialogueSound();
    }

}
