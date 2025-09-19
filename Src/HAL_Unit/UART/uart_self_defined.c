#include "uart_self_defined.h"

#define TX_BUF_SIZE 128
#define RX_BUF_SIZE 128
static uint8_t tx_buf[TX_BUF_SIZE];
static uint8_t rx_buf[RX_BUF_SIZE];

void UART_Self_Receive(uint8_t *pData, uint16_t Size)
{
    uint16_t count = 0;
    while ((rx_tail != rx_head) && (count < Size)) {
        pData[count++] = rx_buf[rx_tail];
        rx_tail = (rx_tail + 1) % RX_BUF_SIZE;
    }
}

void UART_Self_Transmit(uint8_t *pData, uint16_t Size)
{
    for (uint16_t i = 0; i < Size; i++) {
        uint16_t next = (tx_head + 1) % TX_BUF_SIZE;
        while (next == tx_tail) {
            // 缓冲区满，简单阻塞等待（也可以返回错误码）
        }
        tx_buf[tx_head] = pData[i];
        tx_head = next;
    }
    USART2->CR1 |= USART_CR1_TXEIE; // 打开发送数据寄存器空中断
}

void USART2_IRQHandler(void)
{
    if (USART2->SR & USART_SR_RXNE) {
        uint8_t received = (uint8_t)USART2->DR;
        uint16_t next = (rx_head + 1) % RX_BUF_SIZE;
        if (next != rx_tail) { // 缓冲区未满
            rx_buf[rx_head] = received;
            rx_head = next;
        }
        // 如果满了，可以丢掉或者覆盖，这里选择丢掉
    }

    // 发送中断
    if ((USART2->SR & USART_SR_TXE) && (USART2->CR1 & USART_CR1_TXEIE)) {
        if (tx_tail != tx_head) {
            USART2->DR = tx_buf[tx_tail];
            tx_tail = (tx_tail + 1) % TX_BUF_SIZE;
        } else {
            // 没数据可发，关闭 TXE 中断
            USART2->CR1 &= ~USART_CR1_TXEIE;
            // 可选：打开 TCIE，等最后一个字节真正发出去
        }
    }

    // 发送完成中断（可选）
    if ((USART2->SR & USART_SR_TC) && (USART2->CR1 & USART_CR1_TCIE)) {
        USART2->SR &= ~USART_SR_TC; // 清除 TC
        // 可以在这里做发送完成标志
    }
}

static uint32_t usart_brr_calc(uint32_t pclk, uint32_t baudrate, uint32_t oversampling)
{
    if (baudrate == 0 || oversampling == 0) return 0;

    if (oversampling == 16) {
        float usartdiv = (float)pclk / (16.0f * baudrate);
        uint32_t mantissa = (uint32_t)usartdiv;
        uint32_t fraction = (uint32_t)((usartdiv - mantissa) * 16 + 0.5f); // 四舍五入
        if (fraction > 15) { mantissa++; fraction = 0; }
        return (mantissa << 4) | (fraction & 0x0F);
    } else {
        float usartdiv = (float)pclk / (8.0f * baudrate);
        uint32_t mantissa = (uint32_t)usartdiv;
        uint32_t fraction = (uint32_t)((usartdiv - mantissa) * 8 + 0.5f);
        if (fraction > 7) { mantissa++; fraction = 0; }
        return (mantissa << 3) | (fraction & 0x07);
    }
}

void UART_Self_Init(void)
{
    // 打开时钟
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;   // GPIOA 时钟
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;  // USART2 时钟

    // 配置 PA2, PA3 为复用模式 (AF7)
    GPIOA->MODER &= ~((3U << (2 * 2)) | (3U << (3 * 2)));
    GPIOA->MODER |=  ((2U << (2 * 2)) | (2U << (3 * 2)));
    GPIOA->AFR[0] &= ~((0xF << (2 * 4)) | (0xF << (3 * 4)));
    GPIOA->AFR[0] |=  (7U << (2 * 4)) | (7U << (3 * 4));

    // 设置波特率
    uint32_t pclk = HAL_RCC_GetPCLK1Freq();
    uint32_t brr  = usart_brr_calc(pclk, 9600, 16);
    USART2->BRR = brr;

    // 使能 TX, RX, USART, 以及接收中断
    USART2->CR1 = 0;
    USART2->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_UE | USART_CR1_RXNEIE | USART_CR1_TXEIE;

    // NVIC 配置00
    NVIC_SetPriority(USART2_IRQn, 5);
    NVIC_EnableIRQ(USART2_IRQn);
}

