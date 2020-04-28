file(GLOB SRC_FILES "*.h" "*.cpp" )

add_executable(program ${SRC_FILES})
target_compile_features(program PRIVATE cxx_std_17)
target_link_libraries(program PRIVATE yunas-core)
