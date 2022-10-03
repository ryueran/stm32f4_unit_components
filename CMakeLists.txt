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


add_subdirectory(Drivers)
add_subdirectory(Src)
