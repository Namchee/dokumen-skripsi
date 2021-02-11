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
add_executable(test-dtw ${TEST_DIR}/test-dtw.cpp ${SOURCE_DIR}/dtw.h ${SOURCE_DIR}/dtw.cpp)
add_executable(test-io ${TEST_DIR}/io/test-io.cpp ${SOURCE_DIR}/io.h ${SOURCE_DIR}/io.cpp)
add_executable(test-io-path ${TEST_DIR}/io/test-io-path.cpp ${SOURCE_DIR}/io.h ${SOURCE_DIR}/io.cpp)
add_executable(test-io-exception-minimum-entity ${TEST_DIR}/io/test-io-exception-minimum-entity.cpp ${SOURCE_DIR}/io.h ${SOURCE_DIR}/io.cpp)
add_executable(test-io-exception-minimum-interval ${TEST_DIR}/io/test-io-exception-minimum-interval.cpp ${SOURCE_DIR}/io.h ${SOURCE_DIR}/io.cpp)
add_executable(test-io-exception-maximum-range ${TEST_DIR}/io/test-io-exception-maximum-range.cpp ${SOURCE_DIR}/io.h ${SOURCE_DIR}/io.cpp)
add_executable(test-io-exception-cosine-similarity ${TEST_DIR}/io/test-io-exception-cosine-similarity.cpp ${SOURCE_DIR}/io.h ${SOURCE_DIR}/io.cpp)

add_subdirectory(./libs/argparse)
target_link_libraries(main argparse)

enable_testing()

# unit test for dynamic time warping algorithm
add_test(NAME DTWAlgorithm COMMAND test-dtw)
add_test(NAME IO COMMAND test-io seq_eth 3 10 0.15 1.0)
add_test(NAME IOPath COMMAND test-io-path seq_eth 3 10 0.15 1.0 -p=abc)
add_test(NAME IOExceptionMinimumEntity COMMAND test-io-exception-minimum-entity seq_eth 1 2 3.0 1.0)
add_test(NAME IOExceptionMinimumInterval COMMAND test-io-exception-minimum-interval seq_eth 2 1 3.0 1.0)
add_test(NAME IOExceptionMaximumRange COMMAND test-io-exception-maximum-range seq_eth 2 2 -3.0 1.0)
add_test(NAME IOExceptionCosineSimilarity COMMAND test-io-exception-cosine-similarity seq_eth 2 2 3.0 1.1)
