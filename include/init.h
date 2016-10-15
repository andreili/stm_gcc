#ifndef __INIT__
#define __INIT__

#define F_CPU 		72000000UL
#define HSE 8000000UL
#define APB2_MUL 6UL
#define PLL_MUL 9UL
#define TimerTick	F_CPU/1000-1

void RCCInit(void);
void SystemInit(void);

#endif // __INIT__
