#ifndef _SLEEP_H
#define _SLEEP_H

#define PWRDOWN_PRR (1<<PRTIM1) | (1<<PRTIM0)

void sleep_idle( void );

void sleep_powerdown( void );

#endif // _SLEEP_H
