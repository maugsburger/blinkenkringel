#include <avr/sleep.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include "sleep.h"
#include "led.h"
#include "key.h"

#define soft_reset() do { wdt_enable(WDTO_15MS); for(;;) { } } while(0) 

uint8_t mcusr_mirror __attribute__ ((section (".noinit")));

void get_mcusr(void) \
  __attribute__((naked)) \
  __attribute__((section(".init3")));
void get_mcusr(void)
{
  mcusr_mirror = MCUSR;
  MCUSR = 0;
  wdt_disable();
}

void sleep_idle( void ){
    set_sleep_mode(SLEEP_MODE_IDLE);
    sleep_mode();   
}

void sleep_powerdown( void ){
    power_boost( 0 );
    PRR |= PWRDOWN_PRR;
    // activate ICP interrupt
//    TIMSK |= (1<<ICIE1);
    GIMSK |= (1<<4);    //PCIE2
    PCMSK2 |= (1<<PCINT17);
    cli();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    //sleep_mode();   
    sleep_enable();
    BODCR = (1<<BPDS) | (1<<BPDSE);
    BODCR = (1<<BPDS);
    sei();
    sleep_cpu();
    soft_reset();
}

// sets system clock prescaler to 2^exponent
void change_clock_prescale( uint8_t exponent ) {
    cli();
    CLKPR = (1<<CLKPCE);
    CLKPR = exponent;
    sei();
}

void power_boost (uint8_t on) {
    if( on ){
        POWER_PORT |= (1<<POWER_PIN);
    } else {
        POWER_PORT &= ~(1<<POWER_PIN);
    }
}

ISR (PCINT_D_vect) {
    // simulate hard reset with wdt
    soft_reset();
}
