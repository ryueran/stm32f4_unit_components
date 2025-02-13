SET(ASM_OPTIONS "-x assembler-with-cpp") 

# 处理 CPU 相关参数
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=softfp")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -mcpu=cortex-m4 -mthumb")

set(LINK_FLAGS "--gc-sections")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --specs=nosys.specs -T ${CMAKE_CURRENT_LIST_DIR}/Linker/STM32F411RETx_FLASH.ld")

# 可能 nosys.specs 有问题，可以改成 nano.specs
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --specs=nosys.specs")
