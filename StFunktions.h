#ifndef STFUNKTIONS_H_INCLUDED
#define STFUNKTIONS_H_INCLUDED

/*In diesem Datei werden die Aktionenfunktionen definiert, die für die Zustände der Kommunikation gehören*/
/*Aufgaben der Funktionen: 1 Zustandsabhängigen Aktionen abarbeiten. 2 Dann EVENT an die Zustandsmaschine senden*/
void initStateMachineCom( void ) ;  // In dieser Funktionen werden die Initialisationsprozeduren durchgeführt
void chargStrButtOn( void ) ;       // ButtonOn gedruckt - > EVENT
void trmChrgStrSig( void ) ;        // transmit Charge sequence signal 1" signal -> EVENT
void rec_trmCANData( void ) ;       // Receive initial vehicle CAN data and transmit charger CAN data in return -> EVENT
void prcssInfChrgCnt( void ) ;      // transmit, receive information for charge control before charging -> EVENT
void recVicChrgPermSig( void ) ;    // "Vehicle charge permission" signal. opto-coupler(j):ON switch(k):ON -> EVENT
void evContOpen( void ) ;
void inslDCCir( void ) ;
void termInslDCCirCom( void ) ;
void trmSigChrgSetCom( void ) ;
void recStrChrgIOut( void ) ;
void recStpChrg( void ) ;
void checkDCVless10V( void ) ;
void checkDCVless10V( void ) ;
void termCANComm( void ) ;

/*Hauptfunktion, in der alle anderen Funktionen aufgerufen werden*/
void stateAtcionFct( int state ) ;

int getEVBuff( void ) ;

#endif // STFUNKTIONS_H_INCLUDED
