/*
 * LiquidCrystal_LCD.h
 *
 * Created: 24-10-2022 
 *  Author: Partha Singha Roy
 */ 

#ifndef LIQUIDCRYSTAL_LCD_H_
#define LIQUIDCRYSTAL_LCD_H_

// Atmega16 PORT Initialization
#define LCD_Dir  DDRC			// Define LCD data port direction 
#define LCD_Port PORTC			// Define LCD data port 
#define RS PC0					// Define Register Select pin 
#define EN PC1 					// Define Enable signal pin 

// LCD Hex Code 
#define LCD_Mode 0x02					//send for 4 bit initialization of LCD  
#define LCD_Matrix 0x28					//2 line, 5*7 matrix in 4-bit mode
#define LCD_Cursor_Off  0xC				//Display on cursor off
#define LCD_Cursor_Increment 0x06		//Increment cursor (shift cursor to right)
#define LCD_Clear_Screen 0x01			//Clear display screen
#define LCD_Cursor_Home 0x80			//Cursor at home position 

#define Atmega_Port_Init 0xFF			//PORT 7:0

void LCD_Command( unsigned char cmnd )
{
	LCD_Port = (LCD_Port & 0x0F) | (cmnd & 0xF0);		// Sending upper nibble 
	LCD_Port &= ~ (1<<RS);								// RS=0, command reg. 
	LCD_Port |= (1<<EN);								// Enable pulse 
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);

	_delay_us(200);

	LCD_Port = (LCD_Port & 0x0F) | (cmnd << 4);			// Sending lower nibble
	LCD_Port |= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);
	_delay_ms(2);
}

void LCD_Char( unsigned char data )
{
	LCD_Port = (LCD_Port & 0x0F) | (data & 0xF0);		// ending upper nibble 
	LCD_Port |= (1<<RS);								// RS=1, data reg. 
	LCD_Port|= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);

	_delay_us(200);

	LCD_Port = (LCD_Port & 0x0F) | (data << 4);		// Sending lower nibble
	LCD_Port |= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);
	_delay_ms(2);
}

void LCD_Init (void)								// LCD Initialize function 
{
	LCD_Dir = Atmega_Port_Init;						// Make LCD port direction as o/p 
	_delay_ms(20);									// LCD Power ON delay always >15ms 
	LCD_Command(LCD_Mode);								
	LCD_Command(LCD_Matrix);							
	LCD_Command(LCD_Cursor_Off);					
	LCD_Command(LCD_Cursor_Increment);				
	LCD_Command(LCD_Clear_Screen);							
	_delay_ms(2);
}

void LCD_String (char *str)							/* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++)							/* Send each char of string till the NULL */
	{
		LCD_Char (str[i]);
	}
}

/*
* Function Name : LCD_Clear
* Arguments     : char row, char pos, char *str
* Return	    : none
* Return type   : none
*/
void LCD_String_xy (char row, char pos, char *str)	/* Send string to LCD with xy position */
{
	if (row == 0 && pos<16)
		LCD_Command((pos & 0x0F)|0x80);					/* Command of first row and required position<16 */
	else if (row == 1 && pos<16)
		LCD_Command((pos & 0x0F)|0xC0);					/* Command of first row and required position<16 */
	LCD_String(str);								/* Call LCD string function */
}

/*
* Function Name : LCD_Clear
* Arguments     : none
* Return	    : none
* Return type   : none
*/
void LCD_Clear()
{
	LCD_Command (LCD_Clear_Screen);
	_delay_ms(2);
	LCD_Command (LCD_Cursor_Home);		
}

#endif /* LIQUIDCRYSTAL_LCD_H_ */