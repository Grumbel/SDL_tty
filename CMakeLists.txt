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
target_link_libraries(SDL_tty ${SDL_LIBRARY} ${SDL_IMAGE_LIBRARIES})
target_include_directories(SDL_tty
  SYSTEM PUBLIC ${SDL_INCLUDE_DIR} ${SDL_IMAGE_INCLUDE_DIRS}
  PUBLIC include/ src/)

add_executable(fontdump src/fontdump.c)
target_link_libraries(fontdump SDL_tty)

add_executable(c64lookalike src/c64lookalike.c)
target_link_libraries(c64lookalike SDL_tty)

install(TARGETS fontdump c64lookalike RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS SDL_tty c64lookalike
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER ${CMAKE_INSTALL_INCLUDES})

# EOF #

