# CMake generated Testfile for 
# Source directory: /media/namchee/Shared Disk/skripsi/repository/program
# Build directory: /media/namchee/Shared Disk/skripsi/repository/program
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(DTWAlgorithm "/media/namchee/Shared Disk/skripsi/repository/program/bin/test-similarity" "dtw")
set_tests_properties(DTWAlgorithm PROPERTIES  _BACKTRACE_TRIPLES "/media/namchee/Shared Disk/skripsi/repository/program/CMakeLists.txt;34;add_test;/media/namchee/Shared Disk/skripsi/repository/program/CMakeLists.txt;0;")
add_test(CosineSimilarity "/media/namchee/Shared Disk/skripsi/repository/program/bin/test-similarity" "cosine")
set_tests_properties(CosineSimilarity PROPERTIES  _BACKTRACE_TRIPLES "/media/namchee/Shared Disk/skripsi/repository/program/CMakeLists.txt;35;add_test;/media/namchee/Shared Disk/skripsi/repository/program/CMakeLists.txt;0;")
add_test(Input "/media/namchee/Shared Disk/skripsi/repository/program/bin/test-i" "seq_eth" "3" "10" "0.15" "1.0")
set_tests_properties(Input PROPERTIES  _BACKTRACE_TRIPLES "/media/namchee/Shared Disk/skripsi/repository/program/CMakeLists.txt;36;add_test;/media/namchee/Shared Disk/skripsi/repository/program/CMakeLists.txt;0;")
add_test(InputPath "/media/namchee/Shared Disk/skripsi/repository/program/bin/test-i-path" "seq_eth" "3" "10" "0.15" "1.0" "-p=abc")
set_tests_properties(InputPath PROPERTIES  _BACKTRACE_TRIPLES "/media/namchee/Shared Disk/skripsi/repository/program/CMakeLists.txt;37;add_test;/media/namchee/Shared Disk/skripsi/repository/program/CMakeLists.txt;0;")
add_test(InputExceptionMinimumEntity "/media/namchee/Shared Disk/skripsi/repository/program/bin/test-i-exception-minimum-entity" "seq_eth" "1" "2" "3.0" "1.0")
set_tests_properties(InputExceptionMinimumEntity PROPERTIES  _BACKTRACE_TRIPLES "/media/namchee/Shared Disk/skripsi/repository/program/CMakeLists.txt;38;add_test;/media/namchee/Shared Disk/skripsi/repository/program/CMakeLists.txt;0;")
add_test(InputExceptionMinimumInterval "/media/namchee/Shared Disk/skripsi/repository/program/bin/test-i-exception-minimum-interval" "seq_eth" "2" "1" "3.0" "1.0")
set_tests_properties(InputExceptionMinimumInterval PROPERTIES  _BACKTRACE_TRIPLES "/media/namchee/Shared Disk/skripsi/repository/program/CMakeLists.txt;39;add_test;/media/namchee/Shared Disk/skripsi/repository/program/CMakeLists.txt;0;")
add_test(InputExceptionMaximumRange "/media/namchee/Shared Disk/skripsi/repository/program/bin/test-i-exception-maximum-range" "seq_eth" "2" "2" "-3.0" "1.0")
set_tests_properties(InputExceptionMaximumRange PROPERTIES  _BACKTRACE_TRIPLES "/media/namchee/Shared Disk/skripsi/repository/program/CMakeLists.txt;40;add_test;/media/namchee/Shared Disk/skripsi/repository/program/CMakeLists.txt;0;")
add_test(InputExceptionCosineSimilarity "/media/namchee/Shared Disk/skripsi/repository/program/bin/test-i-exception-cosine-similarity" "seq_eth" "2" "2" "3.0" "1.1")
set_tests_properties(InputExceptionCosineSimilarity PROPERTIES  _BACKTRACE_TRIPLES "/media/namchee/Shared Disk/skripsi/repository/program/CMakeLists.txt;41;add_test;/media/namchee/Shared Disk/skripsi/repository/program/CMakeLists.txt;0;")
add_test(Parser "/media/namchee/Shared Disk/skripsi/repository/program/bin/test-parser")
set_tests_properties(Parser PROPERTIES  _BACKTRACE_TRIPLES "/media/namchee/Shared Disk/skripsi/repository/program/CMakeLists.txt;42;add_test;/media/namchee/Shared Disk/skripsi/repository/program/CMakeLists.txt;0;")
subdirs("libs/argparse")
