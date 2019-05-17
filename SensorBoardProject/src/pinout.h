/*
 * pinout.h
 *
 * Created: 5/17/2019 1:25:23 AM
 *  Author: Justin
 */ 

#ifndef PINOUT_H_
#define PINOUT_H_

#include <asf.h>

// CAN PIN CONFIGURATION
#define CAN_TX_MUX_SETTING MUX_PA24G_CAN0_TX
#define CAN_TX_PIN PIN_PA24G_CAN0_TX
#define CAN_RX_MUX_SETTING MUX_PA25G_CAN0_RX
#define CAN_RX_PIN PIN_PA25G_CAN0_RX

// ADC PIN CONFIGURATION
#define ADC_AIN0_MUX_SETTING MUX_PA02B_ADC0_AIN0
#define ADC_AIN0_PIN PIN_PA02B_ADC0_AIN0

#define ADC_AIN1_MUX_SETTING MUX_PA03B_ADC0_AIN1
#define ADC_AIN1_PIN PIN_PA03B_ADC0_AIN1

#define ADC_AIN10_MUX_SETTING MUX_PA08B_ADC1_AIN10
#define ADC_AIN10_PIN PIN_PA08B_ADC1_AIN10

#define ADC_AIN11_MUX_SETTING MUX_PA09B_ADC1_AIN11
#define ADC_AIN11_PIN PIN_PA09B_ADC1_AIN11

/**
	Set up the pin configuration for the board.
**/
void configure_pinout();

#endif /* PINOUT_H_ */