#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "main.h"
#include "Bibl.h"
#include "testHeader.h"
#include "SysAParam.h"
#include "StMachSysA.h"
#include "StFunktions.h"

int EVBuff = 0x0000 ;

/*Um die tempor�le Events zu erhalten , wird die Fkt verwendet*/
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
    stateVal = 1 ; /*1 wenn die Taste gedr�ckt wird*/
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

// �berpr�fen ob Konnektor auf ist. // Check that EV contactors are surely opened (Voltage on output terminals is less than 10V.)
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
    // Test durchf�hren
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
    //�berpr�fen, ob Test zu Ende ist
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
    // �berpr�fen der Spannung kleiner 10 V
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
    uint8_t *ptrIDHundZwei, *ptrIDHundNeun ;
    ptrIDHundZwei =  getHundertZweiID() ;
    ptrIDHundNeun = getHundertNeunID() ;

    // Senden Flag 0
    //uint8_t stateVal = 0x0000 ;
    /*Hier sind unterschiedliche Gr�nde der Termination beschrieben*/
    if( ( *( ptrIDHundZwei + 5 ) & 0b00000001 == 0x0000 ) && ( 1/*Switch (k)^a off*/ ) ) {
        /*�bergang zur Termination*/
        EVBuff = EV_CHRG_RAT_REACH_LEVEL ;
    } else if( ( *( ptrIDHundZwei + 5 ) & 0b00000001 == 0x0000 ) && ( 1/*Switch (k)^a off*/ ) && (1/*Fault-related flags in #102 == 1*/) ) {
        /*�bergang zur Termination*/
        EVBuff = EV_VEHI_CHRG_MALFKT_DET ;
    } else if( *( ptrIDHundNeun + 5 ) & 0b00100000  == 1 ) {
        /*�bergang zur Termination*/
        EVBuff = EV_CHRG_STP_BUTT_TIM_RE ;
    } else if( ( *( ptrIDHundNeun + 5 ) & 0b00100000 == 1 ) && ( 1/*Fault-related flags in #109.5 == 1*/ ) ) {
        /*�bergang zur Termination*/
        EVBuff = EV_CHRG_VEHI_MALFKT_DET ;
    } else {
        EVBuff = EV_CHECK_PASSED ;
    }

    /*Time-out F�lle f�hren zur Termination*/
    if( ( *( ptrIDHundZwei + 5 ) & 0b00000100) == 1 ) { // time-out process by the vehicle, change #102.5.2 (charging system fault)
        /*�bergang in Termination*/
        EVBuff = EV_VIHIC_TIME_OUT_PROCE ;
    }

    if( 1/*Wenn timeout ist out*/ ) {   // time out process by the charger, change #109.5.4 (Charger system malfunction)
        /*�bergang in Termination*/
        // Notiz: Zun�chst soll der Time out detektiert werden un der 1 Bit in CAN gesendet werden

        setHundertNeunID( FEHL_FKT_LADE_SYS_5_4 / 10, 0b00010000 ) ;
        EVBuff = EV_CHARG_TIME_OUT_PROCE ;
    }
}

//Terminationsprozess
void trmProzess( void ) {
    /*Funktiosbody hier ...*/

    EVBuff = EV_CHECK_PASSED ;
}

//void termCANComm( void ) { // Terminate CAN communication
// TErmination Prozess Starten
//  HandleState( ----- ) ;
//}

/*  An dieser Stelle wird zun�chst �berpr�ft in welchem Zustand sich das System befindet.
*   Dann abh�ngig von dem Zustand wird eine Funktion aufgerufen und falls gefordetr ist, das
*   System in den neuen Zustand �berf�hrt wird
*/
void stateAtcionFct(int state) {
    switch(state) {
        case ST_ANY :
            anySTProz() ;   // Hier werden alle F�lle, die zum Termination f�hren bescrhrieben
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

        break ;

        case ST_LOCK_CHARGING_CONNEC :

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

        break ;

        case ST_STOP________CHARGING :

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
    }
}
