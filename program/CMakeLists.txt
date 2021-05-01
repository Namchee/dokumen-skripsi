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

set(SOURCES ${SOURCE_DIR}/utils.h ${SOURCE_DIR}/utils.cpp ${SOURCE_DIR}/eval.h ${SOURCE_DIR}/eval.cpp ${SOURCE_DIR}/similarity.cpp ${SOURCE_DIR}/similarity.h ${SOURCE_DIR}/parser.cpp ${SOURCE_DIR}/parser.h ${SOURCE_DIR}/rombongan.cpp ${SOURCE_DIR}/io.h ${SOURCE_DIR}/io.cpp ./include/rombongan.h ./include/entity.h)

add_executable(main ${SOURCE_DIR}/main.cpp ${SOURCES})
add_executable(test-similarity ${TEST_DIR}/test-similarity.cpp ${SOURCE_DIR}/similarity.h ${SOURCE_DIR}/similarity.cpp)
add_executable(test-i ${TEST_DIR}/io/test-i.cpp ${SOURCE_DIR}/io.h ${SOURCE_DIR}/io.cpp ${SOURCE_DIR}/utils.h ${SOURCE_DIR}/utils.cpp)
add_executable(test-i-path ${TEST_DIR}/io/test-i-path.cpp ${SOURCE_DIR}/io.h ${SOURCE_DIR}/io.cpp ${SOURCE_DIR}/utils.h ${SOURCE_DIR}/utils.cpp)
add_executable(test-i-exception-minimum-entity ${TEST_DIR}/io/test-i-exception-minimum-entity.cpp ${SOURCE_DIR}/io.h ${SOURCE_DIR}/io.cpp ${SOURCE_DIR}/utils.h ${SOURCE_DIR}/utils.cpp)
add_executable(test-i-exception-minimum-interval ${TEST_DIR}/io/test-i-exception-minimum-interval.cpp ${SOURCE_DIR}/io.h ${SOURCE_DIR}/io.cpp ${SOURCE_DIR}/utils.h ${SOURCE_DIR}/utils.cpp)
add_executable(test-i-exception-maximum-range ${TEST_DIR}/io/test-i-exception-maximum-range.cpp ${SOURCE_DIR}/io.h ${SOURCE_DIR}/io.cpp ${SOURCE_DIR}/utils.h ${SOURCE_DIR}/utils.cpp)
add_executable(test-i-exception-cosine-similarity ${TEST_DIR}/io/test-i-exception-cosine-similarity.cpp ${SOURCE_DIR}/io.h ${SOURCE_DIR}/io.cpp ${SOURCE_DIR}/utils.h ${SOURCE_DIR}/utils.cpp)
add_executable(test-parser ${TEST_DIR}/test-parser.cpp ${SOURCE_DIR}/parser.cpp ${SOURCE_DIR}/parser.h ./include/entity.h)
add_executable(test-eval ${TEST_DIR}/test-eval.cpp ${SOURCE_DIR}/eval.cpp ${SOURCE_DIR}/eval.h)

add_subdirectory(./libs/argparse)
target_link_libraries(main argparse)

enable_testing()

# unit test for dynamic time warping algorithm
add_test(NAME DTWAlgorithm COMMAND test-similarity dtw)
add_test(NAME CosineSimilarity COMMAND test-similarity cosine)
add_test(NAME Input COMMAND test-i seq_eth 3 10 0.15 0.0)
add_test(NAME InputPath COMMAND test-i-path seq_eth 3 10 0.15 1.0 -p=abc)
add_test(NAME InputExceptionMinimumEntity COMMAND test-i-exception-minimum-entity seq_eth 1 2 3.0 1.0)
add_test(NAME InputExceptionMinimumInterval COMMAND test-i-exception-minimum-interval seq_eth 2 1 3.0 1.0)
add_test(NAME InputExceptionMaximumRange COMMAND test-i-exception-maximum-range seq_eth 2 2 -3.0 1.0)
add_test(NAME InputExceptionCosineSimilarity COMMAND test-i-exception-cosine-similarity seq_eth 2 2 3.0 1.1)
add_test(NAME Parser COMMAND test-parser)
add_test(NAME Eval COMMAND test-eval)
