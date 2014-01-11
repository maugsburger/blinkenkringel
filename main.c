#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


// led props:
//

volatile uint8_t pwmports = 0x00;
const uint8_t pwm_ontime = 0x08;
volatile uint8_t pwm_offtime = 254;

int main (void) {
    // init pwm counter
    TCCR0A = (1<<WGM01); // CTC
    TCCR0B = (1<<CS02) | (1<<CS02); // PRESCALE /128
    TIMSK = (1<<OCIE0A);
    OCR0A = pwm_ontime; // 1kHz@8MHz

    DDRB = 0xff;
    sei();
    for(;;) {
        /*
        while ( pwm_offtime < 0xFF ) {
            _delay_ms(100);
            pwm_offtime++;
        } 
        _delay_ms(100);
        pwm_offtime = pwm_ontime;
        */
        _delay_ms(500);
        pwm_offtime = 0xFF;
        _delay_ms(500);
        pwm_offtime = 0x30;
        _delay_ms(500);
        pwm_offtime = pwm_ontime;
    }
}

ISR (TIMER0_COMPA_vect) { 
    if ( PORTB == 0xFF ) {
        PORTB = 0x00;
        OCR0A = pwm_offtime;
    } else {
        PORTB = 0xFF;
        OCR0A = pwm_ontime;
    }
}

