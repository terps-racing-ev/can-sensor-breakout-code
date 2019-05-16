/*
 * breakout_can.h
 *
 * Created: 5/15/2019 1:16:29 AM
 *  Author: Justin
 */ 


#ifndef BREAKOUT_CAN_H_
#define BREAKOUT_CAN_H_

#include <asf.h>

void handle_rx_fifo_0_new_message();
void handle_rx_fifo_1_new_message();
void handle_rx_buffer_new_message();

/** 
	Initialize the CAN0 hardware module. 
**/
void configure_can();

/**
	Send a standard message over the CAN network.
	
	id_value: The ID of the CAN message to send. 
	
	data: The 8-byte buffer of data to send. 
**/
void can_send_standard_message(uint32_t id_value, uint8_t *data);


#endif /* BREAKOUT_CAN_H_ */