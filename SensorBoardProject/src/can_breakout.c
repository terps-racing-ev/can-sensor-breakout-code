
#include "can_breakout.h"

// SETTINGS
#define CAN_ID_OFFSET 0x100


// SOME OTHER STUFF
#define CAN_TX_BUFFER_INDEX    0

// Hardware Instance of CAN module
static struct can_module can_instance;

// ...
static volatile uint32_t receive_index_fifo_0 = 0;
static volatile uint32_t receive_index_fifo_1 = 0;

/* 
	Handler for CAN interrupts
	
	Called by API code. 
*/
void CAN0_Handler() {
	
	volatile uint32_t status, i, rx_buffer_index;
	status = can_read_interrupt_status(&can_instance);
	
	if (status & CAN_RX_BUFFER_NEW_MESSAGE) {
		handle_rx_buffer_new_message();
	}
	
	if (status & CAN_RX_FIFO_0_NEW_MESSAGE) {
		handle_rx_fifo_0_new_message();
	}
	
	if (status & CAN_RX_FIFO_1_NEW_MESSAGE) {
		handle_rx_fifo_0_new_message();
	}
	
	printf("CAN Message handler! \n");
	
	// Handle Protocol Errors
	if ((status & CAN_PROTOCOL_ERROR_ARBITRATION) ||
	(status & CAN_PROTOCOL_ERROR_DATA)) {
		
		can_clear_interrupt_status(&can_instance,
		CAN_PROTOCOL_ERROR_ARBITRATION | CAN_PROTOCOL_ERROR_DATA);
		
		printf("Protocol error, please double check the clock in two boards. \r\n\r\n");
	}
}

void configure_can() {
	
	struct can_config config_can;
	can_get_config_defaults(&config_can);
	can_init(&can_instance, CAN0, &config_can);
	
	can_start(&can_instance);
	
	/* Enable Interrupts */
	system_interrupt_enable(SYSTEM_INTERRUPT_MODULE_CAN0);
	can_enable_interrupt(&can_instance,
	CAN_PROTOCOL_ERROR_ARBITRATION | CAN_PROTOCOL_ERROR_DATA);
}

void handle_rx_fifo_0_new_message() {
	
	static struct can_rx_element_fifo_0 rx_element_fifo_0;
	
	can_clear_interrupt_status(&can_instance, CAN_RX_FIFO_0_NEW_MESSAGE);
	can_get_rx_fifo_0_element(&can_instance, &rx_element_fifo_0,
	receive_index_fifo_0);
	can_rx_fifo_acknowledge(&can_instance, 0,
	receive_index_fifo_0);
	receive_index_fifo_0++;
	if (receive_index_fifo_0 == CONF_CAN0_RX_FIFO_0_NUM) {
		receive_index_fifo_0 = 0;
	}
	printf("\n\r Standard message received in FIFO 0. The received data is: \r\n");
	for (uint32_t i = 0; i < rx_element_fifo_0.R1.bit.DLC; i++) {
		printf("  %d",rx_element_fifo_0.data[i]);
	}
	printf("\r\n\r\n");
}

void handle_rx_fifo_1_new_message() {
	
	static struct can_rx_element_fifo_1 rx_element_fifo_1;
	
	can_clear_interrupt_status(&can_instance, CAN_RX_FIFO_1_NEW_MESSAGE);
	can_get_rx_fifo_1_element(&can_instance, &rx_element_fifo_1,
	receive_index_fifo_1);
	can_rx_fifo_acknowledge(&can_instance, 0,
	receive_index_fifo_1);
	receive_index_fifo_1++;
	if (receive_index_fifo_1 == CONF_CAN0_RX_FIFO_1_NUM) {
		receive_index_fifo_1 = 0;
	}
	printf("\n\r Standard message received in FIFO 1. The received data is: \r\n");
	for (uint32_t i = 0; i < rx_element_fifo_1.R1.bit.DLC; i++) {
		printf("  %d",rx_element_fifo_1.data[i]);
	}
	printf("\r\n\r\n");
	
	
}

void handle_rx_buffer_new_message() {
	
	uint32_t rx_buffer_index;
	static struct can_rx_element_buffer rx_element_buffer;
	
	can_clear_interrupt_status(&can_instance, CAN_RX_BUFFER_NEW_MESSAGE);
	for (uint32_t i = 0; i < CONF_CAN0_RX_BUFFER_NUM; i++) {
		if (can_rx_get_buffer_status(&can_instance, i)) {
			rx_buffer_index = i;
			can_rx_clear_buffer_status(&can_instance, i);
			can_get_rx_buffer_element(&can_instance, &rx_element_buffer,
			rx_buffer_index);
			if (rx_element_buffer.R0.bit.XTD) {
				printf("\n\r Extended message received in Rx buffer. The received data is: \r\n");
				} else {
				printf("\n\r Standard message received in Rx buffer. The received data is: \r\n");
			}
			for (i = 0; i < rx_element_buffer.R1.bit.DLC; i++) {
				printf("  %d",rx_element_buffer.data[i]);
			}
			printf("\r\n\r\n");
		}
	}
}


void can_send_standard_message(uint32_t id_value, uint8_t *data) {
	struct can_tx_element tx_element;
	can_get_tx_buffer_element_defaults(&tx_element);
	
	tx_element.T0.reg |= CAN_TX_ELEMENT_T0_STANDARD_ID(id_value);
	tx_element.T1.bit.DLC = 8;
	
	for (uint32_t i = 0; i < 8; i++) {
		tx_element.data[i] = *data;
		data++;
	}

	can_set_tx_buffer_element(&can_instance, &tx_element, CAN_TX_BUFFER_INDEX);
	can_tx_transfer_request(&can_instance, 1 << CAN_TX_BUFFER_INDEX);
}