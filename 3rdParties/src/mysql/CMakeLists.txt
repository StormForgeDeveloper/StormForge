


#set(CURL_STATICLIB ON)


include_directories(
	./
)



set(SRC_FILES
)




add_library(mysqlclient ${SRC_FILES})


install (TARGETS mysqlclient
         ARCHIVE DESTINATION lib COMPONENT SF3rdParties
         LIBRARY DESTINATION lib COMPONENT SF3rdParties
         RUNTIME DESTINATION bin COMPONENT SF3rdParties)



