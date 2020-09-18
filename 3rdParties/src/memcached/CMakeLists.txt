

set(MEMCACHED_PATH libmemcached-1.0.18)


include_directories(AFTER 
	./
	../SFWinport/src/include
	${MEMCACHED_PATH}
)

source_group(INCLUDES FILES
    ${MEMCACHED_PATH}/libhashkit-1.0/configure.h 
	${MEMCACHED_PATH}/libmemcached-1.0/configure.h 
	${MEMCACHED_PATH}/libmemcached/csl/parser.h 
	${MEMCACHED_PATH}/libmemcached/csl/scanner.h
	${MEMCACHED_PATH}/clients/client_options.h 
	${MEMCACHED_PATH}/clients/execute.h 
	${MEMCACHED_PATH}/clients/generator.h 
	${MEMCACHED_PATH}/clients/ms_atomic.h 
	${MEMCACHED_PATH}/clients/ms_conn.h 
	${MEMCACHED_PATH}/clients/ms_memslap.h 
	${MEMCACHED_PATH}/clients/ms_setting.h 
	${MEMCACHED_PATH}/clients/ms_sigsegv.h 
	${MEMCACHED_PATH}/clients/ms_stats.h 
	${MEMCACHED_PATH}/clients/ms_task.h 
	${MEMCACHED_PATH}/clients/ms_thread.h 
	${MEMCACHED_PATH}/clients/utilities.h
	${MEMCACHED_PATH}/libhashkit-1.0/algorithm.h 
	${MEMCACHED_PATH}/libhashkit-1.0/behavior.h 
	${MEMCACHED_PATH}/libhashkit-1.0/configure.h 
	${MEMCACHED_PATH}/libhashkit-1.0/digest.h 
	${MEMCACHED_PATH}/libhashkit-1.0/function.h 
	${MEMCACHED_PATH}/libhashkit-1.0/has.h 
	${MEMCACHED_PATH}/libhashkit-1.0/hashkit.h 
	${MEMCACHED_PATH}/libhashkit-1.0/hashkit.hpp 
	${MEMCACHED_PATH}/libhashkit-1.0/strerror.h 
	${MEMCACHED_PATH}/libhashkit-1.0/string.h 
	${MEMCACHED_PATH}/libhashkit-1.0/str_algorithm.h 
	${MEMCACHED_PATH}/libhashkit-1.0/types.h 
	${MEMCACHED_PATH}/libhashkit-1.0/visibility.h 
	${MEMCACHED_PATH}/libmemcached-1.0/struct/allocator.h 
	${MEMCACHED_PATH}/libmemcached-1.0/struct/analysis.h 
	${MEMCACHED_PATH}/libmemcached-1.0/struct/callback.h 
	${MEMCACHED_PATH}/libmemcached-1.0/struct/memcached.h 
	${MEMCACHED_PATH}/libmemcached-1.0/struct/result.h 
	${MEMCACHED_PATH}/libmemcached-1.0/struct/sasl.h 
	${MEMCACHED_PATH}/libmemcached-1.0/struct/server.h 
	${MEMCACHED_PATH}/libmemcached-1.0/struct/stat.h 
	${MEMCACHED_PATH}/libmemcached-1.0/struct/string.h 
	${MEMCACHED_PATH}/libmemcached-1.0/types/behavior.h 
	${MEMCACHED_PATH}/libmemcached-1.0/types/callback.h 
	${MEMCACHED_PATH}/libmemcached-1.0/types/connection.h 
	${MEMCACHED_PATH}/libmemcached-1.0/types/hash.h 
	${MEMCACHED_PATH}/libmemcached-1.0/types/return.h 
	${MEMCACHED_PATH}/libmemcached-1.0/types/server_distribution.h 
	${MEMCACHED_PATH}/libmemcached-1.0/alloc.h 
	${MEMCACHED_PATH}/libmemcached-1.0/allocators.h 
	${MEMCACHED_PATH}/libmemcached-1.0/analyze.h 
	${MEMCACHED_PATH}/libmemcached-1.0/auto.h 
	${MEMCACHED_PATH}/libmemcached-1.0/basic_string.h 
	${MEMCACHED_PATH}/libmemcached-1.0/behavior.h 
	${MEMCACHED_PATH}/libmemcached-1.0/callback.h 
	${MEMCACHED_PATH}/libmemcached-1.0/callbacks.h 
	${MEMCACHED_PATH}/libmemcached-1.0/configure.h 
	${MEMCACHED_PATH}/libmemcached-1.0/defaults.h 
	${MEMCACHED_PATH}/libmemcached-1.0/delete.h 
	${MEMCACHED_PATH}/libmemcached-1.0/deprecated_types.h 
	${MEMCACHED_PATH}/libmemcached-1.0/dump.h 
	${MEMCACHED_PATH}/libmemcached-1.0/encoding_key.h 
	${MEMCACHED_PATH}/libmemcached-1.0/error.h 
	${MEMCACHED_PATH}/libmemcached-1.0/exception.hpp 
	${MEMCACHED_PATH}/libmemcached-1.0/exist.h 
	${MEMCACHED_PATH}/libmemcached-1.0/fetch.h 
	${MEMCACHED_PATH}/libmemcached-1.0/flush.h 
	${MEMCACHED_PATH}/libmemcached-1.0/flush_buffers.h 
	${MEMCACHED_PATH}/libmemcached-1.0/get.h 
	${MEMCACHED_PATH}/libmemcached-1.0/hash.h 
	${MEMCACHED_PATH}/libmemcached-1.0/limits.h 
	${MEMCACHED_PATH}/libmemcached-1.0/memcached.h 
	${MEMCACHED_PATH}/libmemcached-1.0/memcached.hpp 
	${MEMCACHED_PATH}/libmemcached-1.0/options.h 
	${MEMCACHED_PATH}/libmemcached-1.0/parse.h 
	${MEMCACHED_PATH}/libmemcached-1.0/platform.h 
	${MEMCACHED_PATH}/libmemcached-1.0/quit.h 
	${MEMCACHED_PATH}/libmemcached-1.0/result.h 
	${MEMCACHED_PATH}/libmemcached-1.0/return.h 
	${MEMCACHED_PATH}/libmemcached-1.0/sasl.h 
	${MEMCACHED_PATH}/libmemcached-1.0/server.h 
	${MEMCACHED_PATH}/libmemcached-1.0/server_list.h 
	${MEMCACHED_PATH}/libmemcached-1.0/stats.h 
	${MEMCACHED_PATH}/libmemcached-1.0/storage.h 
	${MEMCACHED_PATH}/libmemcached-1.0/strerror.h 
	${MEMCACHED_PATH}/libmemcached-1.0/touch.h 
	${MEMCACHED_PATH}/libmemcached-1.0/triggers.h 
	${MEMCACHED_PATH}/libmemcached-1.0/types.h 
	${MEMCACHED_PATH}/libmemcached-1.0/verbosity.h 
	${MEMCACHED_PATH}/libmemcached-1.0/version.h 
	${MEMCACHED_PATH}/libmemcached-1.0/visibility.h 
	${MEMCACHED_PATH}/libmemcached/memcached.h 
	${MEMCACHED_PATH}/libmemcached/memcached.hpp 
	${MEMCACHED_PATH}/libmemcached/util.h 
	${MEMCACHED_PATH}/libhashkit/hashkit.h 
	${MEMCACHED_PATH}/libhashkit/aes.h 
	${MEMCACHED_PATH}/libhashkit/algorithm.h 
	${MEMCACHED_PATH}/libhashkit/murmur3.h 
	${MEMCACHED_PATH}/libhashkit/common.h 
	${MEMCACHED_PATH}/libhashkit/is.h 
	${MEMCACHED_PATH}/libhashkit/rijndael.hpp 
	${MEMCACHED_PATH}/libhashkit/string.h 
	${MEMCACHED_PATH}/libmemcached/csl/common.h 
	${MEMCACHED_PATH}/libmemcached/csl/context.h 
	${MEMCACHED_PATH}/libmemcached/csl/parser.h 
	${MEMCACHED_PATH}/libmemcached/csl/scanner.h 
	${MEMCACHED_PATH}/libmemcached/csl/server.h 
	${MEMCACHED_PATH}/libmemcached/csl/symbol.h 
	${MEMCACHED_PATH}/libmemcached/array.h 
	${MEMCACHED_PATH}/libmemcached/assert.hpp 
	${MEMCACHED_PATH}/libmemcached/backtrace.hpp 
	${MEMCACHED_PATH}/libmemcached/behavior.hpp 
	${MEMCACHED_PATH}/libmemcached/byteorder.h 
	${MEMCACHED_PATH}/libmemcached/common.h 
	${MEMCACHED_PATH}/libmemcached/connect.hpp 
	${MEMCACHED_PATH}/libmemcached/continuum.hpp 
	${MEMCACHED_PATH}/libmemcached/do.hpp 
	${MEMCACHED_PATH}/libmemcached/encoding_key.h 
	${MEMCACHED_PATH}/libmemcached/error.hpp 
	${MEMCACHED_PATH}/libmemcached/flag.hpp 
	${MEMCACHED_PATH}/libmemcached/initialize_query.h 
	${MEMCACHED_PATH}/libmemcached/instance.hpp 
	${MEMCACHED_PATH}/libmemcached/internal.h libmemcached/io.h 
	${MEMCACHED_PATH}/libmemcached/io.hpp libmemcached/is.h 
	${MEMCACHED_PATH}/libmemcached/key.hpp 
	${MEMCACHED_PATH}/libmemcached/libmemcached_probes.h 
	${MEMCACHED_PATH}/libmemcached/memcached/protocol_binary.h 
	${MEMCACHED_PATH}/libmemcached/memcached/vbucket.h 
	${MEMCACHED_PATH}/libmemcached/memory.h 
	${MEMCACHED_PATH}/libmemcached/namespace.h 
	${MEMCACHED_PATH}/libmemcached/options.hpp 
	${MEMCACHED_PATH}/libmemcached/poll.h libmemcached/response.h 
	${MEMCACHED_PATH}/libmemcached/result.h libmemcached/sasl.hpp 
	${MEMCACHED_PATH}/libmemcached/server.hpp 
	${MEMCACHED_PATH}/libmemcached/server_instance.h 
	${MEMCACHED_PATH}/libmemcached/socket.hpp 
	${MEMCACHED_PATH}/libmemcached/string.hpp 
	${MEMCACHED_PATH}/libmemcached/udp.hpp 
	${MEMCACHED_PATH}/libmemcached/version.hpp 
	${MEMCACHED_PATH}/libmemcached/virtual_bucket.h 
	${MEMCACHED_PATH}/libmemcached/watchpoint.h 
	${MEMCACHED_PATH}/libmemcached/windows.hpp 
	${MEMCACHED_PATH}/libmemcachedutil/common.h 
	${MEMCACHED_PATH}/libmemcachedutil-1.0/flush.h 
	${MEMCACHED_PATH}/libmemcachedutil-1.0/ostream.hpp 
	${MEMCACHED_PATH}/libmemcachedutil-1.0/pid.h 
	${MEMCACHED_PATH}/libmemcachedutil-1.0/ping.h 
	${MEMCACHED_PATH}/libmemcachedutil-1.0/pool.h 
	${MEMCACHED_PATH}/libmemcachedutil-1.0/util.h 
	${MEMCACHED_PATH}/libmemcachedutil-1.0/version.h 
	${MEMCACHED_PATH}/util/daemon.hpp 
	${MEMCACHED_PATH}/util/instance.hpp 
	${MEMCACHED_PATH}/util/logfile.hpp 
	${MEMCACHED_PATH}/util/log.hpp 
	${MEMCACHED_PATH}/util/operation.hpp 
	${MEMCACHED_PATH}/util/signal.hpp 
	${MEMCACHED_PATH}/util/string.hpp 
	${MEMCACHED_PATH}/util/pidfile.hpp 
	${MEMCACHED_PATH}/win32/wrappers.h
)


set(SRC_FILES
	${MEMCACHED_PATH}/libhashkit/nohsieh.cc 
#	${MEMCACHED_PATH}/libmemcached/csl/parser.cc 
#	${MEMCACHED_PATH}/libmemcached/csl/scanner.cc 
	${MEMCACHED_PATH}/libhashkit/aes.cc 
	${MEMCACHED_PATH}/libhashkit/algorithm.cc 
	${MEMCACHED_PATH}/libhashkit/behavior.cc 
	${MEMCACHED_PATH}/libhashkit/crc32.cc 
	${MEMCACHED_PATH}/libhashkit/digest.cc 
	${MEMCACHED_PATH}/libhashkit/encrypt.cc 
	${MEMCACHED_PATH}/libhashkit/fnv_32.cc 
	${MEMCACHED_PATH}/libhashkit/fnv_64.cc 
	${MEMCACHED_PATH}/libhashkit/function.cc 
	${MEMCACHED_PATH}/libhashkit/has.cc 
	${MEMCACHED_PATH}/libhashkit/hashkit.cc 
	${MEMCACHED_PATH}/libhashkit/jenkins.cc 
	${MEMCACHED_PATH}/libhashkit/ketama.cc 
	${MEMCACHED_PATH}/libhashkit/md5.cc 
	${MEMCACHED_PATH}/libhashkit/murmur.cc 
	${MEMCACHED_PATH}/libhashkit/murmur3.cc 
	${MEMCACHED_PATH}/libhashkit/murmur3_api.cc 
	${MEMCACHED_PATH}/libhashkit/one_at_a_time.cc 
	${MEMCACHED_PATH}/libhashkit/rijndael.cc 
	${MEMCACHED_PATH}/libhashkit/str_algorithm.cc 
	${MEMCACHED_PATH}/libhashkit/strerror.cc 
	${MEMCACHED_PATH}/libhashkit/string.cc 
	${MEMCACHED_PATH}/libhashkit/hsieh.cc 
	${MEMCACHED_PATH}/libhashkit/nohsieh.cc 
	# ${MEMCACHED_PATH}/libmemcached/csl/context.cc 
	# ${MEMCACHED_PATH}/libmemcached/csl/parser.cc 
	# ${MEMCACHED_PATH}/libmemcached/csl/scanner.cc 
	${MEMCACHED_PATH}/libmemcached/instance.cc 
	${MEMCACHED_PATH}/libmemcached/allocators.cc 
	${MEMCACHED_PATH}/libmemcached/allocators.hpp 
	${MEMCACHED_PATH}/libmemcached/analyze.cc 
	${MEMCACHED_PATH}/libmemcached/array.c 
	${MEMCACHED_PATH}/libmemcached/auto.cc 
	${MEMCACHED_PATH}/libmemcached/backtrace.cc 
	${MEMCACHED_PATH}/libmemcached/behavior.cc 
	${MEMCACHED_PATH}/libmemcached/byteorder.cc 
	${MEMCACHED_PATH}/libmemcached/callback.cc 
	${MEMCACHED_PATH}/libmemcached/connect.cc 
	${MEMCACHED_PATH}/libmemcached/delete.cc 
	${MEMCACHED_PATH}/libmemcached/do.cc 
	${MEMCACHED_PATH}/libmemcached/dump.cc 
	${MEMCACHED_PATH}/libmemcached/error.cc 
	${MEMCACHED_PATH}/libmemcached/exist.cc 
	${MEMCACHED_PATH}/libmemcached/fetch.cc 
	${MEMCACHED_PATH}/libmemcached/flag.cc 
	${MEMCACHED_PATH}/libmemcached/flush.cc 
	${MEMCACHED_PATH}/libmemcached/flush_buffers.cc 
	${MEMCACHED_PATH}/libmemcached/get.cc 
	${MEMCACHED_PATH}/libmemcached/hash.cc 
	${MEMCACHED_PATH}/libmemcached/hash.hpp 
	${MEMCACHED_PATH}/libmemcached/hosts.cc 
	${MEMCACHED_PATH}/libmemcached/initialize_query.cc 
	${MEMCACHED_PATH}/libmemcached/io.cc 
	${MEMCACHED_PATH}/libmemcached/key.cc 
	${MEMCACHED_PATH}/libmemcached/memcached.cc 
	${MEMCACHED_PATH}/libmemcached/encoding_key.cc 
	${MEMCACHED_PATH}/libmemcached/namespace.cc 
	${MEMCACHED_PATH}/libmemcached/options.cc 
	${MEMCACHED_PATH}/libmemcached/parse.cc 
	${MEMCACHED_PATH}/libmemcached/poll.cc 
	${MEMCACHED_PATH}/libmemcached/purge.cc 
	${MEMCACHED_PATH}/libmemcached/quit.cc 
	${MEMCACHED_PATH}/libmemcached/quit.hpp 
	${MEMCACHED_PATH}/libmemcached/response.cc 
	${MEMCACHED_PATH}/libmemcached/result.cc 
	${MEMCACHED_PATH}/libmemcached/sasl.cc 
	${MEMCACHED_PATH}/libmemcached/server.cc 
	${MEMCACHED_PATH}/libmemcached/server_list.cc 
	${MEMCACHED_PATH}/libmemcached/server_list.hpp 
	${MEMCACHED_PATH}/libmemcached/stats.cc 
	${MEMCACHED_PATH}/libmemcached/storage.cc 
	${MEMCACHED_PATH}/libmemcached/strerror.cc 
	${MEMCACHED_PATH}/libmemcached/string.cc 
	${MEMCACHED_PATH}/libmemcached/touch.cc 
	${MEMCACHED_PATH}/libmemcached/udp.cc 
	${MEMCACHED_PATH}/libmemcached/verbosity.cc 
	${MEMCACHED_PATH}/libmemcached/version.cc 
	${MEMCACHED_PATH}/libmemcached/virtual_bucket.c 
	${MEMCACHED_PATH}/libmemcached/backtrace.cc 
	${MEMCACHED_PATH}/libmemcachedutil/flush.cc 
	${MEMCACHED_PATH}/libmemcachedutil/pid.cc 
	${MEMCACHED_PATH}/libmemcachedutil/ping.cc 
	${MEMCACHED_PATH}/libmemcachedutil/pool.cc 
	${MEMCACHED_PATH}/libmemcachedutil/version.cc 
)



#add_definitions(-DLIBRDKAFKA_STATICLIB)
# set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -Wregister -Wdeprecated-register")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wregister -Wdeprecated-register")




add_library(memcached ${SRC_FILES})



install (TARGETS memcached
         ARCHIVE DESTINATION lib COMPONENT SF3rdParties
         LIBRARY DESTINATION lib COMPONENT SF3rdParties
         RUNTIME DESTINATION bin COMPONENT SF3rdParties)




