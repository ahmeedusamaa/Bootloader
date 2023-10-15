################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/OS/subdir.mk
-include Src/MCAL/UASRT/subdir.mk
-include Src/MCAL/STK/subdir.mk
-include Src/MCAL/SPI/subdir.mk
-include Src/MCAL/SCB/subdir.mk
-include Src/MCAL/RCC/subdir.mk
-include Src/MCAL/NVIC/subdir.mk
-include Src/MCAL/GPIO/subdir.mk
-include Src/MCAL/FMI/subdir.mk
-include Src/MCAL/EXTI/subdir.mk
-include Src/HAL/TFT/subdir.mk
-include Src/HAL/LCD/subdir.mk
-include Src/HAL/KEYPAD/subdir.mk
-include Src/APP/HEXPARSER/subdir.mk
-include Src/APP/subdir.mk
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
BootloaderFinal.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
BootloaderFinal.list \

OBJCOPY_BIN += \
BootloaderFinal.bin \


# All Target
all: BootloaderFinal.elf secondary-outputs

# Tool invocations
BootloaderFinal.elf: $(OBJS) $(USER_OBJS) C:\Users\adham\STM32CubeIDE\workspace_1.4.0\BootloaderFinal\STM32F401CCUX_FLASH.ld
	arm-none-eabi-gcc -o "BootloaderFinal.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\adham\STM32CubeIDE\workspace_1.4.0\BootloaderFinal\STM32F401CCUX_FLASH.ld" --specs=nosys.specs -Wl,-Map="BootloaderFinal.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

BootloaderFinal.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "BootloaderFinal.list"
	@echo 'Finished building: $@'
	@echo ' '

BootloaderFinal.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "BootloaderFinal.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
