################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../UGV/Drivers/QMC/QMC5883/qmc5883.c 

OBJS += \
./UGV/Drivers/QMC/QMC5883/qmc5883.o 

C_DEPS += \
./UGV/Drivers/QMC/QMC5883/qmc5883.d 


# Each subdirectory must supply rules for building sources it contributes
UGV/Drivers/QMC/QMC5883/%.o UGV/Drivers/QMC/QMC5883/%.su UGV/Drivers/QMC/QMC5883/%.cyclo: ../UGV/Drivers/QMC/QMC5883/%.c UGV/Drivers/QMC/QMC5883/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV/Drivers" -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV/Drivers/QMC" -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV/Drivers/QMC/Kalman" -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV/Drivers/QMC/QMC5883" -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV/Drivers/PID" -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV/Drivers/MotorDriver" -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV/Drivers/ledControl" -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV/Drivers/crc" -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV/Drivers/RC" -I../Core/Inc -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV/Helper" -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV/Main" -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-UGV-2f-Drivers-2f-QMC-2f-QMC5883

clean-UGV-2f-Drivers-2f-QMC-2f-QMC5883:
	-$(RM) ./UGV/Drivers/QMC/QMC5883/qmc5883.cyclo ./UGV/Drivers/QMC/QMC5883/qmc5883.d ./UGV/Drivers/QMC/QMC5883/qmc5883.o ./UGV/Drivers/QMC/QMC5883/qmc5883.su

.PHONY: clean-UGV-2f-Drivers-2f-QMC-2f-QMC5883

