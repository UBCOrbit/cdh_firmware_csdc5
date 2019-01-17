set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_SIZE arm-none-eabi-size)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(FLAGS_COMMON "-mthumb -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -fdata-sections -ffunction-sections -Wall -g3" CACHE INTERNAL "C / C++ common Flags")
set(FLAGS_CXX "-fno-unwind-tables -fno-exceptions -fno-rtti" CACHE INTERNAL "C++ only Flags")
set(FLAGS_C "" CACHE INTERNAL "C only Flags")
set(FLAGS_LINKER "-Wl,--gc-sections --specs=nano.specs -Tmem.ld -lc -lm -lnosys -Wl,-Map=bin/${CMAKE_PROJECT_NAME}.map" CACHE INTERNAL "Linker flags")

set(CMAKE_C_FLAGS "${FLAGS_COMMON} ${FLAGS_C}" CACHE STRING "C Compiler Flags")
set(CMAKE_C_FLAGS_DEBUG "-Og")
set(CMAKE_C_FLAGS_RELEASE "-Os")

set(CMAKE_CXX_FLAGS "${FLAGS_COMMON} ${FLAGS_CXX}" CACHE STRING "C++ Compiler Flags")
set(CMAKE_CXX_FLAGS_DEBUG "-Og")
set(CMAKE_CXX_FLAGS_RELEASE "-Os")

set(CMAKE_EXE_LINKER_FLAGS "${FLAGS_COMMON} ${FLAGS_LINKER}" CACHE STRING "Linker flags")
