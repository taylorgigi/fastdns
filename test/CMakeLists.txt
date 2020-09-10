SET(CMAKE_CXX_COMPILER "g++")
SET(CMAKE_CXX_FLAGS "-g -Wall -O0")

include_directories(AFTER SYSTEM /usr/local/include $ENV{HOME}/boost_1_73_0 $ENV{TBBROOT}/include)
link_directories(/usr/local/lib $ENV{HOME}/boost_1_73_0/stage/lib $ENV{TBBROOT}/build/linux_intel64_gcc_cc10.1.1_libc2.31_kernel5.7.6_release)

add_executable(config-parse-test config-parse-test.cpp ../config_parse.cpp ../port_config.cpp ../logger.cpp)

target_link_libraries(config-parse-test yaml-cpp boost_filesystem pthread)
