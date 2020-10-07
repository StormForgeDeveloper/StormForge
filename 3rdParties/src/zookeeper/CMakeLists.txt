

# configure_file(	zlib-1.2.8/zconf.h.cmakein
		# zlib-1.2.8/zconf.h @ONLY)

include_directories(AFTER 
	zookeeperConnector/include
)


# Identity of this package.
add_definitions(-DPACKAGE_NAME="zookeeper C client")
add_definitions(-DPACKAGE_TARNAME="zookeeper")
add_definitions(-DPACKAGE_VERSION="3.4.10")
add_definitions(-DPACKAGE_STRING="zookeeper C client 3.4.10")
add_definitions(-DPACKAGE_BUGREPORT="user@zookeeper.apache.org")
add_definitions(-DPACKAGE_URL="")
add_definitions(-DTHREADED)


set(SRC_FILES
    zookeeperConnector/generated/zookeeper.jute.c
	zookeeperConnector/include/zookeeper.jute.h
	zookeeperConnector/src/hashtable/hashtable.c
	zookeeperConnector/src/hashtable/hashtable_itr.c
	#zookeeperConnector/src/cli.c
	zookeeperConnector/src/mt_adaptor.c
	zookeeperConnector/src/recordio.c
	#zookeeperConnector/src/st_adaptor.c
	zookeeperConnector/src/winport.c
	zookeeperConnector/src/zk_hashtable.c
	zookeeperConnector/src/zk_log.c
	zookeeperConnector/src/zookeeper.c
)



add_library(zookeeper ${SRC_FILES})

install (TARGETS zookeeper
         ARCHIVE DESTINATION lib COMPONENT SF3rdParties
         LIBRARY DESTINATION lib COMPONENT SF3rdParties
         RUNTIME DESTINATION bin COMPONENT SF3rdParties)



