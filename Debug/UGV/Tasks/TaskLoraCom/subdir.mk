################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../UGV/Tasks/TaskLoraCom/taskLoraCom.c 

OBJS += \
./UGV/Tasks/TaskLoraCom/taskLoraCom.o 

C_DEPS += \
./UGV/Tasks/TaskLoraCom/taskLoraCom.d 


# Each subdirectory must supply rules for building sources it contributes
UGV/Tasks/TaskLoraCom/%.o UGV/Tasks/TaskLoraCom/%.su UGV/Tasks/TaskLoraCom/%.cyclo: ../UGV/Tasks/TaskLoraCom/%.c UGV/Tasks/TaskLoraCom/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV/Drivers" -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV/Drivers/Mpu6050" -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV/Drivers/GPS" -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV/Database" -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV/Tasks/TaskLoraCom" -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV/Tasks/TaskSensor" -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV/Tasks/TaskLoraCom" -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV/Tasks/TaskMotorDrive" -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV/Tasks" -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV/Drivers/SX1278" -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV/Drivers/RcFilter" -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV/Drivers/RcFilter" -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV/Drivers/Servo" -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV/Drivers/PID" -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV/Drivers/MotorDriver" -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV/Drivers/ledControl" -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV/Drivers/crc" -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV/Drivers/RC" -I../Core/Inc -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV/Helper" -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV/Main" -I"C:/Users/Mehmet Dincer/Desktop/Bitirme/Kodlar/gomulu/001_UGV_VEHICLE/UGV" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-UGV-2f-Tasks-2f-TaskLoraCom

clean-UGV-2f-Tasks-2f-TaskLoraCom:
	-$(RM) ./UGV/Tasks/TaskLoraCom/taskLoraCom.cyclo ./UGV/Tasks/TaskLoraCom/taskLoraCom.d ./UGV/Tasks/TaskLoraCom/taskLoraCom.o ./UGV/Tasks/TaskLoraCom/taskLoraCom.su

.PHONY: clean-UGV-2f-Tasks-2f-TaskLoraCom

