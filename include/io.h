#ifndef __IO__
#define __IO__

#include "stm32f10x.h"

#define STATUS_LED_PORT B
#define STATUS_LED_PIN_MODE 3
#define STATUS_LED_PIN_FAULT 4
#define STATUS_LED_PIN_CPU_LOAD 5

#define MODE_NORMAL() GPIOB->BSRR = GPIO_BSRR_BS3
#define MODE_PROGRAM() GPIOB->BSRR = GPIO_BSRR_BR3
#define CPU_LOAD_ON() GPIOB->BSRR = GPIO_BSRR_BS5
#define CPU_LOAD_OFF() GPIOB->BSRR = GPIO_BSRR_BR5
#define FAULT_NORMAL() GPIOB->BSRR = GPIO_BSRR_BS4
#define FAULT_ERROR() GPIOB->BSRR = GPIO_BSRR_BR4

class IO
{
public:
	static void init();

	static void inline cpu_on() { CPU_LOAD_ON(); }
	static void inline cpu_off() { CPU_LOAD_OFF(); }

	static void inline mode_on() { MODE_NORMAL(); }
	static void inline mode_off() { MODE_PROGRAM(); }

	static void inline fault_on() { FAULT_ERROR(); }
	static void inline fault_off() { FAULT_NORMAL(); }
};

#endif // __IO__
