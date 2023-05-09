################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Button/Button.c 

OBJS += \
./Button/Button.o 

C_DEPS += \
./Button/Button.d 


# Each subdirectory must supply rules for building sources it contributes
Button/%.o: ../Button/%.c Button/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra -g -DNDEBUG -DSTM32F401xE -DHSE_VALUE=8000000 -I"C:\Users\Anwar\Desktop\SBME 2024\YEAR 3 (2022-2023)\SEMESTER 2\Embedded Systems\Final Project\Code\VehicleDoorHandle_ControlUnit\Delay" -I"C:\Users\Anwar\Desktop\SBME 2024\YEAR 3 (2022-2023)\SEMESTER 2\Embedded Systems\Final Project\Code\VehicleDoorHandle_ControlUnit\Button" -I"C:\Users\Anwar\Desktop\SBME 2024\YEAR 3 (2022-2023)\SEMESTER 2\Embedded Systems\Final Project\Code\VehicleDoorHandle_ControlUnit\Led" -I"C:\Users\Anwar\Desktop\SBME 2024\YEAR 3 (2022-2023)\SEMESTER 2\Embedded Systems\Final Project\Code\VehicleDoorHandle_ControlUnit\Gpio" -I"C:\Users\Anwar\Desktop\SBME 2024\YEAR 3 (2022-2023)\SEMESTER 2\Embedded Systems\Final Project\Code\VehicleDoorHandle_ControlUnit\Lib" -I"C:\Users\Anwar\Desktop\SBME 2024\YEAR 3 (2022-2023)\SEMESTER 2\Embedded Systems\Final Project\Code\VehicleDoorHandle_ControlUnit\Rcc" -I"../include" -I"../system/include" -I"../system/include/cmsis" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


