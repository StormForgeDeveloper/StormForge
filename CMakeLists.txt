
cmake_minimum_required(VERSION 3.16)

include (build/StormForge.cmake)

project(StormForge C CXX)



if(WIN32)

elseif(ANDROID_PLATFORM)

elseif(IOS)

elseif(UNIX)

endif()




#set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/build${CMAKE_SYSTEM_NAME}/${ARTECTURE}${CMAKE_BUILD_TYPE})




add_subdirectory(Engine/Src/SFCore)
add_subdirectory(Engine/Src/SFEngine)
add_subdirectory(Engine/Src/Protocol)
add_subdirectory(Engine/Src/SFEngineDLL)
add_subdirectory(Test)




