#pragma once
#include <adc.h>

class TroykaThermometer {
public:
	TroykaThermometer(ADC_HandleTypeDef * const hadc);
	float getTemperatureC();
	~TroykaThermometer() = default;
private:
	uint16_t _get_pin_value();
	static constexpr size_t THERMO_SAMPLE_TIMES = 1U;
	static constexpr uint32_t POLL_FOR_CONVERSION_TIMEOUT = 100U;
	static constexpr size_t THERMO_ADC_VALUE_MAX = 4096U; 			// 12-bit ADC
	static constexpr float THERMO_OPERATING_VOLTAGE = 3.3F; 		// 3V3
	ADC_HandleTypeDef * const _hadc;
};
