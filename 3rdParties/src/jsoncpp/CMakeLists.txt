




include_directories(AFTER 
	jsoncpp/include
)

set(SRC_FILES
	jsoncpp/include/json/allocator.h
	jsoncpp/include/json/assertions.h
	jsoncpp/include/json/config.h
	jsoncpp/include/json/forwards.h
	jsoncpp/include/json/json.h
	jsoncpp/include/json/json_features.h
	jsoncpp/include/json/reader.h
	jsoncpp/include/json/value.h
	jsoncpp/include/json/version.h
	jsoncpp/include/json/writer.h
	jsoncpp/src/lib_json/json_reader.cpp
	jsoncpp/src/lib_json/json_tool.h
	jsoncpp/src/lib_json/json_value.cpp
	jsoncpp/src/lib_json/json_valueiterator.inl
	jsoncpp/src/lib_json/json_writer.cpp
)






add_library(jsoncpp ${SRC_FILES})


install (TARGETS jsoncpp
         ARCHIVE DESTINATION lib COMPONENT SF3rdParties
         LIBRARY DESTINATION lib COMPONENT SF3rdParties
         RUNTIME DESTINATION bin COMPONENT SF3rdParties)




