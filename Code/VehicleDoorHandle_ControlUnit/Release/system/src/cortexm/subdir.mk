################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/src/cortexm/exception-handlers.c \
../system/src/cortexm/initialize-hardware.c \
../system/src/cortexm/reset-hardware.c 

OBJS += \
./system/src/cortexm/exception-handlers.o \
./system/src/cortexm/initialize-hardware.o \
./system/src/cortexm/reset-hardware.o 

C_DEPS += \
./system/src/cortexm/exception-handlers.d \
./system/src/cortexm/initialize-hardware.d \
./system/src/cortexm/reset-hardware.d 


# Each subdirectory must supply rules for building sources it contributes
system/src/cortexm/%.o: ../system/src/cortexm/%.c system/src/cortexm/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra -g -DNDEBUG -DSTM32F401xE -DHSE_VALUE=8000000 -I"C:\Users\Anwar\Desktop\SBME 2024\YEAR 3 (2022-2023)\SEMESTER 2\Embedded Systems\Final Project\Code\VehicleDoorHandle_ControlUnit\Delay" -I"C:\Users\Anwar\Desktop\SBME 2024\YEAR 3 (2022-2023)\SEMESTER 2\Embedded Systems\Final Project\Code\VehicleDoorHandle_ControlUnit\GPT" -I"C:\Users\Anwar\Desktop\SBME 2024\YEAR 3 (2022-2023)\SEMESTER 2\Embedded Systems\Final Project\Code\VehicleDoorHandle_ControlUnit\Button" -I"C:\Users\Anwar\Desktop\SBME 2024\YEAR 3 (2022-2023)\SEMESTER 2\Embedded Systems\Final Project\Code\VehicleDoorHandle_ControlUnit\Led" -I"C:\Users\Anwar\Desktop\SBME 2024\YEAR 3 (2022-2023)\SEMESTER 2\Embedded Systems\Final Project\Code\VehicleDoorHandle_ControlUnit\Gpio" -I"C:\Users\Anwar\Desktop\SBME 2024\YEAR 3 (2022-2023)\SEMESTER 2\Embedded Systems\Final Project\Code\VehicleDoorHandle_ControlUnit\Lib" -I"C:\Users\Anwar\Desktop\SBME 2024\YEAR 3 (2022-2023)\SEMESTER 2\Embedded Systems\Final Project\Code\VehicleDoorHandle_ControlUnit\Rcc" -I"../include" -I"../system/include" -I"../system/include/cmsis" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


