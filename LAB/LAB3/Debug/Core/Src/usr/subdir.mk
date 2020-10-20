################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/usr/Phase1.c 

OBJS += \
./Core/Src/usr/Phase1.o 

C_DEPS += \
./Core/Src/usr/Phase1.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/usr/Phase1.o: ../Core/Src/usr/Phase1.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/usr/Phase1.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

