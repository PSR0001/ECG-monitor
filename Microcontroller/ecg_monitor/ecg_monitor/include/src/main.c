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
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "ADC.h"
#include "uart.h"
#include "LiquidCrystal_LCD.h"

//Global variable
int adc_value_int=0;
char adc_value_char[10];




int main()
{
	// enable global interrupt
	sei();
	//DDRA = 0x04;
	//Initialization all the init function
	UART_init(9600);
	LCD_Init();
	ADC_Init();
	
	
	while(1)
	{
		//PORTA = PORTA | (1<<3);
		LCD_Clear();
		LCD_String("ADC");
		
		//adc read
		adc_value_int=ADC_Read(0);
		itoa(adc_value_int,adc_value_char,10);
		UART_SendString(adc_value_char);
		LCD_String_xy(2,1,adc_value_char);	
		
		_delay_ms(2000);
		
	}
}

//ADC Lib is interrupt based









