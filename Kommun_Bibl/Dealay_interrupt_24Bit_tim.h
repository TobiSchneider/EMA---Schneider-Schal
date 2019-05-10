#ifndef DEALAY_INTERRUPT_24BIT_TIM_H_INCLUDED
#define DEALAY_INTERRUPT_24BIT_TIM_H_INCLUDED

void delay_ms(uint32_t milliseconds) ;
void setSoftWatchdog( uint32_t timeOutVal ) ;
uint8_t getSoftWatchdog( void ) ;

#endif // DEALAY_INTERRUPT_24BIT_TIM_H_INCLUDED
