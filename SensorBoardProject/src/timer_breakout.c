/*
 * timer_breakout.c
 *
 * Created: 5/17/2019 12:22:15 AM
 *  Author: Justin
 */ 

#include "timer_breakout.h"

// Hardware instance of the timer. 
struct tcc_module timer_instance;

tcc_callback_t main_timer_callback;

void timer_callback(struct tcc_module* const module)
{
	system_interrupt_enter_critical_section();
	main_timer_callback(module);
	system_interrupt_leave_critical_section();
}

void configure_timer(uint32_t period_ms, tcc_callback_t callback)
{	
	main_timer_callback = callback;
	
	struct tcc_config config_tcc;
	tcc_get_config_defaults(&config_tcc, TCC0);
	
	// Why is this 1200 and not 12000. I am confused here, but 1200 works. 
	config_tcc.counter.period = 1200 * period_ms;
	config_tcc.counter.clock_prescaler = TCC_CLOCK_PRESCALER_DIV4;
	
	tcc_init(&timer_instance, TCC0, &config_tcc);
	tcc_enable(&timer_instance);
	tcc_register_callback(&timer_instance, timer_callback, TCC_CALLBACK_OVERFLOW);
}

void enable_timer()
{
	tcc_enable_callback(&timer_instance, TCC_CALLBACK_OVERFLOW);
}