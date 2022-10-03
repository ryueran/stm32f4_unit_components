cmake_minimum_required(VERSION 3.15)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

project (unit_project LANGUAGES C ASM)
add_executable(unit_project main.c stm32f4xx_hal_msp.c stm32f4xx_it.c)

add_subdirectory(HAL_Unit)

target_link_libraries(HAL_UNIT soc_sp)
target_link_libraries(unit_project soc_sp HAL_UNIT)

target_include_directories(unit_project
PUBLIC
    ../Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/HAL_Unit
)