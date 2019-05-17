/*
 * adc_breakout.c
 *
 * Created: 5/15/2019 10:44:56 PM
 *  Author: Justin
 */ 

#include "adc_breakout.h"

struct adc_module adc0_instance;
struct adc_module adc1_instance;

volatile bool adc0_read_done = true;
volatile bool adc1_read_done = true;

uint16_t adc_result_buffer[4];

main_adc_callback_t main_adc_callback;

uint8_t adc_start_read_request()
{	
	// Check to make sure ADCs are ready to read
	if(!adc0_read_done &&  !adc1_read_done) {
		return STATUS_BUSY;
	}
	
	// Reset ADC Status
	adc0_read_done = false;
	adc1_read_done = false;	
	
	// Start ADC read requests
	adc_read_buffer_job(&adc0_instance, adc_result_buffer, 2);
	adc_read_buffer_job(&adc1_instance, adc_result_buffer + 2, 2);
	
	return STATUS_OK;
}

void adc0_complete_callback(struct adc_module *const module)
{
	system_interrupt_enter_critical_section();
		
	adc0_read_done = true;
	
	if(adc1_read_done) {
		main_adc_callback(adc_result_buffer);
	}
	
	system_interrupt_leave_critical_section();
}

void adc1_complete_callback(struct adc_module *const module)
{
	system_interrupt_enter_critical_section();
	
	adc1_read_done = true;
	
	if(adc0_read_done) {
		main_adc_callback(adc_result_buffer);
	}
	
	system_interrupt_leave_critical_section();
}

void configure_adc1()
{	
	struct adc_config config_adc;
	adc_get_config_defaults(&config_adc);
	
	config_adc.reference = ADC_REFERENCE_INTVCC2;			// VDDANA
	config_adc.resolution = ADC_RESOLUTION_16BIT;			// Oversampling
	config_adc.sampling_time_compensation_enable = true;	// OFFCOMP. sample_length must = 0
	
	adc_init(&adc1_instance, ADC1, &config_adc);
	adc_enable(&adc1_instance);
	adc_enable_positive_input_sequence(&adc1_instance, (1 << 10) | (1 << 11));
	adc_register_callback(&adc1_instance, adc1_complete_callback, ADC_CALLBACK_READ_BUFFER);
	adc_enable_callback(&adc1_instance, ADC_CALLBACK_READ_BUFFER);	
}

void configure_adc0()
{
	struct adc_config config_adc;
	adc_get_config_defaults(&config_adc);
	
	// TODO: Implement gain and offset correction?
	// config_adc.correction = ??
	// How to implement per-input correction?

	// Not sure if prescaling is necessary. As Timer time decreases, prescaling value 
	// Needs to decrease in order to keep sample time lower than timer period. 	
	config_adc.clock_prescaler = ADC_CLOCK_PRESCALER_DIV16;

	config_adc.reference = ADC_REFERENCE_INTVCC2;			// VDDANA
	config_adc.resolution = ADC_RESOLUTION_16BIT;			// Oversampling
	config_adc.sampling_time_compensation_enable = true;	// OFFCOMP. sample_length must = 0
	
	adc_init(&adc0_instance, ADC0, &config_adc);
	adc_enable(&adc0_instance);
	adc_enable_positive_input_sequence(&adc0_instance, (1 << 0)| (1 << 1));
	adc_register_callback(&adc0_instance, adc0_complete_callback, ADC_CALLBACK_READ_BUFFER);
	adc_enable_callback(&adc0_instance, ADC_CALLBACK_READ_BUFFER);	
}

void configure_adc(main_adc_callback_t callback) 
{
	main_adc_callback = callback;
	configure_adc0();
	configure_adc1();
}