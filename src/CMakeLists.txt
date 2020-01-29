# Copyright 2020, Murray Cumming
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

set (SOURCE_FILES
  buffer.h
  buffer.cc
  camera.h
  camera.cc
  shader.h
  shader.cc
  program.h
  program.cc
  texture.h
  texture.cc
  transform.h
  transform.cc
  vertex.h
  vertex.cc
  vertex_array.h
  vertex_array.cc
  main.cc
)

add_executable(example ${SOURCE_FILES})
target_link_libraries(example ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} -lstb)

