# Compiler, Assembler, Linker
CC      = arm-none-eabi-gcc
AS      = arm-none-eabi-as 
LD      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size

# Directories
SRC_DIR         = Src
INC_DIR         = Inc
BUILD_DIR       = build
STARTUP_DIR     = Startup
CMSIS_DEVICE_INC = CMSIS/Device/ST/STM32F4xx/Include
CMSIS_DEVICE_SRC = CMSIS/Device/ST/STM32F4xx/Source
CMSIS_CORE_INC   = CMSIS/Include

# MCU Settings
MCU       = cortex-m4
FPU       = fpv4-sp-d16
FLOAT_ABI = hard

# Defines
DEFINES = -DSTM32F411xE

# Includes
INCLUDES = -I$(INC_DIR) \
           -I$(CMSIS_DEVICE_INC) \
           -I$(CMSIS_CORE_INC)

# Source files
SRC_APP      = $(SRC_DIR)/main.c \
               $(SRC_DIR)/Gpio.c

SRC_CMSIS    = $(CMSIS_DEVICE_SRC)/Templates/system_stm32f4xx.c

# Objects
OBJ_APP      = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_APP))
OBJ_CMSIS    = $(patsubst $(CMSIS_DEVICE_SRC)/Templates/%.c,$(BUILD_DIR)/%.o,$(SRC_CMSIS))

OBJ_STARTUP  = $(BUILD_DIR)/startup_stm32f411vetx.o

OBJ_ALL      = $(OBJ_APP) $(OBJ_CMSIS) $(OBJ_STARTUP)

# Output files
TARGET = $(BUILD_DIR)/STM32F411
ELF    = $(TARGET).elf
BIN    = $(TARGET).bin
MAP    = $(TARGET).map

# Compiler flags
ifdef DEBUG
DEBUG_CFLAGS = -O0 -g3 -DDEBUG
else
DEBUG_CFLAGS = -O2 -g
endif

CFLAGS = -mcpu=$(MCU) -mthumb -mfpu=$(FPU) -mfloat-abi=$(FLOAT_ABI) \
         $(DEFINES) $(DEBUG_CFLAGS) -Wall -ffunction-sections -fdata-sections \
         $(INCLUDES)

LDFLAGS = -T$(STARTUP_DIR)/STM32F411VETX_FLASH.ld -mcpu=$(MCU) -mthumb \
          -mfpu=$(FPU) -mfloat-abi=$(FLOAT_ABI) -Wl,--gc-sections \
          -Wl,-Map=$(MAP)

# Header dependencies
DEPS = $(wildcard $(INC_DIR)/*.h)

# Rules
all: $(BIN)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Compile application source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile CMSIS source files
$(BUILD_DIR)/%.o: $(CMSIS_DEVICE_SRC)/Templates/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Assemble startup assembly file
$(BUILD_DIR)/%.o: $(STARTUP_DIR)/%.s | $(BUILD_DIR)
	$(AS) -mcpu=$(MCU) -mthumb $< -o $@

# Link all objects
$(ELF): $(OBJ_ALL)
	$(LD) $(LDFLAGS) $^ -o $@
	$(SIZE) $@

# Convert ELF to BIN
$(BIN): $(ELF)
	$(OBJCOPY) -O binary $< $@

# Flash to device (using st-flash)
flash: $(BIN)
	st-flash write $(BIN) 0x8000000

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean flash
