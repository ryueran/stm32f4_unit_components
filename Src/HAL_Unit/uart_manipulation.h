#ifndef UART_MANIPULATION_H_
#define UART_MANIPULATION_H_

#include <unistd.h>
#include <stdint.h>
#include "stm32f4xx_hal_rcc.h"
#include "stm32f4xx_hal_dma.h"
#include "stm32f4xx_hal_uart.h"
#include "stm32f4xx_hal_usart.h"

void UART_Write_Data(UART_HandleTypeDef * huart, uint8_t *buf, int size);
void UART_Init(UART_HandleTypeDef *huart);
void UART_DMA_Init(DMA_HandleTypeDef  *hdma_usart2_tx, UART_HandleTypeDef *huart);

#endif