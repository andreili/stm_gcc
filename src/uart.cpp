#include "stm32f10x.h"
#include "uart.h"
#include "init.h"
#include "ISRstm32f10x_md.h"
#include "my_func.h"

#define UART_BRR (HSE * PLL_MUL) / UART_BR

char	UART::m_rx_buf[UART_BUF_SIZE];
int		UART::m_rx_size;
int		UART::m_rx_pos;

char	UART::m_tx_buf[UART_BUF_SIZE];
int		UART::m_tx_size;
int		UART::m_tx_pos;

void UART::init()
{
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN |
					RCC_APB2ENR_IOPAEN;

	USART1->BRR = UART_BRR;
	USART1->CR1 |=	USART_CR1_UE |		// USART1 ON
					USART_CR1_TE |		// TX ON
					USART_CR1_RE |		// RX ON
					USART_CR1_RXNEIE;	// RX Interrupt  ON

	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	GPIOA->CRH &= ~(GPIO_CRH_CNF9 |
					GPIO_CRH_CNF10 |
					GPIO_CRH_MODE10);
	GPIOA->CRH |=	GPIO_CRH_CNF9_1 |
					GPIO_CRH_MODE9_0 |
					GPIO_CRH_CNF10_0;

	NVIC_EnableIRQ(USART1_IRQn);
}

void UART::send_str(const char *str)
{
	send_buf(str, strlen(str) + 1);
}

void UART::send_buf(const char *buf, int size)
{
	m_tx_size = size;
	m_tx_pos = 0;
	memcpy(m_tx_buf, buf, size);
	USART1->CR1 |= USART_CR1_TXEIE;
}

void inline UART::irq_proc()
{
	if (USART1->SR & USART_SR_RXNE)
		recv_data();
	else if (USART1->SR & USART_SR_TXE)
		send_data();
}

void UART::recv_data()
{
	m_rx_buf[m_rx_pos++] = USART1->DR;
	++m_rx_size;
}

void UART::send_data()
{
	USART1->DR = m_tx_buf[m_tx_pos++];
	if (m_tx_pos >= m_tx_size)
		USART1->CR1 &= ~(USART_CR1_TXEIE);
}

void ISR::USART1_IRQ()
{
	UART::irq_proc();
}
