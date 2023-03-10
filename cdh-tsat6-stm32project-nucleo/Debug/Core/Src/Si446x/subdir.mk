################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Si446x/Si446x.c \
../Core/Src/Si446x/Si446x_spi.c 

OBJS += \
./Core/Src/Si446x/Si446x.o \
./Core/Src/Si446x/Si446x_spi.o 

C_DEPS += \
./Core/Src/Si446x/Si446x.d \
./Core/Src/Si446x/Si446x_spi.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Si446x/%.o Core/Src/Si446x/%.su: ../Core/Src/Si446x/%.c Core/Src/Si446x/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L452xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Si446x

clean-Core-2f-Src-2f-Si446x:
	-$(RM) ./Core/Src/Si446x/Si446x.d ./Core/Src/Si446x/Si446x.o ./Core/Src/Si446x/Si446x.su ./Core/Src/Si446x/Si446x_spi.d ./Core/Src/Si446x/Si446x_spi.o ./Core/Src/Si446x/Si446x_spi.su

.PHONY: clean-Core-2f-Src-2f-Si446x

