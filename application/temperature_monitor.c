#include <drivers/ntc.h>
#include <stddef.h>
#include <stdint.h>

#include "temperature_monitor.h"
#include "tripper.h"

static void (*temperature_monitor_cb)(int8_t fault);

struct temperature_tripper_input {
	int8_t temperature;
	int8_t min_threshold;
	int8_t max_threshold;
};

static tripper *temperature_monitor_tripper = NULL;

static int8_t evaluate_inputs(void *input_data)
{
	struct temperature_tripper_input *input = (struct temperature_tripper_input*)input_data;

	if (input->temperature > input->max_threshold || input->temperature < input->min_threshold)
		return -1;

	return 0;
}

static int8_t reset_tripper(void)
{
	int8_t result;
	struct temperature_tripper_input input = {
		.temperature = ntc_read_celsius(),
		.min_threshold = CONFIG_TEMPERATURE_MONITORING_MIN_THRESHOLD + 1,
		.max_threshold = CONFIG_TEMPERATURE_MONITORING_MAX_THRESHOLD - 1
	};

	result = evaluate_inputs(&input);

	if (result == 0)
		tripper_reset(temperature_monitor_tripper);

	return result;
}

void temperature_monitor_init(void (*callback)(int8_t fault))
{
	temperature_monitor_cb = callback;
	static struct tripper_interface temperature_monitor_impl_tripper = {
		.evaluate_input_data = evaluate_inputs,
		.reset_fn = reset_tripper,
	};

	temperature_monitor_tripper = tripper_new(&temperature_monitor_impl_tripper,
						  NULL,
						  CONFIG_TEMPERATURE_MONITORING_HOLD_OFF_TIME);
}

void temperature_monitor_run(void)
{
	struct temperature_tripper_input input = {
		.temperature = ntc_read_celsius(),
		.min_threshold = CONFIG_TEMPERATURE_MONITORING_MIN_THRESHOLD,
		.max_threshold = CONFIG_TEMPERATURE_MONITORING_MAX_THRESHOLD
	};

	tripper_new_input(temperature_monitor_tripper, &input);

	if (tripper_tripped(temperature_monitor_tripper)) {
		temperature_monitor_cb(tripper_get_error(temperature_monitor_tripper));
	}
}

int8_t temperature_monitor_reset(void)
{
	return reset_tripper();
}
