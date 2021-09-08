#include <boards/board.h>
#include <boards/board_config.h>
#include <drivers/adc.h>
#include <drivers/clock.h>
#include <drivers/gpio.h>

void board_init(void)
{
	/* Violation on coding style due to interface with vendor drivers */
	HAL_Init();

	clock_init();
	adc_init(ADC_1);
	gpio_init();
}

void board_run(void) {}
