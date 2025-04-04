#ifndef UART_INSTANCE
#define UART_INSTANCE

#include <unistd.h>
#include <stdint.h>
#include "uart_manipulation.h"
#include "stm32f4xx_hal_uart.h"
#include "stm32f4xx_hal_dma.h"

typedef struct {
    void (*uart_init) (UART_HandleTypeDef *huart);
    void (*write) (UART_HandleTypeDef * huart, uint8_t *buf, int size);
    void (*dma_init) (DMA_HandleTypeDef  *hdma_usart2_tx, UART_HandleTypeDef *huart);
} uart_instance;

uart_instance uart2_instance = {
    .dma_init = UART_DMA_Init,
    .uart_init = UART_Init,
    .write = UART_Write_Data
};
#endif