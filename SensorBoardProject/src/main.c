
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

// ADC Documentation
// http://ww1.microchip.com/downloads/en/AppNotes/Atmel-42451-SAM-Analog-to-Digital-Converter-ADC-Driver_ApplicationNote_AT11380.pdf

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

#include "can_breakout.h"
#include "adc_breakout.h"

// USART
struct usart_module usart_instance;

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

void configure_pins() {
	
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
	configure_pins();
	configure_usart();
	configure_can();
	configure_adc();
	
	// Enable System Interrupts
	system_interrupt_enable_global();
	
	// Reset the terminal
	printf("\033c");
	
	printf("\rHello, World!\r\n");	
	
	adc_start_read_request();
	
	
	
	// SETUP RX FILTERS HERE!
	
	uint8_t key;
	
	// Echo Server
	while(1) {
		scanf("%c", (char *)&key);
		
		if (key == '\r') {
			printf("\r\n");	
		} else {
			printf("%c", key);		
		}		
		
		adc_start_read_request();
	}
}
