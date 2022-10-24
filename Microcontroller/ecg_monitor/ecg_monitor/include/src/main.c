/********************************
 * Bluetooth_test.c				*
 *								*
 * Created: 21-10-2022			*
 * Author : Partha Singha Roy	*
 *								*
 ********************************/

#define F_CPU 8000000UL	
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "LiquidCrystal_LCD.h"
#include <stdlib.h>
#include <stdio.h>

char val;



int main()
{
	DDRA = 0x0F;
	UART_init(9600);
	LCD_Init();
	
	while(1)
	{
		PORTA = PORTA | (1<<3);
		LCD_Clear();
		LCD_String("LED ON");
		LCD_String(45);
		
		
		
		UART_SendString("Blue tooth ");
		_delay_ms(2000);
		PORTA = PORTA & (~(1<<3));
		
		LCD_Clear();	
		LCD_String("LED OFF");
		
		
		
		_delay_ms(2000);
	}
}