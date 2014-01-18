#ifndef _LED_H
#define _LED_H

// intensity levels:
// nr of total cycles (looping 0…LED_CYCLES-1)
#define LED_CYCLES   64
// nr of cycles led is on (max LED_CYCLES/2-1)
#define LED_INTENS_4 30
#define LED_INTENS_3 25
#define LED_INTENS_2 13
#define LED_INTENS_1 3

// led port (always 0-3!)
#define LED_PORT PORTD
#define LED_DDR  DDRD

#define PLED_RED    5
#define PLED_GREEN  4
#define PLED_PORT   PORTD
#define PLED_DDR    DDRD


inline void pled_off( uint8_t mask ) {
    PLED_PORT &= ~mask;
}
inline void pled_on( uint8_t mask ) {
    PLED_PORT |= mask;
}
inline void pled_toggle( uint8_t mask ) {
    PLED_PORT ^= mask;
}

volatile uint8_t led_pwm_cycle;

/* mode:
 * 4 4-bit nibbles: min, low-med, high-med, on (default max)
 * minimum brightness set will be used
 */
volatile uint8_t _led_mode_a;
volatile uint8_t _led_mode_b;

volatile uint8_t led_lum;

void led_set_mode_r( uint8_t l12_mode, uint8_t l34_mode, uint8_t pos);

void led_set_mode( uint8_t l1_mode, uint8_t l2_mode,
        uint8_t l3_mode, uint8_t l4_mode);

void led_start_timer0( void );
void led_init_timer_port( void );

ISR (TIMER0_COMPA_vect);

#endif // _LED_H
