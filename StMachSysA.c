#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "main.h"
#include "Bibl.h"
#include "testHeader.h"
#include "SysAParam.h"
#include "StMachSysA.h"


int stateSt = 0;
/********************************
 * State machines that I've designed before (C, not C++) have all come down to a
 *  struct array and a loop. The structure basically consists of a state and event
 *  (for look-up) and a function that returns the new state, something like:
 */
typedef struct {
    int st;             // Zustand
    int ev;             // Trigger
    int Wartezeit;      // Wartezeit
    int (*fn)(void);    // Diese Funktion liefert neue, naechste Zustand
} tTransition;

/***************************************
 * Then you define all the functions that are called by the transitions:
 *
 * All these function are written to take no variables and return the new
 * state for the state machine. In this example global variables are used
 * for passing any information into the state functions where necessary.
 */
 /*Diese Funktionen werden während Zustandsaenderungen aufgerufen*/
//static int startUp (void) { return ST_RUN_STARTUP; }
static int error (void) { return ST_ANY; }

/*Fehlerzustände*/
/*vehicle*/
static int errBattOverV (void) { return ST_ERR_BATTERY_OVERVOLT ; } // Battery overvoltage
static int errBattUnderV (void) { return ST_ERR_BATTER_UNDERVOLT ; } // Battery undervoltage
static int errBattDeviatI (void) { return ST_ERR_BATT_CURR_DEVIAT ; } // Battery current deviation error
static int errBattHighTemp (void) { return ST_ERR_HIGH_BATTER_TEMP ; } // High battery temperature
static int errBattDiffV (void) { return ST_ERR_BATT_VOLT_DIFFER ; } // Battery voltage differentia error
static int errChargSysFault (void) { return ST_ERR_CHARG_SYST_FAULT ; } // Charging system fault
static int errVehicleShiftPos (void) { return ST_ERR_VIHIC_SHIFT_POSI ; } // Vehicle shift position

/*charger*/
static int errChargerMalFct (void) { return ST_ERR_CHARGER_MALFUNCT ; } // Charger malfunction
static int errChargingSysMalFct (void) { return ST_ERR_CHARGING_MALFUNC ; } // Charging system malfunction
static int errBattIncompat (void) { return ST_ERR_BATTERY_INCOMPAT ; } // Battery incompatibility

//static int CVC (void) { return ST_RUN_CV_CONTROL; }
static int noChange (void) { return stateSt; }


/*chademo Dokument */
/*Die Funktionen führen die Zustandsmaschine in den naechsten Zustand ueber*/
static int chargeStartButt( void ) { return ST_CHARGE_START__BUTTON ; }
static int transChargeStartSig( void ) { return ST_TRANS_CHARGE_STR_SIG ; }
static int recTraInitCANData( void ) { return ST_REC_TRA_INI_CAN_DATA ; }
static int procInfoForChargeCont( void ) { return ST_PROC_INF_CHARGE_CONT ; }
static int lockChargingConnec( void ) { return ST_LOCK_CHARGING_CONNEC ; }
static int checkEVContOpened( void ) { return ST_CHECK_EV_CONT_OPENED ; }
static int insulTestOnOutCirc( void ) { return ST_INSU_TEST_OUT_DC_CIR ; }
static int checkTeminInsulTest( void ) { return ST_CHECK_TERM_INSU_TEST ; }
static int transSigOfChargiComp( void ) { return ST_TRANS_SIG_CHARGE_COM ; }
static int startChargingOut( void ) { return ST_START_CHARGIN_OUTPUT ; }
static int stopCharging( void ) { return ST_CHECK_DC_V_LESS_10_V ; }
static int checkDCVoltLess10V( void ) { return EV_EV_CONT_IS_OPEN_COMP ; }
static int unlockChargingConnec( void ) { return ST_UNLOCK_CHARGING_CONN ; }
static int termCANCommun( void ) { return ST_TERMINATE_CAN_COMMUN ; }
static int termProzess( void ) { return ST__TERMINATIONSPROZESS ; }


/****************************************
 * The transitions array then defines all possible transitions and the
 * functions that get called for those transitions (including the catch-all last one):
 * What that means is: if you're in the ST_INIT state and you receive the EV_KEYPRESS event, make a call to GotKey.
 */

 /*Alle mögliche Übergaenge und dazugehörige Funktionen*/
 /*Man befindet sich in der ST Zustand und wenn ein EV (trigger) empfangen wird, wird die &fct aufgerufen*/
 /*chademo Dokument. Figure A.13Charging control flow*/
tTransition trans[] = {
                        /*Keine Zustandsänderungen*/
                        { ST_INIT,                 EV_CHECK_PASSED , 10,  &noChange },

                        { ST_CHARGE_START__BUTTON, EV_CHECK_PASSED , 10, &noChange },
                        { ST_TRANS_CHARGE_STR_SIG, EV_CHECK_PASSED , 10, &noChange },
                        { ST_REC_TRA_INI_CAN_DATA, EV_CHECK_PASSED , 10, &noChange },
                        { ST_PROC_INF_CHARGE_CONT, EV_CHECK_PASSED , 10, &noChange },
                        { ST_LOCK_CHARGING_CONNEC, EV_CHECK_PASSED , 10, &noChange },
                        { ST_CHECK_EV_CONT_OPENED, EV_CHECK_PASSED , 10, &noChange },
                        { ST_INSU_TEST_OUT_DC_CIR, EV_CHECK_PASSED , 10, &noChange },
                        { ST_CHECK_TERM_INSU_TEST, EV_CHECK_PASSED , 10, &noChange },
                        { ST_TRANS_SIG_CHARGE_COM, EV_CHECK_PASSED , 10, &noChange },
                        { ST_START_CHARGIN_OUTPUT, EV_CHECK_PASSED | EV_START_CHARGING_I_REQ , 10, &noChange },
                        { ST_STOP________CHARGING, EV_CHECK_PASSED , 10, &noChange },
                        { ST_CHECK_DC_V_LESS_10_V, EV_CHECK_PASSED , 10, &noChange },
                        { ST_UNLOCK_CHARGING_CONN, EV_CHECK_PASSED , 10, &noChange },
                        { ST_TERMINATE_CAN_COMMUN, EV_CHECK_PASSED , 10, &noChange },

                        { ST_ANY,                  EV_CHECK_PASSED , 10, &noChange },  // Dies wird fuer alle Uebergaenge aufgerufen

                        /*Zustandsänderungen nach EVents*/
                        { ST_INIT,   EV_INITIALISAT_COMPLETE, 10, &chargeStartButt },   // Termination der Initialisation.

                        { ST_CHARGE_START__BUTTON, EV_CHARGE_START_BUTT_ON, 10, &transChargeStartSig   }, // Warten bis BUTTON ist an. Keine Zusätzliche Funktion erforderlich. Irgendwo wird Event gesetzt.
                        { ST_TRANS_CHARGE_STR_SIG, EV_TRA_CHAR_STR_SIG_COM, 10, &recTraInitCANData     }, // Es soll START Signal einmal gesendet werden. trmChrgStrSig()
                        { ST_REC_TRA_INI_CAN_DATA, EV_START_CAN_COMMUNICAT, 10, &procInfoForChargeCont }, // Warten auf Antwort von Fahrzeug. Irgendwo wird Event gesetzt.
                        { ST_PROC_INF_CHARGE_CONT, EV_PROC_INF_CHARGE_CONT, 10, &lockChargingConnec    }, // Informationaustauch in beiden Richtungen. prcssInfChrgCnt().Event setzet
                        { ST_LOCK_CHARGING_CONNEC, EV_TRAN_SIG_VIH_SET_COM, 10, &checkEVContOpened     }, //
                        { ST_CHECK_EV_CONT_OPENED, EV_EV_CONT_IS_OPEN_COMP, 10, &insulTestOnOutCirc    },
                        { ST_INSU_TEST_OUT_DC_CIR, EV_INSU_OUT_DC_CIR_COMP, 10, &checkTeminInsulTest   },
                        { ST_CHECK_TERM_INSU_TEST, EV_V_OUT_TERM_LESS_20_V, 10, &transSigOfChargiComp  },
                        { ST_TRANS_SIG_CHARGE_COM, EV_TRA_SIG_CHAR_COM_COM, 10, &startChargingOut      },
                        //{ ST_START_CHARGIN_OUTPUT, EV_START_CHARGING_I_REQ, &noChange },
                        { ST_START_CHARGIN_OUTPUT, EV_TRAN_CHARGIN_STOP_RQ, 10, &stopCharging          },   // Ladezustand

                        { ST_STOP________CHARGING, EV_STOP____CHARGING_COM, 10, &checkDCVoltLess10V },

                        { ST_CHECK_DC_V_LESS_10_V, EV_DC_VOL_LESS_10_V_COM , 10, &unlockChargingConnec },
                        { ST_UNLOCK_CHARGING_CONN, EV_UNLOCK_CHAR_CONN_COM , 10, &termCANCommun },
                        //{ ST_TERMINATE_CAN_COMMUN,                          },


                        /*Die EVENTS sollten von draussen generiert werden*/

                        /*Falle die zur Termination führen*/
                        { ST_ANY, EV_CHRG_RAT_REACH_LEVEL, 10, &termProzess },
                        { ST_ANY, EV_VEHI_CHRG_MALFKT_DET, 10, &termProzess },
                        { ST_ANY, EV_CHRG_STP_BUTT_TIM_RE, 10, &termProzess },
                        { ST_ANY, EV_CHRG_VEHI_MALFKT_DET, 10, &termProzess },

                        /*Table A.32—CHARGER_MESSAGES*/
/*->*/                       { ST_PROC_INF_CHARGE_CONT, EV_EXCEE_TARG_BATT_VOLT, 10, &termProzess   },
/*->*/                       { ST_PROC_INF_CHARGE_CONT, EV_EXCEE_VEHI_CURR_REQU, 10, &termProzess  },
/*->*/                       { ST_PROC_INF_CHARGE_CONT, EV_CHRG_VOLT_REACH_THRS, 10, &stopCharging },

                        /*Time out Zustände*/
                        { ST_ANY, EV_VIHIC_TIME_OUT_PROCE, 10, &termProzess },
                        { ST_ANY, EV_CHARG_TIME_OUT_PROCE, 10, &termProzess },

                        /*Terminationsprozess*/
                        { ST__TERMINATIONSPROZESS, EV_ANY, 10, &noChange    },
                        //{                           }

                        /*ERROR Zustände */
                        /*source -> vehicle*/
                        { ST_ANY, EV_ERR_BATT_VOLT_UP_LIM, 10, &errBattOverV /*&termProzess */ },
                        { ST_ANY, EV_ERR_BATT_VOLT_DO_LIM, 10, &errBattUnderV /*&termProzess */},
                        { ST_ANY, EV_ERR_OUT_CURRE_DEVIAT, 10, &errBattDeviatI /*&termProzess */},
                        { ST_ANY, EV_ERR_BATT_TEMP_UP_LIM, 10, &errBattHighTemp /*&termProzess */},
                        { ST_ANY, EV_ERR__CHARG_VOLT_DIFF, 10, &errBattDiffV /*&termProzess */},
                        { ST_ANY, EV_ERR_CHARGER_TIME_OUT, 10, &errChargSysFault /*&termProzess */},
                        { ST_ANY, EV_ERR_CHRG_DATA_NO_REC, 10, &errChargSysFault /*&termProzess */},
                        { ST_ANY, EV_ERR_VIH_ANY_OTH_FAUL, 10, &errChargSysFault /*&termProzess */},
                        { ST_ANY, EV_ERR_VEHIC_MOVABLE_ST, 10, &errVehicleShiftPos /*&termProzess */},
                        { ST_ANY, EV_ERR_ANY_FAUL_IN_VEHI, 10, &errChargSysFault /*&termProzess */},

                        /*Jeder Zustand soll noch bearbeitet werden, oder es geht in Terminationsprozess über*/
                        { ST_ERR_BATTERY_OVERVOLT, EV_ANY, 10, &termProzess } ,
                        { ST_ERR_BATTER_UNDERVOLT, EV_ANY, 10, &termProzess } ,
                        { ST_ERR_BATT_CURR_DEVIAT, EV_ANY, 10, &termProzess } ,
                        { ST_ERR_HIGH_BATTER_TEMP, EV_ANY, 10, &termProzess } ,
                        { ST_ERR_BATT_VOLT_DIFFER, EV_ANY, 10, &termProzess } ,
                        { ST_ERR_CHARG_SYST_FAULT, EV_ANY, 10, &termProzess } ,
                        { ST_ERR_VIHIC_SHIFT_POSI, EV_ANY, 10, &termProzess } ,

                        /*source -> charger*/
                        { ST_ANY, EV_ERR_ERROR_IN_CHARGER, 10, &errChargerMalFct/*&termProzess*/ },
                        { ST_ANY, EV_ERR__CHARG_CONN_LOCK, 10, &errChargerMalFct/*&termProzess*/ },
                        { ST_ANY, EV_ERR_MAIN_CIRCUIT_ERR, 10, &errChargingSysMalFct/*&termProzess*/ },
                        { ST_ANY, EV_ERR_EMER_STP_BUTT_ON, 10, &errChargerMalFct/*&termProzess*/ },
                        { ST_ANY, EV_ERR_REQU_VOLT_HIGHER, 10, &errBattIncompat/*&termProzess*/ },
                        { ST_ANY, EV_ERR_VEHICLE_TIME_OUT, 10, &errChargingSysMalFct/*&termProzess*/ },
                        { ST_ANY, EV_ERR_VEHI_DATA_NO_REC, 10, &errChargingSysMalFct/*&termProzess*/ },
                        { ST_ANY, EV_ERR_BATT_VOLT_NO_APP, 10, &errChargingSysMalFct/*&termProzess*/ },
                        { ST_ANY, EV_ERR_CHARGE_VOLT_HIGH, 10, &errChargingSysMalFct/*&termProzess*/ },
                        { ST_ANY, EV_ERR_BATT_VOL_AFT_TER, 10, &errChargingSysMalFct/*&termProzess*/ },
                        { ST_ANY, EV_ERR_DC_HIGH_TRS_VOLT, 10, &errChargingSysMalFct/*&termProzess*/ },
                        { ST_ANY, EV_ERR_CHR_ANY_OTH_FAUL, 10, &errChargingSysMalFct/*&termProzess*/ },
                        { ST_ANY, EV_ERR_DISC_CAN_SEQ_SIG, 10, &errChargingSysMalFct/*&termProzess*/ },

                        { ST_ERR_CHARGER_MALFUNCT, EV_ANY, 10, &termProzess },
                        { ST_ERR_CHARGING_MALFUNC, EV_ANY, 10, &termProzess },
                        { ST_ERR_BATTERY_INCOMPAT, EV_ANY, 10, &termProzess },

                        { ST_ANY, EV_ANY, 10, &error }
} ;

/*tTransition trans[] = {
                       // Bounary Value Check Passed
                       { ST_INIT, EV_CHECK_PASSED , &noChange},
                       { ST_RUN_CC_CONTROL, EV_CHECK_PASSED , &noChange},
                       { ST_RUN_CC_CONTROL_BURST, EV_CHECK_PASSED , &noChange},
                       { ST_RUN_CV_CONTROL, EV_CHECK_PASSED , &noChange},
                       { ST_RUN_CV_CONTROL_BURST, EV_CHECK_PASSED , &noChange},
                       { ST_IDLE, EV_CHECK_PASSED , &noChange},
                       { ST_ERROR_OVERVOLTAGE, EV_CHECK_PASSED , &noChange},
                       { ST_ERROR_UNDERVOLTAGE, EV_CHECK_PASSED , &noChange},
                       { ST_ERROR_OVERCURRENT, EV_CHECK_PASSED , &noChange},
                       { ST_ERROR_UNDERCURRENT, EV_CHECK_PASSED , &noChange},
                       { ST_ERROR_OVERTEMPERATURE, EV_CHECK_PASSED , &noChange},
                       { ST_ERROR_UNDEFINED, EV_CHECK_PASSED , &noChange},
                       { ST_ERROR_HOST_COMMUNICATION, EV_CHECK_PASSED , &noChange},
                       { ST_ANY, EV_CHECK_PASSED , &noChange},  // Dies wird fuer alle Uebergaenge aufgerufen
                       // Bounary Value Check Failed
                       // EV over current
                       // EV over voltage
                       // Grid
                       { ST_INIT, EV_INIT_COMPLETE, &startUp},
                       { ST_RUN_STARTUP, EV_STARTUP_COMPLETE, &CVC},
                       { ST_ANY, EV_ANY, &error}    // Wenn Zustandsmaschiene falsch aufgebaut wurde  und eine undefinierte Übergang vorkommt
};*/
#define TRANS_COUNT (sizeof(trans)/sizeof(*trans))

/**************************************
 * The workings of the FSM then become a relatively simple loop:
 *
 * As alluded to above, note the use of ST_ANY as wild-cards,
 * allowing an event to call a function no matter the current state.
 * EV_ANY also works similarly, allowing any event at a specific
 * state to call a function.
 *
 * It can also guarantee that, if you reach the end of the transitions
 * array, you get an error stating your FSM hasn't been built correctly
 * (by using the ST_ANY/EV_ANY combination.
 */

 /*EVENT wysivaet funkciyu ne sawisemo ot STATE
 *STATE wysivaet funkciyu ne sawisemo ot EVENT
 */
void HandleState(int event){
    int i= 0;
    for (i = 0; i < TRANS_COUNT; i++) {
        if ((stateSt == trans[i].st) || (ST_ANY == trans[i].st)) {
            if ((event == trans[i].ev) || (EV_ANY == trans[i].ev)) {
                stateSt = (trans[i].fn)();
                break;
            }
        }
    }

    /*Aktionsfunktion -> bedingte EVENT*/
    /*Esche posmotret' . tak kak ne vsegda dolzhni wisywatsya EVENTS-> ili doch wsegda ??*/
    stateAtcionFct( getState() ) ;

}

int getState(void){ return stateSt; }

void InitStateMachine(void){    //Anfangszustand
    stateSt = ST_INIT;
}

/*****************************************************
 * And, as ldog states in a comment, you can avoid the globals altogether by passing a structure pointer to all
 * functions (and using that in the event loop). This will allow multiple state machines to run side-by-side
 * without interference.
 *
 * Just create a structure type which holds the machine-specific data (state at a bare minimum) and use that instead
 * of the globals.
 *
 * You mentioned that you share data by using globals, but it would probably be cleaner if you define the state
 * functions to be int (*fn)(void*); where void* is the pointer to the data that each state function takes in
 * as a parameter. Then the state functions can either use the data or ignore them.  ldog
 */

