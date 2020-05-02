cmake_minimum_required(VERSION 3.10)
project(yunas-core)

# include conan scripts
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
include(${CMAKE_BINARY_DIR}/conan_paths.cmake)
conan_basic_setup()

# Src and Include folders
file(GLOB SRC_FILES "src/*.h" "src/*.cpp" )
include_directories("src")

# Build Library
add_library(yunas-core ${SRC_FILES})
target_compile_features(yunas-core PRIVATE cxx_std_17)
target_link_libraries(yunas-core ${CONAN_LIBS})

target_include_directories(yunas-core
    PUBLIC 
        $<INSTALL_INTERFACE:src>   
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)

## Copy Shader
file(GLOB TEX_FILES "shaders/*.*")
foreach(file ${TEX_FILES})
    file(RELATIVE_PATH file_rel_path ${CMAKE_CURRENT_SOURCE_DIR} ${file})
    configure_file(${file} "bin/${file_rel_path}" COPYONLY)
endforeach()

## Copy Textures
file(GLOB TEX_FILES "textures/*.*")
foreach(file ${TEX_FILES})
    file(RELATIVE_PATH file_rel_path ${CMAKE_CURRENT_SOURCE_DIR} ${file})
    configure_file(${file} "bin/${file_rel_path}" COPYONLY)
endforeach()

## Copy Textures
file(GLOB TEX_FILES "models/*.*")
foreach(file ${TEX_FILES})
    file(RELATIVE_PATH file_rel_path ${CMAKE_CURRENT_SOURCE_DIR} ${file})
    configure_file(${file} "bin/${file_rel_path}" COPYONLY)
endforeach()


# Build Samples
option (BUILD_SAMPLES "Build the samples" ON)
if (BUILD_SAMPLES)
    add_subdirectory(samples)
endif()


# Build Tests
enable_testing()
option (BUILD_TESTS "Build the samples" ON)
if (BUILD_TESTS)
    add_subdirectory(tests)
endif()
