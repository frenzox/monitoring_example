#ifndef PRODUCTX_H
#define PRODUCTX_H

#include <stm32f301x8.h>
#include <stm32f3xx_hal.h>

#include "cubemx/Core/Inc/adc.h"
#include "cubemx/Core/Inc/gpio.h"
#include "cubemx/Core/Inc/main.h"

#define BOARD_NAME_STRING "ProductX"

/*
 * GPIO configuration
 */
#define HEARTBEAT_LED_GPIO            1

#define GPIO_DEVICES                                                           \
{                                                                              \
	GPIO_DEVICE(HEARTBEAT_LED_GPIO,                                        \
	            HEARTBEAT_LED_GPIO_Port,                                   \
	            HEARTBEAT_LED_Pin),                                        \
}

/*
 * ADC Configuration
 */
#define ADC_1 1

#define ADC_DEVICES                                                            \
{                                                                              \
	ADC_DEVICE(ADC_1, hadc1),                                              \
}

/*
 * NTC configuration
 */
#define NTC_ADC         ADC_1
#define NTC_ADC_CHANNEL ADC_CHANNEL_11

#endif /* PRODUCTX_H */
