#include <boards/board.h>
#include <stdbool.h>
#include <stdint.h>

#include "temperature_monitor.h"

static void critical_temperature_reached(int8_t error)
{
	(void)error;

	/* hang */
	while (true) {}
}

int main(void)
{
	board_init();
	temperature_monitor_init(critical_temperature_reached);

	while (true) {
		board_run();
		temperature_monitor_run();
	}
}
