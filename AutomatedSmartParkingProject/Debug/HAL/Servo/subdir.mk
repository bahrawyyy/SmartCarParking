################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/Servo/Servo.c 

OBJS += \
./HAL/Servo/Servo.o 

C_DEPS += \
./HAL/Servo/Servo.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/Servo/Servo.o: ../HAL/Servo/Servo.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -c -I"C:/Users/Abdallah/STM32CubeIDE/workspace_1.4.0/AutomatedSmartParkingProject/HAL/includes" -I"C:/Users/Abdallah/STM32CubeIDE/workspace_1.4.0/AutomatedSmartParkingProject/Stm32_F103C6_Drivers/inc" -I"C:/Users/Abdallah/STM32CubeIDE/workspace_1.4.0/AutomatedSmartParkingProject/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/Servo/Servo.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

