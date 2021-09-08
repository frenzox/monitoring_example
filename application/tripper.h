#ifndef TRIPPER_H_
#define TRIPPER_H_

#include <stdbool.h>
#include <stdint.h>

/* Tripper pool size */
#define TRIPPER_MAX_COUNT 1

struct tripper_interface {
	int8_t (*evaluate_input_data)(void *input_data);
	int8_t (*reset_fn)(void);
};

typedef struct tripper tripper;

tripper *tripper_new(struct tripper_interface *interface,
		     void (*tripper_cb)(void),
		     uint16_t hold_off_time);
void tripper_new_input(tripper *t, void *x);
bool tripper_tripped(tripper *t);
void tripper_reset(tripper *t);
void tripper_reset_all(void);
void tripper_set_hold_off_time(tripper *t, uint16_t time);
int8_t tripper_get_error(tripper *t);
uint32_t tripper_get_elapsed_hold_off_time(tripper *t);

#endif /* TRIPPER_H_ */
