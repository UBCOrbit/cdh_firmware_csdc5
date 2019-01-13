project(csdc5 C CXX ASM)

cmake_minimum_required(VERSION 3.6)
enable_language(ASM)

# put binaries in ./bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

# all our sources are under ./src
aux_source_directory(src SOURCES)
set(ASM_SOURCES src/startup.s src/isr_vec.s)
include_directories(src)

# includes from external packages
include_directories(packages/cmsis)
include_directories(packages/hal/Inc)
aux_source_directory(packages/hal/Src SOURCES)

add_executable(csdc5.elf ${SOURCES} ${ASM_SOURCES})

# when the build is complete, show how much flash memory we've used up
add_custom_command(
  TARGET csdc5.elf
  POST_BUILD
  COMMAND ${CMAKE_SIZE} bin/csdc5.elf
)
