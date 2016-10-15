#include "io.h"

/*#define MODE_NORMAL() GPIO ## STATUS_LED_PORT->BSRR = GPIO_BSRR_BR0
#define MODE_PROGRAM() GPIOB->BSRR = GPIO_BSRR_BS0
#define CPU_LOAD_ON() GPIOB->BSRR = GPIO_BSRR_BS0
#define CPU_LOAD_OFF() GPIOB->BSRR = GPIO_BSRR_BR0*/

void IO::init()
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN |
					RCC_APB2ENR_IOPBEN;

	// status LEDs
	GPIOB->CRL &= ~(GPIO_CRL_CNF3 |
					GPIO_CRL_CNF4 |
					GPIO_CRL_CNF5);
	GPIOB->CRL |=	GPIO_CRL_MODE3_0 |
					GPIO_CRL_MODE4_0 |
					GPIO_CRL_MODE5_0;
	MODE_NORMAL();
	FAULT_NORMAL();
	CPU_LOAD_OFF();
	
	// IOs. Default - as DI, Pull-UP, output 0
	GPIOA->CRL = 	GPIO_CRL_CNF0_1 |
					GPIO_CRL_CNF1_1 |
					GPIO_CRL_CNF2_1 |
					GPIO_CRL_CNF3_1 |
					GPIO_CRL_MODE0_0 |
					GPIO_CRL_MODE1_0 |
					GPIO_CRL_MODE2_0 |
					GPIO_CRL_MODE3_0;
	GPIOA->CRH =	GPIO_CRH_CNF8_1 |
					GPIO_CRH_CNF9_1 |
					GPIO_CRH_CNF10_1 |
					GPIO_CRH_CNF11_1 |
					GPIO_CRH_CNF12_1 |
					GPIO_CRH_CNF13_1 |
					GPIO_CRH_MODE8_0 |
					GPIO_CRH_MODE9_0 |
					GPIO_CRH_MODE10_0 |
					GPIO_CRH_MODE11_0 |
					GPIO_CRH_MODE12_0;
	GPIOA->BSRR =	GPIO_BSRR_BR0 |
					GPIO_BSRR_BR1 |
					GPIO_BSRR_BR2 |
					GPIO_BSRR_BR3 |
					GPIO_BSRR_BR8 |
					GPIO_BSRR_BR9 |
					GPIO_BSRR_BR10 |
					GPIO_BSRR_BR11 |
					GPIO_BSRR_BR12;

	GPIOB->CRH =	GPIO_CRH_CNF12_1 |
					GPIO_CRH_CNF13_1 |
					GPIO_CRH_CNF14_1 |
					GPIO_CRH_CNF15_1 |
					GPIO_CRH_MODE12_0 |
					GPIO_CRH_MODE13_0 |
					GPIO_CRH_MODE14_0 |
					GPIO_CRH_MODE15_0;
	GPIOB->BSRR =	GPIO_BSRR_BR12 |
					GPIO_BSRR_BR13 |
					GPIO_BSRR_BR14 |
					GPIO_BSRR_BR15;

	GPIOA->CRL &= ~(GPIO_CRL_CNF0_1 | GPIO_CRL_CNF1_1);
}
