/*
 * timer_breakout.h
 *
 * Created: 5/17/2019 12:22:26 AM
 *  Author: Justin
 */ 

#ifndef TIMER_BREAKOUT_H_
#define TIMER_BREAKOUT_H_

#include <asf.h>

/**
	Initialize the timer. 
	
	period_ms: Period in milliseconds of the timer.
	callback: Function to call when timer fires.  
**/
void configure_timer(uint32_t period_ms, tcc_callback_t callback);

/**
	Start the timer. 
**/
void enable_timer();

#endif /* TIMER_BREAKOUT_H_ */