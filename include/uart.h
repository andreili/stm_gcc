#ifndef __UART__
#define __UART__

#define UART_BR 115200
#define UART_BUF_SIZE 1024

class UART
{
public:
	static void init();
	static void send_str(const char *str);
	static void send_buf(const char *buf, int size);

	static void irq_proc();
private:
	static void recv_data();
	static void send_data();

	static char		m_rx_buf[UART_BUF_SIZE];
	static int		m_rx_size;
	static int		m_rx_pos;

	static char		m_tx_buf[UART_BUF_SIZE];
	static int		m_tx_size;
	static int		m_tx_pos;
};

#endif // __UART__
