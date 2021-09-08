#ifndef FSM_H_
#define FSM_H_

#include <stdbool.h>
#include <stdint.h>

/* FSM pool size */
#define FSM_MAX_COUNT 12

/* Max number of events that can be defined for an FSM instance */
#define MAX_EVENT_COUNT 10

typedef struct fsm_state {
    int id;
    void (*on_entry)(void *data);
    void (*on_tick)(void *data);
    void (*on_exit)(void *data);
    int transitions[MAX_EVENT_COUNT];
} fsm_state;

typedef struct fsm fsm;

fsm *fsm_new(const char *name,
	     const fsm_state *state_table,
	     const fsm_state *start_state,
	     void *user_data);

void fsm_tick(fsm *sm);
void fsm_send_event(fsm *sm, const int event);
int fsm_get_current_state(const fsm *sm);
void fsm_init_entry_action(fsm *sm);

#endif /* FSM_H */
