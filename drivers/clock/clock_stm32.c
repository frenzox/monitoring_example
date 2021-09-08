#include <boards/board_config.h>
#include <drivers/clock.h>
#include <stdint.h>

/* CubeMX clock configuration function */
extern void SystemClock_Config(void);

void clock_init(void)
{
	SystemClock_Config();
}

uint32_t clock_get_tick(void)
{
	return HAL_GetTick();
}

uint32_t clock_elapsed_time_ms(uint32_t time)
{
	return HAL_GetTick() - time;
}
