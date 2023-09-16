################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/KeyPad/KPD_program.c 

OBJS += \
./HAL/KeyPad/KPD_program.o 

C_DEPS += \
./HAL/KeyPad/KPD_program.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/KeyPad/KPD_program.o: ../HAL/KeyPad/KPD_program.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -c -I"C:/Users/Abdallah/STM32CubeIDE/workspace_1.4.0/AutomatedSmartParkingProject/HAL/includes" -I"C:/Users/Abdallah/STM32CubeIDE/workspace_1.4.0/AutomatedSmartParkingProject/Stm32_F103C6_Drivers/inc" -I"C:/Users/Abdallah/STM32CubeIDE/workspace_1.4.0/AutomatedSmartParkingProject/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/KeyPad/KPD_program.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

