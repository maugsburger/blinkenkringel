/************************************************************************/
/*                                                                      */
/*                      Debouncing 8 Keys                               */
/*          Sampling 4 Times                                            */
/*          With Repeat Function                                        */
/*                                                                      */
/*              Author: Peter Dannegger                                 */
/*                      danni@specs.de                                  */
/*                                                                      */
/************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "key.h"
#include "sleep.h"
#include "led.h"


volatile uint8_t wait_countdown = 0;

ISR (TIMER1_COMPA_vect) {         // every 5ms
    static uint8_t ct0, ct1, rpt;

    // every 2nd run->10ms
    uint8_t i;

    i = key_state ^ ~KEY_PIN;                       // key changed ?
    ct0 = ~( ct0 & i );                             // reset or count ct0
    ct1 = ct0 ^ (ct1 & i);                          // reset or count ct1
    i &= ct0 & ct1;                                 // count until roll over ?
    key_state ^= i;                                 // then toggle debounced state
    key_press |= key_state & i;                     // 0->1: key press detect

    if( (key_state & REPEAT_MASK) == 0 )            // check repeat function
        rpt = REPEAT_START;                         // start delay
    if( --rpt == 0 ){
        rpt = REPEAT_NEXT;                          // repeat delay
        key_rpt |= key_state & REPEAT_MASK;
    }
    //}

    wait_countdown--;
}


uint8_t get_key_press( uint8_t key_mask ) {
    cli();                      // read and clear atomic !
    key_mask &= key_press;      // read key(s)
    key_press ^= key_mask;      // clear key(s)
    sei();
    return key_mask;
}


uint8_t get_key_rpt( uint8_t key_mask ) {
    cli();                      // read and clear atomic !
    key_mask &= key_rpt;        // read key(s)
    key_rpt ^= key_mask;        // clear key(s)
    sei();
    return key_mask;
}


uint8_t get_key_short( uint8_t key_mask ) {
    cli();            // read key state and key press atomic !
    return get_key_press( ~key_state & key_mask );
}


uint8_t get_key_long( uint8_t key_mask ) {
    return get_key_press( get_key_rpt( key_mask ));
}


void key_init_timer_port( void ) {
    OCR1A = 0x139;          // 625
    TCCR1B = (1<<WGM12) | (1<<CS10) | (1<<CS11); // /64, CTC
    TIMSK |= (1<<OCIE1A);    // Interrupt

    // debug CTC
    //DDRB |= 0x10;
    //TCCR1A = (1<<COM1B0);    // CTC
    KEY_DDR &= ~ALL_KEYS;                // configure key port for input
    KEY_PORT |= ALL_KEYS;                // and turn on pull up resistors
}

void key_wait_times_5ms ( const uint8_t times ) {
    // reset counter to 0 for accurate timing, 
    cli();
    wait_countdown = times;
    TCNT1 = 0; // 
    sei();
    while ( wait_countdown ) {
        sleep_idle();
        // key pressed -> exit current wait
        if ( key_press & ALL_KEYS ) return;
    };
}


