#include <avr/sleep.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include "sleep.h"
#include "led.h"
#include "key.h"

#define soft_reset() do { wdt_enable(WDTO_15MS); for(;;) { } } while(0) 


// disable wdt after reset
void disable_wdt(void) __attribute__ ((naked)) \
             __attribute__ ((section (".init3")));

void disable_wdt( void ){
    MCUSR = 0;
    wdt_disable();
}


void sleep_idle( void ){
    set_sleep_mode(SLEEP_MODE_IDLE);
    sleep_mode();   
}

void sleep_powerdown( void ){
    PRR |= PWRDOWN_PRR;
    // activate ICP interrupt
//    TIMSK |= (1<<ICIE1);
    GIMSK |= (1<<4);    //PCIE2
    PCMSK2 |= (1<<PCINT17);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_mode();
    PRR &= ~PWRDOWN_PRR;
    // reenable counter
    led_init_timer_port();
    key_init_timer_port();
    sei();
}

// sets system clock prescaler to 2^exponent
void change_clock_prescale( uint8_t exponent ) {
    cli();
    CLKPR = (1<<CLKPCE);
    CLKPR = exponent;
    sei();
}


ISR (PCINT_D_vect) {
    // simulate hard reset with wdt
    cli();
    soft_reset();
}
