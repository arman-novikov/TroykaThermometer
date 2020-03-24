/*
includes:
	<cstdio> (sprintf)
	<cstring> (strlen)
*/
void thermometerTest()
{
  TroykaThermometer thermo(&hadc1);
  while (1) {
	char print_buf[32]{0};
	float temprC = thermo.getTemperatureC();
	auto integral_part = static_cast<int>(temprC);
	auto floating_part = static_cast<int>(temprC/100.0F);

	sprintf(print_buf,
		  "Temperature is %d,%d C", integral_part, floating_part);

	HAL_UART_Transmit(&huart1,
		  (uint8_t*)(print_buf), ::strlen(print_buf), HAL_MAX_DELAY);
	HAL_Delay(1000);
  }
}