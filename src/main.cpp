#include <stdio.h>
#include "uart.h"
#include "io.h"
#include "ISRstm32f10x_md.h"

int32_t f = 0;

int main()
{
	f = 0;
	UART::send_str("Hello world!~\n\r");
	while (1)
	{}
}

void ISR::SysTickTimer()
{
	switch (f++)
	{
	case 0:
		IO::cpu_on();
		break;
	case 50:
		IO::cpu_off();
		break;
	case 1000:
		f = 0;
		break;
	}
}
