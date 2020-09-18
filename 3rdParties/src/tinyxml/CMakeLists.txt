



set(SRC_FILES
    src/tinyxml2.cpp
)



add_library(tinyxml ${SRC_FILES})

install (TARGETS tinyxml
         ARCHIVE DESTINATION lib COMPONENT SF3rdParties
         LIBRARY DESTINATION lib COMPONENT SF3rdParties
         RUNTIME DESTINATION bin COMPONENT SF3rdParties)



