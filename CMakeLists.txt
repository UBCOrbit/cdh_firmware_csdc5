project(csdc5 C CXX ASM)

cmake_minimum_required(VERSION 3.6)
enable_language(ASM)
if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Debug")
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# put binaries in ./bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY bin)

# all our sources are under ./src
file(GLOB_RECURSE SOURCES src/*.cpp src/*.h)
set(ASM_SOURCES src/startup/startup.s src/startup/isr_vec.s)
include_directories(src)
include_directories(config)

# includes from external packages
include_directories(packages/cmsis)
include_directories(packages/hal/Inc)
include_directories(packages/freertos/include)
include_directories(packages/freertos/portable/GCC/ARM_CM7/r0p1)

aux_source_directory(packages/hal/Src HAL_SOURCES)
aux_source_directory(packages/freertos RTOS_SOURCES)
aux_source_directory(packages/freertos/portable/GCC/ARM_CM7/r0p1 RTOS_SOURCES)

add_library(sthal STATIC ${HAL_SOURCES})
add_library(freertos STATIC ${RTOS_SOURCES})

add_executable(csdc5-a.elf ${SOURCES} ${ASM_SOURCES})
set_target_properties(csdc5-a.elf PROPERTIES COMPILE_DEFINITIONS "TRILLIUM=1")
target_link_libraries(csdc5-a.elf sthal freertos)

add_executable(csdc5-b.elf ${SOURCES} ${ASM_SOURCES})
set_target_properties(csdc5-b.elf PROPERTIES COMPILE_DEFINITIONS "TRILLIUM=2")
target_link_libraries(csdc5-b.elf sthal freertos)

add_executable(csdc5-c.elf ${SOURCES} ${ASM_SOURCES})
set_target_properties(csdc5-c.elf PROPERTIES COMPILE_DEFINITIONS "TRILLIUM=3")
target_link_libraries(csdc5-c.elf sthal freertos)

add_compile_options("-Wall" "-Wextra" "-fexceptions")

# when the build is complete, show how much flash memory we've used up
add_custom_command(
  TARGET csdc5-a.elf
  POST_BUILD
  COMMAND ${CMAKE_SIZE} bin/csdc5-a.elf
)
