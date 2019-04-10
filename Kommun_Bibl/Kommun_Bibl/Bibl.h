#ifndef BIBL_H_INCLUDED
#define BIBL_H_INCLUDED

#include <stdbool.h>

#define ROT       1
#define GRUEN     2
#define GELB      4
#define ROTGELB   5

/*Tabelle 2*/
#define NEIN    0
#define JA      1

#define OFFEN          0
#define GESCHLOSSEN    1

void Ampel1( unsigned char Farbe );   // schaltet Ampel1 auf eine Farbe
void Ampel2( unsigned char Farbe );   // schaltet Ampel2 auf eine Farbe
int Induktionsschleife(void);   // fragt die Induktionsschleife ab
void stateMachine(void) ;

typedef enum { OSTWEST_GRUEN=0, OSTWEST_GELB, ALLE_ROT_1,
               NORDSUED_ROTGELB, NORDSUED_GRUEN, NORDSUED_GELB, ALLE_ROT_2,
               OSTWEST_ROTGELB } state_t;

typedef struct {
    int Ampel1;
    int Ampel2;
    int I_Schleife;
    int Wartezeit;
    int Naechster;
} ampel_state_t;


/*Ladezustaends von Gleichstromladestation fuer Elektrofahrzeuge. Tabelle 102*/
typedef struct {
    bool Fahrzeug_verbunden   ;
    bool Fahrzeug_Schuetz     ;
    bool Ladevorgang_moeglich ;
    int Wartezeit             ;
    int Naechster             ;
} ladestation_state_t ;

/*Ladezustaends von Gleichstromladestation fuer Elektrofahrzeuge. Tabelle 102*/
typedef enum {
                DC_A   = 0,   // Nicht verbunden
                DC_B1  = 1,   // Initialisierung
                DC_B2  = 2,  // Initialisierung
                DC_B3  = 3,   // Initialisierung
                DC_C   = 4,   // Energieübertragung
                DC_D   = 5,    // Energieübertragung
                DC_B_1 = 6,   // Abschaltung
                DC_B_2 = 7,   // Abschaltung
                DC_B_3 = 8,   // Abschaltung
                DC_B_4 = 9,   // Abschaltung
                DC_E   = 11,      // Fehler
                DC_F   = 12        // Fehlfunktion
} state_t_ladestation ;

#endif // BIBL_H_INCLUDED

















