#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "main.h"
#include "Bibl.h"
#include "testHeader.h"
#include "SysAParam.h"
#include "StMachSysA.h"
#include "StFunktions.h"

/*Dieser Block generiert die Events*/
/*-> WICHTIG: Die EVs sollen erst generiert werden , wenn der handle abgelufen wurde*/
int EVvalue = 0x0000 ;

//HandleState( getEVBuff( ) ) ;
