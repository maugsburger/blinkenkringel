#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "led.h"

void led_set_mode_r( const uint8_t l12_mode, const uint8_t l34_mode, const uint8_t pos ) {
    uint8_t leda = l12_mode>>4;
    uint8_t ledb = l12_mode & 0x07;
    uint8_t ledc = l34_mode>>4;
    uint8_t ledd = l34_mode & 0x07;

    uint8_t *ledp[4] = { &leda, &ledb, &ledc, &ledd };

    uint8_t led[4] = { 0, 1, 2, 3 };

    for( uint8_t i = 0; i < 4; i++ ) {
        led[i] -= pos;
        led[i] = led[i] & 0x03;
    }

    led_set_mode( *ledp[led[0]], *ledp[led[1]], *ledp[led[2]], *ledp[led[3]] );

}

void led_set_mode( const uint8_t l1_mode, const uint8_t l2_mode,
        const uint8_t l3_mode, const uint8_t l4_mode) {
    cli();
        // high nibble: x_mode = 0010
        // low nibble:  x_mode = 0001
        _led_mode_b = 
            ( l4_mode == 1 ? 0x80 : 0) |
            ( l3_mode == 1 ? 0x40 : 0) |
            ( l2_mode == 1 ? 0x20 : 0) |
            ( l1_mode == 1 ? 0x10 : 0) |
            ( l4_mode == 2 ? 0x08 : 0 ) |
            ( l3_mode == 2 ? 0x04 : 0 ) |
            ( l2_mode == 2 ? 0x02 : 0 ) |
            ( l1_mode == 2 ? 0x01 : 0 );
        // high nibble: x_mode = 0011
        // low nibble:  x_mode = any 1 set
        _led_mode_a = 
            ( l4_mode == 3 ? 0x80 : 0) |
            ( l3_mode == 3 ? 0x40 : 0) |
            ( l2_mode == 3 ? 0x20 : 0) |
            ( l1_mode == 3 ? 0x10 : 0) |
            ( l4_mode > 0 ? 0x08 : 0 ) |
            ( l3_mode > 0 ? 0x04 : 0 ) |
            ( l2_mode > 0 ? 0x02 : 0 ) |
            ( l1_mode > 0 ? 0x01 : 0 );
    sei();             
}

ISR (TIMER0_COMPA_vect) { 
    /* pwm: 64 (1…64) cycles, two groups for current distribution
     * g1: on 0…30 off: 1…63
     * g2: on 33…63 off: 34…63
     */ 
    switch (led_pwm_cycle) {
        // g1:
        case LED_CYCLES-1:
            led_pwm_cycle = 0;
            LED_PORT |= _led_mode_a & 0x03;
            break;
        // g2:
        case LED_CYCLES/2:
            LED_PORT |= _led_mode_a & 0x0C;
            break;
        case LED_INTENS_4:
        case LED_CYCLES/2 + LED_INTENS_4:
            // all off
            LED_PORT &= ~(0x0F);
            break;
        case LED_INTENS_3:
        case LED_CYCLES/2 + LED_INTENS_3:
            //LED_PORT &= ~( ( (led_lum>>4) & (~led_lum) ) & 0x0F );
            //LED_PORT &= (~led_lum>>4) | (led_lum) | 0xF0;
            LED_PORT &= ~_led_mode_a>>4 | 0xF0;
            break;
        case LED_INTENS_2:
        case LED_CYCLES/2 + LED_INTENS_2:
            //LED_PORT &= ~( ( (~led_lum>>4) & (led_lum) ) & 0x0F );
            //LED_PORT &= (led_lum>>4) | (~led_lum) | 0xF0;
            LED_PORT &= ~_led_mode_b | 0xF0;
            break;
        case LED_INTENS_1:
        case LED_CYCLES/2 + LED_INTENS_1:
            //LED_PORT &= ~( ( (~led_lum>>4) & (~led_lum) ) & 0x0F );
            //LED_PORT &= (led_lum>>4) | (led_lum) | 0xF0;
            LED_PORT &= ~_led_mode_b>>4 | 0xF0;
            break;
    }
    led_pwm_cycle++;

}

void led_init_timer_port () {
    TCCR0A = (1<<WGM01); // CTC
    TCCR0B = (1<<CS02); // PRESCALE /256
    OCR0A = 0;
    TIMSK |= (1<<OCIE0A);
    LED_DDR |= 0x0f;
}

