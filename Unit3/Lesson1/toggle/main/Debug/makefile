################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
main.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
main.list \

OBJCOPY_HEX += \
main.hex \

OBJCOPY_BIN += \
main.bin \


# All Target
all: main.elf secondary-outputs

# Tool invocations
main.elf: $(OBJS) $(USER_OBJS) D:\Online\ courses\Embedded\ Systems\ Online\ Diploma\Unit\ 3\toggle\main\STM32F103C6TX_FLASH.ld
	arm-none-eabi-gcc -o "main.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\Online courses\Embedded Systems Online Diploma\Unit 3\toggle\main\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="main.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

main.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "main.list"
	@echo 'Finished building: $@'
	@echo ' '

main.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "main.hex"
	@echo 'Finished building: $@'
	@echo ' '

main.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "main.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
