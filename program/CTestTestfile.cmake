# CMake generated Testfile for 
# Source directory: /media/namchee/Shared Disk/OS/skripsi/program
# Build directory: /media/namchee/Shared Disk/OS/skripsi/program
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(DTWAlgorithm "/media/namchee/Shared Disk/OS/skripsi/program/bin/test-dtw")
set_tests_properties(DTWAlgorithm PROPERTIES  _BACKTRACE_TRIPLES "/media/namchee/Shared Disk/OS/skripsi/program/CMakeLists.txt;34;add_test;/media/namchee/Shared Disk/OS/skripsi/program/CMakeLists.txt;0;")
add_test(IO "/media/namchee/Shared Disk/OS/skripsi/program/bin/test-io" "seq_eth" "3" "10" "0.15" "1.0")
set_tests_properties(IO PROPERTIES  _BACKTRACE_TRIPLES "/media/namchee/Shared Disk/OS/skripsi/program/CMakeLists.txt;35;add_test;/media/namchee/Shared Disk/OS/skripsi/program/CMakeLists.txt;0;")
add_test(IOPath "/media/namchee/Shared Disk/OS/skripsi/program/bin/test-io-path" "seq_eth" "3" "10" "0.15" "1.0" "-p=abc")
set_tests_properties(IOPath PROPERTIES  _BACKTRACE_TRIPLES "/media/namchee/Shared Disk/OS/skripsi/program/CMakeLists.txt;36;add_test;/media/namchee/Shared Disk/OS/skripsi/program/CMakeLists.txt;0;")
add_test(IOExceptionMinimumEntity "/media/namchee/Shared Disk/OS/skripsi/program/bin/test-io-exception-minimum-entity" "seq_eth" "1" "2" "3.0" "1.0")
set_tests_properties(IOExceptionMinimumEntity PROPERTIES  _BACKTRACE_TRIPLES "/media/namchee/Shared Disk/OS/skripsi/program/CMakeLists.txt;37;add_test;/media/namchee/Shared Disk/OS/skripsi/program/CMakeLists.txt;0;")
add_test(IOExceptionMinimumInterval "/media/namchee/Shared Disk/OS/skripsi/program/bin/test-io-exception-minimum-interval" "seq_eth" "2" "1" "3.0" "1.0")
set_tests_properties(IOExceptionMinimumInterval PROPERTIES  _BACKTRACE_TRIPLES "/media/namchee/Shared Disk/OS/skripsi/program/CMakeLists.txt;38;add_test;/media/namchee/Shared Disk/OS/skripsi/program/CMakeLists.txt;0;")
add_test(IOExceptionMaximumRange "/media/namchee/Shared Disk/OS/skripsi/program/bin/test-io-exception-maximum-range" "seq_eth" "2" "2" "-3.0" "1.0")
set_tests_properties(IOExceptionMaximumRange PROPERTIES  _BACKTRACE_TRIPLES "/media/namchee/Shared Disk/OS/skripsi/program/CMakeLists.txt;39;add_test;/media/namchee/Shared Disk/OS/skripsi/program/CMakeLists.txt;0;")
add_test(IOExceptionCosineSimilarity "/media/namchee/Shared Disk/OS/skripsi/program/bin/test-io-exception-cosine-similarity" "seq_eth" "2" "2" "3.0" "1.1")
set_tests_properties(IOExceptionCosineSimilarity PROPERTIES  _BACKTRACE_TRIPLES "/media/namchee/Shared Disk/OS/skripsi/program/CMakeLists.txt;40;add_test;/media/namchee/Shared Disk/OS/skripsi/program/CMakeLists.txt;0;")
subdirs("libs/argparse")
