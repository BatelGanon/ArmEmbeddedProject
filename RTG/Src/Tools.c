#include "RTG.h"
#include <stdbool.h>
#include <udp.h>

#define BUFFER_LEN   5
#define INIT_ZERO    0
#define MSG_SIZE     256
#define Timer        1
#define UART         2
#define SPI          4
#define I2C          8
#define ADC_          16

// structure for unpacking
typedef struct packet{
	uint32_t  id;
	uint8_t   per;
	uint8_t   iter;
	uint8_t   size;
	char*     msg;
}Packet_t;

// global helper variable
uint8_t result;
Packet_t pack;
uint8_t msg_buffer[MSG_SIZE] = {INIT_ZERO};


// callbak will got as we get a packet on lwip
void udp_receive_callback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port)
{
	// Get the IP of the Client
	//const char* remoteIP = ipaddr_ntoa(addr);
	char buf[BUFFER_LEN] = {'\0'};

	// allocate pbuf from RAM
	struct pbuf *txBuf = pbuf_alloc(PBUF_TRANSPORT, p->len, PBUF_RAM);

	// fill the pack with the data we got from remote side
	pack.id = *(uint32_t *)(p->payload + 0);
	pack.per = *(uint8_t *)(p->payload + 4);
	pack.iter = *(uint8_t *)(p->payload + 5);
	pack.size = *(uint8_t *)(p->payload + 6);
	memcpy(msg_buffer, p->payload + 7, p->tot_len - 7);
	pack.msg = (char*)msg_buffer;


	// switch case - send to the relevant function
	// from pack.per 1.Timer 2.UART 4.SPI 8.I2C 16.ADC
	// and save the return from the function in result var
	switch(pack.per)
	{
		case Timer:
			result = CheckTIMER(pack.iter);
			break;
		case UART:
			result = CheckUART(pack.size,pack.msg, pack.iter);
			break;

		case SPI:
			result = CheckSPI(pack.size, pack.msg, pack.iter);
			break;

		case I2C:
			result = CheckI2C(pack.size, pack.msg, pack.iter);
			break;

		case ADC_:
			result = CheckADC(pack.iter);
			break;
	}

	// reload the id and result to buffer
	*(uint8_t*)(buf + 0) = result;
	*(uint32_t*)(buf + 1) = pack.id;

	// copy the data into the buffer
	pbuf_take(txBuf, buf, BUFFER_LEN);

	//Connect to the remote client
	udp_connect(upcb, addr, port);

	//Send a Reply to the Client
	udp_send(upcb, txBuf);

	//free the UDP connection, so we can accept new clients
	udp_disconnect(upcb);

	//Free the p_tx buffer
	pbuf_free(txBuf);

	//Free the p buffer
	pbuf_free(p);

}

void udpServer_init(void) {

	// UDP Control Block structure
   struct udp_pcb* upcb = udp_new();
   err_t err = udp_bind(upcb, &gnetif.ip_addr, SERVER_PORT);  // 7 is the server UDP port

   /* 3. Set a receive callback for the upcb */
   if (err == ERR_OK) {
	   udp_recv(upcb, udp_receive_callback, NULL);
   }
   else {
	   udp_remove(upcb);
   }
}

// printf
int __io_putchar(int ch) {
	HAL_UART_Transmit(UART_DEBUG, (uint8_t*) &ch, 1, 0xFFFF);
	return ch;
}

int _write(int file, char *ptr, int len) {
	HAL_UART_Transmit(UART_DEBUG, (uint8_t*) ptr, len, 0xFFFF);
	return len;
}

// scanf
int __io_getchar(void) {
	uint8_t ch = 0;
	HAL_UART_Receive(UART_DEBUG, &ch, 1, HAL_MAX_DELAY);
	HAL_UART_Transmit(UART_DEBUG, &ch, 1, HAL_MAX_DELAY);
	return ch;
}

int _read(int file, char *ptr, int len) {
	int DataIdx = 0;
	char ch;
	//int counter = 0;
	for (; DataIdx < len; DataIdx++) {
		ch = __io_getchar();
		*ptr = ch;
		ptr++;
		if (ch == CARRIAGE_RETURN || ch == LINE_FEED) {
			*(ptr) = 0;
			break;
		}
	}
	return DataIdx + 1;
}
