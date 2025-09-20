# CMakeList.txt : CMake project for pong, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (pong "main.cpp")

find_package(SDL3 CONFIG REQUIRED)
target_link_libraries(pong PRIVATE SDL3::SDL3)

find_package(raylib CONFIG REQUIRED)
target_link_libraries(pong PRIVATE raylib)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET pong PROPERTY CXX_STANDARD 23)
endif()

# TODO: Add tests and install targets if needed.
