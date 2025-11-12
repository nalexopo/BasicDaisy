

TARGET = daisy
BUILD_DIR = build

CHIPSET ?= stm32h7x

TARGET_BIN=$(TARGET).bin
TARGET_ELF=$(TARGET).elf


MODULE_DIR=src

CPP_MODULES = \
sys/system \
app/main \
per/gpio \
per/tim \
per/rng

C_MODULES = \
sys/dma \
sys/system_stm32h7xx


# C++ Source
CPP_SOURCES += $(addsuffix .cpp, $(addprefix $(MODULE_DIR)/, $(CPP_MODULES)))
C_SOURCES += $(addsuffix .c, $(addprefix $(MODULE_DIR)/, $(C_MODULES)))

C_SOURCES += \
core/startup_stm32h750xx.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_gpio.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_gpio.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_cortex.c 

# Expose platform configuration to all compilation units (CMSIS DSP components)
C_INCLUDES += -include stm32h7xx.h

# ASM_SOURCES += \
# core/startup_stm32h750xx.s

######################################
# OpenOCD stuff
# TODO: add config.mk file for settings like programmer, etc.
######################################
OCD=openocd
OCD_DIR ?= /usr/local/share/openocd/scripts
PGM_DEVICE ?= interface/stlink.cfg
OCDFLAGS = -f $(PGM_DEVICE) -f target/$(CHIPSET).cfg

GDB_FLAGS=

#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-

ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CXX = $(GCC_PATH)/$(PREFIX)g++
GDB = $(GCC_PATH)/$(PREFIX)gdb
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
CXX = $(PREFIX)g++
GDB = $(PREFIX)gdb
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S


#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m7

# fpu
FPU = -mfpu=fpv5-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)
# macros for gcc
# AS defines
AS_DEFS =

# C defines
C_DEFS ?=
C_DEFS +=  \
-DUSE_HAL_DRIVER \
-DSTM32H750xx \
-DHSE_VALUE=16000000 \

# imported from libdaisy internal makefile
C_DEFS +=  \
-DCORE_CM7  \
-DSTM32H750IB \
-DARM_MATH_CM7 \
-DUSE_FULL_LL_DRIVER

# for debugging bootloaded applications
ifdef DEBUG
C_DEFS += -DDEBUG
endif

# AS includes
AS_INCLUDES =

C_INCLUDES ?=

C_INCLUDES += \
-IDrivers/CMSIS_5/CMSIS/Core/Include/ \
-IDrivers/CMSIS-DSP/Include \
-IDrivers/CMSIS-Device/ST/STM32H7xx/Include \
-IDrivers/STM32H7xx_HAL_Driver/Inc/ \
-Isrc/sys \
-Isrc/per
# -I$(LIBDAISY_DIR) \
# -I$(LIBDAISY_DIR)/src/ \
# -I$(LIBDAISY_DIR)/src/sys \
# -I$(LIBDAISY_DIR)/src/usbd \
# -I$(LIBDAISY_DIR)/src/usbh \
# -I$(LIBDAISY_DIR)/Middlewares/ST/STM32_USB_Device_Library/Core/Inc \
# -I$(LIBDAISY_DIR)/Middlewares/ST/STM32_USB_Host_Library/Core/Inc \
# -I$(LIBDAISY_DIR)/Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc \
# -I$(LIBDAISY_DIR)/Middlewares/ST/STM32_USB_Host_Library/Class/MIDI/Inc \
# -I$(SYSTEM_FILES_DIR)/


# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
ASFLAGS += -g -ggdb
endif

OPT ?= -Og

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -Wno-missing-attributes -fasm -fdata-sections -ffunction-sections -Wno-stringop-overflow

CFLAGS += -g -ggdb

# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

CPPFLAGS = $(CFLAGS)
CPPFLAGS += \
-fno-exceptions \
-fasm \
-finline \
-finline-functions-called-once \
-fshort-enums \
-fno-move-loop-invariants \
-fno-unwind-tables \
-fno-rtti \
-Wno-register \
-Wno-volatile

C_STANDARD = -std=gnu11
CPP_STANDARD ?= -std=c++23
#######################################
# Boot Management
#######################################

INTERNAL_ADDRESS = 0x08000000

STM_PID = df11

BOOT_BIN ?= core/dsy_bootloader_v6_3-intdfu-2000ms.bin
LDSCRIPT ?= core/STM32H750IB_flash.lds
USBPID = $(STM_PID)
FLASH_ADDRESS ?= $(INTERNAL_ADDRESS)

LIBS += -lc -lm -lnosys
LIBDIR += -L$ build


LDFLAGS ?=
LDFLAGS += $(MCU) --specs=nano.specs --specs=nosys.specs -T $(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections -Wl,--print-memory-usage

# default action: build all
all:$(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin

#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(CPP_SOURCES:.cpp=.o)))
vpath %.cpp $(sort $(dir $(CPP_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) $(C_STANDARD) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.cpp Makefile | $(BUILD_DIR)
	$(CXX) -c $(CPPFLAGS) $(CPP_STANDARD) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.cpp=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(ASFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@

#######################################
# clean up
#######################################
clean:
	-rm -rf $(BUILD_DIR)/*

#######################################
# openocd recipes
#######################################

openocd:
	$(OCD) -s $(OCD_DIR) $(OCDFLAGS)

debug:
	@if ! nc -z localhost 3333; then \
        echo "\n\t[Error] OpenOCD is not running! Start it with: 'make openocd'\n"; exit 1; \
    else \
        $(GDB)  -ex "target extended localhost:3333" \
            -ex "monitor arm semihosting enable" \
            -ex "monitor reset halt" \
            -ex "load" \
            -ex "monitor reset init" \
            $(GDBFLAGS) build/$(TARGET).elf; \
    fi

debug_client:
	ddd --eval-command="target remote localhost:3333" --debugger $(GDB) $(TARGET_ELF)


APP_TYPE ?= BOOT_NONE
ifeq ($(APP_TYPE), BOOT_NONE)
program:
	$(OCD) -s $(OCD_DIR) $(OCDFLAGS) \
		-c "program ./build/$(TARGET).elf verify reset exit"
else
program:
	$(error Cannot program via openocd with an app type of "$(APP_TYPE)". Try program-dfu instead)
endif

#######################################
# dfu-util
#######################################

program-dfu:
	dfu-util -a 0 -s $(FLASH_ADDRESS):leave -D $(BUILD_DIR)/$(TARGET_BIN) -d ,0483:$(USBPID)

program-boot:
	dfu-util -a 0 -s $(INTERNAL_ADDRESS):leave -D $(BOOT_BIN) -d ,0483:$(STM_PID)

#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***