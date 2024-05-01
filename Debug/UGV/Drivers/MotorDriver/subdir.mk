################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../UGV/Drivers/MotorDriver/MotorDrive.c 

OBJS += \
./UGV/Drivers/MotorDriver/MotorDrive.o 

C_DEPS += \
./UGV/Drivers/MotorDriver/MotorDrive.d 


# Each subdirectory must supply rules for building sources it contributes
UGV/Drivers/MotorDriver/%.o UGV/Drivers/MotorDriver/%.su UGV/Drivers/MotorDriver/%.cyclo: ../UGV/Drivers/MotorDriver/%.c UGV/Drivers/MotorDriver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV/Drivers" -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV/Drivers/QMC" -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV/Drivers/QMC/Kalman" -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV/Drivers/QMC/QMC5883" -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV/Drivers/PID" -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV/Drivers/MotorDriver" -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV/Drivers/ledControl" -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV/Drivers/crc" -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV/Drivers/RC" -I../Core/Inc -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV/Helper" -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV/Main" -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-UGV-2f-Drivers-2f-MotorDriver

clean-UGV-2f-Drivers-2f-MotorDriver:
	-$(RM) ./UGV/Drivers/MotorDriver/MotorDrive.cyclo ./UGV/Drivers/MotorDriver/MotorDrive.d ./UGV/Drivers/MotorDriver/MotorDrive.o ./UGV/Drivers/MotorDriver/MotorDrive.su

.PHONY: clean-UGV-2f-Drivers-2f-MotorDriver

