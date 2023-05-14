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
Wheelchair.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Wheelchair.list \

OBJCOPY_HEX += \
Wheelchair.hex \

OBJCOPY_BIN += \
Wheelchair.bin \


# All Target
all: Wheelchair.elf secondary-outputs

# Tool invocations
Wheelchair.elf: $(OBJS) $(USER_OBJS) C:\Users\ibrah\OneDrive\Desktop\Wheelchair\Workspace\Wheelchair\STM32F103C6TX_FLASH.ld
	arm-none-eabi-gcc -gdwarf-2 -o "Wheelchair.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\Users\ibrah\OneDrive\Desktop\Wheelchair\Workspace\Wheelchair\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Wheelchair.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Wheelchair.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Wheelchair.list"
	@echo 'Finished building: $@'
	@echo ' '

Wheelchair.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "Wheelchair.hex"
	@echo 'Finished building: $@'
	@echo ' '

Wheelchair.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Wheelchair.bin"
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
