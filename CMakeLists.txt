cmake_minimum_required(VERSION 3.11)
project ( Flock )
include_directories(3rdparty/gtest/include)
link_directories(3rdparty/gtest/lib)

include_directories(3rdparty/SFML-2.4.2/include)
link_directories(3rdparty/SFML-2.4.2/lib)


file(GLOB SFML_LIBS "3rdparty/SFML-2.4.2/lib/*.lib")
file(GLOB SFML_DLIBS "3rdparty/SFML-2.4.2/bin/*.dll")

file(GLOB LOCAL_SRC "include/*.h")
file(GLOB LOCAL_INC "src/*.cpp")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
message(STATUS "files  ${LOCAL_SRC} ${LOCAL_INC}")

add_executable (flockCMake main.cpp ${LOCAL_SRC} ${LOCAL_INC})
target_link_libraries(flockCMake gtest gtest_main ${SFML_LIBS})
