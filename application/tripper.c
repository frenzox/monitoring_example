#include <boards/board.h>
#include <drivers/clock.h>
#include <math.h>
#include <stdlib.h>

#include "fsm.h"
#include "fsm_tripper.h"
#include "tripper.h"

struct tripper {
	fsm *fsm;
	void *input;
	struct tripper_interface *tripper_iface;
	void (*tripper_cb)(void);
	uint16_t hold_off_time;
	uint32_t last_transition_time;
	int8_t error;
};

static struct tripper tripper_pool[TRIPPER_MAX_COUNT];
static uint8_t trippers_in_use = 0;

tripper *tripper_new(struct tripper_interface *interface, void (*tripper_cb)(void), uint16_t hold_off_time)
{
	uint32_t new_tripper_idx = trippers_in_use;
	struct tripper *new_tripper = &tripper_pool[new_tripper_idx++];

	new_tripper->hold_off_time = hold_off_time;
	new_tripper->tripper_iface = interface;
	new_tripper->tripper_cb = tripper_cb;
	new_tripper->fsm = fsm_tripper_new(new_tripper);

	return new_tripper;
}

void tripper_new_input(tripper *t, void *x)
{
	t->input = x;
	fsm_tick(t->fsm);
}

bool tripper_tripped(tripper *t)
{
	int state = fsm_get_current_state(t->fsm);
	if (state == TRIPPER_STATE_TRIPPED) {
		return true;
	} else {
		return false;
	}
}

void tripper_reset(tripper *t)
{
	fsm_send_event(t->fsm, TRIPPER_EVENT_RESET);
}

void tripper_reset_all(void)
{
	for (uint8_t i = 0; i < trippers_in_use; i++) {
		struct tripper *tripper_to_reset = &tripper_pool[i];
		tripper_to_reset->tripper_iface->reset_fn();
	}
}

int8_t tripper_get_error(tripper *t)
{
	return t->error;
}

void tripper_set_hold_off_time(tripper *t, uint16_t time)
{
	t->hold_off_time = time;
}

uint32_t tripper_get_elapsed_hold_off_time(tripper *t)
{
	if (t->last_transition_time == 0) {
		return 0;
	}

	return clock_elapsed_time_ms(t->last_transition_time);
}

void tripper_nominal_on_entry(void *data)
{
	struct tripper *t = data;
	t->last_transition_time = 0;
}

void tripper_nominal_on_tick(void *data)
{
	struct tripper *t = data;

	t->error = t->tripper_iface->evaluate_input_data(t->input);
	if (t->error != 0) {
		fsm_send_event(t->fsm, TRIPPER_EVENT_INPUT_OUT_OF_RANGE);
	}
}

void tripper_hold_on_entry(void *data)
{
	struct tripper *t = data;
	t->last_transition_time = clock_get_tick();
}

void tripper_hold_on_tick(void *data)
{
	struct tripper *t = data;

	if (clock_elapsed_time_ms(t->last_transition_time) >= t->hold_off_time) {
		fsm_send_event(t->fsm, TRIPPER_EVENT_HOLD_TIMEOUT);
		return;
	}

	t->error = t->tripper_iface->evaluate_input_data(t->input);
	if (t->error == 0) {
		fsm_send_event(t->fsm, TRIPPER_EVENT_INPUT_NOMINAL);
		return;
	}
}

void tripper_tripped_on_entry(void *data)
{
	struct tripper *t = data;

	if (t->tripper_cb != NULL) {
		t->tripper_cb();
	}
}
