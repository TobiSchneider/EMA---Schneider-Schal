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

/*Testbereich*/
uint8_t testArr[10] ={0b00000001, 0b00000011, 0b00010111 , 40, 0b10100001, 12, 100, 122, 133, 144} ; // Da wird später eine Buffervariable von Can verwendet.
uint8_t *ptrArr = testArr ;

int main(void) {
    //printf("Hello world!\n");

    while(1) {
       //stateMachine();
       //strLadenSysA(ptrArr) ;
       HandleState( getEVBuff( ) ) ;
    }

    return 0;
}
