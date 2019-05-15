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

/* Dieser Modul Beschreibt die interrupt basierte  Funktionen,
*  die zur Messung der zeitlichen Abschnittn bestimmt sind
*  Mit set Funktionen wird der Zeitabschnitt eingesetzt
*  Mit get Funktionen erhält man den zustand des Softwaretimers
*  Die Softwaretimers Zahlen vom Minimalwert bis Maximalwert runter .
*  Ist der Timerwert Null, lisfert die get Funktionen den Wert 1 zurück.
*  Ist der Timerwert NOCH größer als Null, liefert die get Funktione 0 zurück
*  Die Interrupt Funktion ist der Interrupt under/over Flow Interruptfunktion
*  des stm32 24 core 24 Bit Timer. Da soll die Interruptfuntion jede zB 1 ms
*  aufgerufen werden. Dafür soll der Timer zunaechst eingestellt werden.
*/

volatile uint8_t m = 0x0000 ; // Eine wariable um aus ms 1 s zu bekommen mittels Interruptfunktion .

/*Timers im Sekundenbereich*/
uint32_t timerAPeriodS = 0x0000 ;
uint32_t timerBPeriodS = 0x0000 ;
uint32_t timerCPeriodS = 0x0000 ;
uint32_t timerDPeriodS = 0x0000 ;

volatile uint32_t ticks_delay_A_S = 0x0000 ;
volatile uint32_t ticks_delay_B_S = 0x0000 ;
volatile uint32_t ticks_delay_C_S = 0x0000 ;
volatile uint32_t ticks_delay_D_S = 0x0000 ;

/*Timers im Millisekundenbereich*/
uint32_t timerAPeriodMS = 0x0000 ;
uint32_t timerBPeriodMS = 0x0000 ;
uint32_t timerCPeriodMS = 0x0000 ;
uint32_t timerDPeriodMS = 0x0000 ;

volatile uint32_t ticks_delay_A_MS = 0x0000 ;
volatile uint32_t ticks_delay_B_MS = 0x0000 ;
volatile uint32_t ticks_delay_C_MS = 0x0000 ;
volatile uint32_t ticks_delay_D_MS = 0x0000 ;

/*set Funktionen für ms Bereich */
void setTimAMSek( uint32_t timeOutVal ) {
    timerAPeriodMS = timeOutVal ;
    ticks_delay_A_MS = 0x0000 ;
}

void setTimBMSek( uint32_t timeOutVal ) {
    timerBPeriodMS = timeOutVal ;
    ticks_delay_B_MS = 0x0000 ;
}

void setTimCMSek( uint32_t timeOutVal ) {
    timerCPeriodMS = timeOutVal ;
    ticks_delay_C_MS = 0x0000 ;
}

void setTimDMSek( uint32_t timeOutVal ) {
    timerDPeriodMS = timeOutVal ;
    ticks_delay_D_MS = 0x0000 ;
}

/*set Funktionen für s Bereich */
void setTimASek( uint32_t timeOutVal ) {
    timerAPeriodS = timeOutVal ;
    ticks_delay_A_S = 0x0000 ;
}

void setTimBSek( uint32_t timeOutVal ) {
    timerBPeriodS = timeOutVal ;
    ticks_delay_B_S = 0x0000 ;
}

void setTimCSek( uint32_t timeOutVal ) {
    timerCPeriodS = timeOutVal ;
    ticks_delay_C_S = 0x0000 ;
}

void setTimDSek( uint32_t timeOutVal ) {
    timerDPeriodS = timeOutVal ;
    ticks_delay_D_S = 0x0000 ;
}

/* get Funktionen für ms Bereich */
/* return 0 -> if timeout not occur */
/* retutn 1 -> if timeout occur     */
uint8_t getTimAMSek( void ) {
    if( ticks_delay_A_S >= timerAPeriodS) {
        ticks_delay_A_S = 0 ;

        return 1 ;
    } else {

        return 0 ;
    }
}

uint8_t getTimBMSek( void ) {
    if( ticks_delay_B_S >= timerBPeriodS) {
        ticks_delay_B_S = 0 ;

        return 1 ;
    } else {

        return 0 ;
    }
}

uint8_t getTimCMSek( void ) {
    if( ticks_delay_C_S >= timerCPeriodS) {
        ticks_delay_C_S = 0 ;

        return 1 ;
    } else {

        return 0 ;
    }
}

uint8_t getTimDMSek( void ) {
    if( ticks_delay_D_S >= timerDPeriodS) {
        ticks_delay_D_S = 0 ;

        return 1 ;
    } else {

        return 0 ;
    }
}


/* get Funktionen für Sekundenbereich */
/* return 0 -> if timeout not occur */
/* retutn 1 -> if timeout occur     */
uint8_t getTimASek( void ) {
    if( ticks_delay_A_S >= timerAPeriodS) {
        ticks_delay_A_S = 0 ;

        return 1 ;
    } else {

        return 0 ;
    }
}

uint8_t getTimBSek( void ) {
    if( ticks_delay_B_S >= timerBPeriodS) {
        ticks_delay_B_S = 0 ;

        return 1 ;
    } else {

        return 0 ;
    }
}

uint8_t getTimCSek( void ) {
    if( ticks_delay_C_S >= timerCPeriodS) {
        ticks_delay_C_S = 0 ;

        return 1 ;
    } else {

        return 0 ;
    }
}

uint8_t getTimDSek( void ) {
    if( ticks_delay_D_S >= timerDPeriodS) {
        ticks_delay_D_S = 0 ;

        return 1 ;
    } else {

        return 0 ;
    }
}


/* MC Interrupt Funktion - spaeter wird mit Interruptfunktion ersetzt*/
void SysTick_Handler(void) {
  //ticks_delay ++ ;

    ticks_delay_A_MS ++ ;
    ticks_delay_B_MS ++ ;
    ticks_delay_C_MS ++ ;
    ticks_delay_D_MS ++ ;

    m ++ ;
    if( m > 1000 ) { // Der Interrupt wird jede ms aufgerufen -> um 1 s zu erreichen, soll der Interrupt 1000 mal aufgerufen werden.
        m = 0x0000 ;
        ticks_delay_A_S ++ ;
        ticks_delay_B_S ++ ;
        ticks_delay_C_S ++ ;
        ticks_delay_D_S ++ ;
    }
}

/* MC Interrupt basierte Delay-Funktion */
/*void delay_ms(uint32_t milliseconds) {
  uint32_t start = ticks_delay ;
  while( ( ticks_delay - start ) < milliseconds ) ;
}


void setSoftWatchdog( uint32_t timeOutVal ) {
    timePeriod = timeOutVal ;
    ticks_delay = 0x0000 ;
}*/

/* Software watchdog zu dem Timeout Kontrolle */
/* return 0 -> if timeout not occur */
/* retutn 1 -> if timeout occur     */
/*uint8_t getSoftWatchdog( void ) {
    if( ticks_delay >= timePeriod) {
        ticks_delay = 0 ;

        return 1 ;
    } else {

        return 0 ;
    }
}*/
