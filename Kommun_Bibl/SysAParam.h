#ifndef SYSAPARAM_H_INCLUDED
#define SYSAPARAM_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/*DINEN61851-24 Tabelle A.2 Einzelne Tabellenbits*/
#define MAX_BATT_VOLT_4      4
#define MAX_BATT_VOLT_5      5
#define BEMESS_KAP_BATT_5    5
#define BEMESS_KAP_BATT_6    6
#define KONST_ANG_LADE_ST_6  6
#define MAX_LADE_Z_S_1       1
#define MAX_LADE_Z_M_2       2
#define GESCH_LADE_Z_3       3
#define PROT_NR_STR_0        0
#define SOLL_WT_BATT_VOLT_1  1
#define SOLL_WT_BATT_VOLT_2  2
#define LADE_CURRENT_ANF_3   3
#define LADE_ST_6            6
#define LADE_FRZG_FREI_5_0   50
#define SLT_HBL_STL_FRZG_5_1 51
#define FEHL_LADE_SYS_5_2    52
#define FRZG_ST_5_3          53
#define NOR_STP_ANF_LADE_5_4 54
#define UEBER_VOLT_BATT_4_0  40
#define UNTER_VOLT_BATT_4_1  41
#define ABW_FEHL_BATT_MD_4_2 42
#define HOHE_BATT_TEMP_4_3   43
#define ABW_FEHL_BATT_VOLT_4_4 44
#define KENN_ERK_VER_SCH_0   0
#define VERF_OUT_VOLT_1      1
#define VERF_OUT_VOLT_2      2
#define VERF_OUT_CURR_3      3
#define SCHWELL_VOLT_4       4
#define SCHWELL_VOLT_5       5
#define VERS_NR_PROT_0       0
#define OUT_VOLT_1           1
#define OUT_VOLT_2           2
#define OUT_CUURR_3          3
#define VERB_LADE_TIM_S_6    6
#define VERB_LADE_TIM_S_7    7
#define STAT_ST_5_0          50
#define FEHL_FKT_STAT_5_1    51
#define VERR_FRZG_KUPP_5_2   52
#define BATT_KOMPAT_5_3      53
#define FEHL_FKT_LADE_SYS_5_4 54
#define STEUER_LADE_AB_5_5   55



/*Nachrichten IDs*/
#define HUNDERT_ID      0x100
#define HUNDERT_EINS_ID 0x101
#define HUNDERT_ZWEI_ID 0x102
#define HUNDERT_ACHT_ID 0x108
#define HUNDERT_NEUN_ID 0x109

/*Maximale Koeffizienten der Nachrichtenfelder*/
#define HUND_ID_MAX 6
#define HUND_EINS_ID_MAX 7
#define HUND_ZWEI_ID_MAX 7
#define HUND_ACHT_ID_MAX 6
#define HUND_NEUN_ID_MAX 8

/*Nachrichten-Felder*/
uint8_t hundertID[HUND_ID_MAX]          ;
uint8_t hundertEinsID[HUND_EINS_ID_MAX] ;
uint8_t hundertZweiID[HUND_ZWEI_ID_MAX] ;
uint8_t hundertAchtID[HUND_ACHT_ID_MAX] ;
uint8_t hundertNeunID[HUND_NEUN_ID_MAX] ;

bool strLadenSysA( uint8_t *ptrID ) ;

/*Die Übergabe der Nachrichtenwerten aus der Modul geht über get Funktionen*/
uint8_t *getHundertID( void ) ;
uint8_t *getHundertEinstID( void ) ;
uint8_t *getHundertZweiID( void ) ;
//uint8_t *getHundertDreiID( void ) ;
uint8_t *getHundertAchtID( void ) ;
uint8_t *getHundertNeunID( void ) ;

/*set Funktionen*/
void setHundertID( uint8_t koeff, uint8_t value )      ;
void setHundertEinstID( uint8_t koeff, uint8_t value ) ;
void setHundertZweiID( uint8_t koeff, uint8_t value )  ;
void setHundertDreiID( uint8_t koeff, uint8_t value )  ;
void setHundertAchtID( uint8_t koeff, uint8_t value )  ;
void setHundertNeunID( uint8_t koeff, uint8_t value )  ;

#endif // SYSAPARAM_H_INCLUDED
