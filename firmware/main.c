#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <irq.h>
#include <uart.h>
#include <console.h>
#include <generated/csr.h>

#include "logic_game.c"
#include "uart0/uart0.c"

static char *readstr(void)
{
	char c[2];
	static char s[64];
	static int ptr = 0;

	if(readchar_nonblock()) {
		c[0] = readchar();
		c[1] = 0;
		switch(c[0]) {
			case 0x7f:
			case 0x08:
				if(ptr > 0) {
					ptr--;
					putsnonl("\x08 \x08");
				}
				break;
			case 0x07:
				break;
			case '\r':
			case '\n':
				s[ptr] = 0x00;
				putsnonl("\n");
				ptr = 0;
				return s;
			default:
				if(ptr >= (sizeof(s) - 1))
					break;
				putsnonl(c);
				s[ptr] = c[0];
				ptr++;
				break;
		}
	}

	return NULL;
}

static char *get_token(char **str)
{
	char *c, *d;

	c = (char *)strchr(*str, ' ');
	if(c == NULL) {
		d = *str;
		*str = *str+strlen(*str);
		return d;
	}
	*c = 0;
	d = *str;
	*str = c+1;
	return d;
}

static void prompt(void)
{
	printf("RUNTIME>");
}

static void help(void)
{
	puts("Available commands:");
	puts("help                            - this command");
	puts("reboot                          - reboot CPU");
	puts("1                               - Start game");
	puts("2                               - Initialize screen");
	puts("3                               - fill screen");
	puts("4                               - Serial loop");
	puts("5                               - Print text");
}

static void reboot(void)
{
	ctrl_reset_write(1);
}

static void gameStart(void)
{   
    lcd_initialize();

	while(1) {
		game();
	}
}

static void initScreen(void)
{
    puts("LCD initialization");
    lcd_initialize();
}

static void fill(void)
{
    fillScreen();
}

static void console_service(void)
{
	char *str;
	char *token;

	str = readstr();
	if(str == NULL) return;
	token = get_token(&str);
	if(strcmp(token, "help") == 0)
		help();
	else if(strcmp(token, "reboot") == 0)
		reboot();
	else if(strcmp(token, "1") == 0)
		gameStart();
	else if(strcmp(token, "2") == 0)
		initScreen();
	else if(strcmp(token, "3") == 0)
		fill();
	else if(strcmp(token, "4") == 0){
		while(1){
			puts("HOLA MUNDO");
			busy_wait(1000);
			}
		}
	else if(strcmp(token, "5") == 0){
		initScreen();
		fill();
	    printCharacter('!', 10, 10, 0x7bef, 0x86c0);
	    printCharacter('A', 12, 10, 0x0BB0, 0x86c0);
	    printCharacter('a', 14, 10, 0xce59, 0x86c0);
	    printCharacter('2', 16, 10, 0x0BB0, 0x86c0);
	}
	prompt();
}

int main(void)
{
    puts("\nHuman machine interface TestBench ");
	irq_setmask(0);
	irq_setie(1);
	uart_init();

	buttons_ev_enable_write(0xff);
	buttons_ev_pending_write(0xff);
	irq_setmask(irq_getmask() | (1<< 4));

	puts("\nHuman machine interface TestBench "__DATE__" "__TIME__"\n");
	help();
	prompt();

	while(1) {
		console_service();
	}

	return 0;
}
