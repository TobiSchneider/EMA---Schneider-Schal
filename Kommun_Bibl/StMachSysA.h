#ifndef STMACHSYSA_H_INCLUDED
#define STMACHSYSA_H_INCLUDED

//---------------------------------------------------------------------------
// State Machine:
// Define your states and events with simple defines
// (the ANY ones are special markers, see below):
// States:
#define ST_INIT                     0
#define ST_TERM                     -99

    // Running states
/*#define ST_RUN_STARTUP              1
#define ST_RUN_CC_CONTROL           2
#define ST_RUN_CC_CONTROL_BURST     3
#define ST_RUN_CV_CONTROL           4
#define ST_RUN_CV_CONTROL_BURST     5
#define ST_IDLE                     6
*/


void HandleState(int event) ;

/*ZUSTAENDE*/
/*chademo Dokument*/
/*Figure A.13—Charging control flow*/

/*Ladesäule Initialisation states*/
#define ST_CHARGE_START__BUTTON 1  // "Charge start button" ON
#define ST_TRANS_CHARGE_STR_SIG 2  // Transmit charge start signal
#define ST_REC_TRA_INI_CAN_DATA 3  // Receive initial vehicle CAN data and transmit charger CAN data in return
#define ST_PROC_INF_CHARGE_CONT 4  // Process the information for charge control before charging (Battery compatibility, charging time calculation etc.)
#define ST_LOCK_CHARGING_CONNEC 5  // Lock charging connector

/*Falls alles ok ist, fängt die Ladesäule anzuladen.*/
#define ST_CHECK_EV_CONT_OPENED 6  // Check that EV contactors are surely opened (Voltage on output terminals is less than 10V.)
#define ST_INSU_TEST_OUT_DC_CIR 7  // Insulation test on output DC circuit
#define ST_CHECK_TERM_INSU_TEST 8  // Check the termination of insulation test (Voltage on output terminals is less than 20V.)
#define ST_TRANS_SIG_CHARGE_COM 9  // Transmit the signal of charger setup completion
#define ST_START_CHARGIN_OUTPUT 10 // Start charging current output

/*Ende des Ladeprozesses */
#define ST_STOP________CHARGING 11 // Stop charging
#define ST_CHECK_DC_V_LESS_10_V 12 // Check that DC voltage is less than 10V
#define ST_UNLOCK_CHARGING_CONN 13 // Unlock charging connector
#define ST_TERMINATE_CAN_COMMUN 14 // Terminate CAN communication

/*Terminationsprozess*/
#define ST__TERMINATIONSPROZESS 15

/*EVENTS*/
/*events von chademo Dokument*/
#define EV_INITIALISAT_COMPLETE 5000    // Initialisation is completed
#define EV_CHARGE_START_BUTT_ON 5001    // "Charge start button" ON
#define EV_START_CAN_COMMUNICAT 5003    // Start CAN communication
#define EV_PROC_INF_CHARGE_CONT 5004    // Process the information for charge control before charging (On-board battery information, maximum charging time etc.)
#define EV_TRAN_SIG_VIH_SET_COM 5005    // Transmit the signal of vehicle setup completion. opto-coupler(j):ON switch(k):ON
#define EV_START_CHARGING_I_REQ 5005    // Start charging current request
#define EV_TRAN_CHARGIN_STOP_RQ 5010    // Transmit charging stop request. opto-coupler(j):OFF switch(k):OFF
#define EV_TRA_CHAR_STR_SIG_COM 5002    // charge start signal complet
#define EV_EV_CONT_IS_OPEN_COMP 5006    // Check that EV contactors are surely opened (Voltage on output terminals is less than 10V.)
#define EV_INSU_OUT_DC_CIR_COMP 5007    // Insulation test on output DC circuit
#define EV_V_OUT_TERM_LESS_20_V 5008    // Check the termination of insulation test (Voltage on output terminals is less than 20V.)
#define EV_TRA_SIG_CHAR_COM_COM 5009    // Transmit the signal of charger setup completion complet
#define EV_DC_VOL_LESS_10_V_COM 5012    // Check that DC voltage is less than 10V
#define EV_UNLOCK_CHAR_CONN_COM 5013    // Unlock charging connector. "Charging connector lock" flag to 0
#define EV_STOP____CHARGING_COM 5011    // Stop charging Propzess complete

/*Events for Terminationsprozess*/
#define EV_CHRG_RAT_REACH_LEVEL 5012    // Vehicle: Charged rate of on-board battery has reached a specified level.
#define EV_VEHI_CHRG_MALFKT_DET 5013    // Vehicle: Vehicle malfunction detected Charger malfunction detected
#define EV_CHRG_STP_BUTT_TIM_RE 5014    // Charger: “Charge stop button has been pushed.” Or “Charging time has reached a specified value.”
#define EV_CHRG_VEHI_MALFKT_DET 5015    // Charger: Charger malfunction detected Vehicle malfunction detected
#define EV_VIHIC_TIME_OUT_PROCE 5016    //
#define EV_CHARG_TIME_OUT_PROCE 5017    //

/**/
/*#define FRZG_NICHT_VERB 0
#define FRZG_VERB       1

#define FRZG_SCHUTZ_OFFEN   0
#define FRZG_SCHUTZ_GESCHL  1

#define LADE_MOEGL          1
#define LADE_NICHT_MOEGL    0*/

    // Error states
#define ST_ERROR_OVERVOLTAGE        7
#define ST_ERROR_UNDERVOLTAGE       8
#define ST_ERROR_OVERCURRENT        9
#define ST_ERROR_UNDERCURRENT       10
#define ST_ERROR_OVERTEMPERATURE    11
#define ST_ERROR_UNDEFINED          -2
#define ST_ERROR_HOST_COMMUNICATION -3
    // Wild card state
#define ST_ANY                      -1

// Events:
/*#define EV_EV_OVERVOLTAGE           5001
#define EV_EV_UNDERVOLTAGE          5002
#define EV_EV_OVERCURRENT           5003*/
#define EV_CHECK_PASSED             5004

/*#define EV_GRID_OVERVOLTAGE         5005
#define EV_GRID_UNDERVOLTAGE        5006
#define EV_GRID_OVERCURRENT         5007

#define EV_INVALID_DIRECTION        5009
#define EV_STARTUP_COMPLETE         5010
#define EV_INIT_COMPLETE            5011
#define EV_WATCHDOG_EXPIRED         5012

#define EV_SU_S                     5000
#define EV_MOUSEMOVE                5001*/
#define EV_ANY                      5999

/**/
/*#define EV_FRZG_NICHT_VERB          6001
#define EV_KUPPL_ANGESCHL           6002
#define EV_AKTIV_DCC_VCC            6003
#define EV_INIT_DAT_UEBERT          6004
#define EV_KOMM HERG                6005
#define EV_KUPPL_VERRIG             6006
#define EV_ISOL PRUEF_LEIT          6007
#define EV_VORLADUNG                6008
#define EV_FRZG_SCHUETZE_GESCHL     6009
#define EV_LADE_NACH_I_BEDARF       6010
#define EV_LADE_NACH_U_BEDARF       6011
#define EV_I_REDUKT                 6012
#define EV_NEUBEWERT_PARAM_GRENZ    6013
#define EV_NULL_I_BESTAET           6014
#define EV_ERKENN_VERSCH_SCHUETZ    6015
#define EV_FRZG_SCHUETZE_OFFEN      6016
#define EV_UEBERPR_U_DC_LEIT        6017
#define EV_KUPPL_ENTRIEG            6018
#define EV_ENDE_LADE_KOMM_EBENE     6019
#define EV_KUPPL_HERAUSGEZ          6020*/

/*chademo*/


#endif // STMACHSYSA_H_INCLUDED
