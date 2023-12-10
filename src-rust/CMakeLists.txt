add_subdirectory(wrapper)


message("bruh ${CMAKE_CURRENT_SOURCE_DIR}")

add_custom_target(build_src_rust
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/skyfire-rs 
    COMMAND cargo build --release
)

install( 
    FILES ${CMAKE_CURRENT_SOURCE_DIR}/skyfire-rs/target/release/libskyfire_rs.so
    DESTINATION lib
)