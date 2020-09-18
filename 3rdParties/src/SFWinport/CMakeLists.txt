

include_directories(AFTER 
	./src/include
)


set(SRC_FILES
	src/include/SFWinport.h
    src/SFWinport.cpp
)



add_library(SFWinport ${SRC_FILES})

install (TARGETS SFWinport
         ARCHIVE DESTINATION lib COMPONENT SF3rdParties
         LIBRARY DESTINATION lib COMPONENT SF3rdParties
         RUNTIME DESTINATION bin COMPONENT SF3rdParties)



