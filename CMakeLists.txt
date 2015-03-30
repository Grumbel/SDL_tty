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

cmake_minimum_required(VERSION 3.0)
project(SDL_tty VERSION 0.0.0)

find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)

set(SDL_TTY_SOURCES src/SDL_fnt.c src/SDL_tty.c)
set(FONTDUMP_SOURCES src/fontdump.c)
set(C64LOOKALIKE_SOURCES src/c64lookalike.c)

include_directories(include/)
include_directories(src/)

add_library(SDL_tty ${SDL_TTY_SOURCES})
target_link_libraries(SDL_tty ${SDL_LIBRARY} ${SDL_IMAGE_LIBRARIES})
target_include_directories(SDL_tty SYSTEM PUBLIC ${SDL_INCLUDE_DIR} ${SDL_IMAGE_INCLUDE_DIRS})

add_executable(fontdump ${FONTDUMP_SOURCES})
target_link_libraries(fontdump SDL_tty)

add_executable(c64lookalike ${C64LOOKALIKE_SOURCES})
target_link_libraries(c64lookalike SDL_tty)

# EOF #
