cmake_minimum_required(VERSION 2.6)

set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS)
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS)

set(CMAKE_CXX_FLAGS "-Wall -fexceptions -std=c++11")

set(main_SRCS
    read_dht.cpp
)

add_subdirectory(AdafruitDHT)

add_executable(read_dht
    ${main_SRCS}
)

target_link_libraries(read_dht
    adafruitdht
    rt
)

#install(TARGETS read_dht DESTINATION bin)
