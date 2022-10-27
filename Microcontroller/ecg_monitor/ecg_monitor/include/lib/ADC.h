/*
 * ADC.h
 *
 * Created: 24-10-2022 
 *  Author: Partha Singha Roy
 */ 


#ifndef ADC_H_
#define ADC_H_

/****
*   ADC.h is interrupt based adc is used.
****/
#include <stdint.h>




void ADC_Init()
{
	/*ADCSRA = 0b11100011;	// 0xE3	// Enable ADC, Prescaler= 8 crystal use 8mhz so 8MHz/8 = 1MHz  
	ADMUX = 0x40;			// V ref: A vcc, ADC channel: 1 */

	ADCSRA|= (1<<ADEN)  | (1<<ADPS1) | (1<<ADPS0); //ADC Enable, Set Pre scalar 8, Local Interrupt Enable
	ADMUX|=(1<<REFS0); //Ref. voltage set to AVcc
}


int ADC_Read(char channel)
{
	int Ain,AinLow;
	
	ADMUX=ADMUX|(channel & 0x0f);	// Set input channel to read 

	ADCSRA |= (1<<ADSC);		// Start conversion 
	while((ADCSRA&(1<<ADIF))==0);	// Monitor end of conversion interrupt 
	
	_delay_us(12);
	AinLow = (int)ADCL;		// Read lower byte
	Ain = (int)ADCH*256;		// Read higher 2 bits and Multiply with weight 
	
	Ain = Ain + AinLow;				
	return(Ain);			// Return digital value
}




#endif /* ADC_H_ */