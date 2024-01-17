/*
 * main.c
 *
 * Created: 1/7/2024 8:03:24 AM
 * Author : hdzungx
 */ 

#define degree_sysmbol 0xdf
#define F_CPU 8000000UL
#include <avr/io.h>
#include <string.h>
#include <stdio.h>
#include <util/delay.h>
#include "DHT11.h"
#include "LCD_16x2.h"

float NhietDo = 0, DoAm = 0;


int main(void)
{	
	// Declare your local variables here
	DDRD |= 0xFF;
	PORTD |= 0xAA;
	DDRC |= 0xFF;
	PORTC |= 0x00;
	LCD_Init();                 /* initialize 16x2 LCD*/
	LCD_Clear();
	LCD_String_xy(1,0, "Do An 2");
	LCD_String_xy(2,0, "Nhiet Do - Do Am");
	_delay_ms(500);
	LCD_Clear();
	while(1)
	{	
		DHT11_Read_Data(&DoAm, &NhietDo);
		
		LCD_String_xy(1, 0, "Nhiet Do: ");
		LCD_Char((int)(NhietDo*10) / 100 + 48);
		LCD_Char(((int)(NhietDo*10) % 100) / 10 + 48);
		LCD_Char('.');
		LCD_Char((int)(NhietDo*10) % 10 + 48);
		LCD_Char(degree_sysmbol);
		LCD_String("C");

		LCD_String_xy(2, 0, "Do Am: ");
		LCD_Char((int)(DoAm*10) / 100 + 48);
		LCD_Char(((int)(DoAm*10) % 100) / 10 + 48);
		LCD_Char('.');
		LCD_Char((int)(DoAm*10) % 10 + 48);
		LCD_String("%");
		_delay_ms(500);
	}
	return 0;
}

