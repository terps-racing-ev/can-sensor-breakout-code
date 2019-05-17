/*
 * pinout.c
 *
 * Created: 5/17/2019 1:25:34 AM
 *  Author: Justin
 */ 

#include "pinout.h"

void configure_pinout() 
{
	struct system_pinmux_config pin_config;
	system_pinmux_get_config_defaults(&pin_config);
	
	// Configure CAN TX/RX Pins
	
	// CAN TX
	pin_config.mux_position = CAN_TX_MUX_SETTING;
	system_pinmux_pin_set_config(CAN_TX_PIN, &pin_config);
	
	// CAN RX
	pin_config.mux_position = CAN_RX_MUX_SETTING;
	system_pinmux_pin_set_config(CAN_RX_PIN, &pin_config);
	
	// Configure ADC AIN Pins
	
	// ADC0, AIN0
	pin_config.mux_position = ADC_AIN0_MUX_SETTING;
	system_pinmux_pin_set_config(ADC_AIN0_PIN, &pin_config);

	// ADC0, AIN1
	pin_config.mux_position = ADC_AIN1_MUX_SETTING;
	system_pinmux_pin_set_config(ADC_AIN1_PIN, &pin_config);
	
	// ADC1, AIN10
	pin_config.mux_position = ADC_AIN10_MUX_SETTING;
	system_pinmux_pin_set_config(ADC_AIN10_PIN, &pin_config);
	
	// ADC1, AIN11
	pin_config.mux_position = ADC_AIN11_MUX_SETTING;
	system_pinmux_pin_set_config(ADC_AIN11_PIN, &pin_config);
}
