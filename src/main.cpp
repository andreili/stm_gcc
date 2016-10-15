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
	++f;
    if (f > 500)
    {
        IO::cpu_on();
    }
    if (f > 1000)
    {
        IO::cpu_off();
        f = 0;
    }
}
