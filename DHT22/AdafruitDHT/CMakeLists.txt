set(CMAKE_CXX_FLAGS "-Wall -fexceptions -std=c++11")

set(adafruitdht_SRCS
    common_dht_read.c
    common_dht_read.h
    pi_2_dht_read.c
    pi_2_dht_read.h
    pi_2_mmio.c
    pi_2_mmio.h
)

# Declare the library
add_library(adafruitdht STATIC
    ${adafruitdht_SRCS}
)

# Specify here the include directories exported
# by this library
target_include_directories(adafruitdht PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
