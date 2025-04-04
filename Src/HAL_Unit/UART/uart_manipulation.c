#include "uart_manipulation.h"

void UART_Write_Data(UART_HandleTypeDef *huart, uint8_t *buf, int size)
{
    HAL_UART_Transmit_DMA(huart, buf, size);
}

void UART_Init(UART_HandleTypeDef *huart)
{
    __USART2_CLK_ENABLE();

    huart->Instance = USART2;
    huart->Init.BaudRate = 9600;
    huart->Init.WordLength = UART_WORDLENGTH_8B;
    huart->Init.StopBits = UART_STOPBITS_1;
    huart->Init.Parity = UART_PARITY_NONE;
    huart->Init.Mode = UART_MODE_TX_RX;
    huart->Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart->Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(huart);

    /* Peripheral interrupt init*/
    HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
}

void UART_DMA_Init(DMA_HandleTypeDef *hdma_usart2_tx, UART_HandleTypeDef *huart)
{
    /* DMA controller clock enable */
    __DMA1_CLK_ENABLE();
    /* Peripheral DMA init*/
    hdma_usart2_tx->Instance = DMA1_Stream6;
    hdma_usart2_tx->Init.Channel = DMA_CHANNEL_4;
    hdma_usart2_tx->Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_usart2_tx->Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart2_tx->Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart2_tx->Init.PeriphDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart2_tx->Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart2_tx->Init.Mode = DMA_NORMAL;
    hdma_usart2_tx->Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart2_tx->Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    HAL_DMA_Init(hdma_usart2_tx);

    __HAL_LINKDMA(huart,hdmatx,*hdma_usart2_tx);
    /* DMA interrupt init */
    /* DMA1_Channel4_5_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn);
}
