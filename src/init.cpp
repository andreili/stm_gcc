#include "io.h"
#include "init.h"
#include "uart.h"
#include "ISRstm32f10x_md.h"

int main();

void RCCInit(void)
{
	NVIC_EnableIRQ(RCC_IRQn);
	/* Enable HSE */ 
	RCC->CR =	RCC_CR_HSEON | 
				RCC_CR_CSSON;// |
				//RCC_CR_HSEBYP;
	/* Wait till HSE is ready and if Time out is reached exit */
	while ((RCC->CR & RCC_CR_HSERDY) != RCC_CR_HSERDY) {}
	
	/* Enable Prefetch Buffer */
	FLASH->ACR |= FLASH_ACR_PRFTBE;
	/* Flash 2 wait state */
	FLASH->ACR &= ~FLASH_ACR_LATENCY;
	FLASH->ACR |= FLASH_ACR_LATENCY_2;  
	
	/* HCLK = SYSCLK */
	RCC->CFGR |=	RCC_CFGR_HPRE_DIV1 |
					RCC_CFGR_PPRE2_DIV1 |	/* PCLK2 = HCLK */
					RCC_CFGR_PPRE1_DIV2;	/* PCLK1 = HCLK */
	/*  PLL configuration: PLLCLK = HSE * 9 = 72 MHz */
	RCC->CFGR &= ~(RCC_CFGR_PLLSRC | 
					RCC_CFGR_PLLXTPRE | 
					RCC_CFGR_PLLMULL);
	RCC->CFGR |= RCC_CFGR_PLLSRC_HSE | 
				 RCC_CFGR_PLLMULL9;
	
	/* Enable PLL */
	RCC->CR |= RCC_CR_PLLON;
	/* Wait till PLL is ready */
	while ((RCC->CR & RCC_CR_PLLRDY) != RCC_CR_PLLRDY) {}
	
	/* Select PLL as system clock source */
	RCC->CFGR &= ~(RCC_CFGR_SW);
	RCC->CFGR |= RCC_CFGR_SW_PLL; 

	/* Wait till PLL is used as system clock source */
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_1) {}
}

void SystemInit (void)
{
	RCC->CR = 0;
	RCC->CFGR = 0;
	/* Disable all interrupts and clear pending bits  */
	RCC->CIR = 0x009F0000;

	__enable_fault_irq();
	__enable_irq();
	RCCInit();
	IO::init();
	SysTick_Config(TimerTick);
	UART::init();

#ifdef VECT_TAB_SRAM
  //SCB->VTOR = SRAM_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal SRAM. */
#else
  //SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal FLASH. */
#endif 
}

void ISR::Reset()
{
    SystemInit();
    main();
}
