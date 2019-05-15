
// Example Code:
// http://asf.atmel.com/docs/latest/samc21/html/asfdoc_sam0_can_basic_use_case.html

// CAN Documentation
// http://asf.atmel.com/docs/latest/samc21/html/group__asfdoc__sam0__can__group.html#ga20f2a0f117dbbcbe5a1195e8b7af5914

// ASF Documentation
// http://ww1.microchip.com/downloads/en/AppNotes/Atmel-42698-ASF-Manual-(SAMC21)_ApplicationNote_AT13526.pdf

// SAM C21 CAN Documentation
// http://ww1.microchip.com/downloads/en/AppNotes/Atmel-42464-SAMC21-CAN-BUS-Firmware_ApplicationNote_AT6493.pdf

// SAM C21 USART Documentation
// http://ww1.microchip.com/downloads/en/AppNotes/Atmel-42118-SAM-Serial-USART-Sercom-USART-Driver_ApplicationNote_AT03256.pdf

// Bugfix for SERCOM5_GCLK_ID_CORE Bug
// https://www.avrfreaks.net/comment/2328706#comment-2328706

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to system_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <asf.h>

#include "breakout_can.h"

// USART
struct usart_module usart_instance;

void configure_usart() {
		struct usart_config config_usart;
		usart_get_config_defaults(&config_usart);
		
		config_usart.baudrate = 9600;
		config_usart.mux_setting = USART_RX_1_TX_0_RTS_2_CTS_3;
		config_usart.pinmux_pad0 = PINMUX_PA16C_SERCOM1_PAD0;
		config_usart.pinmux_pad1 = PINMUX_PA17C_SERCOM1_PAD1;
		config_usart.pinmux_pad2 = PINMUX_PA18C_SERCOM1_PAD2;
		config_usart.pinmux_pad3 = PINMUX_PA19C_SERCOM1_PAD3;
		
		stdio_serial_init(&usart_instance, SERCOM1, &config_usart);
		usart_enable(&usart_instance);
}

int main ()
{
	system_init();
	configure_usart();
	configure_can();
	
	printf("\033c");
	
	printf("\rHello, World!\r\n");	
	
	// SETUP RX FILTERS HERE!
	
	uint8_t key;
	
	while(1) {
		scanf("%c", (char *)&key);
		
		if (key == '\r') {
			printf("\r\n");	
		} else {
			printf("%c", key);		
		}		
	}
}
