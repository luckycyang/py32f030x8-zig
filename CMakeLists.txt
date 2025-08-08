cmake_minimum_required(VERSION 3.20)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/toolchain.cmake)

file(GLOB C_SOURCES "PY32F0xx_Firmware/Drivers/PY32F0xx_HAL_Driver/Src/*.c")

project(hal)
add_library(hal STATIC ${C_SOURCES})
target_include_directories(
  hal
  PUBLIC "PY32F0xx_Firmware/Drivers/PY32F0xx_HAL_Driver/Inc"
         "./PY32F0xx_Firmware/Drivers/CMSIS/Device/PY32F0xx/Include"
         "./PY32F0xx_Firmware/Drivers/CMSIS/Include" "inc")
target_compile_definitions(hal PUBLIC -DPY32F030x8)
target_compile_options(hal PUBLIC -mcpu=cortex-m0plus -mthumb)
