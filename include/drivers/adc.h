#ifndef ADC_H
#define ADC_H

#include <stdint.h>

typedef struct adc_device adc_device;

void adc_init(uint8_t device_id);
adc_device *adc_get_device(uint8_t device_id);
uint32_t adc_read_raw(adc_device *adc, uint32_t channel);
float adc_read_voltage(adc_device *adc, uint32_t channel);

#endif /* ADC_H */
