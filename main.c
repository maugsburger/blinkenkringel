#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// intensity levels:
// nr of total cycles (looping 0…LED_CYCLES-1)
#define LED_CYCLES   64
// nr of cycles led is on
#define LED_INTENS_4 30
#define LED_INTENS_3 16
#define LED_INTENS_2 8
#define LED_INTENS_1 1
// led props:

volatile uint8_t pwm_cycle = 0x00;
/* lum:
 * high bit  low bit
 *  4 3 2 1  4 3 2 1
 */
volatile uint8_t led_lum = 0b11001010;
volatile uint8_t led_on = 0x0F;

int main (void) {
    // init pwm counter
    TCCR0A = (1<<WGM01); // CTC
    TCCR0B = (1<<CS02) | (1<<CS02); // PRESCALE /256
    TIMSK = (1<<OCIE0A);
    OCR0A = 0;

    DDRB = 0xff;
    sei();
    for(;;) {
    }
}

ISR (TIMER0_COMPA_vect) { 
    /* pwm: 64 (1…64) cycles, two groups for current distribution
     * g1: on 0…30 off: 1…63
     * g2: on 33…63 off: 34…63
     */ 
    switch (pwm_cycle) {
        // g1:
        case LED_CYCLES-1:
            pwm_cycle = 0;
            PORTB = led_on & 0x03;
            break;
        // g2:
        case LED_CYCLES/2:
            PORTB = led_on & 0x0C;
            break;
        case LED_INTENS_4:
        case LED_CYCLES/2 + LED_INTENS_4:
            // all off
            PORTB &= ~(0x0F);
            break;
        case LED_INTENS_3:
        case LED_CYCLES/2 + LED_INTENS_3:
            //PORTB &= ~( ( (led_lum>>4) & (~led_lum) ) & 0x0F );
            PORTB &= (~led_lum>>4) | (led_lum) | 0xF0;
            break;
        case LED_INTENS_2:
        case LED_CYCLES/2 + LED_INTENS_2:
            //PORTB &= ~( ( (~led_lum>>4) & (led_lum) ) & 0x0F );
            PORTB &= (led_lum>>4) | (~led_lum) | 0xF0;
            break;
        case LED_INTENS_1:
        case LED_CYCLES/2 + LED_INTENS_1:
            //PORTB &= ~( ( (~led_lum>>4) & (~led_lum) ) & 0x0F );
            PORTB &= (led_lum>>4) | (led_lum) | 0xF0;
            break;
    }
    pwm_cycle++;

}

