#ifndef UART_SELF_DEFINED_H
#define UART_SELF_DEFINED_H

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"

static volatile uint16_t tx_head = 0, tx_tail = 0;
static volatile uint16_t rx_head = 0, rx_tail = 0;

void UART_Self_Init(void);
void UART_Self_Transmit(uint8_t *pData, uint16_t Size);
void UART_Self_Receive(uint8_t *pData, uint16_t Size);

#endif  /* UART_SELF_DEFINED_H */