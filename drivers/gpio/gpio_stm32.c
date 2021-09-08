#include <boards/board_config.h>
#include <drivers/gpio.h>
#include <stdint.h>
#include <stm32f3xx_hal_gpio.h>

#define GPIO_DEVICE(n, p, i)                                                   \
{                                                                              \
	.device_id = n, .port = p, .pin = i                                       \
}

#define GPIO_DEVICES_IN_USE (sizeof(devices) / sizeof(struct gpio_device))

struct gpio_device {
	uint8_t device_id;
	GPIO_TypeDef *port;
	uint16_t pin;
};

static struct gpio_device devices[] = GPIO_DEVICES;

void gpio_init()
{
	MX_GPIO_Init();
}

gpio_device *gpio_get_device(uint8_t device_id)
{
	for (uint8_t i = 0; i < GPIO_DEVICES_IN_USE; i++) {
		if (devices[i].device_id == device_id) {
			return &devices[i];
		}
	}

	return NULL;
}

enum gpio_state gpio_get_state(gpio_device *device)
{
	return (enum gpio_state)HAL_GPIO_ReadPin(device->port, device->pin);
}

void gpio_set_state(gpio_device *device, enum gpio_state state)
{
	HAL_GPIO_WritePin(device->port, device->pin, (GPIO_PinState)state);
}

void gpio_toggle_state(gpio_device *device)
{
	HAL_GPIO_TogglePin(device->port, device->pin);
}
