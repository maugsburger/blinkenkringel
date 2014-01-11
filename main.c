#include <stdlib.h>
#include <avr/io.h>

int main (void) {
    DDRB = 0xff;
    for(;;) {
        PORTB = 0x00;
        asm volatile ("nop");
        asm volatile ("nop");
        PORTB = 0xff;
    }
}

