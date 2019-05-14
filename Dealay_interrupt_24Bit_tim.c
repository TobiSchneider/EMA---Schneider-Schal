#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "main.h"
#include "Bibl.h"
#include "testHeader.h"
#include "SysAParam.h"
#include "StMachSysA.h"
#include "StFunktions.h"

volatile uint32_t ticks_delay = 0x0000 ;
uint32_t timePeriod = 0x0000 ;

/* MC Interrupt Funktion - spaeter wird mit Interruptfunktion ersetzt*/
void SysTick_Handler(void) {
  ticks_delay ++ ;
}

/* MC Interrupt basierte Delay-Funktion */
void delay_ms(uint32_t milliseconds) {
  uint32_t start = ticks_delay ;
  while( ( ticks_delay - start ) < milliseconds ) ;
}

/* Software watchdog zu dem Timeout Kontrolle */
/* timeOutVal ist Timeout- Wert in ms*/
void setSoftWatchdog( uint32_t timeOutVal ) {
    timePeriod = timeOutVal ;
    ticks_delay = 0x0000 ;
}

/* Software watchdog zu dem Timeout Kontrolle */
/* return 0 -> if timeout not occur */
/* retutn 1 -> if timeout occur     */
uint8_t getSoftWatchdog( void ) {
    if( ticks_delay >= timePeriod) {
        ticks_delay = 0 ;

        return 1 ;
    } else {

        return 0 ;
    }
}
