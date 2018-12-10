################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
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
LSS += \
Gwiazdka_led.lss \

FLASH_IMAGE += \
Gwiazdka_led.hex \

EEPROM_IMAGE += \
Gwiazdka_led.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Gwiazdka_led.elf secondary-outputs

# Tool invocations
Gwiazdka_led.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Gwiazdka_led.map -mmcu=attiny13 -o "Gwiazdka_led.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Gwiazdka_led.lss: Gwiazdka_led.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Gwiazdka_led.elf  >"Gwiazdka_led.lss"
	@echo 'Finished building: $@'
	@echo ' '

Gwiazdka_led.hex: Gwiazdka_led.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Gwiazdka_led.elf  "Gwiazdka_led.hex"
	@echo 'Finished building: $@'
	@echo ' '

Gwiazdka_led.eep: Gwiazdka_led.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Gwiazdka_led.elf  "Gwiazdka_led.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Gwiazdka_led.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=attiny13 Gwiazdka_led.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Gwiazdka_led.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
