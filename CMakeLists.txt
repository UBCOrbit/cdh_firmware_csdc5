project(csdc5 C CXX ASM)

cmake_minimum_required(VERSION 3.6)
enable_language(ASM)
if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Debug")
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# put binaries in ./bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

# all our sources are under ./src
aux_source_directory(src SOURCES)
set(ASM_SOURCES src/startup.s src/isr_vec.s)
include_directories(src)
include_directories(config)

# includes from external packages
include_directories(packages/cmsis)
include_directories(packages/hal/Inc)
include_directories(packages/freertos/include)
include_directories(packages/freertos/portable/GCC/ARM_CM7/r0p1)
aux_source_directory(packages/hal/Src SOURCES)
aux_source_directory(packages/freertos SOURCES)

add_executable(csdc5.elf ${SOURCES} ${ASM_SOURCES})
add_compile_options("-Wall" "-Wextra" "-fexceptions")

# when the build is complete, show how much flash memory we've used up
add_custom_command(
  TARGET csdc5.elf
  POST_BUILD
  COMMAND ${CMAKE_SIZE} bin/csdc5.elf
)
