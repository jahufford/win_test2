################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/debug_serial_port.c \
../src/lcd_hardware.c \
../src/main.c \
../src/stm32f4xx_it.c \
../src/syscalls.c \
../src/system_stm32f4xx.c \
../src/touchscreen.c 

OBJS += \
./src/debug_serial_port.o \
./src/lcd_hardware.o \
./src/main.o \
./src/stm32f4xx_it.o \
./src/syscalls.o \
./src/system_stm32f4xx.o \
./src/touchscreen.o 

C_DEPS += \
./src/debug_serial_port.d \
./src/lcd_hardware.d \
./src/main.d \
./src/stm32f4xx_it.d \
./src/syscalls.d \
./src/system_stm32f4xx.d \
./src/touchscreen.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DDEBUG -DSTM32F446xx -DUSE_HAL_DRIVER -DUSE_RTOS_SYSTICK -I"/home/joe/programming/embedded/projects/win_test2/Middlewares/ST/STemWin/Config" -I"/home/joe/programming/embedded/projects/win_test2/HAL_Driver/Inc/Legacy" -I"/home/joe/programming/embedded/projects/win_test2/Middlewares/ST/STemWin/inc" -I"/home/joe/programming/embedded/projects/win_test2/Utilities/STM32F4xx-Nucleo" -I"/home/joe/programming/embedded/projects/win_test2/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/home/joe/programming/embedded/projects/win_test2/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/home/joe/programming/embedded/projects/win_test2/inc" -I"/home/joe/programming/embedded/projects/win_test2/CMSIS/device" -I"/home/joe/programming/embedded/projects/win_test2/CMSIS/core" -I"/home/joe/programming/embedded/projects/win_test2/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/home/joe/programming/embedded/projects/win_test2/HAL_Driver/Inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


