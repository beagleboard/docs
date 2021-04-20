// From: http://git.ti.com/pru-software-support-package/pru-software-support-package/trees/master/examples/am335x/PRU_Hardware_UART

#include <stdint.h>
#include <pru_uart.h>
#include "resource_table_empty.h"

/* The FIFO size on the PRU UART is 16 bytes; however, we are (arbitrarily)
 * only going to send 8 at a time */
#define FIFO_SIZE	16
#define MAX_CHARS	8

void main(void)
{
	uint8_t tx;
	uint8_t rx;
	uint8_t cnt;

	/*  hostBuffer points to the string to be printed */
	char* hostBuffer;
	
	/*** INITIALIZATION ***/

	/* Set up UART to function at 115200 baud - DLL divisor is 104 at 16x oversample
	 * 192MHz / 104 / 16 = ~115200 */
	CT_UART.DLL = 104;
	CT_UART.DLH = 0;
	CT_UART.MDR = 0x0;

	/* Enable Interrupts in UART module. This allows the main thread to poll for
	 * Receive Data Available and Transmit Holding Register Empty */
	CT_UART.IER = 0x7;

	/* If FIFOs are to be used, select desired trigger level and enable
	 * FIFOs by writing to FCR. FIFOEN bit in FCR must be set first before
	 * other bits are configured */
	/* Enable FIFOs for now at 1-byte, and flush them */
	CT_UART.FCR = (0x8) | (0x4) | (0x2) | (0x1);
	//CT_UART.FCR = (0x80) | (0x4) | (0x2) | (0x01); // 8-byte RX FIFO trigger

	/* Choose desired protocol settings by writing to LCR */
	/* 8-bit word, 1 stop bit, no parity, no break control and no divisor latch */
	CT_UART.LCR = 3;

	/* Enable loopback for test */
	CT_UART.MCR = 0x00;

	/* Choose desired response to emulation suspend events by configuring
	 * FREE bit and enable UART by setting UTRST and URRST in PWREMU_MGMT */
	/* Allow UART to run free, enable UART TX/RX */
	CT_UART.PWREMU_MGMT = 0x6001;

	/*** END INITIALIZATION ***/

	/* Priming the 'hostbuffer' with a message */
	hostBuffer = "Hello!  This is a long string\r\n";

	/*** SEND SOME DATA ***/

	/* Let's send/receive some dummy data */
	while(1) {
		cnt = 0;
		while(1) {
			/* Load character, ensure it is not string termination */
			if ((tx = hostBuffer[cnt]) == '\0')
				break;
			cnt++;
			CT_UART.THR = tx;
	
			/* Because we are doing loopback, wait until LSR.DR == 1
			 * indicating there is data in the RX FIFO */
			while ((CT_UART.LSR & 0x1) == 0x0);
	
			/* Read the value from RBR */
			rx = CT_UART.RBR;
	
			/* Wait for TX FIFO to be empty */
			while (!((CT_UART.FCR & 0x2) == 0x2));
		}
	}

	/*** DONE SENDING DATA ***/

	/* Disable UART before halting */
	CT_UART.PWREMU_MGMT = 0x0;

	/* Halt PRU core */
	__halt();
}
