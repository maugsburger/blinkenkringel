#include <avr/sleep.h>
#include "sleep.h"

void sleep_idle( void ){
    set_sleep_mode(SLEEP_MODE_IDLE);
    sleep_mode();   
}

void sleep_powerdown( void ){
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_mode();
}
