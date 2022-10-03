cmake_minimum_required(VERSION 3.15)
project(soc_cp LANGUAGES C ASM)
ENABLE_LANGUAGE(ASM)
add_library(soc_sp STATIC)
set(CMAKE_CXX_STANDARD 11)

target_sources(soc_sp
PUBLIC
    HAL/Src/stm32f4xx_hal_cortex.c
    HAL/Src/stm32f4xx_hal_flash_ex.c
    HAL/Src/stm32f4xx_hal_flash.c
    HAL/Src/stm32f4xx_hal_gpio.c
    HAL/Src/stm32f4xx_hal_i2c_ex.c
    HAL/Src/stm32f4xx_hal_i2c.c
    HAL/Src/stm32f4xx_hal_pwr_ex.c
    HAL/Src/stm32f4xx_hal_pwr.c
    HAL/Src/stm32f4xx_hal_rcc_ex.c
    HAL/Src/stm32f4xx_hal_rcc.c
    HAL/Src/stm32f4xx_hal_tim_ex.c
    HAL/Src/stm32f4xx_hal_tim.c
    HAL/Src/stm32f4xx_hal.c
    HAL/Src/stm32f4xx_hal_spi.c
    HAL/Src/stm32f4xx_hal_dma.c
    HAL/Src/stm32f4xx_hal_uart.c
    System/system_stm32f4xx.c
PRIVATE
    Startup/startup_stm32f411xe.s
)

target_include_directories(soc_sp 
PUBLIC
    HAL/Inc
    HAL/Inc/Legacy
    CMSIS/Device/ST/STM32F4xx/Include
    CMSIS/Include
    ../Inc
)