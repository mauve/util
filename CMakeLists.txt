cmake_minimum_required(VERSION 2.8)

project(util)

find_package(Boost COMPONENTS regex system unit_test_framework thread REQUIRED)

include_directories("${CMAKE_SOURCE_DIR}")

set(util_test_SRCS
		ansi/colors.cpp
		ansi/colors_tests.cpp

		asio/buffer_queue.cpp
		
		buffer/appendable_buffer.cpp
		buffer/appendable_buffer_tests.cpp

		console/console.cpp
		console/mode.cpp

		crypto/_detail/sha1.c
		crypto/_detail/shannon_impl.cpp

		crypto/sha1_hmac.cpp
		crypto/shannon.cpp

		endian/byteswap_tests.cpp

		iostream/imemstream.cpp
		iostream/imemstream_tests.cpp

		memory/read_tests.cpp

		process/_detail/zero_terminated.cpp
		process/_detail/zero_terminated_tests.cpp

		string/expand.cpp
		string/expand_tests.cpp

		stupidtest/stupidtest.cpp
		stupidtest/stupidtest_tests.cpp

		memstream.cpp
		memstream_tests.cpp
		util_test.cpp
		)

#
# util test
#

add_executable(util_test ${util_test_SRCS})

target_link_libraries(util_test ${Boost_LIBRARIES})

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

