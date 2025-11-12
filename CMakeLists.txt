cmake_minimum_required(VERSION 3.13)
set(CMAKE_C_COMPILER "arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER "arm-none-eabi-g++")
set(CMAKE_ASM_COMPILER "arm-none-eabi-gcc")
set(CMAKE_OBJCOPY "arm-none-eabi-objcopy")
set(CMAKE_SIZE "arm-none-eabi-size")
set(CMAKE_CXX_COMPILER_FORCED true)
set(CMAKE_C_COMPILER_FORCED true)

set(CDEFS "-DUSE_HAL_DRIVER -DSTM32H750xx -DHSE_VALUE=16000000")
set(MCU "-mcpu=cortex-m7 -mthumb -mfpu=fpv5-d16 -mfloat-abi=hard")
set(COMMON_FLAGS "${MCU} ${CDEFS} -fdata-sections -fasm -ffunction-sections -Wno-address-of-packed-member -Wall -fasm -Wno-unused-parameter -Wno-stringop-overflow")
set(CMAKE_C_FLAGS "${COMMON_FLAGS} -Wno-missing-attributes")
set(CMAKE_CXX_FLAGS "${COMMON_FLAGS} -Wno-register -fno-exceptions -fno-rtti -fno-threadsafe-statics")


set(CMAKE_C_FLAGS_DEBUG "-g -gdwarf-2 -O0")
set(CMAKE_CXX_FLAGS_DEBUG "-g -gdwarf-2 -O0")
set(CMAKE_C_FLAGS_RELEASE "-O2 -flto")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -flto")
set(CMAKE_C_FLAGS_MINSIZEREL "-Os -flto")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -flto")

project(daisy VERSION 1.0.1)
enable_language(C CXX ASM)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(EXECUTABLE ${PROJECT_NAME}.elf)

message(CMAKE_CURRENT_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

add_compile_options(-include stm32h7xx.h)



add_executable(
  ${EXECUTABLE}
  core/startup_stm32h750xx.c
  Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_gpio.c
  Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_gpio.c
  Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim.c
  Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim_ex.c
  Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc.c
  Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc_ex.c
  Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr_ex.c
  Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal.c
  Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_cortex.c
	src/sys/dma.c
	src/sys/system_stm32h7xx.c
	src/sys/system.cpp
  src/app/main.cpp
  src/per/gpio.cpp
  src/per/tim.cpp
  src/per/rng.cpp
)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/Drivers/CMSIS_5/CMSIS/Core/Include
	${CMAKE_CURRENT_SOURCE_DIR}/Drivers/CMSIS-DSP/Include
	${CMAKE_CURRENT_SOURCE_DIR}/Drivers/CMSIS-Device/ST/STM32H7xx/Include
	${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Inc
	${CMAKE_CURRENT_SOURCE_DIR}/src/sys
	${CMAKE_CURRENT_SOURCE_DIR}/src/per)

target_link_options(
  ${EXECUTABLE}
  PUBLIC
  -T${CMAKE_CURRENT_SOURCE_DIR}/core/STM32H750IB_flash.lds
  -mcpu=cortex-m7
  -mthumb
  -specs=nano.specs
  -Wl,--no-warn-rwx-segments
  -Wl,-Map=${PROJECT_NAME}.map,--cref
  -Wl,--gc-sections,--print-memory-usage)

  # Print executable size
add_custom_command(
  TARGET ${EXECUTABLE}
  POST_BUILD
  COMMAND arm-none-eabi-size ${EXECUTABLE})

# Create hex file
add_custom_command(
  TARGET ${EXECUTABLE}
  POST_BUILD
  COMMAND arm-none-eabi-objcopy -O ihex ${EXECUTABLE} ${PROJECT_NAME}.hex
  COMMAND arm-none-eabi-objcopy -O binary ${EXECUTABLE} ${PROJECT_NAME}.bin)

add_custom_target(program
  COMMAND openocd -f interface/stlink.cfg -f target/stm32h7x.cfg
          -c "program ${PROJECT_NAME}.elf verify reset exit"
  DEPENDS ${EXECUTABLE}
  COMMENT "Flashing ${PROJECT_NAME}.elf via OpenOCD (auto-reset)"
)