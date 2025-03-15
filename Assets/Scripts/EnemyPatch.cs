using System.Collections.Generic;
using UnityEngine;

public class EnemyPatch : MonoBehaviour
{
    public List<EnemyWeapon> enemyWeapons = new List<EnemyWeapon>();
    public List<EnemyShield> enemyShields = new List<EnemyShield>();


    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        for (int i = 0; i < enemyWeapons.Count; i++)
        {
            SetEnemyParams(i);
        }
        //need to figure out when combat over thing 
        //then add a new weapon and shield and move to that int, set its values
        //
    }

    // Update is called once per frame
    void Update()
    {

    }

    public void SetEnemyParams(int i)
    {
        foreach (var enemyWeapon in enemyWeapons)
        {
            enemyWeapons[i] = enemyWeapon;

            //dict w values for weapon, for shield, and for their respective stats 
            var enemyWeaponParamDict = new Dictionary<string, float>
            {
            { "shipstate", 0 },
            //source params
            { "pitch", enemyWeapon.pitch },//changes
            { "source", enemyWeapon.source },//changes
            { "wiresplitter", 0 },
            //AM params
            { "AM", enemyWeapon.AM },//whole section could change
            { "AMsource", enemyWeapon.AMSource },
            { "AMfreq", enemyWeapon.AMFreq },
            { "AMdepth", enemyWeapon.AMDepth },
            //FM params
            { "FM", enemyWeapon.FM },//whole section could change
            { "FMsource", enemyWeapon.FMSource },
            { "FMfreq", enemyWeapon.FMFreq },
            { "FMdepth", enemyWeapon.FMDepth },
            //AM2 params
            { "AM2", 0 },
            { "AM2source", 1 },
            { "AM2freq", 1 },
            { "AM2depth", 1 },
            //FM2 params
            { "FM2", 0 },
            { "FM2source", 1 },
            { "FM2freq", 1 },
            { "FM2depth", 100 },
            //AM on FM params 
            { "FMAM", 0 },
            { "FMAMsource", 1 },
            { "FMAMfreq", 1 },
            { "FMAMdepth", 1 },
            //FM on AM params
            { "AMFM", 0 },
            { "AMFMsource", 1 },
            { "AMFMfreq", 1 },
            { "AMFMdepth", 100 },

            //arp params 
            { "arpstart", 1 },
            { "arp", 1 },
            //arp rhythm params
            { "metro", enemyWeapon.metro }, //whole section could change
            { "note1", enemyWeapon.note1 },
            { "note2", enemyWeapon.note2 },
            { "note3", enemyWeapon.note3 },
            { "note4", enemyWeapon.note4 },
            //arp adsr params
            { "attack", enemyWeapon.attack }, //whole section could change
            { "decay", enemyWeapon.decay },
            { "sustain", enemyWeapon.sustain },
            { "release", enemyWeapon.release },
            //arp pitch params
            { "apitch1", enemyWeapon.apitch1 },//whole section changes
            { "apitch2", enemyWeapon.apitch2 },
            { "apitch3", enemyWeapon.apitch3 },
            { "apitch4", enemyWeapon.apitch4 }

            };
            var enemyWeaponStatDict = new Dictionary<string, float>
        {
            { "", 0 },
            { "extraHealth", 0 },
            { "incomingDamageMult", 1 },
            { "damage", enemyWeapon.damage },
            { "attackSpeed", enemyWeapon.attackSpeed },
            { "accuracy", enemyWeapon.accuracy },
            { "evasion", 0 },
            { "izki", enemyWeapon.izki },
            { "aubo", enemyWeapon.aubo },
            { "dwth", enemyWeapon.dwth }
        };
            enemyWeapon.enemyWeaponInst = FMODUnity.RuntimeManager.CreateInstance(enemyWeapon.moduleRef);
            AudioManager.Instance.SetEnemyParametersByDict();
        }

        foreach (var enemyShield in enemyShields)
        {
            var enemyShieldParamDict = new Dictionary<string, float>
            {
            { "shipstate", 0 },
            //source params
            { "pitch", enemyShield.pitch },//changes
            { "source", enemyShield.source },//changes
            { "wiresplitter", 0 },
            //AM params
            { "AM", enemyShield.AM },//whole section could change
            { "AMsource", enemyShield.AMSource },
            { "AMfreq", enemyShield.AMFreq },
            { "AMdepth", enemyShield.AMDepth },
            //FM params
            { "FM", enemyShield.FM },//whole section could change
            { "FMsource", enemyShield.FMSource },
            { "FMfreq", enemyShield.FMFreq },
            { "FMdepth", enemyShield.FMDepth },
            //AM2 params
            { "AM2", 0 },
            { "AM2source", 1 },
            { "AM2freq", 1 },
            { "AM2depth", 1 },
            //FM2 params
            { "FM2", 0 },
            { "FM2source", 1 },
            { "FM2freq", 1 },
            { "FM2depth", 100 },
            //AM on FM params 
            { "FMAM", 0 },
            { "FMAMsource", 1 },
            { "FMAMfreq", 1 },
            { "FMAMdepth", 1 },
            //FM on AM params
            { "AMFM", 0 },
            { "AMFMsource", 1 },
            { "AMFMfreq", 1 },
            { "AMFMdepth", 100 },

            //arp params 
            { "arpstart", 1 },
            { "arp", 1 },
            //arp rhythm params
            { "metro", 500 },
            { "note1", 1 },
            { "note2", 1 },
            { "note3", 1 },
            { "note4", 1 },
            //arp adsr params
            { "attack", 100 },
            { "decay", 70 },
            { "sustain", 0 },
            { "release", 1000 },
            //arp pitch params
            { "apitch1", 440 },
            { "apitch2", 554.37f },
            { "apitch3", 659.26f },
            { "apitch4", 880 }

            };
            var enemyShieldStatDict = new Dictionary<string, float>
        {
            { "", 0 },
            { "extraHealth", enemyShield.extraHealth },
            { "incomingDamageMult", enemyShield.incomingDamageMult },
            { "damage", 0 },
            { "attackSpeed", 1 },
            { "accuracy", 0 },
            { "evasion", enemyShield.evasion },
            { "izki", enemyShield.izki },
            { "aubo", enemyShield.aubo },
            { "dwth", enemyShield.dwth }
        };
            AudioManager.Instance.SetParametersByDict(i, enemyShieldParamDict);
        }
    }
}
