#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/wdt.h>
#include "main.h"
#include "led.h"
#include "key.h"
#include "patterns.h"
#include "sleep.h"

/* Counter Usage:
 * TC0 in led.c
 *  - prescale 1024 => 7.8125kHz, 128µs
 *  - CTC Interrupt OCR0A = 0, 128µs
 *  - 64 cycles for 1 pwm cycle => 122Hz PWM
 *
 *  TC1 in key.c
 *  - prescale 64 => 125kHz, 8µs
 *  - CTC Interrupt OCR1A = 500, 5ms
 *  - wait_countdown-- for pattern timer
 *  - key debouncing in interrupt routine
 *  INFO PROBABLY OUTDATED DUE TO CLOCK CHANGE TO 4MHZ!
 */

int main (void) {

    // disable unused functions for powersaving
    PRR = (1<<PRUSI) | (1<<PRUSART);

    DDRA = 0xff;

    change_clock_prescale( 0x01 );  // full speed 4MHz

    led_init_port();

    // brownout @1.8V if device is started with insuficcient bats.
    if ( mcusr_mirror == (1<<BORF) ) {
        blink_red_powersave();
        sleep_powerdown();        
    }
    uint8_t i=0;    // selected pattern;
    uint8_t pwrhyst = 0;

    // switch on stepup, change frequency after short delay
    POWER_DDR |= (1<<POWER_PIN);
    POWER_PORT |= (1<<POWER_PIN);

    // bat comparator
    ACSR = (1<<ACBG);
    DIDR |= (1<<AIN1D);

    // init pwm counter
    led_init_timer();
    key_init_timer_port();

    // alive signal 
    pled_on( (1<<PLED_RED) | (1<<PLED_GREEN) );
    led_set_mode_r( 0x11, 0x11, 0 );
    _delay_ms(50);
    led_set_mode_r( 0x00, 0x00, 0 );
    _delay_ms(200);
    pled_off( (1<<PLED_RED) );

    // check initial bat state for undervolt
    if ( (ACSR & (1<<ACO)) ) pwrhyst = 0xFF;
    sei();

    for(;;) {

        for(uint8_t r=0; r< (*light_patterns[i]).rotate; r++) {
            // if there is a change to measure with leds off, then here
            // => check bat voltage
            if ( ACSR & (1<<ACO) ) {
                if ( pwrhyst == 0x0f ) { 
                    pled_on( 1<<PLED_RED);
                    pled_off(1<<PLED_GREEN);
                } else {
                    pwrhyst++;
                }
            } else {
                if ( pwrhyst == 0x00 ) {
                    pled_on(1<<PLED_GREEN);
                    pled_off( 1<<PLED_RED);
                } else {
                    pwrhyst--;
                }
            } 
            for(uint8_t p=0; p<(*light_patterns[i]).nr_elements; p++) {
                if ( key_press & ALL_KEYS ) {
                    pwrhyst = 0;
                    led_set_mode_r(0x00,0x00,0);
                    if( get_key_short( 1<<KEY0 )) {
                        r = 0;
                        p = 0;
                        i++;
                        if ( i >= sizeof(light_patterns)/sizeof(light_patterns[0]) )
                            i = 0;
                    }
                    if( get_key_long( 1<<KEY0 )) {
                        pled_off( (1<<PLED_RED) | (1<<PLED_GREEN) );
                        power_boost( 0 );
                        // wait for key release (with pullup=>1)
                        loop_until_bit_is_set( KEY_PIN, KEY0 );
                        // give key some time to debounce
                        _delay_ms(100);
                        sleep_powerdown();
                    }
                } else {
                    led_set_mode_r(
                        (*light_patterns[i]->lp_elements)[p]->l12,
                        (*light_patterns[i]->lp_elements)[p]->l34,
                        r);
                    key_wait_times_5ms(
                        (*light_patterns[i]->lp_elements)[p]->duration 
                    );
                }
            }
        }
    }
}


void blink_red_powersave() {
    power_boost( 0 );
    PRR |= PWRDOWN_PRR; // disable timer 
    pled_on( 1<<PLED_RED);
    pled_off(1<<PLED_GREEN);
    for(uint8_t i=100; i!=0; i--){
        pled_toggle(1<<PLED_RED);
        _delay_ms(300);
    }
    pled_off( 1<<PLED_RED);
}
