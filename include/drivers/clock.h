#ifndef CLOCK_H
#define CLOCK_H

#include <stdint.h>

void clock_init(void);
uint32_t clock_get_tick(void);
uint32_t clock_elapsed_time_ms(uint32_t time);

#endif /* CLOCK_H */
