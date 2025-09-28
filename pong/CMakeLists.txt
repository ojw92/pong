# CMakeList.txt : CMake project for pong, include source and define project specific logic here.
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


# --- Assets setup ---
set(PONG_ASSETS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/assets)

# Make assets appear next to the built exe
add_custom_command(
  TARGET pong POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          "${PONG_ASSETS_DIR}" "$<TARGET_FILE_DIR:pong>/assets"
  COMMENT "Copying assets to $<TARGET_FILE_DIR:pong>/assets"
)


# TODO: Add tests and install targets if needed.
