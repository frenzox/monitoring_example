/*
 * Brief: HAL header for G5-plus hardware.
 *
 * Each separate hardware platform must provide this header.
 *
 * Copyright (C) EVBox B.V., All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#ifndef BOARDS_TEST_H
#define BOARDS_TEST_H

#define UNIT_TEST
/* Platform configuration
 * ---------------------------------------------------------------------------------------------- */
#define PLATFORM_NAME_STRING "G5-plus"

#define SYSTEM_CLOCK_FREQ_HZ  ((float)(64 * 1000 * 1000))
#define RELAY_PWM_TIM_FREQ_HZ (1600 * 1000)
#define PRESCALER_PWM_TIM     (SYSTEM_CLOCK_FREQ_HZ / RELAY_PWM_TIM_FREQ_HZ)

/* APB1 is 32MHz */
#define PCLK_FREQ_HZ (32 * 1000 * 1000)

#define LEAKAGE_SENSOR_TIM_FREQ_HZ     SYSTEM_CLOCK_FREQ_HZ
#define LEAKAGE_SENSOR_TIM_TICK_TIME_S ((float)(1.0f / LEAKAGE_SENSOR_TIM_FREQ_HZ))

/* Accordingly to G5Plus Schematics 1ph Relay covers L1 and L2, bit map is 00000110b
 * EU variant has only one relay to cover L1, L2, L3 and N, bit map is 00001111b
 * */
#define RELAY_MAP_1PH (0x06)
#define RELAY_MAP_3PH (0x0F)
#define RELAY_MAP_PE  (0x10)

/*
 * GPIO configuration
 */
#define HEARTBEAT_LED_GPIO            1
#define LEAKAGE_SENSOR_W1_SWITCH_GPIO 2
#define LEAKAGE_SENSOR_W2_SWITCH_GPIO 3
#define LEAKAGE_SENSOR_WT_SWITCH_GPIO 4
#define PE_SENSOR_OUTPUT_GPIO         5
#define PE_SENSOR_SWITCH_GPIO         6
#define RELAY_DRIVER_CS_GPIO          7
#define RELAY_MIRROR_FEEDBACK_GPIO    8
#define RELAY_OPTO_FEEDBACK_L1_GPIO   9
#define RELAY_OPTO_FEEDBACK_L2_GPIO   10
#define RELAY_OPTO_FEEDBACK_L3_GPIO   11
#define RELAY_OPTO_FEEDBACK_N_GPIO    12

/*
 * USART Configuration
 */
#define DEBUG_USART 1
#define COMM_USART  2

#define USART_BUFFER_LENGTH 256

/*
 * ADC Configuration
 */
#define ADC_1 1

/*
 * SPI configuration
 */
#define SPI_3 3

/*
 * Relay driver configuration
 */
#define RELAY_PWM_DEFAULT_PERIOD_TICKS    80 /* 20kHz */
#define RELAY_PWM_SWITCH_DUTY_CYCLE_TICKS RELAY_PWM_DEFAULT_PERIOD_TICKS /* 100% duty cycle */
#define RELAY_PWM_HOLD_DUTY_CYCLE_TICKS   40 /* 50% duty cycle */

/*
 * PE sensor configuration
 */
#define PE_SENSOR_SWITCH_ON_LEVEL 0x0
#define PE_SENSOR_CONNECTED_LEVEL 0x0

/*
 * Leakage sensor configuration
 */
#define LEAKAGE_SENSOR_W1_SWITCH_ON_LEVEL 0x0
#define LEAKAGE_SENSOR_W2_SWITCH_ON_LEVEL 0x0
#define LEAKAGE_SENSOR_WT_SWITCH_ON_LEVEL 0x1

/*
 * Heartbeat LED configuration
 */
#define HEARTBEAT_LED_SWITCH_ON_LEVEL 0x1

/*
 * Flash configuration
 *
 * Here Flash_Device == Partition == group of pages/sectors
 * Note: Some devices refer to pages as sectors due to their larger size.
 *       Some devices have pages/sectors with different sizes, hence we have
 *       to declare each page/sector.
 */
#define FACTORY_DATA_PARTITION 1
#define MEMORY_TEST_PARTITION  2

#endif /* BOARDS_TEST_H */
