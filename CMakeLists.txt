cmake_minimum_required(VERSION 3.15)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

message(STATUS "Building for TARGET")
project(stm32f4_unit LANGUAGES C ASM)
set(CMAKE_EXE_LINKER_FLAGS "-T ${CMAKE_CURRENT_LIST_DIR}/Linker/STM32F411RETx_FLASH.ld")

if (CMAKE_BUILD_TYPE MATCHES "Debug")
    message("-- debug mode")
    include(toolchain_target_debug.cmake)
else()
    message("-- release mode")
    include(toolchain_target_release.cmake)
endif (CMAKE_BUILD_TYPE MATCHES "Debug")

# 创建 freertos_config 目标
add_library(freertos_config INTERFACE)
target_include_directories(freertos_config SYSTEM INTERFACE ${CMAKE_SOURCE_DIR}/config)

# Set freertos port
set(FREERTOS_PORT "GCC_ARM_CM4F" CACHE STRING "ARM Cortex-M4 with FPU")
set(FREERTOS_HEAP "4" CACHE STRING "" FORCE)

include_directories(
    Drivers/CMSIS/Device/ST/STM32F4xx/Include
    Drivers/CMSIS/Core/Include
    third_party/FreeRTOS/FreeRTOS/Source/include
    config
    third_party/FreeRTOS/FreeRTOS/Source/portable/GCC/ARM_CM4F
)

add_subdirectory(Drivers)
add_subdirectory(third_party/FreeRTOS/FreeRTOS/Source)
add_subdirectory(Src)
