#include "TroykaThermometer.h"

TroykaThermometer::TroykaThermometer(ADC_HandleTypeDef * const hadc):
	_hadc(hadc)
{
	HAL_ADCEx_Calibration_Start(this->_hadc);
}

float TroykaThermometer::getTemperatureC()
{
	static constexpr float VOLTAGE_PER_DISCRETE_STEP =
			this->THERMO_OPERATING_VOLTAGE / this->THERMO_ADC_VALUE_MAX;
	float sensorADC = 0;
	float sensorVoltage = 0.0F;

	for (size_t i = 0; i < this->THERMO_SAMPLE_TIMES; ++i)
		sensorADC += static_cast<float>(this->_get_pin_value());

	sensorADC /= this->THERMO_SAMPLE_TIMES;
	sensorVoltage = sensorADC *	VOLTAGE_PER_DISCRETE_STEP;

	return (sensorVoltage - 0.5) * 100.0;
}

uint16_t TroykaThermometer::_get_pin_value()
{
	uint16_t res;
	HAL_ADC_Start(this->_hadc);
	HAL_ADC_PollForConversion(this->_hadc, this->POLL_FOR_CONVERSION_TIMEOUT);
	res = HAL_ADC_GetValue(this->_hadc);
	HAL_ADC_Stop(this->_hadc);
	return res;
}
