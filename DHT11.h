#ifndef DHT11_H_					/* Define library H file if not defined */
#define DHT11_H_


#define F_CPU 8000000UL					/* Define CPU Frequency e.g. here its 8MHz */
#include <avr/io.h>						/* Include AVR std. library file */

#define DHT_PIN 0
#define DHT_DDR DDRA
#define DHT_OUTPUT PORTA
#define DHT_INPUT PINA

void DHT_GPIO_Write(uint8_t state);
int DHT_GPIO_Read();
void DHT11_Init();
int DHT11_Read();
void DHT11_Read_Data(float *humi, float *temp);
#endif
