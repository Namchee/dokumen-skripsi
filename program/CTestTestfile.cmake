# CMake generated Testfile for 
# Source directory: /cygdrive/d/skripsi/repository/program
# Build directory: /cygdrive/d/skripsi/repository/program
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(DTWAlgorithm "/cygdrive/d/skripsi/repository/program/bin/test-similarity.exe" "dtw")
set_tests_properties(DTWAlgorithm PROPERTIES  _BACKTRACE_TRIPLES "/cygdrive/d/skripsi/repository/program/CMakeLists.txt;34;add_test;/cygdrive/d/skripsi/repository/program/CMakeLists.txt;0;")
add_test(CosineSimilarity "/cygdrive/d/skripsi/repository/program/bin/test-similarity.exe" "cosine")
set_tests_properties(CosineSimilarity PROPERTIES  _BACKTRACE_TRIPLES "/cygdrive/d/skripsi/repository/program/CMakeLists.txt;35;add_test;/cygdrive/d/skripsi/repository/program/CMakeLists.txt;0;")
add_test(Input "/cygdrive/d/skripsi/repository/program/bin/test-i.exe" "seq_eth" "3" "10" "0.15" "1.0")
set_tests_properties(Input PROPERTIES  _BACKTRACE_TRIPLES "/cygdrive/d/skripsi/repository/program/CMakeLists.txt;36;add_test;/cygdrive/d/skripsi/repository/program/CMakeLists.txt;0;")
add_test(InputPath "/cygdrive/d/skripsi/repository/program/bin/test-i-path.exe" "seq_eth" "3" "10" "0.15" "1.0" "-p=abc")
set_tests_properties(InputPath PROPERTIES  _BACKTRACE_TRIPLES "/cygdrive/d/skripsi/repository/program/CMakeLists.txt;37;add_test;/cygdrive/d/skripsi/repository/program/CMakeLists.txt;0;")
add_test(InputExceptionMinimumEntity "/cygdrive/d/skripsi/repository/program/bin/test-i-exception-minimum-entity.exe" "seq_eth" "1" "2" "3.0" "1.0")
set_tests_properties(InputExceptionMinimumEntity PROPERTIES  _BACKTRACE_TRIPLES "/cygdrive/d/skripsi/repository/program/CMakeLists.txt;38;add_test;/cygdrive/d/skripsi/repository/program/CMakeLists.txt;0;")
add_test(InputExceptionMinimumInterval "/cygdrive/d/skripsi/repository/program/bin/test-i-exception-minimum-interval.exe" "seq_eth" "2" "1" "3.0" "1.0")
set_tests_properties(InputExceptionMinimumInterval PROPERTIES  _BACKTRACE_TRIPLES "/cygdrive/d/skripsi/repository/program/CMakeLists.txt;39;add_test;/cygdrive/d/skripsi/repository/program/CMakeLists.txt;0;")
add_test(InputExceptionMaximumRange "/cygdrive/d/skripsi/repository/program/bin/test-i-exception-maximum-range.exe" "seq_eth" "2" "2" "-3.0" "1.0")
set_tests_properties(InputExceptionMaximumRange PROPERTIES  _BACKTRACE_TRIPLES "/cygdrive/d/skripsi/repository/program/CMakeLists.txt;40;add_test;/cygdrive/d/skripsi/repository/program/CMakeLists.txt;0;")
add_test(InputExceptionCosineSimilarity "/cygdrive/d/skripsi/repository/program/bin/test-i-exception-cosine-similarity.exe" "seq_eth" "2" "2" "3.0" "1.1")
set_tests_properties(InputExceptionCosineSimilarity PROPERTIES  _BACKTRACE_TRIPLES "/cygdrive/d/skripsi/repository/program/CMakeLists.txt;41;add_test;/cygdrive/d/skripsi/repository/program/CMakeLists.txt;0;")
add_test(Parser "/cygdrive/d/skripsi/repository/program/bin/test-parser.exe")
set_tests_properties(Parser PROPERTIES  _BACKTRACE_TRIPLES "/cygdrive/d/skripsi/repository/program/CMakeLists.txt;42;add_test;/cygdrive/d/skripsi/repository/program/CMakeLists.txt;0;")
subdirs("libs/argparse")
