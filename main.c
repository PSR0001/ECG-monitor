/*
 * main.c
 *
 * Created: 10/18/2022 9:26:08 AM
 *  Author: sunirban
*/ 
#define F_CPU 8000000UL 
//#define USART_BAUDRATE 9600
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)

void UART_init(long USART_BAUDRATE)
{
	UCSRB |= (0 << RXEN) | (1 << TXEN);	/* Turn on transmission and reception */
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1) | (0 << UCSZ2);/* Use 8-bit char size */
	UBRRL = BAUD_PRESCALE;			/* Load lower 8-bits of the baud rate */
	UBRRH = (BAUD_PRESCALE >> 8);		/* Load upper 8-bits*/
}

void UART_TxChar(unsigned char ch)
{
	while (! (UCSRA & (1<<UDRE)));  /* Wait for empty transmit buffer */
	UDR = ch ;
}

void ADC_Init()
{
	DDRA=0x0;			/* Make ADC port as input */
	ADCSRA = 0x87;			/* Enable ADC, fr/128  */
	ADMUX = 0x40;			/* Vref: Avcc, ADC channel: 0 */
	
}

int ADC_Read(char channel)
{
	int Ain,AinLow;
	
	ADMUX=ADMUX|(channel & 0x0f);	/* Set input channel to read */

	ADCSRA |= (1<<ADSC);		/* Start conversion */
	while((ADCSRA&(1<<ADIF))==0);	/* Monitor end of conversion interrupt */
	
	_delay_us(10);
	AinLow = (int)ADCL;		/* Read lower byte*/
	Ain = (int)ADCH*256;		/* Read higher 2 bits and 
					Multiply with weight */
	Ain = Ain + AinLow;				
	return(Ain);			/* Return digital value*/
}

void UART_SendString(const char *str){
	unsigned char j=0;
	
	while (str[j]!=0)		/* Send string till null */
	{
		UART_TxChar(str[j]);
		j++;
	}
}


int main(void)

{	
	UART_init(115200);
	         //make PORTC as output to connect 8 leds
	
	

	ADC_Init();

	int i = 0; // define an integer to save adc read value
	
	char value=0;
	
	while (1)

	{
		//i = ADC_Read(0);   //save adc read value in integ
		
		UART_TxChar('i');
		UART_TxChar('a');
		UART_TxChar('m');
		UART_TxChar('s');
		_delay_us(1000);
		
		
		
	}

}