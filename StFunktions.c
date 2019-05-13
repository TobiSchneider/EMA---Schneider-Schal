#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "main.h"
#include "Bibl.h"
#include "testHeader.h"
#include "SysAParam.h"
#include "StMachSysA.h"
#include "StFunktions.h"
#include "Dealay_interrupt_24Bit_tim.h"

/*Globale Variablen*/
int EVBuff = 0x0000 ;

/*Erfördeliche Größen*/
uint8_t *ptrIDHundAcht, *ptrIDHundNeun, *ptrIDHundZwei, *ptrIDHund, *ptrIDHundEins ;
uint16_t targetBattVoltVehic = 0x0000, maxOutputVoltCharger = 0x0000 ;
uint8_t chargeCurrRequestVehic = 0x0000, maxOutputCurrentCharger = 0x0000 ;
uint16_t maxOutputVoltVehic = 0x0000 ;
uint16_t outVoltCharger = 0x0000 ;
uint8_t outCurrCharger = 0x0000 ;
uint16_t thresVoltCharger = 0x0000 ;
uint16_t maxBattVoltVehic = 0x0000 ;
uint8_t maxChargTimeS = 0x0000, maxChargTimeM = 0x0000 ;       // from vehicle. Maximum charging time (by 10 seconds). Maximum charging time (by 1 minute).
uint8_t remainChargTimeS = 0x0000, remainChargTimeM = 0x0000 ; // from charger. Remaining charge time (by 10 seconds). Remaining charge time (by 1 minute).

 /*   ptrIDHund     = getHundertID() ;
    ptrIDHundEins = getHundertEinstID() ;
    ptrIDHundZwei = getHundertZweiID() ;
    ptrIDHundAcht = getHundertAchtID() ;
    ptrIDHundNeun = getHundertNeunID() ;
*/

/*Um die temporäle Events zu erhalten , wird die Fkt verwendet*/
int getEVBuff( void ) { return EVBuff ; }

// Aktionsfunktionen mit EVENT am Ende

/*Erste Funktion, wird aufgerufen bei der initialisation des Systems*/
void initStateMachineCom( void ) {
    uint8_t stateVal = 0x0000 ;
    //

    if(stateVal) {
        // Initialisation kommplett
        //HandleState( EV_INITIALISAT_COMPLETE ) ;
    } else {
        // Initialisation nicht komplett
        //Zustandsmaschine bleibt in altem zustand
        //HandleState( EV_CHECK_PASSED ) ;
        EVBuff = EV_CHECK_PASSED ;
    }
}

/* */
void chargStrButtOn( void ) {
    uint8_t stateVal = 0x0000 ;
    stateVal = 1 ; /*1 wenn die Taste gedrückt wird*/
    if(stateVal) {
        // Initialisation kommplett
        //HandleState( EV_CHARGE_START_BUTT_ON ) ;
    } else {
        // Initialisation nicht komplett
        //Zustandsmaschine bleibt in altem zustand
        //HandleState( EV_CHECK_PASSED ) ;
        EVBuff = EV_CHECK_PASSED ;
    }
}

// low level Funktionen zum Senden der Daten aus HAL verwenden
void trmChrgStrSig( void ) {
    uint8_t stateVal = 0x0000 ;
    /*TRANSMIT -> Charge sequence signal 1" signal ENABLE*/
    /*switch(d1):ON*/
    /*opto-coupler(f):ON*/

    stateVal = 1 ;
    if(stateVal) {
        // Initialisation kommplett
        //HandleState( EV_TRA_CHAR_STR_SIG_COM ) ;
    } else {
        // Initialisation nicht komplett
        //Zustandsmaschine bleibt in altem zustand
        //HandleState( EV_CHECK_PASSED ) ;
        EVBuff = EV_CHECK_PASSED ;
    }
}

// low level Funktionen zum Senden/Empfangen der Daten aus HAL verwenden
void rec_trmCANData( void ) {

    uint8_t stateVal = 0x0000 ;

    if(stateVal) {
        // Initialisation kommplett
        //HandleState( EV_START_CAN_COMMUNICAT ) ;
    } else {
        // Initialisation nicht komplett
        //Zustandsmaschine bleibt in altem zustand
        //HandleState( EV_CHECK_PASSED ) ;
        EVBuff = EV_CHECK_PASSED ;
    }
}

    // low level Funktionen zum Senden der Daten aus HAL verwenden
void prcssInfChrgCnt( void ) {

    uint8_t stateVal = 0x0000 ;

    if(stateVal) {
        // Initialisation kommplett
        //HandleState( EV_PROC_INF_CHARGE_CONT ) ;
    } else {
        // Initialisation nicht komplett
        //Zustandsmaschine bleibt in altem zustand
        //HandleState( EV_CHECK_PASSED ) ;
        EVBuff = EV_CHECK_PASSED ;
    }
}

// low level Funktionen zum Empfangen der Daten aus HAL verwenden
void recVicChrgPermSig( void ) {

    uint8_t stateVal = 0x0000 ;

    if(stateVal) {
        // Initialisation kommplett
        //HandleState( EV_TRAN_SIG_VIH_SET_COM ) ;
    } else {
        // Initialisation nicht komplett
        //Zustandsmaschine bleibt in altem zustand
        //HandleState( EV_CHECK_PASSED ) ;
        EVBuff = EV_CHECK_PASSED ;
    }
}

// Überprüfen ob Konnektor auf ist. // Check that EV contactors are surely opened (Voltage on output terminals is less than 10V.)
void evContOpen( void ) {

    uint8_t stateVal = 0x0000 ;

    if(stateVal) {
        // Initialisation kommplett
       // HandleState( EV_EV_CONT_IS_OPEN_COMP ) ;
    } else {
        // Initialisation nicht komplett
        //Zustandsmaschine bleibt in altem zustand
        //HandleState( EV_CHECK_PASSED ) ;
        EVBuff = EV_CHECK_PASSED ;
    }
}

//Insulation test on output DC circuit
void inslDCCir( void ) {
    // Test durchführen
    uint8_t stateVal = 0x0000 ;

    if(stateVal) {
        // Initialisation kommplett
       //HandleState( EV_INSU_OUT_DC_CIR_COMP ) ;
    } else {
        // Initialisation nicht komplett
        //Zustandsmaschine bleibt in altem zustand
       // HandleState( EV_CHECK_PASSED ) ;
       EVBuff = EV_CHECK_PASSED ;
    }
}

// Check the termination of insulation test (Voltage on output terminals is less than 20V.)
void  termInslDCCirCom( void ) {
    //Überprüfen, ob Test zu Ende ist
    uint8_t stateVal = 0x0000 ;

    if(stateVal) {
        // Initialisation kommplett
        //HandleState( EV_V_OUT_TERM_LESS_20_V ) ;
    } else {
        // Initialisation nicht komplett
        //Zustandsmaschine bleibt in altem zustand
        //HandleState( EV_CHECK_PASSED ) ;
        EVBuff = EV_CHECK_PASSED ;
    }
}

// "Charge sequence signal 2" signal. switch(d2):ON opto-coupler(g):ON.Transmit the signal of charger setup completion
void trmSigChrgSetCom( void ) {
    // Signal 2 an Fahrzeug senden
    uint8_t stateVal = 0x0000 ;

    if(stateVal) {
        // Initialisation kommplett
        //HandleState( EV_TRA_SIG_CHAR_COM_COM ) ;
    } else {
        // Initialisation nicht komplett
        //Zustandsmaschine bleibt in altem zustand
        //HandleState( EV_CHECK_PASSED ) ;
        EVBuff = EV_CHECK_PASSED ;
    }
}

// Start charging current output
void recStrChrgIOut( void ) {
    // Empfangen von Stop Nachricht
    uint8_t stateVal = 0x0000 ;

    if(stateVal) {
        // Initialisation kommplett
       // HandleState( EV_TRAN_CHARGIN_STOP_RQ ) ;
    } else {
        // Initialisation nicht komplett
        //Zustandsmaschine bleibt in altem zustand
       // HandleState( EV_CHECK_PASSED ) ;
       EVBuff = EV_CHECK_PASSED ;
    }
}

// Stop charging. "Vehicle charge permission" signal and "Vehicle charging enabled" flag
void recStpChrg( void ) {
    // Ladevorgang anhalten
    uint8_t stateVal = 0x0000 ;

    if(stateVal) {
        // Initialisation kommplett
        //HandleState( EV_STOP____CHARGING_COM ) ;
    } else {
        // Initialisation nicht komplett
        //Zustandsmaschine bleibt in altem zustand
        //HandleState( EV_CHECK_PASSED ) ;
        EVBuff = EV_CHECK_PASSED ;
    }
}

// Check that DC voltage is less than 10V
void checkDCVless10V( void ) {
    // Überprüfen der Spannung kleiner 10 V
    uint8_t stateVal = 0x0000 ;

    if(stateVal) {
        // Initialisation kommplett
        //HandleState( EV_DC_VOL_LESS_10_V_COM ) ;
    } else {
        // Initialisation nicht komplett
        //Zustandsmaschine bleibt in altem zustand
        //HandleState( EV_CHECK_PASSED ) ;
        EVBuff = EV_CHECK_PASSED ;
    }
}

//Unlock charging connector. "Charging connector lock" flag to 0
void trmUnlChrgConn( void ) {
    // Senden Flag 0
    uint8_t stateVal = 0x0000 ;

    if(stateVal) {
        // Initialisation kommplett
        //HandleState( EV_UNLOCK_CHAR_CONN_COM ) ;
    } else {
        // Initialisation nicht komplett
        //Zustandsmaschine bleibt in altem zustand
        //HandleState( EV_CHECK_PASSED ) ;
        EVBuff = EV_CHECK_PASSED ;
    }
}

/**/
void anySTProz( void ) {
    /*uint8_t *ptrIDHundZwei, *ptrIDHundNeun ;
    ptrIDHundZwei =  getHundertZweiID() ;
    ptrIDHundNeun = getHundertNeunID() ;*/

    /*Die globale Variablen werden hier jede Iterration neu zugewiesen*/
    ptrIDHund     = getHundertID() ;
    ptrIDHundEins = getHundertEinstID() ;
    ptrIDHundZwei = getHundertZweiID() ;
    ptrIDHundAcht = getHundertAchtID() ;
    ptrIDHundNeun = getHundertNeunID() ;

    outVoltCharger = ( *( ptrIDHundNeun + 1 ) >> 8 ) & ( *( ptrIDHundNeun + 2 ) ) ;
    outCurrCharger = *( ptrIDHundNeun + 3 ) ;

    targetBattVoltVehic  = ( *( ptrIDHundZwei + 1 ) >> 8 ) & ( *( ptrIDHundZwei + 2 ) ) ;
    maxOutputVoltCharger = ( *( ptrIDHundAcht + 1 ) >> 8 ) & ( *( ptrIDHundAcht + 2 ) ) ;

    chargeCurrRequestVehic  = *( ptrIDHundZwei + 3 ) ;
    maxOutputCurrentCharger = *( ptrIDHundAcht + 3 ) ;

    /*if bed. wird nicht gebraucht, da es an der Seite d. FRZG ausgeführt wird*/
    if( getVehicChargePerm() == OFF ) { // This value shall be updated until switch (k) is turned on. Do not update this value after final value is set
        maxBattVoltVehic = ( *( ptrIDHund + 4 ) >> 8 ) & ( *( ptrIDHund + 5 ) ) ;
    }
    thresVoltCharger     = ( *( ptrIDHundAcht + 4 ) >> 8 ) & ( *( ptrIDHundAcht + 5 ) ) ;

    maxChargTimeS = *( ptrIDHundEins + 1 ) ; // max time 10 s von Fahrzeug
    maxChargTimeM = *( ptrIDHundEins + 2 ) ; // max time 1 m von Fahrzeug

        /*Berechnung der Variablen remainChargTimeS und remainChargTimeM*/
    // remainChargTimeS = maxChargTimeS - timervalue ;
    // remainChargTimeM = maxChargTimeS - timervalue ;

    // Senden Flag 0
    //uint8_t stateVal = 0x0000 ;

    /*Table A.15Charge control termination command patterns.*/
    /*TERMINATION*/
    if( ( ( *( ptrIDHundZwei + 5 ) & 0b00000001 ) == 0x0000 ) && ( 1/*Switch (k)^a off*/ ) ) {
        /*Übergang zur Termination*/
        EVBuff = EV_CHRG_RAT_REACH_LEVEL ;

    } else if( ( ( *( ptrIDHundZwei + 5 ) & 0b00000001 ) == 0x0000 ) && ( 1/*Switch (k)^a off*/ ) && (1/*Fault-related flags in #102 == 1*/) ) {
        /*Übergang zur Termination*/
        EVBuff = EV_VEHI_CHRG_MALFKT_DET ;

    } else if( ( *( ptrIDHundNeun + 5 ) & 0b00100000 )  == 1 ) {
/*->*/        //setHundertNeunID( 5, 0b00000010 ) ; // Charger malfunction. Flag indicating the presence of the malfunction originated in the charger among the malfunctions detected by the charger.

        /*Übergang zur Termination*/
        EVBuff = EV_CHRG_STP_BUTT_TIM_RE ;

    } else if( ( ( *( ptrIDHundNeun + 5 ) & 0b00100000 ) == 1 ) && ( 1/*Fault-related flags in #109.5 == 1*/ ) ) {
/*->*/        //setHundertNeunID( 5, 0b00000010 ) ; // Charger malfunction. Flag indicating the presence of the malfunction originated in the charger among the malfunctions detected by the charger.

        /*Übergang zur Termination*/
        EVBuff = EV_CHRG_VEHI_MALFKT_DET ;

    } else {
        EVBuff = EV_CHECK_PASSED ;  // no change state
    }


    /*Time-out Fälle führen zur Termination*/
    if( 1/*hier ausgelaufene Zeit von Dealay*/ ) { // time-out process by the vehicle, change #102.5.2 (charging system fault)
        /*Übergang in Termination*/
        //( *( ptrIDHundZwei + 5 ) & 0b00000100) == 1
        setHundertNeunID( 5, 0b00000100 ) ;

        EVBuff = EV_VIHIC_TIME_OUT_PROCE ;
    }

    if( getSoftWatchdog( ) ) {   // time out process by the charger, change #109.5.4 (Charger system malfunction)
        /*Übergang in Termination*/


        setHundertNeunID( FEHL_FKT_LADE_SYS_5_4 / 10, 0b00010000 ) ;
        EVBuff = EV_CHARG_TIME_OUT_PROCE ;
    }
}

//Terminationsprozess
void trmProzess( void ) {
    /*Funktiosbody hier ...*/

    EVBuff = EV_CHECK_PASSED ;
}


void prozInfoBeforeCharg( void ) {
    /*************************Vllt soll es mit any_state*********************************/
    /*Variablen global ???*/
    /*uint8_t *ptrIDHundAcht, *ptrIDHundNeun, *ptrIDHundZwei, *ptrIDHund, *ptrIDHundEins ;
    uint16_t targetBattVoltVehic = 0x0000, maxOutputVoltCharger = 0x0000 ;
    uint8_t chargeCurrRequestVehic = 0x0000, maxOutputCurrentCharger = 0x0000 ;
    uint16_t maxOutputVoltVehic = 0x0000 ;
    uint16_t outVoltCharger = 0x0000 ;
    uint8_t outCurrCharger = 0x0000 ;
    uint16_t thresVoltCharger = 0x0000 ;
    uint16_t maxBattVoltVehic = 0x0000 ;

    uint8_t maxChargTimeS = 0x0000, maxChargTimeM = 0x0000 ;       // from vehicle. Maximum charging time (by 10 seconds). Maximum charging time (by 1 minute).
    uint8_t remainChargTimeS = 0x0000, remainChargTimeM = 0x0000 ; // from charger. Remaining charge time (by 10 seconds). Remaining charge time (by 1 minute).
    */

   /* ptrIDHund     = getHundertID() ;
    ptrIDHundEins = getHundertEinstID() ;
    ptrIDHundZwei = getHundertZweiID() ;
    ptrIDHundAcht = getHundertAchtID() ;
    ptrIDHundNeun = getHundertNeunID() ;
*/

    if( targetBattVoltVehic > maxOutputVoltCharger ) {          // Hier wird die Target-Battery-Voltage mit maximaler Spannung der Säule verglichen
        EVBuff = EV_EXCEE_TARG_BATT_VOLT ;                      // Wenn targetBattVoltVehic > maxOutputVoltCharger, Zustatndmaschine geht in Terminationszustand über
    }

    if( chargeCurrRequestVehic > maxOutputCurrentCharger ) {    // Hier wird die current-request  mit maximalem Strom der Säule verglichen
        EVBuff = EV_EXCEE_VEHI_CURR_REQU ;                      // Wenn
    }

    if( ( outVoltCharger - maxBattVoltVehic  ) == thresVoltCharger ) {  // Judgmental voltage value to stop charging process for on-board battery protection.
        EVBuff = EV_CHRG_VOLT_REACH_THRS  ;
    }
    /*********************************************************************************/

    // Set after obtaining the “Maximum charge time” of the vehicle.
    if(maxChargTimeS > 0) { // Initialisation vom remainChargTimeS
        setHundertNeunID( 6, remainChargTimeS ) ;   // Initialisation Remaining charge time (by 10 seconds)
    }

    if(maxChargTimeM > 0) { // Initialisation vom remainChargTimeM
        setHundertNeunID( 7, remainChargTimeM ) ; // Initialisation Remaining charge time (by 1  minute)
    }
}


void startCharging( void ) {
    setHundertNeunID( 5, 0b00000001 ) ;         // Charger status. Wenn der Strom gleich Ladestrom ist. Flag indicating that the charger is outputting charge current.
/*->*/    //setHundertNeunID( 5, 0b00000000 ) ; // Für allen anderen Zustände und wenn der Ladestrom kleiner als 5 A ist.
    setHundertNeunID( 6, remainChargTimeS ) ;   // Update Remaining charge time (by 10 seconds)
    setHundertNeunID( 7, remainChargTimeM ) ;   // Update Remaining charge time (by 1  minute)

    /*Wenn einer der folgenden Fälle passiert, wird "CHERGING STOP CONTROL Flag" auf Eins gesetzt und die ZM in naechsten Zustand ueberfuehrt wird*/

    // (1) Opto-coupler(j) OFF. Vehicle charge permission OFF
    if( getVehicChargePerm() == OFF ) {
        setHundertNeunID( 5, 0b00100000 ) ; //Charging stop control
        EVBuff = EV_TRAN_CHARGIN_STOP_RQ ;
    }

    // (2) “Charge stop button” ON. Charge sequence signal 1
    if( getChargeSeqSign_1() == ON) {
        setHundertNeunID( 5, 0b00100000 ) ; //Charging stop control
        EVBuff = EV_TRAN_CHARGIN_STOP_RQ ;
    }

    // (3) “Emergency stop button” ON. Charge sequence signal 2
    if( getChargeSeqSign_2() == ON ) {
        setHundertNeunID( 5, 0b00100000 ) ; //Charging stop control
        EVBuff = EV_TRAN_CHARGIN_STOP_RQ ;
    }

    // (4) “Remaining charge time” becomes 0. Time out ??
    if( getSoftWatchdog() == 1 ) {
        setHundertNeunID( 5, 0b00100000 ) ; //Charging stop control
        EVBuff = EV_TRAN_CHARGIN_STOP_RQ ;
    }

    // (5) Charger detects abnormality See Figure A.26 hier ist noch unklar wie es bestimmt werden muss
    /*if() {
        setHundertNeunID( 5, 0b00100000 ) ; //Charging stop control
        EVBuff = EV_TRAN_CHARGIN_STOP_RQ ;
    }*/
}

void stopChargingOut( void ) {
    setHundertNeunID( 5, 0b00100000 ) ; //Charging stop control
    setHundertNeunID( 6, 0x0000 ) ;   // Set Remaining charge time (by 10 seconds) auf 0
    setHundertNeunID( 7, 0x0000 ) ;   // Set Remaining charge time (by 1 minute) auf 0

}

//void termCANComm( void ) { // Terminate CAN communication
// TErmination Prozess Starten
//  HandleState( ----- ) ;
//}

/*  An dieser Stelle wird zunächst überprüft in welchem Zustand sich das System befindet.
*   Dann abhängig von dem Zustand wird eine Funktion aufgerufen und falls gefordetr ist, das
*   System in den neuen Zustand überführt wird
*/

/*ERROR states. source -> vehicle */
void battOverVolt( void) {

    // geht automatisch in Terminationzustnd über
    EVBuff = EV_ANY ;
}

void battUnderVolt( void ) {

    // geht automatisch in Terminationzustnd über
    EVBuff = EV_ANY ;
}

void battCurrDeviat( void ) {

    // geht automatisch in Terminationzustnd über
    EVBuff = EV_ANY ;
}

void battHighTemp( void ) {

    // geht automatisch in Terminationzustnd über
    EVBuff = EV_ANY ;
}

void battDiffVolt( void ) {

    // geht automatisch in Terminationzustnd über
    EVBuff = EV_ANY ;
}

void chargSysFault( void ) {

    // geht automatisch in Terminationzustnd über
    EVBuff = EV_ANY ;
}

void vehicShiftPos( void ) {

    // geht automatisch in Terminationzustnd über
    EVBuff = EV_ANY ;
}

/*ERROR states. source -> charger */
void chargerMalFkt( void ) {
    /*Chademo. Table A.32—CHARGER_MESSAGES*/
    setHundertNeunID( 5, 0b00000010 ) ;
    setHundertNeunID( 5, 0b00001000 ) ;
    setHundertNeunID( 5, 0b00010000 ) ;
    // geht automatisch in Terminationzustnd über
    EVBuff = EV_ANY ;
}

void chargigSysMalFkt( void ) {
    /*Chademo. Table A.32—CHARGER_MESSAGES*/
    setHundertNeunID( 5, 0b00000010 ) ;
    setHundertNeunID( 5, 0b00001000 ) ;
    setHundertNeunID( 5, 0b00010000 ) ;
    // geht automatisch in Terminationzustnd über
    EVBuff = EV_ANY ;
}

void battIncompat( void ) {
    /*Chademo. Table A.32—CHARGER_MESSAGES*/
    setHundertNeunID( 5, 0b00000010 ) ;
    setHundertNeunID( 5, 0b00001000 ) ;
    setHundertNeunID( 5, 0b00010000 ) ;
    // geht automatisch in Terminationzustnd über
    EVBuff = EV_ANY ;
}


void lockChargConn( void ) {
    setHundertNeunID( 5, 0b00000100 ) ; // lock charging connector
}

void unlockChargConn( void ) {
    setHundertNeunID( 5, 0b00000000 ) ; // unlock charging connector
}

/*Hier werden die funktionen im geforderten (momentanen) Zustand ausgeführt und die Events generiert*/
void stateAtcionFct(int state) {
    switch(state) {
        case ST_ANY :
            anySTProz() ;   // Hier werden alle Fälle, die zur Termination führen bescrhrieben
        break ;

        case ST_INIT :
            initStateMachineCom() ;
        break ;

        case ST_CHARGE_START__BUTTON :

        break ;

        case ST_TRANS_CHARGE_STR_SIG :

        break ;

        case ST_REC_TRA_INI_CAN_DATA :

        break ;

        case ST_PROC_INF_CHARGE_CONT :
            prozInfoBeforeCharg() ;// Process the information for charge control before charging (Battery compatibility, charging time calculation etc.)
        break ;

        case ST_LOCK_CHARGING_CONNEC :
            lockChargConn() ;
        break ;

        case ST_CHECK_EV_CONT_OPENED :

        break ;

        case ST_INSU_TEST_OUT_DC_CIR :

        break ;

        case ST_CHECK_TERM_INSU_TEST :

        break ;

        case ST_TRANS_SIG_CHARGE_COM :

        break ;

        case ST_START_CHARGIN_OUTPUT :
            startCharging() ;
        break ;

        case ST_STOP________CHARGING :
            stopChargingOut() ;
        break ;

        case ST_CHECK_DC_V_LESS_10_V :

        break ;

        case ST_UNLOCK_CHARGING_CONN :

        break ;

        case ST_TERMINATE_CAN_COMMUN :

        break ;

        case ST__TERMINATIONSPROZESS :
            trmProzess();
        break ;

        /*ERROR states. source -> vehicle */
        case ST_ERR_BATTERY_OVERVOLT :
            battOverVolt();
        break ;

        case ST_ERR_BATTER_UNDERVOLT :
            battUnderVolt() ;
        break ;

        case ST_ERR_BATT_CURR_DEVIAT :
            battCurrDeviat();
        break ;

        case ST_ERR_HIGH_BATTER_TEMP :
            battHighTemp();
        break ;

        case ST_ERR_BATT_VOLT_DIFFER :
            battDiffVolt();
        break ;

        case ST_ERR_CHARG_SYST_FAULT :
            chargSysFault();
        break ;

        case ST_ERR_VIHIC_SHIFT_POSI :
            vehicShiftPos();
        break ;

        /*ERROR states. source -> charger*/
        case ST_ERR_CHARGER_MALFUNCT :
            chargerMalFkt() ;
        break ;

        case ST_ERR_CHARGING_MALFUNC :
            chargigSysMalFkt() ;
        break ;

        case ST_ERR_BATTERY_INCOMPAT :
            battIncompat() ;
        break ;
    }
}
