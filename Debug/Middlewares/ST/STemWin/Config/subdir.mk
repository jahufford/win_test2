################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/STemWin/Config/GUIConf.c \
../Middlewares/ST/STemWin/Config/GUIDRV_Template.c \
../Middlewares/ST/STemWin/Config/LCDConf.c \
../Middlewares/ST/STemWin/Config/LCDConf_Lin_Template.c \
../Middlewares/ST/STemWin/Config/SIMConf.c 

OBJS += \
./Middlewares/ST/STemWin/Config/GUIConf.o \
./Middlewares/ST/STemWin/Config/GUIDRV_Template.o \
./Middlewares/ST/STemWin/Config/LCDConf.o \
./Middlewares/ST/STemWin/Config/LCDConf_Lin_Template.o \
./Middlewares/ST/STemWin/Config/SIMConf.o 

C_DEPS += \
./Middlewares/ST/STemWin/Config/GUIConf.d \
./Middlewares/ST/STemWin/Config/GUIDRV_Template.d \
./Middlewares/ST/STemWin/Config/LCDConf.d \
./Middlewares/ST/STemWin/Config/LCDConf_Lin_Template.d \
./Middlewares/ST/STemWin/Config/SIMConf.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/STemWin/Config/%.o: ../Middlewares/ST/STemWin/Config/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DDEBUG -DSTM32F446xx -DUSE_HAL_DRIVER -DUSE_RTOS_SYSTICK -I"/home/joe/programming/embedded/projects/win_test2/Middlewares/ST/STemWin/Config" -I"/home/joe/programming/embedded/projects/win_test2/HAL_Driver/Inc/Legacy" -I"/home/joe/programming/embedded/projects/win_test2/Middlewares/ST/STemWin/inc" -I"/home/joe/programming/embedded/projects/win_test2/Utilities/STM32F4xx-Nucleo" -I"/home/joe/programming/embedded/projects/win_test2/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/home/joe/programming/embedded/projects/win_test2/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/home/joe/programming/embedded/projects/win_test2/inc" -I"/home/joe/programming/embedded/projects/win_test2/CMSIS/device" -I"/home/joe/programming/embedded/projects/win_test2/CMSIS/core" -I"/home/joe/programming/embedded/projects/win_test2/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/home/joe/programming/embedded/projects/win_test2/HAL_Driver/Inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


