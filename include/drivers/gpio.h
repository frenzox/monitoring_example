#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

typedef struct gpio_device gpio_device;

enum gpio_state { LOW = 0, HIGH };

void gpio_init(void);
gpio_device *gpio_get_device(uint8_t device_id);
enum gpio_state gpio_get_state(gpio_device *device);
void gpio_set_state(gpio_device *device, enum gpio_state state);
void gpio_toggle_state(gpio_device *device);

#endif /* GPIO_H */
