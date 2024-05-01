################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include UGV/Tasks/TaskSensor/subdir.mk
-include UGV/Tasks/TaskMotorDrive/subdir.mk
-include UGV/Tasks/TaskLoraCom/subdir.mk
-include UGV/Main/subdir.mk
-include UGV/Drivers/ledControl/subdir.mk
-include UGV/Drivers/crc/subdir.mk
-include UGV/Drivers/Servo/subdir.mk
-include UGV/Drivers/SX1278/subdir.mk
-include UGV/Drivers/RcFilter/subdir.mk
-include UGV/Drivers/RC/subdir.mk
-include UGV/Drivers/QMC/QMC5883/subdir.mk
-include UGV/Drivers/QMC/Kalman/subdir.mk
-include UGV/Drivers/PID/subdir.mk
-include UGV/Drivers/MotorDriver/subdir.mk
-include UGV/Drivers/GPS/subdir.mk
-include UGV/Database/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
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

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := 001_UGV_VEHICLE
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
001_UGV_VEHICLE.elf \

MAP_FILES += \
001_UGV_VEHICLE.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
001_UGV_VEHICLE.list \


# All Target
all: main-build

# Main-build Target
main-build: 001_UGV_VEHICLE.elf secondary-outputs

# Tool invocations
001_UGV_VEHICLE.elf 001_UGV_VEHICLE.map: $(OBJS) $(USER_OBJS) C:\Users\Mehmet\ Dincer\Desktop\Bitirme\Kodlar\gomulu\001_UGV_VEHICLE\STM32F446RETX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "001_UGV_VEHICLE.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\Mehmet Dincer\Desktop\Bitirme\Kodlar\gomulu\001_UGV_VEHICLE\STM32F446RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="001_UGV_VEHICLE.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

001_UGV_VEHICLE.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "001_UGV_VEHICLE.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) 001_UGV_VEHICLE.elf 001_UGV_VEHICLE.list 001_UGV_VEHICLE.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
