################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Mycode/CLI/CLI.c 

OBJS += \
./Mycode/CLI/CLI.o 

C_DEPS += \
./Mycode/CLI/CLI.d 


# Each subdirectory must supply rules for building sources it contributes
Mycode/CLI/CLI.o: ../Mycode/CLI/CLI.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I"C:/Users/61644/Desktop/ENEL487_ASSIGNMENT/ENEL487_Zhelin_Wang/LAB/Project/Mycode/CLI" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Mycode/CLI/CLI.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

