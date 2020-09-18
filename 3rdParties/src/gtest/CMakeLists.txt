


include_directories(
	./
	gtest/googlemock/include
	gtest/googlemock
	gtest/googletest/include
	gtest/googletest
)



set(SRC_FILES
	gtest/googletest/src/gtest-all.cc
	gtest/googlemock/src/gmock-all.cc
)



add_library(gtest ${SRC_FILES})


install (TARGETS gtest
         ARCHIVE DESTINATION lib COMPONENT SF3rdParties
         LIBRARY DESTINATION lib COMPONENT SF3rdParties
         RUNTIME DESTINATION bin COMPONENT SF3rdParties)


