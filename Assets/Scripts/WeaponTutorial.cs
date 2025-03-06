using FMOD.Studio;
using FMODUnity;
using UnityEngine;

public class WeaponTutorial : MonoBehaviour
{
    public EventReference moduleRef;
    public EventInstance moduleInst;

    public float source;
    public float arp;
    public float apitch1;
    public float apitch2;
    public float apitch3;
    public float apitch4;
    public float attack;
    public float decay;
    public float sustain;
    public float release;
    public float note1;
    public float note2;
    public float note3;
    public float note4;
    public float metro;

    public bool isPlaying;

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        moduleInst = FMODUnity.RuntimeManager.CreateInstance(moduleRef);
    }

    // Update is called once per frame
    void Update()
    {

        moduleInst.setParameterByName("source", source);
        moduleInst.setParameterByName("arpstart", 1);
        moduleInst.setParameterByName("arp", arp);
        moduleInst.setParameterByName("apitch1", apitch1);
        moduleInst.setParameterByName("apitch2", apitch2);
        moduleInst.setParameterByName("apitch3", apitch3);
        moduleInst.setParameterByName("apitch4", apitch4);
        moduleInst.setParameterByName("attack", attack);
        moduleInst.setParameterByName("decay", decay);
        moduleInst.setParameterByName("sustain", sustain);
        moduleInst.setParameterByName("release", release);
        moduleInst.setParameterByName("note1", note1);
        moduleInst.setParameterByName("note2", note2);
        moduleInst.setParameterByName("note3", note3);
        moduleInst.setParameterByName("note4", note4);
        moduleInst.setParameterByName("metro", metro);


        if (gameObject.activeSelf)
        {
            if (!isPlaying)
            {
                Debug.Log("Starting event");
                moduleInst.start();
                isPlaying = true;
            }
        }

    }
}
