using System.Collections;
using Unity.VisualScripting;
using UnityEngine;
using TMPro;

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
    public GameObject currentModule;


    //highlight variables
    public GameObject inventoryHighlight;
    private Vector3 modulePlacePos;
    public GameObject modulePlaceHighlight;
    public GameObject startCombatHighlight;
    private Vector3 highlightScale;
    public GameObject battleScreen;

    //rack variables
    public GameObject reactor;
    public GameObject weaponRack;
    public GameObject reactorInput;
    public GameObject weaponInput;

    //transform pos variables for moving things in front of/behind the dimmer
    private Vector3 inventoryPos;
    public Vector3 currentModulePos;
    private Vector3 battleScreenPos;
    private Vector3 reactorPos;
    private Vector3 weaponPos;


    //jack variables
    public GameObject jack1;
    public GameObject jack2;
    private Vector3 jack1Pos;
    private Vector3 jack2Pos;

    public GameObject startButton;
    public GameObject startBlock;

    public float timerLength = 0.2f;
    private bool timerStarted = false;

    //text
    public TextMeshPro tutorialText;


    // Start is called once before the first execution of Update after the MonoBehaviour is created

    void Start()
    {
        fakeCursorPos = new Vector3(fakeCursor.transform.position.x, fakeCursor.transform.position.y, -6f);
        inventoryPos = Inventory.Instance.transform.position;
        battleScreenPos = battleScreen.transform.position;
        reactorPos = reactor.transform.parent.transform.position;
        weaponPos = weaponRack.transform.parent.transform.position;
        UpdateCurrentModule(funnel);
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

            tutorialText.text = "Open your inventory";

            HighlightInventory();
            if (funnel.transform.parent = Inventory.Instance.transform)
            {
                UpdateCurrentModule(funnel);
            }

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

            modulePlacePos = new Vector3(-12, -4, -6);
            highlightScale = new Vector3(9, 9, 9);
            modulePlaceHighlight.SetActive(true);

            reactorPos.z = -4;
            reactor.transform.parent.transform.position = reactorPos;

            tutorialText.text = "Move the Converter module into your Reactor.";

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
                HideInventory();
                CompleteStep();

                bool placedModule = false;
                if (!placedModule)
                {
                    currentModulePos = cursorTarget;
                    currentModule.transform.position = currentModulePos;
                    placedModule = true;
                }
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

            tutorialText.text = "Plug the Converter module into the Reactor's output. <br><br><br>This will speed things up.";

            jack1Pos = new Vector3(funnelOutput.transform.position.x, funnelOutput.transform.position.y, -7);
            jack2Pos = new Vector3(reactorInput.transform.position.x, reactorInput.transform.position.y, -9);
            jack1.SetActive(true);
            jack2.SetActive(true);

            if (Reactor.Instance.rate > 0)
            {
                fakeCursor.SetActive(false);
                jack1.SetActive(false);
                jack2.SetActive(false);
                isComplete = true;
                currentModulePos.z = -1;
                CompleteStep();
            }
        }

        if (currentStep == 3)
        {
            reactorPos.z = 0;
            reactor.transform.parent.transform.position = reactorPos;

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
            cursorTarget = new Vector3(-7, 7, -6f);
            fakeCursor.SetActive(true);

            tutorialText.text = "Open your inventory.";

            if (fuel.transform.parent = Inventory.Instance.transform)
            {
                UpdateCurrentModule(fuel);
            }
            HighlightInventory();

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

            modulePlacePos = new Vector3(-12.5f, 0.5f, -6);
            highlightScale = new Vector3(18, 18, 18);
            modulePlaceHighlight.SetActive(true);

            reactorPos.z = -4;
            reactor.transform.parent.transform.position = reactorPos;

            tutorialText.text = "Move the Power module into your Reactor.";

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
                HideInventory();
                CompleteStep();

                bool placedModule = false;
                if (!placedModule)
                {
                    currentModulePos = cursorTarget;
                    currentModule.transform.position = currentModulePos;
                    placedModule = true;
                }
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

            tutorialText.text = "Route the Power module through your Converter module. <br><br>This will provide power that will be funneled to your weapons.";

            jack1Pos = new Vector3(fuelOutput.transform.position.x, fuelOutput.transform.position.y, -7);
            jack2Pos = new Vector3(funnelInput.transform.position.x, funnelInput.transform.position.y, -9);
            jack1.SetActive(true);
            jack2.SetActive(true);

            if (Reactor.Instance.strength > 0)
            {
                isComplete = true;
                jack1.SetActive(false);
                jack2.SetActive(false);
                fakeCursor.SetActive(false);
                currentModulePos.z = -1;
                CompleteStep();
            }
        }

        if (currentStep == 6)
        {

            reactorPos.z = 0;
            reactor.transform.parent.transform.position = reactorPos;

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

            tutorialText.text = "Open your inventory.";

            HighlightInventory();
            if (izkiModule.transform.parent = Inventory.Instance.transform)
            {
                UpdateCurrentModule(izkiModule);
            }
            

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
            modulePlacePos = new Vector3(-7, -4, -6);
            modulePlaceHighlight.SetActive(true);
            highlightScale = new Vector3(9, 9, 9);

            tutorialText.text = "Move your Source module into your Weapon Rack.";

            weaponPos.z = -5;
            weaponRack.transform.parent.transform.position = weaponPos;

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
                HideInventory();
                CompleteStep();

                bool placedModule = false;
                if (!placedModule)
                {
                    currentModulePos = cursorTarget;
                    currentModule.transform.position = currentModulePos;
                    placedModule = true;
                }
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

            tutorialText.text = "Plug your Source module into your Weapon Rack's Output Jack. <br><br>This will determine what your ship fires.";

            jack1Pos = new Vector3(izkiOutput.transform.position.x, izkiOutput.transform.position.y, -7);
            jack2Pos = new Vector3(weaponInput.transform.position.x, weaponInput.transform.position.y, -9);
            jack1.SetActive(true);
            jack2.SetActive(true);

            if (izkiModule.GetComponent<Module>().nextModule != null)
            {
                fakeCursor.SetActive(false);
                jack1.SetActive(false); 
                jack2.SetActive(false);
                isComplete = true;
                currentModulePos.z = -1;
                CompleteStep();
            }
        }

        if (currentStep == 9)
        {
            weaponPos.z = 0;
            weaponRack.transform.parent.transform.position = weaponPos;

            isComplete = false;
            startCombatHighlight.SetActive(true);
            cursorSpeed = 8;
            cursorStart = new Vector3(0, 0, -3.4775f);
            if (!cursorSet)
            {
                fakeCursorPos = cursorStart;
                cursorSet = true;
            }

            tutorialText.text = "When you're ready, click to start combat";

            currentModule = startBlock;
            currentModulePos = new Vector3(12.5f, 1.85f, -5);
            currentModule.transform.position = currentModulePos;

            //change this to start combat
            cursorTarget = startCombatHighlight.transform.position;
            fakeCursor.SetActive(true);

            if (startButton.GetComponent<StartCombatButton>().Pressed)
            {
                fakeCursor.SetActive(false);
                startCombatHighlight.SetActive(false);
                currentModulePos.z = -1;
                currentModule.transform.position = currentModulePos;
                battleScreenPos = new Vector3(6, -4.15f, -5);
                battleScreen.transform.position = battleScreenPos;
                tutorialText.enabled = false;
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
        AudioManager.Instance.PlayChime();
    }

    void HighlightInventory()
    {
        inventoryPos.z = -5;
        Inventory.Instance.transform.position = inventoryPos;
    }

    void HideInventory()
    {
        inventoryPos.z = -1;
        Inventory.Instance.transform.position = inventoryPos;
    }

    void UpdateCurrentModule(GameObject module)
    {
        currentModule = module;
        bool set = false;
        if (!set)
        {
            currentModulePos = currentModule.transform.localPosition;
            currentModulePos.z = -3;
            currentModule.transform.localPosition = currentModulePos;
            set = true;
        }   
    }

}
