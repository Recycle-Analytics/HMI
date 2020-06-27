#ifndef __UART0_H
#define __UART0_H

#ifdef __cplusplus
extern "C" {
#endif

#define UART0_EV_TX	0x1
#define UART0_EV_RX	0x2

void uart0_init(void);
void uart0_isr(void);
void uart0_sync(void);

void uart0_write(char c);
char uart0_read(void);
int uart0_read_nonblock(void);

#ifdef __cplusplus
}
#endif

#endif
