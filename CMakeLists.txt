
cmake_minimum_required(VERSION 3.25)

project(StormForge LANGUAGES C CXX)

include (StormForge.cmake)

message ( "Adding SFCore" )
add_subdirectory(Engine/Src/SFCore)

message ( "Adding SFEngine" )
add_subdirectory(Engine/Src/SFEngine)

message ( "Adding Protocol" )
add_subdirectory(Engine/Src/Protocol)

message ( "Adding SFEngineDLL" )
add_subdirectory(Engine/Src/SFEngineDLL)

message ( "Adding Tools" )
add_subdirectory(Tools/Src)

message ( "Adding Test" )
add_subdirectory(Test)

#cmake doesn't support new c#. maybe later
#add_subdirectory(Engine/Src/SFCoreSharp)
#add_subdirectory(Engine/Src/SFEngineSharp)



