cmake_minimum_required(VERSION 3.20)
project(VectorEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Release)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -march=native")
endif()

add_library(vector_engine STATIC
    src/vector_engine.cpp
    src/search.cpp
    src/distances.cpp
)

target_include_directories(vector_engine PUBLIC include)

add_executable(tests tests/test_vector_engine.cpp)
target_link_libraries(tests vector_engine)

enable_testing()
add_test(NAME VectorEngineTests COMMAND tests)