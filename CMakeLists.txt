cmake_minimum_required (VERSION 3.8)
project (rt)

# get rid of annoying MSVC warnings.
add_definitions(-D_CRT_SECURE_NO_WARNINGS )

set (CMAKE_CXX_STANDARD 11)
SET(MYCOMPILE_FLAGS "-fopenmp -O3")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${MYCOMPILE_FLAGS}")

add_executable(rt main.cpp Bitmap.cpp shapes.cpp trace_ray.cpp vec3m.cpp)

target_link_libraries(rt ${ALL_LIBS})

