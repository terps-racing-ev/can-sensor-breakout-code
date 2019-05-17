/*
 * adc_breakout.h
 *
 * Created: 5/15/2019 10:46:02 PM
 *  Author: Justin
 */ 

#ifndef ADC_BREAKOUT_H_
#define ADC_BREAKOUT_H_

#include <asf.h>

/**
	Callback type for the ADC. 
**/
typedef void (*main_adc_callback_t)(uint16_t* const result);

/**
	Initialize the ADC.
	
	callback: Function to call when ADC finishes sampling. 
**/
void configure_adc(main_adc_callback_t callback);

/**
	Begin sampling the ADC inputs. 
**/
uint8_t adc_start_read_request();

#endif /* ADC_BREAKOUT_H_ */