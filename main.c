#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/wdt.h>
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
 */
#define PLED_RED    4
#define PLED_GREEN  5
#define PLED_PORT   PORTD
#define PLED_DDR    DDRD

int main (void) {
    // disable unused functions
    PRR = (1<<PRUSI) | (1<<PRUSART);

    // init pwm counter
    led_init_timer_port();
    key_init_timer_port();
    sei();

    PLED_DDR |= (1<<PLED_RED) | (1<<PLED_GREEN);
    
    // alive signal 
    PLED_PORT |= (1<<PLED_RED) | (1<<PLED_GREEN);
    led_set_mode_r( 0x44, 0x44, 0 );
    _delay_ms(50);
    led_set_mode_r( 0x00, 0x00, 0 );
    _delay_ms(500);
    PLED_PORT &= ~( (1<<PLED_GREEN) | (1<<PLED_RED) );

    uint8_t i=0;
    for(;;) {

        for(uint8_t r=0; r< (*light_patterns[i]).rotate; r++) {
            for(uint8_t p=0; p<(*light_patterns[i]).nr_elements; p++) {
                if ( key_press & ALL_KEYS ) {
                    led_set_mode_r(0x00,0x00,0);
                    if( get_key_short( 1<<KEY0 )) {
                        PLED_PORT ^= 1<<PLED_GREEN;
                        r = 0;
                        p = 0;
                        i++;
                        if ( i >= sizeof(light_patterns)/sizeof(light_patterns[0]) )
                            i = 0;
                    }

                    if( get_key_long( 1<<KEY0 )) {
                        //TODO: Poweroff!
                        PLED_PORT = 1<<PLED_RED;
                        _delay_ms(1000);
                        PLED_PORT ^= 1<<PLED_RED;
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


