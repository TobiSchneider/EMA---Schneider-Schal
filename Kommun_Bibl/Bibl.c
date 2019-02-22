#include <stdio.h>
#include <stdlib.h>
#include "Bibl.h"

state_t state = ALLE_ROT_1;
int zaehler=1;

// Tabelle fuer state machine

ampel_state_t state_table[8] = {

// AMPEL1 AMPEL2   Induktionsschleife ?
// |         |       |   Wartezeit in s
// |         |       |   |
// |         |       |   |   naechster Zustand     Name
//----------------------------------------------------------------------
{ROT     , GRUEN   , 1, 10,  OSTWEST_GELB},        // OSTWEST_GRUEN
{ROT     , GELB    , 0,  1,  ALLE_ROT_1},          // OSTWEST_GELB
{ROT     , ROT     , 0,  3,  NORDSUED_ROTGELB},    // ALLE_ROT_1
{ROTGELB , ROT     , 0,  1,  NORDSUED_GRUEN},      // NORDSUED_ROTGELB
{GRUEN   , ROT     , 0, 10,  NORDSUED_GELB},       // NORDSUED_GRUEN
{GELB    , ROT     , 0,  1,  ALLE_ROT_2},          // NORDSUED_GELB
{ROT     , ROT     , 0,  3,  OSTWEST_ROTGELB},     // ALLE_ROT_2
{ROT     , ROTGELB , 0,  1,  OSTWEST_GRUEN}};      // OSTWEST_ROTGELB

/*Ladezustaende von Gleichstromladestation fuer Elektrofahrzeuge. Tabelle 102*/
ladestation_state_t state_table_ladestation[12] = {
    {NEIN, OFFEN,       NEIN,   10, DC_B1},     //DC_A   = 0,   // Nicht verbunden
    {JA,   OFFEN,       NEIN,   10, DC_B2},    // DC_B1  = 1,   // Initialisierung
    {JA,   OFFEN,       NEIN,   10, DC_B3},     //DC_B2  = 2,  // Initialisierun
    {JA,   OFFEN,       NEIN,   10, DC_C | DC_D},  //
    {JA,   GESCHLOSSEN, JA,     10},
    {JA,   GESCHLOSSEN, JA,     10},
    {JA,   GESCHLOSSEN, JA,     10},
    {JA,   GESCHLOSSEN, NEIN,   10},
    {JA,   GESCHLOSSEN, NEIN,   10},
    {JA,   GESCHLOSSEN, NEIN,   10},
    {JA,   GESCHLOSSEN, NEIN,   10},
    {JA,   GESCHLOSSEN, NEIN,   10}
    };



                g
                DC_B3  = 3,   // Initialisierung
                DC_C   = 4,   // Energieübertragung
                DC_D   = 5,    // Energieübertragung
                DC_B_1 = 6,   // Abschaltung
                DC_B_2 = 7,   // Abschaltung
                DC_B_3 = 8,   // Abschaltung
                DC_B_4 = 9,   // Abschaltung
                DC_E   = 11,      // Fehler
                DC_F   = 12        // Fehlfunktion



void Ampel1( unsigned char Farbe ) {

}   // schaltet Ampel1 auf eine Farbe

void Ampel2( unsigned char Farbe ) {

}   // schaltet Ampel2 auf eine Farbe

int Induktionsschleife(void) {

}   // fragt die Induktionsschleife ab

void stateMachine(void) {
    Ampel1(state_table[state].Ampel1);
    Ampel2(state_table[state].Ampel2);

    if (zaehler>0) {
        zaehler--;
    } else {
        if ( ((state_table[state].I_Schleife == 1) && Induktionsschleife() ) ||
             (state_table[state].I_Schleife == 0) )
        {
            state =   state_table[state].Naechster;
            zaehler = state_table[state].Wartezeit;
        }
    }
}
