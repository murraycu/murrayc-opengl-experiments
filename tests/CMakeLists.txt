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

enable_testing ()

set (TEST_SOURCE_FILES
  test_vertex.cc)

function (add_murrayc_opengl_experiments_test TEST_SOURCE_FILE)
	get_filename_component (test_name ${TEST_SOURCE_FILE} NAME_WE)
	add_executable (${test_name} ${TEST_SOURCE_FILE})
	target_include_directories (${test_name} PRIVATE "../src")
	target_link_libraries (${test_name} gtest gtest_main)
	add_test (${test_name} ${CMAKE_CURRENT_BINARY_DIR}/${test_name})
endfunction (add_murrayc_opengl_experiments_test)

foreach (test_file ${TEST_SOURCE_FILES})
	add_murrayc_opengl_experiments_test (${test_file})
endforeach()
