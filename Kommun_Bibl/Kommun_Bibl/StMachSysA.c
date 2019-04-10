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

/****************************************
 * The transitions array then defines all possible transitions and the
 * functions that get called for those transitions (including the catch-all last one):
 * What that means is: if you're in the ST_INIT state and you receive the EV_KEYPRESS event, make a call to GotKey.
 */

 /*Alle mögliche Übergaenge und dazugehörige Funktionen*/
 /*Man befindet sich in der ST Zustand und wenn ein EV (trigger) empfangen wird, wird die &fct aufgerufen*/
 /*chademo Dokument. Figure A.13—Charging control flow*/
tTransition trans[] = {
                        /*Keine Zustandsänderungen*/
                        { ST_INIT,                 EV_CHECK_PASSED , &noChange },

                        { ST_CHARGE_START__BUTTON, EV_CHECK_PASSED , &noChange },
                        { ST_TRANS_CHARGE_STR_SIG, EV_CHECK_PASSED , &noChange },
                        { ST_REC_TRA_INI_CAN_DATA, EV_CHECK_PASSED , &noChange },
                        { ST_PROC_INF_CHARGE_CONT, EV_CHECK_PASSED , &noChange },
                        { ST_LOCK_CHARGING_CONNEC, EV_CHECK_PASSED , &noChange },
                        { ST_CHECK_EV_CONT_OPENED, EV_CHECK_PASSED , &noChange },
                        { ST_INSU_TEST_OUT_DC_CIR, EV_CHECK_PASSED , &noChange },
                        { ST_CHECK_TERM_INSU_TEST, EV_CHECK_PASSED , &noChange },
                        { ST_TRANS_SIG_CHARGE_COM, EV_CHECK_PASSED , &noChange },
                        { ST_START_CHARGIN_OUTPUT, EV_CHECK_PASSED | EV_START_CHARGING_I_REQ , &noChange },
                        { ST_STOP________CHARGING, EV_CHECK_PASSED , &noChange },
                        { ST_CHECK_DC_V_LESS_10_V, EV_CHECK_PASSED , &noChange },
                        { ST_UNLOCK_CHARGING_CONN, EV_CHECK_PASSED , &noChange },
                        { ST_TERMINATE_CAN_COMMUN, EV_CHECK_PASSED , &noChange },

                        { ST_ANY,                  EV_CHECK_PASSED , &noChange },  // Dies wird fuer alle Uebergaenge aufgerufen

                        /*Zustandsänderungen nach EVents*/
                        { ST_INIT,   EV_INITIALISAT_COMPLETE, &chargeStartButt },   // Termination der Initialisation.

                        { ST_CHARGE_START__BUTTON, EV_CHARGE_START_BUTT_ON, &transChargeStartSig   }, // Warten bis BUTTON ist an. Keine Zusätzliche Funktion erforderlich. Irgendwo wird Event gesetzt.
                        { ST_TRANS_CHARGE_STR_SIG, EV_TRA_CHAR_STR_SIG_COM, &recTraInitCANData     }, // Es soll START Signal einmal gesendet werden. trmChrgStrSig()
                        { ST_REC_TRA_INI_CAN_DATA, EV_START_CAN_COMMUNICAT, &procInfoForChargeCont }, // Warten auf Antwort von Fahrzeug. Irgendwo wird Event gesetzt.
                        { ST_PROC_INF_CHARGE_CONT, EV_PROC_INF_CHARGE_CONT, &lockChargingConnec    }, // Informationaustauch in beiden Richtungen. prcssInfChrgCnt().Event setzet
                        { ST_LOCK_CHARGING_CONNEC, EV_TRAN_SIG_VIH_SET_COM, &checkEVContOpened     }, //
                        { ST_CHECK_EV_CONT_OPENED, EV_EV_CONT_IS_OPEN_COMP, &insulTestOnOutCirc    },
                        { ST_INSU_TEST_OUT_DC_CIR, EV_INSU_OUT_DC_CIR_COMP, &checkTeminInsulTest   },
                        { ST_CHECK_TERM_INSU_TEST, EV_V_OUT_TERM_LESS_20_V, &transSigOfChargiComp  },
                        { ST_TRANS_SIG_CHARGE_COM, EV_TRA_SIG_CHAR_COM_COM, &startChargingOut      },
                        //{ ST_START_CHARGIN_OUTPUT, EV_START_CHARGING_I_REQ, &noChange },
                        { ST_START_CHARGIN_OUTPUT, EV_TRAN_CHARGIN_STOP_RQ, &stopCharging          },

                        { ST_STOP________CHARGING, EV_STOP____CHARGING_COM, &checkDCVoltLess10V },

                        { ST_CHECK_DC_V_LESS_10_V, EV_DC_VOL_LESS_10_V_COM , &unlockChargingConnec },
                        { ST_UNLOCK_CHARGING_CONN, EV_UNLOCK_CHAR_CONN_COM , &termCANCommun },
                        //{ ST_TERMINATE_CAN_COMMUN,                          },
                        //{                           },
                        //{                           }

                        /*ERROR Zustände */
                        /*{                           },
                        {                           },
                        {                           },
                        {                           },
                        {                           }*/

                        { ST_ANY, EV_ANY, &error }
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
 * as a parameter. Then the state functions can either use the data or ignore them. – ldog
 */

