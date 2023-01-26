/*
 * RTG.c
 *
 */
#include "RTG.h"


void rtg_main()
{


//
//	//CHECK_ADC_PROTOCOL();
//	char data[3] = {'B', 'A', '\0'};
//	uint8_t length = 2;
//	uint8_t iter = 1;
//	//CHECK_UART_PROTOCOL(length, (uint8_t*) data, iter);
//
//	char data1[3] = {'D', 'C', '\0'};
//	//CHECK_I2C_PROTOCOL(length, (uint8_t*) data1, iter);
//
//	char data2[3] = {'F', 'E', '\0'};
//	CHECK_SPI_PROTOCOL(length,(uint8_t*) data2, iter);
//
//	//UDP server initialization
//	udpServer_init();

	while (TRUE)
	{
		// Handles the actual reception of bytes from the network interface
		ethernetif_input(&gnetif);
		// Handle which checks timeout expiration
		sys_check_timeouts();
	}
}

