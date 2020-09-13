# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)

project ("ObjectPool")

# Define
set(root_dir ${CMAKE_CURRENT_SOURCE_DIR})

# Includes
include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Sources
file(GLOB SOURCES "src/*.cpp")

# Add source to this project's executable.
add_executable (ObjectPool ${SOURCES})

# TODO: Add tests and install targets if needed.
