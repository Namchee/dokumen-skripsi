cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME rombongan)
set(SOURCE_DIR ./src)
set(TEST_DIR ./test)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(${PROJECT_NAME} VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(./include ./src ./test ./libs/argparse/include)

set(SOURCES ${SOURCE_DIR}/dtw.cpp ${SOURCE_DIR}/dtw.h ${SOURCE_DIR}/parser.cpp ${SOURCE_DIR}/parser.h ${SOURCE_DIR}/rombongan.cpp ${SOURCE_DIR}/io.h ${SOURCE_DIR}/io.cpp ./include/rombongan.h ./include/entity.h)

add_executable(main ${SOURCE_DIR}/main.cpp ${SOURCES})
add_executable(test-dtw ${TEST_DIR}/test-dtw.cpp ${SOURCES})

add_subdirectory(./libs/argparse)
target_link_libraries(main argparse)

enable_testing()

# unit test for dynamic time warping algorithm
add_test(NAME dtw COMMAND test-dtw)
