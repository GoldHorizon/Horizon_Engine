################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../source/drawable.cpp \
../source/game.cpp \
../source/globals.cpp \
../source/main.cpp 

OBJS += \
./source/drawable.o \
./source/game.o \
./source/globals.o \
./source/main.o 

CPP_DEPS += \
./source/drawable.d \
./source/game.d \
./source/globals.d \
./source/main.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


