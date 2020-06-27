#include "uart0.h"
#include <irq.h>
#include <generated/csr.h>

/*
 * Buffer sizes must be a power of 2 so that modulos can be computed
 * with logical AND.
 */

//#define UART0_POLLING

#ifndef UART0_POLLING

#define UART0_RINGBUFFER_SIZE_RX 128

static char rx_buf[UART0_RINGBUFFER_SIZE_RX];
static volatile unsigned int rx_produce;
static unsigned int rx_consume;

#define UART0_RINGBUFFER_SIZE_TX 128


static char tx_buf[UART0_RINGBUFFER_SIZE_TX];
static unsigned int tx_produce;
static volatile unsigned int tx_consume;

void uart0_isr(void)
{
	unsigned int stat, rx_produce_next;

	stat = uart0_ev_pending_read();

	if(stat & UART0_EV_RX) {
		while(!uart0_rxempty_read()) {
			rx_produce_next = (rx_produce + 1);
			if(rx_produce_next != rx_consume) {
				rx_buf[rx_produce] = uart0_rxtx_read();
				rx_produce = rx_produce_next;
			}
			uart0_ev_pending_write(UART0_EV_RX);
		}
	}

	if(stat & UART0_EV_TX) {
		uart0_ev_pending_write(UART0_EV_TX);
		while((tx_consume != tx_produce) && !uart0_txfull_read()) {
			uart0_rxtx_write(tx_buf[tx_consume]);
			tx_consume = (tx_consume + 1);
		}
	}
}

/* Do not use in interrupt handlers! */
char uart0_read(void)
{
	char c;

	if(irq_getie()) {
		while(rx_consume == rx_produce);
	} else if (rx_consume == rx_produce) {
		return 0;
	}

	c = rx_buf[rx_consume];
	rx_consume = (rx_consume + 1);
	return c;
}

int uart0_read_nonblock(void)
{
	return (rx_consume != rx_produce);
}

void uart0_write(char c)
{
	unsigned int tx_produce_next = (tx_produce + 1);

	if(irq_getie()) {
		while(tx_produce_next == tx_consume);
	} else if(tx_produce_next == tx_consume) {
		return;
	}

	if((tx_consume != tx_produce) || uart0_txfull_read()) {
		tx_buf[tx_produce] = c;
		tx_produce = tx_produce_next;
	} else {
		uart0_rxtx_write(c);
	}
}

void uart0_init(void)
{
	rx_produce = 0;
	rx_consume = 0;

	tx_produce = 0;
	tx_consume = 0;

	uart0_ev_pending_write(uart0_ev_pending_read());
	uart0_ev_enable_write(UART0_EV_TX | UART0_EV_RX);
}

void uart0_sync(void)
{
	while(tx_consume != tx_produce);
}

#else

void uart0_isr(void)
{
}

char uart0_read(void)
{
	char c;
	while (uart0_rxempty_read());
	c = uart0_rxtx_read();
	uart0_ev_pending_write(UART0_EV_RX);
	return c;
}

int uart0_read_nonblock(void)
{
	return (uart0_rxempty_read() == 0);
}

void uart0_write(char c)
{
	while (uart0_txfull_read());
	uart0_rxtx_write(c);
	uart0_ev_pending_write(UART0_EV_TX);
}

void uart0_init(void)
{
	uart0_ev_pending_write(uart0_ev_pending_read());
	uart0_ev_enable_write(UART0_EV_TX | UART0_EV_RX);
}

void uart0_sync(void)
{
	while (uart0_txfull_read());
}

#endif
