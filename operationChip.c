/*
 * main.c
 *
 * Created: 1/7/2024 8:03:24 AM
 * Author : LongVu
 */ 

#define degree_sysmbol 0xdf
#define F_CPU 8000000UL
#include <avr/io.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h> // Th�m th? vi?n n�y ?? s? d?ng h�m dtostrf
#include <util/delay.h>
#include "DHT11.h"
#include "LCD_16x2.h"

void float_to_string(float value, char* buffer, int decimal_places) {
    // Chuy?n ??i s? th?c sang chu?i k� t? v?i s? ch? s? th?p ph�n x�c ??nh
    dtostrf(value, 6, decimal_places, buffer);
}

float NhietDo = 0, DoAm = 0;

void UART_Init() {
    // set baud: 9600 equivalent to f=8Mhz
    UBRRH = 0;
    UBRRL = 51;
    UCSRA = 0x00;
    UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0); // Set up data frame: 1 bit start - 1 bit stop - no parity - 8 bit frame
    UCSRB = (1 << RXEN) | (1 << TXEN) | (1 << RXCIE);   // Enable rx - tx, and enable interrupt when received data
    sei();
}

unsigned char usart_getchar() {
    while (!(UCSRA & (1 << RXC)))
    ;       // bit RXC tr�n UCSRA cho bi?t qu� tr�nh nh?n k?t th�c hay ch?a
    return UDR; // tr? v? gi� tr? trong thanh ghi d? li?u
}

void usart_putchar(char data) {
    /* Wait for empty transmit buffer */
    while (!(UCSRA & (1 << UDRE))) // ki?m tra bit UDRE tr�n thanh UCRA c� b?ng 0 hay kh�ng, n?u kh�c 0 tr? v? 0 tho�t while
    ;
    /* Put data into buffer, sends the data */
    UDR = data; // ghi gi� tr? l�n thanh ghi d? li?u
}

void usart_write(char *string) {
    int i = 0;
    for (i = 0; i < 255; i++) {
        if (string[i] != 0) {
            usart_putchar(string[i]);
        } else {
            break;
        }
    }
}

int main(void) {
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
    UART_Init(9600);

    char temperature_buffer[8];
    char humidity_buffer[8];

    while(1) {
        DHT11_Read_Data(&DoAm, &NhietDo);

        // Hi?n th? tr�n LCD (gi? nguy�n ph?n n�y n?u mu?n)
        LCD_String_xy(1, 0, "Nhiet Do: ");
        LCD_Char((int)(NhietDo * 10) / 100 + 48);
        LCD_Char(((int)(NhietDo * 10) % 100) / 10 + 48);
        LCD_Char('.');
        LCD_Char((int)(NhietDo * 10) % 10 + 48);
        LCD_Char(degree_sysmbol);
        LCD_String("C");

        LCD_String_xy(2, 0, "Do Am: ");
        LCD_Char((int)(DoAm * 10) / 100 + 48);
        LCD_Char(((int)(DoAm * 10) % 100) / 10 + 48);
        LCD_Char('.');
        LCD_Char((int)(DoAm * 10) % 10 + 48);
        LCD_String("%");
        _delay_ms(500);

        // Truy?n d? li?u nhi?t ?? v� ?? ?m qua UART
        float_to_string(NhietDo, temperature_buffer, 2);  // 2 ch? s? th?p ph�n
        float_to_string(DoAm, humidity_buffer, 2);

        // G?i nhi?t ?? v� ?? ?m qua UART
        usart_write("Nhiet do : ");
        usart_write(temperature_buffer);
        usart_putchar('\n');  // Th�m kho?ng tr?ng gi?a nhi?t ?? v� ?? ?m
        usart_write("Do am : ");
        usart_write(humidity_buffer);
        usart_putchar('\n');  // K?t th�c d�ng
		if (NhietDo >= 20) {
			usart_write("Nhiet do qua gioi han, hay dieu chinh !!!");
    }
	if (DoAm >= 50){
		usart_write("Do am qua gioi han , hay dieu chinh ");
	}
	

    return 0;
}
