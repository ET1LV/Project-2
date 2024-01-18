#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "esp_system.h"
#include <string.h>
#include <stdint.h>

#define M0 12
#define M1 13

#define MY_UART_NUM_1 UART_NUM_0
#define TXD_PIN_1 (GPIO_NUM_1)
#define RXD_PIN_1 (GPIO_NUM_3)

#define MY_UART_NUM_2 UART_NUM_2
#define TXD_PIN_2 (GPIO_NUM_17)
#define RXD_PIN_2 (GPIO_NUM_16)
static const char *TAG = "UART Example";

// Thiết lập uart
void init_uart()
{
    uart_config_t uart_config_1 = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };

    uart_config_t uart_config_2 = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };

    uart_param_config(MY_UART_NUM_1, &uart_config_1);
    uart_set_pin(MY_UART_NUM_1, TXD_PIN_1, RXD_PIN_1, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(MY_UART_NUM_1, 256, 0, 0, NULL, 0);

    uart_param_config(MY_UART_NUM_2, &uart_config_2);
    uart_set_pin(MY_UART_NUM_2, TXD_PIN_2, RXD_PIN_2, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(MY_UART_NUM_2, 256, 0, 0, NULL, 0);
}

void app_main()
{
    init_uart();
    gpio_set_direction(M0, GPIO_MODE_OUTPUT);
    gpio_set_direction(M1, GPIO_MODE_OUTPUT);
    gpio_set_level(M0, 0);
    gpio_set_level(M1, 0);

    uint8_t data[128];
    while (1)
    {

        int length_2 = uart_read_bytes(MY_UART_NUM_2, data, sizeof(data), 350 / portTICK_PERIOD_MS);
        if (length_2 > 0)
    
            // Now 'temperature' contains the integer value of the received data
           ESP_LOGI(TAG,"Data nhan duoc : %s ", data );
        }
    }

