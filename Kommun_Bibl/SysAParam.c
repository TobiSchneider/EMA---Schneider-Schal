#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "SysAParam.h"

//int stateNachrID ;


static void hundertIDFkt(char *ptrID) {

   /*Hier werden die Daten von Can in hundertID übertragen -> Verbindung mit stm32 HAL*/
    hundertID[MAX_BATT_VOLT_4]      = *( ptrID + 4 ) ;
    hundertID[MAX_BATT_VOLT_5]      = *( ptrID + 5 ) ;
    hundertID[KONST_ANG_LADE_ST_6]  = *( ptrID + 6 );
}

static void hundertEinsIDFkt(char *ptrID) {
/*Hier werden die Daten von Can in hundertEinsID übertragen -> Verbindung mit stm32 HAL*/
}

static void hundertZweiIDFkt(char *ptrID) {
/*Hier werden die Daten von Can in hundertZweiID übertragen -> Verbindung mit stm32 HAL*/
}

static void hundertAchtIDFkt(char *ptrID) {
/*Hier werden die Daten von Can in hundertAchtID übertragen -> Verbindung mit stm32 HAL*/
}

static void hundertNeunIDFkt(char *ptrID) {
/*Hier werden die Daten von Can in hundertNeunID übertragen -> Verbindung mit stm32 HAL*/
}

unsigned int testA , testB, testC, testD ;

/*ptrID ist ein Zeiger auf Nachricht von CAN*/
bool strLadenSysA( uint8_t *ptrID ) {

 testA = *( ptrID ) << 8;
 testB = *( ptrID+1 ) ;
 testC = *( ptrID+2 ) ;
 testD = ((*( ptrID ) << 8 ) | *( ptrID+1 )) & 0b0111111111110000 ;
    /*switch( ( ( ( *ptrID ) << 8 ) | *( ptrID ++ ) ) & 0b0111111111110000 ) { // Nachrichten ID aus CAN Nachricht erhalten
        case HUNDERT_ID:      hundertIDFkt( ptrID );     break;
        case HUNDERT_EINS_ID: hundertEinsIDFkt( ptrID ); break;
        case HUNDERT_ZWEI_ID: hundertZweiIDFkt( ptrID ); break;
        case HUNDERT_ACHT_ID: hundertAchtIDFkt( ptrID ); break;
        case HUNDERT_NEUN_ID: hundertNeunIDFkt( ptrID ); break;

        default: printf("Ein FEHLER : Nicht definierte Nachrichten-ID !\n"); break;
    }*/
}
