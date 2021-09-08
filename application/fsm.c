#include <stdint.h>
#include <stdio.h>

#include <fsm.h>

struct fsm {
	uint32_t id;
	const char *name;
	const fsm_state *all_states;
	const fsm_state *current_state;
	int pending_event;
	void *user_data;
};

static struct fsm fsm_pool[FSM_MAX_COUNT];
static uint8_t fsms_in_use = 0;

static void fsm_try_entry_action(const fsm *sm)
{
	if (sm->current_state->on_entry != NULL) {
		sm->current_state->on_entry(sm->user_data);
	}
}

static void fsm_try_exit_action(const fsm *sm)
{
	if (sm->current_state->on_exit != NULL) {
		sm->current_state->on_exit(sm->user_data);
	}
}

static void fsm_try_tick_action(const fsm *sm)
{
	if (sm->current_state->on_tick != NULL) {
		sm->current_state->on_tick(sm->user_data);
	}
}

static void fsm_try_transition(fsm *sm)
{
	if (sm->pending_event != 0) {
		int next_state_id = sm->current_state->transitions[sm->pending_event];

		sm->pending_event = 0;

		if (next_state_id != 0) {
			fsm_try_exit_action(sm);
			sm->current_state = &sm->all_states[next_state_id];
			fsm_try_entry_action(sm);
		}
	}
}

fsm *fsm_new(const char *name,
	     const fsm_state *state_table,
	     const fsm_state *start_state,
	     void *user_data)
{
	uint8_t new_fsm_idx = fsms_in_use;
	struct fsm *new_fsm = &fsm_pool[new_fsm_idx];

	fsms_in_use++;

	new_fsm->id = new_fsm_idx;
	new_fsm->name = name;
	new_fsm->all_states = state_table;
	new_fsm->current_state = start_state;
	new_fsm->pending_event = 0;

	if (user_data != NULL)
		new_fsm->user_data = user_data;
	else
		new_fsm->user_data = (void *)new_fsm;

	return new_fsm;
}

void fsm_tick(fsm *sm)
{
	fsm_try_tick_action(sm);
	fsm_try_transition(sm);
}

void fsm_send_event(fsm *sm, const int event)
{
	sm->pending_event = event;
}

int fsm_get_current_state(const fsm *sm)
{
	return sm->current_state->id;
}

void fsm_init_entry_action(fsm *sm)
{
	fsm_try_entry_action((const fsm *)sm);
}
