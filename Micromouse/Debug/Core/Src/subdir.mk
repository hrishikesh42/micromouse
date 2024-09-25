################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/LED_Display.c \
../Core/Src/adc.c \
../Core/Src/dma.c \
../Core/Src/encoder.c \
../Core/Src/flood.c \
../Core/Src/gpio.c \
../Core/Src/hugger.c \
../Core/Src/lock.c \
../Core/Src/main.c \
../Core/Src/motors.c \
../Core/Src/pdT.c \
../Core/Src/pdV.c \
../Core/Src/spi.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c \
../Core/Src/tim.c 

OBJS += \
./Core/Src/LED_Display.o \
./Core/Src/adc.o \
./Core/Src/dma.o \
./Core/Src/encoder.o \
./Core/Src/flood.o \
./Core/Src/gpio.o \
./Core/Src/hugger.o \
./Core/Src/lock.o \
./Core/Src/main.o \
./Core/Src/motors.o \
./Core/Src/pdT.o \
./Core/Src/pdV.o \
./Core/Src/spi.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o \
./Core/Src/tim.o 

C_DEPS += \
./Core/Src/LED_Display.d \
./Core/Src/adc.d \
./Core/Src/dma.d \
./Core/Src/encoder.d \
./Core/Src/flood.d \
./Core/Src/gpio.d \
./Core/Src/hugger.d \
./Core/Src/lock.d \
./Core/Src/main.d \
./Core/Src/motors.d \
./Core/Src/pdT.d \
./Core/Src/pdV.d \
./Core/Src/spi.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d \
./Core/Src/tim.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/LED_Display.cyclo ./Core/Src/LED_Display.d ./Core/Src/LED_Display.o ./Core/Src/LED_Display.su ./Core/Src/adc.cyclo ./Core/Src/adc.d ./Core/Src/adc.o ./Core/Src/adc.su ./Core/Src/dma.cyclo ./Core/Src/dma.d ./Core/Src/dma.o ./Core/Src/dma.su ./Core/Src/encoder.cyclo ./Core/Src/encoder.d ./Core/Src/encoder.o ./Core/Src/encoder.su ./Core/Src/flood.cyclo ./Core/Src/flood.d ./Core/Src/flood.o ./Core/Src/flood.su ./Core/Src/gpio.cyclo ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/hugger.cyclo ./Core/Src/hugger.d ./Core/Src/hugger.o ./Core/Src/hugger.su ./Core/Src/lock.cyclo ./Core/Src/lock.d ./Core/Src/lock.o ./Core/Src/lock.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/motors.cyclo ./Core/Src/motors.d ./Core/Src/motors.o ./Core/Src/motors.su ./Core/Src/pdT.cyclo ./Core/Src/pdT.d ./Core/Src/pdT.o ./Core/Src/pdT.su ./Core/Src/pdV.cyclo ./Core/Src/pdV.d ./Core/Src/pdV.o ./Core/Src/pdV.su ./Core/Src/spi.cyclo ./Core/Src/spi.d ./Core/Src/spi.o ./Core/Src/spi.su ./Core/Src/stm32f1xx_hal_msp.cyclo ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_it.cyclo ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f1xx.cyclo ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su ./Core/Src/tim.cyclo ./Core/Src/tim.d ./Core/Src/tim.o ./Core/Src/tim.su

.PHONY: clean-Core-2f-Src

