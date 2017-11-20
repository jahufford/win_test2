################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/STemWin/OS/GUI_X.c \
../Middlewares/ST/STemWin/OS/GUI_X_OS.c 

OBJS += \
./Middlewares/ST/STemWin/OS/GUI_X.o \
./Middlewares/ST/STemWin/OS/GUI_X_OS.o 

C_DEPS += \
./Middlewares/ST/STemWin/OS/GUI_X.d \
./Middlewares/ST/STemWin/OS/GUI_X_OS.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/STemWin/OS/%.o: ../Middlewares/ST/STemWin/OS/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DDEBUG -DSTM32F446xx -DUSE_HAL_DRIVER -DUSE_RTOS_SYSTICK -I"/home/joe/programming/embedded/projects/win_test2/Middlewares/ST/STemWin/Config" -I"/home/joe/programming/embedded/projects/win_test2/HAL_Driver/Inc/Legacy" -I"/home/joe/programming/embedded/projects/win_test2/Middlewares/ST/STemWin/inc" -I"/home/joe/programming/embedded/projects/win_test2/Utilities/STM32F4xx-Nucleo" -I"/home/joe/programming/embedded/projects/win_test2/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/home/joe/programming/embedded/projects/win_test2/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/home/joe/programming/embedded/projects/win_test2/inc" -I"/home/joe/programming/embedded/projects/win_test2/CMSIS/device" -I"/home/joe/programming/embedded/projects/win_test2/CMSIS/core" -I"/home/joe/programming/embedded/projects/win_test2/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/home/joe/programming/embedded/projects/win_test2/HAL_Driver/Inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


