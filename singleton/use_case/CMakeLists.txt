CMAKE_MINIMUM_REQUIRED(VERSION 3.8.2)
project(Singleton)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_BUILD_TYPE Debug CACHE STRING "set build type")
message("CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE})

set(CMAKE_CXX_FLAGS_DEBUG "-g -ggdb -std=c++11  -Wall -w -O1 -fPIC -pthread -fopenmp -fsigned-char -save-temps")
set(CMAKE_CXX_FLAGS_RELEASE "-std=c++11  -Wall -w -O3 -fPIC -pthread -fopenmp -fsigned-char")
set(CMAKE_C_FLAGS_DEBUG "-g -ggdb -std=c11 -Wall -w -O0 -fPIC -pthread -fopenmp -fsigned-char -save-temps")
set(CMAKE_C_FLAGS_RELEASE "-std=c11 -Wall -w -O3 -fPIC -pthread -fopenmp -fsigned-char")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/testSuite/include
					${CMAKE_CURRENT_SOURCE_DIR}/opTest/include
					${CMAKE_CURRENT_SOURCE_DIR}/transposeTest/include
					)

file(GLOB TESTSUITE_SRCS ${CMAKE_CURRENT_LIST_DIR}/testSuite/source/*.cpp)
message("TESTSUITE_SRCS: " ${TESTSUITE_SRCS})

file(GLOB OPTEST_SRCS ${CMAKE_CURRENT_LIST_DIR}/opTest/source/*.cpp)
message("OPTEST_SRCS: " ${OPTEST_SRCS})
add_executable(opTest.out ${OPTEST_SRCS} ${TESTSUITE_SRCS})

file(GLOB TRANSPOSETEST_SRCS ${CMAKE_CURRENT_LIST_DIR}/transposeTest/source/*.cpp)
message("TRANSPOSETEST_SRCS: " ${TRANSPOSETEST_SRCS})
add_executable(transposeTest.out ${TRANSPOSETEST_SRCS} ${TESTSUITE_SRCS})