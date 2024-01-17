/*
 * LCD_16x2_C_file.c
 * 
 *
 */


#include "LCD_16x2.h"						/* Include LCD header file */

void LCD_Enable(void)
{
	CONTROL |= (1 << LCD_EN);  //LCD_EN = 1;
	_delay_us(7);
	CONTROL &= ~(1 << LCD_EN);  //LCD_EN=0;
	_delay_us(50);
}
void LCD_Send4Bit(char Data)
{
	//LCD_D4=Data & 0x01;
	if (Data & 0x01)
	{
		DATA |= (1 << LCD_D4);
	}
	else DATA &= ~(1 << LCD_D4);
	
	//LCD_D5=(Data>>1)&1;
	if ((Data >> 1) & 1)
	{
		DATA |= (1 << LCD_D5);
	}
	else DATA &= ~(1 << LCD_D5);
	//LCD_D6=(Data>>2)&1;
	if ((Data >> 2) & 1)
	{
		DATA |= (1 << LCD_D6);
	}
	else DATA &= ~(1 << LCD_D6);
	//LCD_D7=(Data>>3)&1;
	if ((Data >> 3) & 1)
	{
		DATA |= (1 << LCD_D7);
	}
	else DATA &= ~(1 << LCD_D7);
}

void LCD_Command (char cmd)							/* LCD command write function */
{
	LCD_Send4Bit(cmd >>4);
	LCD_Enable();
	LCD_Send4Bit(cmd);
	LCD_Enable();								/* Wait little bit */
}

void LCD_Char (char char_data)						/* LCD data write function */
{
	CONTROL |= (1 << LCD_RS);//LCD_RS=1;
	LCD_Command(char_data);
	CONTROL &= ~(1 << LCD_RS);//LCD_RS=0 ;								/* Wait little bit */
}

void LCD_Init (void)								/* LCD Initialize function */
{
	LCD_Send4Bit(0x00);
	_delay_ms(20);
	CONTROL &= ~(1 << LCD_RS);//LCD_RS=0;
	CONTROL &= ~(1 << LCD_RW);//LCD_RW=0;
	LCD_Send4Bit(0x03);
	LCD_Enable();
	_delay_ms(5);
	LCD_Enable();
	_delay_us(100);
	LCD_Enable();
	LCD_Send4Bit(0x02);
	LCD_Enable();
	LCD_Command( 0x28 );
	LCD_Command( 0x0C);
	LCD_Command( 0x06 );
	LCD_Command(0x01);
	LCD_Command( 0x02 );
	_delay_ms(2);							/* 8 is for first line and 0 is for 0th position */
}

void LCD_String (char *str)							/* Send string to LCD function */
{
	while (*str)
	{
		LCD_Char(*str);
		str++;
	}
}

void LCD_String_xy (int row, int pos, char *s)	/* Send string to LCD function */
{
	if (row == 1)
	LCD_Command((pos & 0x0F)|0x80);				/* Command of first row and required position<16 */
	else if (row == 2)
	LCD_Command((pos & 0x0F)|0xC0);				/* Command of Second row and required position<16 */
	LCD_String(s);								/* Call LCD string function */
}
void LCD_Clear(void)
{
	LCD_Command(0x01);
	_delay_ms(2);
}