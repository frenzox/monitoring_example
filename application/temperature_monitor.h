#ifndef TEMPERATURE_MONITOR_H
#define TEMPERATURE_MONITOR_H

#include <stdint.h>

void temperature_monitor_init(void (*callback)(int8_t fault));
void temperature_monitor_run(void);
int8_t temperature_monitor_reset(void);

#endif /* TEMPERATURE_MONITOR_H */
