
set(WorldServerRsLib_SRCS
    WorldServerRs.cpp
    WorldServerRs.h
)

add_library(WorldServerRsLib STATIC ${WorldServerRsLib_SRCS})

target_link_libraries(WorldServerRsLib dl)