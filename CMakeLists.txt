# Copyright 2016, The murrayc-opengl-experiments Development Team
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

cmake_minimum_required (VERSION 3.2)

set (MURRAYC_OPENGL_EXPERIMENTS_MAJOR_VERSION 0)
set (MURRAYC_OPENGL_EXPERIMENTS_MINOR_VERSION 0)
set (MURRAYC_OPENGL_EXPERIMENTS_MICRO_VERSION 3)
set (PACKAGE_VERSION ${MURRAYC_OPENGL_EXPERIMENTS_MAJOR_VERSION}.${MURRAYC_OPENGL_EXPERIMENTS_MINOR_VERSION}.${MURRAYC_OPENGL_EXPERIMENTS_MICRO_VERSION})


project (murrayc_opengl_experiments)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

INCLUDE(FindPkgConfig)

set (OpenGL_GL_PREFERENCE GLVND)
INCLUDE(FindOpenGL REQUIRED)
INCLUDE(FindGLEW REQUIRED)

INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${GLEW_INCLUDE_DIR})

pkg_search_module(SDL2 REQUIRED sdl2)

set (PROJECT_SOURCE_DIR "${murrayc_opengl_experiments_SOURCE_DIR}/src")

include_directories (${murrayc_opengl_experiments_SOURCE_DIR})
include_directories (${murrayc_opengl_experiments_BINARY_DIR})


enable_testing()


add_subdirectory (googletest)
add_subdirectory (src)
add_subdirectory (tests)


set (PROJECT_CMAKE_NAME		"${PROJECT_NAME}-1")
set (VERSION_CONFIG     	"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_CMAKE_NAME}ConfigVersion.cmake")
set (LIBMURRAYC_OPENGL_EXPERIMENTS_INCLUDE_DIR	"${CMAKE_INSTALL_PREFIX}/lib/${PROJECT_NAME}-${MURRAYC_OPENGL_EXPERIMENTS_API_VERSION}/include")
set (PROJECT_CONFIG     	"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_CMAKE_NAME}Config.cmake")
set (CONFIG_INSTALL_DIR 	"lib/cmake/${PROJECT_CMAKE_NAME}")
set (TARGETS_EXPORT_NAME    "${PROJECT_CMAKE_NAME}Targets")
include (CMakePackageConfigHelpers)

write_basic_package_version_file (
    "${VERSION_CONFIG}"
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY SameMajorVersion
)

install (
    FILES "${PROJECT_CONFIG}" "${VERSION_CONFIG}"
    DESTINATION "${CONFIG_INSTALL_DIR}"
)

