#include <boards/board_config.h>
#include <drivers/adc.h>
#include <stdint.h>
#include <stm32f3xx_hal_adc.h>

#define GET_ADC_INIT_FUNC(i) &MX_ADC##i##_Init

#define ADC_DEVICE(n, h)                                                     \
{                                                                            \
	.device_id = n, .vendor_init_fn = GET_ADC_INIT_FUNC(n), .handle = &h \
}

#define DEFAULT_SUPPLY_VOLTAGE                (3.3f)
#define ADC_POLL_TIMEOUT_MS                   (1)
#define ADC_REF_VOLTAGE_ADDR                  (0x1FFFF7BA)
#define ADC_12BIT_RESOLUTION                  (4095.0f)
#define ADC_DEVICES_IN_USE                    (sizeof(devices) / sizeof(struct adc_device))
#define ADC_RAW_TO_VOLTAGE(v_supply, raw_value) ((v_supply / ADC_12BIT_RESOLUTION) * (float)raw_value)

struct adc_device {
	uint8_t device_id;
	ADC_HandleTypeDef *handle;
	void (*vendor_init_fn)(void);
};

static struct adc_device devices[] = ADC_DEVICES;
static float supply_voltage;

static uint32_t adc_poll(adc_device *adc, uint32_t channel)
{
	uint32_t value;
	ADC_ChannelConfTypeDef config;

	config.Channel = channel;
	config.Rank = ADC_REGULAR_RANK_1;
	config.SingleDiff = ADC_SINGLE_ENDED;
	config.SamplingTime = ADC_SAMPLETIME_4CYCLES_5;
	config.OffsetNumber = ADC_OFFSET_NONE;
	config.Offset = 0;

	HAL_ADC_ConfigChannel(adc->handle, &config);
	HAL_ADC_Start(adc->handle);
	HAL_ADC_PollForConversion(adc->handle, ADC_POLL_TIMEOUT_MS);

	value = HAL_ADC_GetValue(adc->handle);

	HAL_ADC_Stop(adc->handle);

	return value;
}

/* Public Functions
 * ---------------------------------------------------------------------------------------------- */
void adc_init(uint8_t device_id)
{
	adc_device *device;
	uint32_t ref_voltage;

	supply_voltage = 0.0f;

	for (uint8_t i = 0; i < ADC_DEVICES_IN_USE; i++) {
		if (devices[i].device_id != device_id)
			continue;

		device = &devices[i];
		device->vendor_init_fn();

		HAL_ADCEx_Calibration_Start(device->handle, ADC_SINGLE_ENDED);

		if (supply_voltage < 1) {
			uint32_t cal_voltage = *(uint32_t *)ADC_REF_VOLTAGE_ADDR;
			ref_voltage = adc_poll(device, ADC_CHANNEL_VREFINT);

			float v = DEFAULT_SUPPLY_VOLTAGE *
			          ((float)cal_voltage / (float)ref_voltage);

			supply_voltage = v;
		}
	}
}

adc_device *adc_get_device(uint8_t device_id)
{
	for (uint8_t i = 0; i < ADC_DEVICES_IN_USE; i++)
		if (devices[i].device_id == device_id)
			return &devices[i];

	return NULL;
}

uint32_t adc_read_raw(adc_device *adc, uint32_t channel)
{
	return adc_poll(adc, channel);
}

float adc_read_voltage(adc_device *adc, uint32_t channel)
{
	uint32_t raw_value = adc_poll(adc, channel);

	return ADC_RAW_TO_VOLTAGE(supply_voltage, raw_value);
}
