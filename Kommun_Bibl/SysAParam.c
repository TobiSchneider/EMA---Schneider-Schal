#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "SysAParam.h"

//int stateNachrID ;
uint8_t hundertID[]     = {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000                 } ;
uint8_t hundertEinsID[] = {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000         } ;
uint8_t hundertZweiID[] = {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000         } ;
uint8_t hundertAchtID[] = {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000                 } ;
uint8_t hundertNeunID[] = {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 } ;


static void hundertIDFkt(uint8_t *ptrID) {
    /*Hier werden die Daten von Can in hundertID übertragen -> Verbindung mit stm32 HAL*/
    hundertID[MAX_BATT_VOLT_4]      = *( ptrID + 4 ) ;
    hundertID[MAX_BATT_VOLT_5]      = *( ptrID + 5 ) ;
    hundertID[KONST_ANG_LADE_ST_6]  = *( ptrID + 6 );
}

static void hundertEinsIDFkt(uint8_t *ptrID) {
    /*Hier werden die Daten von Can in hundertEinsID übertragen -> Verbindung mit stm32 HAL*/
    hundertEinsID[BEMESS_KAP_BATT_5] = *( ptrID + 5 ) ;
    hundertEinsID[BEMESS_KAP_BATT_6] = *( ptrID + 6 ) ;
    hundertEinsID[MAX_LADE_Z_S_1] = *( ptrID + 1 ) ;
    hundertEinsID[MAX_LADE_Z_M_2] = *( ptrID + 2 ) ;
    hundertEinsID[GESCH_LADE_Z_3] = *( ptrID + 3 ) ;
}

static void hundertZweiIDFkt(uint8_t *ptrID) {
    /*Hier werden die Daten von Can in hundertZweiID übertragen -> Verbindung mit stm32 HAL*/
    hundertZweiID[PROT_NR_STR_0] = *( ptrID + 0 ) ;
    hundertZweiID[SOLL_WT_BATT_VOLT_1] = *( ptrID + 1 ) ;
    hundertZweiID[SOLL_WT_BATT_VOLT_2] = *( ptrID + 2 ) ;
    hundertZweiID[LADE_CURRENT_ANF_3] = *( ptrID + 3 ) ;
    hundertZweiID[LADE_ST_6] = *( ptrID + 6 ) ;
    hundertZweiID[LADE_FRZG_FREI_5_0 / 10] = *( ptrID + 5 ) & 0b00000001 ;
    hundertZweiID[SLT_HBL_STL_FRZG_5_1 / 10] = *( ptrID + 5 ) & 0b00000010 ;
    hundertZweiID[FEHL_LADE_SYS_5_2 / 10] = *( ptrID + 5 ) & 0b00000100 ;
    hundertZweiID[FRZG_ST_5_3 / 10] = *( ptrID + 5 ) & 0b00001000;
    hundertZweiID[NOR_STP_ANF_LADE_5_4 / 10] = *( ptrID + 5 ) & 0b00010000;
    hundertZweiID[UEBER_VOLT_BATT_4_0 / 10] = *( ptrID + 4 ) & 0b00000001;
    hundertZweiID[UNTER_VOLT_BATT_4_1 / 10] = *( ptrID + 4 ) & 0b00000010;
    hundertZweiID[ABW_FEHL_BATT_MD_4_2 / 10] = *( ptrID + 4 ) & 0b00000010;
    hundertZweiID[ABW_FEHL_BATT_VOLT_4_4 / 10] = *( ptrID + 4 ) & 0b00010000;
}

static void hundertAchtIDFkt(uint8_t *ptrID) {
    /*Hier werden die Daten von Can in hundertAchtID übertragen -> Verbindung mit stm32 HAL*/
     hundertAchtID[KENN_ERK_VER_SCH_0]  = *( ptrID + 0 );
     hundertAchtID[VERF_OUT_VOLT_1]  = *( ptrID + 1 );
     hundertAchtID[VERF_OUT_VOLT_2]  = *( ptrID + 2 );
     hundertAchtID[VERF_OUT_CURR_3]  = *( ptrID + 3 );
     hundertAchtID[SCHWELL_VOLT_4]  = *( ptrID + 4 );
     hundertAchtID[SCHWELL_VOLT_5]  = *( ptrID + 5 );
}

static void hundertNeunIDFkt(uint8_t *ptrID) {
    /*Hier werden die Daten von Can in hundertNeunID übertragen -> Verbindung mit stm32 HAL*/
    hundertNeunID[VERS_NR_PROT_0]  = *( ptrID + 0 );
    hundertNeunID[OUT_VOLT_1]  = *( ptrID + 1 );
    hundertNeunID[OUT_VOLT_2]  = *( ptrID + 2 );
    hundertNeunID[OUT_CUURR_3]  = *( ptrID + 3 );
    hundertNeunID[VERB_LADE_TIM_S_6]  = *( ptrID + 6 );
    hundertNeunID[VERB_LADE_TIM_S_7]  = *( ptrID + 7 );
    hundertNeunID[STAT_ST_5_0 / 10]  = *( ptrID + 5 ) & 0b00000001;
    hundertNeunID[FEHL_FKT_STAT_5_1 / 10]  = *( ptrID + 1 ) & 0b00000010;
    hundertNeunID[VERR_FRZG_KUPP_5_2 / 10]  = *( ptrID + 2 ) & 0b00000100;
    hundertNeunID[BATT_KOMPAT_5_3 / 10]  = *( ptrID + 3 ) & 0b00001000;
    hundertNeunID[FEHL_FKT_LADE_SYS_5_4 / 10]  = *( ptrID + 4 ) & 0b00010000;
    hundertNeunID[STEUER_LADE_AB_5_5 / 10]  = *( ptrID + 5 ) & 0b00100000;
}

unsigned int testA , testB, testC, testD ;

/*ptrID ist ein Zeiger auf Nachricht von CAN*/
bool strLadenSysA( uint8_t *ptrID ) {

 /*testA = *( ptrID ) << 8;
 testB = *( ptrID+1 ) ;
 testC = *( ptrID+2 ) ;
 testD = ((*( ptrID ) << 8 ) | *( ptrID+1 )) & 0b0111111111110000 ;*/

    switch( ( (uint16_t)(  *ptrID << 8 ) | (uint16_t)(*( ptrID + 1 )) ) & 0b0111111111110000 ) { // Nachrichten ID aus CAN Nachricht erhalten
        case HUNDERT_ID:      hundertIDFkt( ptrID );     break;
        case HUNDERT_EINS_ID: hundertEinsIDFkt( ptrID ); break;
        case HUNDERT_ZWEI_ID: hundertZweiIDFkt( ptrID ); break;
        case HUNDERT_ACHT_ID: hundertAchtIDFkt( ptrID ); break;
        case HUNDERT_NEUN_ID: hundertNeunIDFkt( ptrID ); break;

        default: printf("Ein FEHLER : Nicht definierte Nachrichten-ID !\n"); break;
    }
}

/*Get Funktionen*/
uint8_t *getHundertID( void ) {
    return hundertID ;
}


uint8_t *getHundertEinstID( void ) {
    return hundertEinsID ;
}

uint8_t *getHundertZweiID( void ) {
    return hundertZweiID ;
}

/*uint8_t *getHundertDreiID( void ) {
    return hundertDreiID ;
}*/

uint8_t *getHundertAchtID( void ) {
    return hundertAchtID ;
}

uint8_t *getHundertNeunID( void ) {
    return hundertNeunID ;
}


/*set Funktionen*/
void setHundertID( uint8_t koeff, uint8_t value ) {
    hundertID[koeff] &= value ;
}

void setHundertEinstID( uint8_t koeff, uint8_t value ) {
    hundertEinsID[koeff] &= value ;
}

void setHundertZweiID( uint8_t koeff, uint8_t value ) {
    hundertZweiID[koeff] &= value ;
}

/*void setHundertDreiID( uint8_t koeff, uint8_t value ) {
    hundertDreiID[koeff] &= value ;
}*/

void setHundertAchtID( uint8_t koeff, uint8_t value ) {
    hundertAchtID[koeff] &= value ;
}

void setHundertNeunID( uint8_t koeff, uint8_t value ) {
    hundertNeunID[koeff] &= value ;
}
