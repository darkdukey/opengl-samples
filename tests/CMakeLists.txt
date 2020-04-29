find_package(GTest REQUIRED)
include(GoogleTest)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_executable(tests tests.cpp)
target_compile_features(tests PRIVATE cxx_std_17)
# Prevent overriding the parent project's compiler/linker
# settings on Windows
include_directories(${CONAN_INCLUDE_DIRS_GTEST})

if (MSVC)
    target_link_libraries(tests PRIVATE yunas-core gtest)
else()
    target_link_libraries(tests PRIVATE yunas-core gtest pthread)
endif (MSVC)

gtest_discover_tests(tests)
