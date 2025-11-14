cmake_minimum_required(VERSION 3.14)
project(test)
cmake_path(SET PROJ_DIR "${CMAKE_CURRENT_SOURCE_DIR}/..")
cmake_path(SET MODULE_DIR "${PROJ_DIR}/src")
message(MODULE_DIR="${MODULE_DIR}")
message(PROJ_DIR="${PROJ_DIR}")
# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 11)
set(CMAKE_COMPILER_IS_GNUCC TRUE)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/52eb8108c5bdec04579160ae17225d66034bd723.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(
	${PROJ_DIR}/Drivers/CMSIS_5/CMSIS/Core/Include
	${PROJ_DIR}/Drivers/CMSIS-DSP/Include
	${PROJ_DIR}/Drivers/CMSIS-Device/ST/STM32H7xx/Include
	${PROJ_DIR}/Drivers/STM32H7xx_HAL_Driver/Inc
	${PROJ_DIR}/src/sys
	${PROJ_DIR}/src/per
  ${PROJ_DIR}/src/SList
)
add_executable(
  testtest
  ${PROJ_DIR}/src/SList/SList.c
  SList/SList-ut.cpp
  HelloWorld/helloworld.cpp
)
target_link_libraries(
  testtest PUBLIC
  GTest::gtest_main
  GTest::gmock_main
)

message("testtest sources: ${testtest_SOURCES}")

include(GoogleTest)
gtest_discover_tests(testtest)