file(GLOB sources *.cpp *.h *.hpp)

set(SkyfireRsWrapper_SRCS
    ${sources}
)

add_library(skyfire_rs_wrapper STATIC ${SkyfireRsWrapper_SRCS})

target_link_libraries(skyfire_rs_wrapper PRIVATE dl)