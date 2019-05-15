#ifndef DEALAY_INTERRUPT_24BIT_TIM_H_INCLUDED
#define DEALAY_INTERRUPT_24BIT_TIM_H_INCLUDED

/*void delay_ms(uint32_t milliseconds) ;
void setSoftWatchdog( uint32_t timeOutVal ) ;
uint8_t getSoftWatchdog( void ) ;*/

void setTimAMSek( uint32_t timeOutVal ) ;
void setTimBMSek( uint32_t timeOutVal ) ;
void setTimCMSek( uint32_t timeOutVal ) ;
void setTimDMSek( uint32_t timeOutVal ) ;

void setTimASek( uint32_t timeOutVal ) ;
void setTimBSek( uint32_t timeOutVal ) ;
void setTimCSek( uint32_t timeOutVal ) ;
void setTimDSek( uint32_t timeOutVal ) ;


uint8_t getTimAMSek( void ) ;
uint8_t getTimBMSek( void ) ;
uint8_t getTimCMSek( void ) ;
uint8_t getTimDMSek( void ) ;

uint8_t getTimASek( void ) ;
uint8_t getTimBSek( void ) ;
uint8_t getTimCSek( void ) ;
uint8_t getTimDSek( void ) ;

#endif // DEALAY_INTERRUPT_24BIT_TIM_H_INCLUDED
