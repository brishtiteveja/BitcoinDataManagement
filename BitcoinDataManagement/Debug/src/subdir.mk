################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Bitcoin\ Data\ Management.cpp \
../src/ComputeOverBitcoinData.cpp \
../src/CreateBitcoinGraph.cpp \
../src/ExtractFromBlockExplorer.cpp \
../src/IdentifyBitcoinUser.cpp \
../src/IdentifyBitcoinUserEfficient.cpp \
../src/RichGetsRicher.cpp \
../src/main.cpp 

OBJS += \
./src/Bitcoin\ Data\ Management.o \
./src/ComputeOverBitcoinData.o \
./src/CreateBitcoinGraph.o \
./src/ExtractFromBlockExplorer.o \
./src/IdentifyBitcoinUser.o \
./src/IdentifyBitcoinUserEfficient.o \
./src/RichGetsRicher.o \
./src/main.o 

CPP_DEPS += \
./src/Bitcoin\ Data\ Management.d \
./src/ComputeOverBitcoinData.d \
./src/CreateBitcoinGraph.d \
./src/ExtractFromBlockExplorer.d \
./src/IdentifyBitcoinUser.d \
./src/IdentifyBitcoinUserEfficient.d \
./src/RichGetsRicher.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/Bitcoin\ Data\ Management.o: ../src/Bitcoin\ Data\ Management.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/Users/zehadyzbdullahkhan/Documents/workspace/programming_language/C,C++/libraries/boost_1_53_0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Bitcoin Data Management.d" -MT"src/Bitcoin\ Data\ Management.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/Users/zehadyzbdullahkhan/Documents/workspace/programming_language/C,C++/libraries/boost_1_53_0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


