# CMakeList.txt : CMake project for CMakes_me_insane, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (CMakes_me_insane "CMakes_me_insane.cpp" "CMakes_me_insane.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakes_me_insane PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
