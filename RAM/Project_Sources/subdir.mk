################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Project_Sources/adc.c" \
"../Project_Sources/cam.c" \
"../Project_Sources/comms.c" \
"../Project_Sources/cont.c" \
"../Project_Sources/exec.c" \
"../Project_Sources/hello_world.c" \
"../Project_Sources/hl.c" \
"../Project_Sources/lcd.c" \
"../Project_Sources/mot.c" \
"../Project_Sources/schd.c" \
"../Project_Sources/serv.c" \
"../Project_Sources/ui.c" \

C_SRCS += \
../Project_Sources/adc.c \
../Project_Sources/cam.c \
../Project_Sources/comms.c \
../Project_Sources/cont.c \
../Project_Sources/exec.c \
../Project_Sources/hello_world.c \
../Project_Sources/hl.c \
../Project_Sources/lcd.c \
../Project_Sources/mot.c \
../Project_Sources/schd.c \
../Project_Sources/serv.c \
../Project_Sources/ui.c \

OBJS += \
./Project_Sources/adc.o \
./Project_Sources/cam.o \
./Project_Sources/comms.o \
./Project_Sources/cont.o \
./Project_Sources/exec.o \
./Project_Sources/hello_world.o \
./Project_Sources/hl.o \
./Project_Sources/lcd.o \
./Project_Sources/mot.o \
./Project_Sources/schd.o \
./Project_Sources/serv.o \
./Project_Sources/ui.o \

C_DEPS += \
./Project_Sources/adc.d \
./Project_Sources/cam.d \
./Project_Sources/comms.d \
./Project_Sources/cont.d \
./Project_Sources/exec.d \
./Project_Sources/hello_world.d \
./Project_Sources/hl.d \
./Project_Sources/lcd.d \
./Project_Sources/mot.d \
./Project_Sources/schd.d \
./Project_Sources/serv.d \
./Project_Sources/ui.d \

OBJS_QUOTED += \
"./Project_Sources/adc.o" \
"./Project_Sources/cam.o" \
"./Project_Sources/comms.o" \
"./Project_Sources/cont.o" \
"./Project_Sources/exec.o" \
"./Project_Sources/hello_world.o" \
"./Project_Sources/hl.o" \
"./Project_Sources/lcd.o" \
"./Project_Sources/mot.o" \
"./Project_Sources/schd.o" \
"./Project_Sources/serv.o" \
"./Project_Sources/ui.o" \

C_DEPS_QUOTED += \
"./Project_Sources/adc.d" \
"./Project_Sources/cam.d" \
"./Project_Sources/comms.d" \
"./Project_Sources/cont.d" \
"./Project_Sources/exec.d" \
"./Project_Sources/hello_world.d" \
"./Project_Sources/hl.d" \
"./Project_Sources/lcd.d" \
"./Project_Sources/mot.d" \
"./Project_Sources/schd.d" \
"./Project_Sources/serv.d" \
"./Project_Sources/ui.d" \

OBJS_OS_FORMAT += \
./Project_Sources/adc.o \
./Project_Sources/cam.o \
./Project_Sources/comms.o \
./Project_Sources/cont.o \
./Project_Sources/exec.o \
./Project_Sources/hello_world.o \
./Project_Sources/hl.o \
./Project_Sources/lcd.o \
./Project_Sources/mot.o \
./Project_Sources/schd.o \
./Project_Sources/serv.o \
./Project_Sources/ui.o \


# Each subdirectory must supply rules for building sources it contributes
Project_Sources/adc.o: ../Project_Sources/adc.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Project_Sources/adc.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Project_Sources/adc.o"
	@echo 'Finished building: $<'
	@echo ' '

Project_Sources/cam.o: ../Project_Sources/cam.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Project_Sources/cam.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Project_Sources/cam.o"
	@echo 'Finished building: $<'
	@echo ' '

Project_Sources/comms.o: ../Project_Sources/comms.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Project_Sources/comms.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Project_Sources/comms.o"
	@echo 'Finished building: $<'
	@echo ' '

Project_Sources/cont.o: ../Project_Sources/cont.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Project_Sources/cont.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Project_Sources/cont.o"
	@echo 'Finished building: $<'
	@echo ' '

Project_Sources/exec.o: ../Project_Sources/exec.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Project_Sources/exec.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Project_Sources/exec.o"
	@echo 'Finished building: $<'
	@echo ' '

Project_Sources/hello_world.o: ../Project_Sources/hello_world.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Project_Sources/hello_world.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Project_Sources/hello_world.o"
	@echo 'Finished building: $<'
	@echo ' '

Project_Sources/hl.o: ../Project_Sources/hl.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Project_Sources/hl.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Project_Sources/hl.o"
	@echo 'Finished building: $<'
	@echo ' '

Project_Sources/lcd.o: ../Project_Sources/lcd.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Project_Sources/lcd.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Project_Sources/lcd.o"
	@echo 'Finished building: $<'
	@echo ' '

Project_Sources/mot.o: ../Project_Sources/mot.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Project_Sources/mot.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Project_Sources/mot.o"
	@echo 'Finished building: $<'
	@echo ' '

Project_Sources/schd.o: ../Project_Sources/schd.c
	@echo 'Building file: $<'
	@echo 'Executing target #16 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Project_Sources/schd.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Project_Sources/schd.o"
	@echo 'Finished building: $<'
	@echo ' '

Project_Sources/serv.o: ../Project_Sources/serv.c
	@echo 'Building file: $<'
	@echo 'Executing target #17 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Project_Sources/serv.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Project_Sources/serv.o"
	@echo 'Finished building: $<'
	@echo ' '

Project_Sources/ui.o: ../Project_Sources/ui.c
	@echo 'Building file: $<'
	@echo 'Executing target #18 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Project_Sources/ui.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Project_Sources/ui.o"
	@echo 'Finished building: $<'
	@echo ' '


