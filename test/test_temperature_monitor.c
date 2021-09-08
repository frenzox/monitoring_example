#include <string.h>
#include <unity.h>
#include <math.h>

#include "../application/temperature_monitor.h"
#include "mock_clock.h"
#include "mock_ntc.h"

static int8_t local_fault;

void temperature_trip_callback(int8_t fault)
{
    local_fault = fault;
}

void reset_fault(void)
{
    local_fault = 0;
}

void setUp(void)
{
    temperature_monitor_init(temperature_trip_callback);
}

void tearDown(void)
{
}

static void reset_temperature_monitor(void)
{
    reset_fault();
    ntc_read_celsius_ExpectAndReturn(CONFIG_TEMPERATURE_MONITORING_MAX_THRESHOLD - 2);
    temperature_monitor_reset();
    TEST_ASSERT_EQUAL_HEX(0, local_fault);
}

static void set_test_temperature(uint16_t targetTemperature)
{
    ntc_read_celsius_ExpectAndReturn(targetTemperature);
    clock_get_tick_ExpectAndReturn(0);
    clock_elapsed_time_ms_IgnoreAndReturn(CONFIG_TEMPERATURE_MONITORING_HOLD_OFF_TIME + 1);
    temperature_monitor_run();
}

static void extra_tick_temperature_monitor(void)
{
    ntc_read_celsius_ExpectAndReturn(0);
    clock_get_tick_ExpectAndReturn(0);
    clock_elapsed_time_ms_IgnoreAndReturn(CONFIG_TEMPERATURE_MONITORING_HOLD_OFF_TIME + 1);
    temperature_monitor_run();
}

void test_high_temperature_threshold_trip(void)
{
    reset_temperature_monitor();

    set_test_temperature(CONFIG_TEMPERATURE_MONITORING_MAX_THRESHOLD + 1);

    /* The temperature here doesn't really matter, we just want to make sure the hold-off time
     * has elapsed so the trip decision is made. The tripper checks the time before the new input.
     */
    extra_tick_temperature_monitor();

    TEST_ASSERT_EQUAL_HEX(-1, local_fault);
}

void test_low_temperature_threshold_trip(void)
{
    reset_temperature_monitor();

    set_test_temperature(CONFIG_TEMPERATURE_MONITORING_MIN_THRESHOLD - 1);

    /* The temperature here doesn't really matter, we just want to make sure the hold-off time
     * has elapsed so the trip decision is made. The tripper checks the time before the new input.
     */
    extra_tick_temperature_monitor();

    TEST_ASSERT_EQUAL_HEX(-1, local_fault);
}

void test_normal_operation_no_trip(void)
{
    reset_temperature_monitor();

    set_test_temperature(CONFIG_TEMPERATURE_MONITORING_MIN_THRESHOLD + 10);

    /* The temperature here doesn't really matter, we just want to make sure the hold-off time
     * has elapsed so the trip decision is made. The tripper checks the time before the new input.
     */
    extra_tick_temperature_monitor();

    TEST_ASSERT_EQUAL_HEX(0, local_fault);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_normal_operation_no_trip);
    RUN_TEST(test_low_temperature_threshold_trip);
    RUN_TEST(test_high_temperature_threshold_trip);

    return UNITY_END();
}
