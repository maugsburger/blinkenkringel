#ifndef _KEY_H
#define _KEY_H

#define KEY_DDR         DDRD
#define KEY_PORT        PORTD
#define KEY_PIN         PIND
#define KEY0            6
#define ALL_KEYS        (1<<KEY0)

#define REPEAT_MASK     (1<<KEY0)   // repeat: key1, key2
#define REPEAT_START    1000/5         // after 1s
#define REPEAT_NEXT     200/5

volatile uint8_t key_state;      // debounced and inverted key state: 1:pressed
volatile uint8_t key_press;      // key press detect
volatile uint8_t key_rpt;        // key long press and repeat

uint8_t get_key_press( uint8_t key_mask );
uint8_t get_key_rpt( uint8_t key_mask );
uint8_t get_key_short( uint8_t key_mask );
uint8_t get_key_long( uint8_t key_mask );

extern volatile uint8_t wait_countdown;

void key_init_timer_port( void );
void key_wait_times_5ms ( uint8_t times );

#endif  //_KEY_H
