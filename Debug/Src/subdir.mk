################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/ds18b20.c \
../Src/main.c \
../Src/max7219.c \
../Src/stm32f0xx_hal_msp.c \
../Src/stm32f0xx_it.c \
../Src/syscalls.c \
../Src/system_stm32f0xx.c 

OBJS += \
./Src/ds18b20.o \
./Src/main.o \
./Src/max7219.o \
./Src/stm32f0xx_hal_msp.o \
./Src/stm32f0xx_it.o \
./Src/syscalls.o \
./Src/system_stm32f0xx.o 

C_DEPS += \
./Src/ds18b20.d \
./Src/main.d \
./Src/max7219.d \
./Src/stm32f0xx_hal_msp.d \
./Src/stm32f0xx_it.d \
./Src/syscalls.d \
./Src/system_stm32f0xx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F030x6 -I"C:/workspace/Max7219testf30/Inc" -I"C:/workspace/Max7219testf30/Drivers/STM32F0xx_HAL_Driver/Inc" -I"C:/workspace/Max7219testf30/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"C:/workspace/Max7219testf30/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"C:/workspace/Max7219testf30/Drivers/CMSIS/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


