using UnityEngine;
using FMOD;
using FMODUnity;
using FMOD.Studio;
using Unity.Hierarchy;
using System.Collections.Generic;
using System.ComponentModel.Design;
using UnityEngine.UI;
using UnityEngine.EventSystems;
using TMPro;



public class CombatPrototypeAudioManager : MonoBehaviour
{
    //event instances
    private EventInstance shipAttackModuleInst;
    private EventInstance shipDefenseModuleInst;
    private EventInstance shipEvasionModuleInst;
    private EventInstance shipAccuracyModuleInst;
    private EventInstance enemyAttackModuleInst;
    private EventInstance enemyDefenseModuleInst;
    private EventInstance enemyEvasionModuleInst;
    private EventInstance enemyAccuracyModuleInst;

    //instance list
    public List<EventInstance> fmodEvents = new List<EventInstance>();
    //parameter dictionary
    public Dictionary<string, float> testParams = new Dictionary<string, float>();

    //FMOD event references
    public EventReference moduleRef;

    //FMOD parameter variables
    public float arpstart;
    public float pitch;
    public float source;
    public float arp;
    public float thruster;
    public float ringmod;

    //sliders 
    public GameObject shipAttackSlider;
    public GameObject shipDefenseSlider;
    public GameObject shipEvasionSlider;
    public GameObject shipAccuracySlider;
    public GameObject enemyAttackSlider;
    public GameObject enemyDefenseSlider;
    public GameObject enemyEvasionSlider;
    public GameObject enemyAccuracySlider;

    //Dropdowns
    public GameObject shipAttackDropdown;
    public GameObject shipDefenseDropdown;
    public GameObject shipEvasionDropdown;
    public GameObject shipAccuracyDropdown;
    public GameObject enemyAttackDropdown;
    public GameObject enemyDefenseDropdown;
    public GameObject enemyEvasionDropdown;
    public GameObject enemyAccuracyDropdown;

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        //adding events to the list
        fmodEvents.Add(shipAttackModuleInst);
        fmodEvents.Add(shipDefenseModuleInst);
        fmodEvents.Add(shipEvasionModuleInst);
        fmodEvents.Add(shipAccuracyModuleInst);
        fmodEvents.Add(enemyAttackModuleInst);
        fmodEvents.Add(enemyDefenseModuleInst);
        fmodEvents.Add(enemyEvasionModuleInst);
        fmodEvents.Add(enemyAccuracyModuleInst);


        testParams.Add("shipstate", 1);
        testParams.Add("pitch", 440);
        testParams.Add("source", 3);
        testParams.Add("arp", 0);
        testParams.Add("arpstart", 1);
        testParams.Add("thruster", 1);
        testParams.Add("ringmod", 1);

        for (int i = 0; i < fmodEvents.Count; i++)
        {
            fmodEvents[i] = FMODUnity.RuntimeManager.CreateInstance(moduleRef);
            fmodEvents[i].start();


            if (i == 0)
            {
                testParams["arp"] = 1;
                testParams["pitch"] = 261.63f;
                testParams["source"] = 3;
                //shipAttackDropdown.GetComponent<Dropdown>().value = 2;
            }
            else if (i == 4)
            {
                testParams["arp"] = 1;
                testParams["pitch"] = 392.0f;
                testParams["source"] = 2;
                //enemyAttackDropdown.GetComponent<Dropdown>().value = 1;
            }
            else
            {
                testParams["arp"] = 0;
            }

            if (i == 2)
            {
                testParams["thruster"] = 1;
                testParams["pitch"] = 329.63f;
                testParams["source"] = 4;
                //shipEvasionDropdown.GetComponent<Dropdown>().value = 3;
            }
            else if (i == 6)
            {
                testParams["thruster"] = 1;
                testParams["pitch"] = 196.0f;
                testParams["source"] = 3;
                //enemyEvasionDropdown.GetComponent<Dropdown>().value = 2;
            }
            else
            {
                testParams["thruster"] = 0;
            }

            if (i == 3)
            {
                testParams["ringmod"] = 1;
                testParams["pitch"] = 659.26f;
                testParams["source"] = 2;
                //shipAccuracyDropdown.GetComponent<Dropdown>().value = 1;
            }
            else if (i == 7)
            {
                testParams["ringmod"] = 1;
                testParams["pitch"] = 523.75f;
                testParams["source"] = 4;
                //enemyAccuracyDropdown.GetComponent<Dropdown>().value = 3;
            }
            else
            {
                testParams["ringmod"] = 0;
            }

            if (i == 1)
            {
                testParams["pitch"] = 783.99f;
                testParams["source"] = 3;
                //shipDefenseDropdown.GetComponent<Dropdown>().value = 2;
            }
            else if (i == 4)
            {
                testParams["pitch"] = 1046.5f;
                testParams["source"] = 2;
                //enemyDefenseDropdown.GetComponent<Dropdown>().value = 1;
            }

            SetShipParams(i, testParams);
        }


        

    }
    // Update is called once per frame
    void Update()
    {

    }

    public void SetShipParams(int instanceIndex, Dictionary<string, float> parameters)
    {
        if (!fmodEvents[instanceIndex].isValid()) return;

        fmodEvents[instanceIndex].setParameterByName("shipstate", parameters["shipstate"]);
        fmodEvents[instanceIndex].setParameterByName("arpstart", parameters["arpstart"]);
        fmodEvents[instanceIndex].setParameterByName("pitch", parameters["pitch"]);
        fmodEvents[instanceIndex].setParameterByName("source", parameters["source"]);
        fmodEvents[instanceIndex].setParameterByName("arp", parameters["arp"]);
        fmodEvents[instanceIndex].setParameterByName("thruster", parameters["thruster"]);
        fmodEvents[instanceIndex].setParameterByName("ringmod", parameters["ringmod"]);

    }

    public void ChangePitch()
    {
        var currentSlider = EventSystem.current.currentSelectedGameObject;
        if (currentSlider.CompareTag("ShipAttack"))
        {
            fmodEvents[0].setParameterByName("pitch", currentSlider.GetComponent<Slider>().value);
        }
        if (currentSlider.CompareTag("ShipDefense"))
        {
            fmodEvents[1].setParameterByName("pitch", currentSlider.GetComponent<Slider>().value);
        }
        if (currentSlider.CompareTag("ShipEvasion"))
        {
            fmodEvents[2].setParameterByName("pitch", currentSlider.GetComponent<Slider>().value);
        }
        if (currentSlider.CompareTag("ShipAccuracy"))
        {
            fmodEvents[3].setParameterByName("pitch", currentSlider.GetComponent<Slider>().value);
        }
        if (currentSlider.CompareTag("EnemyAttack"))
        {
            fmodEvents[4].setParameterByName("pitch", currentSlider.GetComponent<Slider>().value);
        }
        if (currentSlider.CompareTag("EnemyDefense"))
        {
            fmodEvents[5].setParameterByName("pitch", currentSlider.GetComponent<Slider>().value);
        }
        if (currentSlider.CompareTag("EnemyEvasion"))
        {
            fmodEvents[6].setParameterByName("pitch", currentSlider.GetComponent <Slider>().value);
        }
        if (currentSlider.CompareTag("EnemyAccuracy"))
        {
            fmodEvents[7].setParameterByName("pitch", currentSlider.GetComponent<Slider>().value);
        }
    }

    public void ChangeSource()
    {
        var currentSlider = EventSystem.current.currentSelectedGameObject;
        //UnityEngine.Debug.Log(currentDropdown.GetComponent<TMP_Dropdown>().value);

        if (currentSlider.CompareTag("ShipAttack"))
        {
            fmodEvents[0].setParameterByName("source", currentSlider.GetComponent<Slider>().value + 1);
        }
        if (currentSlider.CompareTag("ShipDefense"))
        {
            fmodEvents[1].setParameterByName("source", currentSlider.GetComponent<Slider>().value + 1);
        }
        if (currentSlider.CompareTag("ShipEvasion"))
        {
            fmodEvents[2].setParameterByName("source", currentSlider.GetComponent<Slider>().value + 1);
        }
        if (currentSlider.CompareTag("ShipAccuracy"))
        {
            fmodEvents[3].setParameterByName("source", currentSlider.GetComponent<Slider  >().value + 1);
        }
        if (currentSlider.CompareTag("EnemyAttack"))
        {
            fmodEvents[4].setParameterByName("source", currentSlider.GetComponent<Slider>().value + 1);
        }
        if (currentSlider.CompareTag("EnemyDefense"))
        {
            fmodEvents[5].setParameterByName("source", currentSlider.GetComponent<Slider>().value + 1);
        }
        if (currentSlider.CompareTag("EnemyEvasion"))
        {
            fmodEvents[6].setParameterByName("source", currentSlider.GetComponent<Slider>().value + 1);
        }
        if (currentSlider.CompareTag("EnemyAccuracy"))
        {
            fmodEvents[7].setParameterByName("source", currentSlider.GetComponent<Slider>().value + 1);
        }
    }
}
