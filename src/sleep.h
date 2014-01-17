#ifndef _SLEEP_H
#define _SLEEP_H

#define PWRDOWN_PRR (1<<PRTIM1) | (1<<PRTIM0)
#define POWER_PIN   2
#define POWER_PORT  PORTB
#define POWER_DDR   DDRB

void sleep_idle( void );
void sleep_powerdown( void );

void change_clock_prescale( uint8_t exponent );

void power_boost (uint8_t on);


extern uint8_t mcusr_mirror __attribute__ ((section (".noinit")));



#endif // _SLEEP_H
