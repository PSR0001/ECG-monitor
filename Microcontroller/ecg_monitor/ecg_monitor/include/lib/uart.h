/*
 * uart.h
 *
 * Created: 24-10-2022 
 *  Author: Partha Singha Roy
 */ 


#ifndef UART_H_
#define UART_H_
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

void UART_init(long USART_BAUDRATE)
{
	UCSRB |= (1 << RXEN) | (1 << TXEN);
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
	UBRRL = BAUD_PRESCALE;
	UBRRH = (BAUD_PRESCALE >> 8);
}

unsigned char UART_RxChar()
{
	while ((UCSRA & (1 << RXC)) == 0);
	return(UDR);
}

void UART_TxChar(char ch)
{
	while (! (UCSRA & (1<<UDRE)));
	UDR = ch; // 8bit uint8_t
}


// Testing Function
void UART_TxInt(uint8_t in)
{
	while (! (UCSRA & (1<<UDRE)));
	UDR = in;
}
void UART_SendString(uint8_t *str)
{
	uint8_t j=0;
	
	while (str[j]!=0)
	{
		UART_TxInt(str[j]);
		j++;
	}
}

//============================================

void UART_SendString(char *str)
{
	unsigned char j=0;
	
	while (str[j]!=0)
	{
		UART_TxChar(str[j]);
		j++;
	}
}

#endif /* UART_H_ */