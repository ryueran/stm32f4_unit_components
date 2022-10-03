cmake_minimum_required(VERSION 3.15)
project(HAL_UNIT LANGUAGES C ASM)
ENABLE_LANGUAGE(ASM)
add_library(HAL_UNIT STATIC)
set(CMAKE_CXX_STANDARD 11)
# set_source_files_properties(Startup/startup_stm32f030x8.s PROPERTIES COMPILE_FLAGS "-x assembler-with-cpp")

target_sources(HAL_UNIT
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/uart_manipulation.c
)

target_include_directories(HAL_UNIT
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ../../Drivers/HAL/Inc
    ../../Drivers/CMSIS/Device/ST/STM32F0xx/Include
    ../../Drivers/CMSIS/Include
    ../../Inc
)

target_link_libraries(HAL_UNIT soc_sp)