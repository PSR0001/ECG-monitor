/********************************
 * ecg_monitor.c				*
 *								*
 * Created: 21-10-2022			*
 * Author : Partha Singha Roy	*
 *								*
 ********************************/

#define F_CPU 8000000UL	
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include "ADC.h"
#include "uart.h"
#include "LiquidCrystal_LCD.h"

//macros
#define ADC_CHANNEL 0
#define LED_REG DDRA
#define LED_PORT PORTA

//Global variable
int adc_value_int=0;
char adc_value_char[10];
uint16_t button_value =0;

//Function Prototype
void interrupt_init();



int main()
{
	//GIE SET
	sei();
	
	//Initialization all the Init function
	UART_init(9600);
	LCD_Init();
	ADC_Init();
	interrupt_init();
		
	//configure the input pins for the Sensor
	DDRB &= ~(1<<DDB0); // LO+
	DDRB &= ~(1<<DDB1); // LO-
	
	//Configure the LED PIN 
	LED_REG |= (1<<1);
	
	// LCD custom char
	//unsigned char Character1[8] = { 0x00, 0x0A, 0x1F, 0x1F, 0x0E, 0x04, 0x00, 0x00 };
		
	//First Time Power On LCD status...
	LCD_Clear();
	LCD_String("Power On");
	_delay_ms(5000);
	//ToDo Add LCD Animation
	
	LCD_Clear();
	LCD_String("Ready to Measure");
	
	while(1){
		
		if (button_value==1){
			
			if((PINB & (1<<PINB0)) || (PINB & (1<<PINB1))){}   
				     
			else{
				//ADC read...
				adc_value_int=ADC_Read(ADC_CHANNEL);
				itoa(adc_value_int,adc_value_char,10); //Convert integer to String 
	
				UART_SendString(adc_value_char);
				_delay_ms(1);
				
				//LCD_String_xy(1,0,adc_value_char);	
				_delay_ms(10);
			}
		}
		else{
			
		}
	}
}

// Interrupt Handling...
ISR(INT0_vect){
	if(button_value == 1){
		button_value=0;
		LED_PORT &= ~(1<<1);
	}
	else{
		button_value=1;
		LED_PORT |= (1<<1);
	}
}



//Function Definition
void interrupt_init(){
	//Enable Interrupt 0
	GICR |= (1<<INT0); //General Interrupt Control Register
	MCUCR |= (1<<ISC01) | (1<<ISC00); // Rising edge pulse
	
}