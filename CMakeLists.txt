cmake_minimum_required(VERSION 3.22)

project(print_Eight_model_IO LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_C_COMPILER MATCHES "arm-none-eabi")
    message(FATAL_ERROR "Use the arm-none-eabi-gcc toolchain (cmake --preset Debug).")
endif()

if(NOT MSPM0_SDK_DIR AND DEFINED ENV{MSPM0_SDK_DIR})
    set(MSPM0_SDK_DIR "$ENV{MSPM0_SDK_DIR}")
endif()
if(NOT MSPM0_SDK_DIR)
    file(GLOB sdk_candidates "$ENV{HOME}/.local/opt/ti/mspm0_sdk_*")
    list(SORT sdk_candidates COMPARE NATURAL ORDER DESCENDING)
    if(sdk_candidates)
        list(GET sdk_candidates 0 MSPM0_SDK_DIR)
    endif()
endif()
if(NOT EXISTS "${MSPM0_SDK_DIR}/source/ti/devices/msp/msp.h")
    message(FATAL_ERROR "Set MSPM0_SDK_DIR to an installed TI MSPM0 SDK directory.")
endif()

set(driverlib "${MSPM0_SDK_DIR}/source/ti/driverlib/lib/gcc/m0p/mspm0g1x0x_g3x0x/driverlib.a")
if(NOT EXISTS "${driverlib}")
    message(FATAL_ERROR "Missing MSPM0G3507 DriverLib: ${driverlib}")
endif()

set(freertos_root "${MSPM0_SDK_DIR}/kernel/freertos")
if(NOT EXISTS "${freertos_root}/Source/include/FreeRTOS.h")
    message(FATAL_ERROR "The selected MSPM0 SDK does not contain FreeRTOS: ${freertos_root}")
endif()

add_executable(${PROJECT_NAME}
    gcc/startup_mspm0g350x_gcc.c
    gcc/assert_handler.c
    Core/Src/ti_msp_dl_config.c
    Core/Src/main.c
    Task/app_main.c
    ${freertos_root}/Source/tasks.c
    ${freertos_root}/Source/list.c
    ${freertos_root}/Source/portable/MemMang/heap_4.c
    ${freertos_root}/Source/portable/GCC/ARM_CM0/port.c
    APP/app_irtracking.c
    APP/app_motor.c
    APP/app_usart.c
    BSP/bsp_at8236.c
    BSP/bsp_enconder.c
    BSP/bsp_usart.c
)

target_include_directories(${PROJECT_NAME} PRIVATE
    . Core/Inc APP BSP Task
    "${freertos_root}/Source/include"
    "${freertos_root}/Source/portable/GCC/ARM_CM0"
    "${MSPM0_SDK_DIR}/source"
    "${MSPM0_SDK_DIR}/source/third_party/CMSIS/Core/Include"
)
target_compile_definitions(${PROJECT_NAME} PRIVATE __MSPM0G3507__)
target_compile_options(${PROJECT_NAME} PRIVATE
    -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft
    -ffunction-sections -fdata-sections -Wall -Wextra
)
target_link_options(${PROJECT_NAME} PRIVATE
    -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft
    -nostartfiles -Wl,--gc-sections
    -T${CMAKE_CURRENT_SOURCE_DIR}/gcc/device_linker.lds
    -Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.map
    --specs=nano.specs --specs=nosys.specs
)
target_link_libraries(${PROJECT_NAME} PRIVATE "${driverlib}" m)
set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".elf")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.hex
    COMMENT "Creating Intel HEX image"
)

# CLion run configuration target: build the firmware without trying to run the
# Cortex-M ELF as a native Linux executable.
add_custom_target(compile_firmware
    DEPENDS ${PROJECT_NAME}
    COMMENT "Firmware build completed: ${PROJECT_NAME}.elf and .hex"
)
