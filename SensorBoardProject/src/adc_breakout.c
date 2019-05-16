/*
 * adc_breakout.c
 *
 * Created: 5/15/2019 10:44:56 PM
 *  Author: Justin
 */ 

#include <asf.h>
#include "adc_breakout.h"

struct adc_module adc0_instance;
struct adc_module adc1_instance;

volatile bool adc_read_done = false;

uint16_t adc_result_buffer[4];

void adc_start_read_request() {
	uint8_t status = adc_read_buffer_job(&adc0_instance, adc_result_buffer, 4);
	printf("STATUS CODE %d\r\n", status);
}

void adc_complete_callback(struct adc_module *const module) {
	adc_read_done = true;
	
	bool is_busy;
	uint8_t status;
	adc_get_sequence_status(&adc0_instance, &is_busy, status);
	
	printf("ADC READ DONE %d %d\r\n", is_busy, status);
	printf("%d %d %d %d\r\n", adc_result_buffer[0], adc_result_buffer[1], adc_result_buffer[2], adc_result_buffer[3]);
}

void configure_adc1() {
	
	struct adc_config config_adc;
	adc_get_config_defaults(&config_adc);
	
	config_adc.reference = ADC_REFERENCE_INTVCC2;			// VDDANA
	config_adc.resolution = ADC_RESOLUTION_16BIT;			// Oversampling
	config_adc.sampling_time_compensation_enable = true;	// OFFCOMP. sample_length must = 0
	
	adc_init(&adc1_instance, ADC1, &config_adc);
	adc_enable(&adc1_instance);
	
}

void configure_adc0() {
	struct adc_config config_adc;
	adc_get_config_defaults(&config_adc);
	
	/*
	config_adc.clock_prescaler;
	config_adc.clock_source;
	config_adc.correction;
	config_adc.positive_input;
	*/
	config_adc.reference = ADC_REFERENCE_INTVCC2;			// VDDANA
	config_adc.resolution = ADC_RESOLUTION_16BIT;			// Oversampling
	config_adc.sampling_time_compensation_enable = true;	// OFFCOMP. sample_length must = 0
	
	adc_init(&adc0_instance, ADC0, &config_adc);
	adc_enable(&adc0_instance);
}

void configure_adc() {
	
	configure_adc0();
	configure_adc1();
	
	adc_set_master_slave_mode(&adc0_instance, &adc1_instance, ADC_DUAL_MODE_INTERLEAVE);
	adc_enable_positive_input_sequence(&adc0_instance, 
		(1 << 0)| (1 << 1) |(1 << 10) | (1 << 11));
		
	adc_register_callback(&adc0_instance, adc_complete_callback, ADC_CALLBACK_READ_BUFFER);
	adc_enable_callback(&adc0_instance, ADC_CALLBACK_READ_BUFFER);	
}