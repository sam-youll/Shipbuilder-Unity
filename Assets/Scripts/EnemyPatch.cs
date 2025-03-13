using System.Collections.Generic;
using UnityEngine;

public class EnemyPatch : MonoBehaviour
{
    public List<GameObject> enemyWeapons = new List<GameObject>();
    public List<GameObject> enemyShields = new List<GameObject>();


    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        for (int i = 0; i < enemyWeapons.Count; i++)
        {
            SetEnemyDefaults(i);
        }
        //need to figure out when combat over thing 
        //then add a new weapon and shield and move to that int, set its values
        //
    }

    // Update is called once per frame
    void Update()
    {

    }

    public void SetEnemyDefaults(int i)
    {
        foreach (var enemyWeapon in enemyWeapons)
        {
            enemyWeapons[i] = enemyWeapon;

            //dict w values for weapon, for shield, and for their respective stats 
            var enemyWeaponParamDict = new Dictionary<string, float>
            {
            { "shipstate", 0 },
            //source params
            { "pitch", 440},//changes
            { "source", 2 },//changes
            { "wiresplitter", 0 },
            //AM params
            { "AM", 0 },//whole section could change
            { "AMsource", 1 },
            { "AMfreq", 1 },
            { "AMdepth", 1 },
            //FM params
            { "FM", 0 },//whole section could change
            { "FMsource", 1 },
            { "FMfreq", 1 },
            { "FMdepth", 100 },
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
            { "metro", 500 }, //whole section could change
            { "note1", 1 }, 
            { "note2", 1 },
            { "note3", 1 },
            { "note4", 1 },
            //arp adsr params
            { "attack", 100 }, //whole section could change
            { "decay", 70 },
            { "sustain", 0 },
            { "release", 1000 },
            //arp pitch params
            { "apitch1", 440 },//whole section changes
            { "apitch2", 554.37f },
            { "apitch3", 659.26f },
            { "apitch4", 880 }

            };
            var enemyWeaponStatDict = new Dictionary<string, float>
        {
            { "", 0 },
            { "extraHealth", 0 },
            { "incomingDamageMult", 1 },
            { "damage", 0 },
            { "attackSpeed", 1 },
            { "accuracy", 0 },
            { "evasion", 0 },
            { "izki", 0 },
            { "aubo", 0 },
            { "dwth", 0 }
        };

            AudioManager.Instance.SetParametersByDict(i, enemyWeaponParamDict);
        }

        foreach (var enemyShield in enemyShields)
        {
            var enemyShieldParamDict = new Dictionary<string, float>
            {
            { "shipstate", 0 },
            //source params
            { "pitch", 440 },//changes
            { "source", 2 },//changes
            { "wiresplitter", 0 },
            //AM params
            { "AM", 0 },//whole section could change
            { "AMsource", 1 },
            { "AMfreq", 1 },
            { "AMdepth", 1 },
            //FM params
            { "FM", 0 },//whole section could change
            { "FMsource", 1 },
            { "FMfreq", 1 },
            { "FMdepth", 100 },
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
            { "extraHealth", 0 },
            { "incomingDamageMult", 1 },
            { "damage", 0 },
            { "attackSpeed", 1 },
            { "accuracy", 0 },
            { "evasion", 0 },
            { "izki", 0 },
            { "aubo", 0 },
            { "dwth", 0 }
        };
            AudioManager.Instance.SetParametersByDict(i, enemyShieldParamDict);
        }
    }
}
