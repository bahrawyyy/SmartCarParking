################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/LED/LED.c 

OBJS += \
./HAL/LED/LED.o 

C_DEPS += \
./HAL/LED/LED.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/LED/LED.o: ../HAL/LED/LED.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -c -I"C:/Users/Abdallah/STM32CubeIDE/workspace_1.4.0/AutomatedSmartParkingProject/HAL/includes" -I"C:/Users/Abdallah/STM32CubeIDE/workspace_1.4.0/AutomatedSmartParkingProject/Stm32_F103C6_Drivers/inc" -I"C:/Users/Abdallah/STM32CubeIDE/workspace_1.4.0/AutomatedSmartParkingProject/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/LED/LED.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

