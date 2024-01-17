/*
 * LCD_16x2.h
 *
 *
 */

#ifndef LCD_16x2_H_					/* Define library H file if not defined */
#define LCD_16x2_H_

#define F_CPU 8000000UL					/* Define CPU Frequency e.g. here its 8MHz */
#include <avr/io.h>						/* Include AVR std. library file */
#include "util/delay.h"

#define LCD_RS 6
#define LCD_RW 5
#define LCD_EN 7
#define LCD_D4 4           //Truyen du lieu qua 4 chan
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7
#define DATA PORTC
#define CONTROL PORTD

void LCD_Enable(void);
void LCD_Send4Bit(char Data);
void LCD_Command(char command);
void LCD_Clear();
void LCD_Init();
void LCD_Char(char Data);
void LCD_String(char *s);
void LCD_String_xy (int x,int y,char* s);	
#endif									/* LCD_16x2_H_ */