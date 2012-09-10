cmake_minimum_required(VERSION 2.8)

project(util)

find_package(Boost COMPONENTS regex system unit_test_framework thread REQUIRED)

include_directories("${CMAKE_SOURCE_DIR}")

set(util_test_SRCS
		ansi/colors.cpp
		ansi/colors.hpp
		ansi/colors_tests.cpp

		asio/buffer_queue.cpp
		asio/buffer_queue.hpp
		
		buffer/appendable_buffer.cpp
		buffer/appendable_buffer.hpp
		buffer/appendable_buffer_tests.cpp

		console/auto_mode.hpp
		console/console.cpp
		console/console.hpp
		console/mode.cpp
		console/mode.hpp

		crypto/_detail/sha1.c
		crypto/_detail/sha1.h
		crypto/_detail/shannon_impl.cpp
		crypto/_detail/shannon_impl.h

		crypto/sha1_hmac.cpp
		crypto/sha1_hmac.hpp
		crypto/shannon.cpp
		crypto/shannon.hpp

		endian/byteswap.hpp
		endian/byteswap_tests.cpp
		endian/endian.hpp

		functional/callback_map.hpp
		functional/member-function-registry.hpp

		iostream/imemstream.cpp
		iostream/imemstream.hpp
		iostream/imemstream_tests.cpp
		iostream/readfile.cpp
		iostream/readfile.hpp
		iostream/writefile.cpp
		iostream/writefile.hpp

		memory/read.hpp
		memory/read_tests.cpp

		posix/fd.cpp
		posix/fd.hpp
		posix/pipe.cpp
		posix/pipe.hpp

		process/_detail/zero_terminated.cpp
		process/_detail/zero_terminated_tests.cpp

		stl/list.hpp
		stl/list_tests.cpp
		stl/vector.hpp
		stl/vector_tests.cpp

		string/expand.cpp
		string/expand.hpp
		string/expand_tests.cpp

		stupidtest/stupidtest.cpp
		stupidtest/stupidtest_tests.cpp

		memstream.cpp
		memstream.hpp
		memstream_tests.cpp
		util_test.cpp
		)

#
# util test
#

add_executable(util_test ${util_test_SRCS})

target_link_libraries(util_test ${Boost_LIBRARIES})

#
# console test
#

set(console_test_SRCS
		console/_test/console_test.cpp

		console/console.cpp
		console/mode.cpp
		)

add_executable(console_test ${console_test_SRCS})

#
# color test
#

set(ansi_colors_test_SRCS
		ansi/_test/colors_test.cpp
		ansi/colors.cpp
		)

add_executable(ansi_colors_test ${ansi_colors_test_SRCS})

#
# process tests
#

add_executable(child_process process/_test/child_process.cpp)

set(process_tests_SRCS
		posix/fd.cpp
		posix/pipe.cpp

		process/_detail/spawner.cpp
		process/_detail/zero_terminated.cpp

		process/_test/process_tests.cpp

		process/child.cpp
		process/child_options.cpp
		process/parent.cpp
		process/stream_id.cpp

		stupidtest/stupidtest.cpp
		)

add_executable(process_test ${process_tests_SRCS})
target_link_libraries(process_test ${Boost_SYSTEM_LIBRARIES} ${Boost_THREAD_LIBRARIES})
get_property(child_process_path TARGET child_process PROPERTY LOCATION)
set_target_properties(process_test PROPERTIES COMPILE_DEFINITIONS "CHILD_PROCESS_PATH=\"${child_process_path}\"")

