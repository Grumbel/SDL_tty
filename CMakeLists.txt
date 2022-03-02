# SDL_tty - Terminal-like output for SDL
# Copyright (C) 2015 Ingo Ruhnke <grumbel@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.11)
project(SDL_tty VERSION 0.0.0)

include(GNUInstallDirs)

find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)

add_library(SDL_tty src/SDL_fnt.c src/SDL_tty.c)
set_target_properties(SDL_tty PROPERTIES
  PUBLIC_HEADER "include/SDL_fnt.h;include/SDL_tty.h")
target_link_libraries(SDL_tty SDL::SDL ${SDL_IMAGE_LIBRARIES})
target_include_directories(SDL_tty
  SYSTEM PUBLIC ${SDL_IMAGE_INCLUDE_DIRS}
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
  $<INSTALL_INTERFACE:include>)

add_executable(sdltty-fontdump src/fontdump.c)
target_link_libraries(sdltty-fontdump SDL_tty)

# c64lookalike to run in build/ directory
add_executable(sdltty-c64lookalike src/c64lookalike.c)
target_compile_definitions(sdltty-c64lookalike PUBLIC
  TTY_DATADIR=\"data/\")
target_link_libraries(sdltty-c64lookalike SDL_tty)

# c64lookalike for install
add_executable(.sdltty-c64lookalike src/c64lookalike.c)
target_compile_definitions(.sdltty-c64lookalike PUBLIC
  TTY_DATADIR=\"${CMAKE_INSTALL_FULL_DATADIR}/${PROJECT_NAME}\")
target_link_libraries(.sdltty-c64lookalike SDL_tty)

file(COPY data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/data/)

# CMake integration
configure_file(sdl_tty-config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_FILES_DIRECTORY}/sdl_tty-config.cmake" @ONLY)
install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_FILES_DIRECTORY}/sdl_tty-config.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/SDL_tty/")
export(TARGETS SDL_tty
  FILE "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_FILES_DIRECTORY}/sdl_tty-targets.cmake")
export(PACKAGE SDL_tty)
install(EXPORT sdl_tty-targets
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/SDL_tty/")

install(TARGETS .sdltty-c64lookalike
  RENAME sdltty-c64lookalike
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(TARGETS sdltty-fontdump
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(TARGETS SDL_tty
  EXPORT sdl_tty-targets
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

install(TARGETS SDL_tty
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER ${CMAKE_INSTALL_INCLUDES})

install(DIRECTORY data/
  DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME})

# EOF #
