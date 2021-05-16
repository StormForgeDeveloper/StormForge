

include(../../../build/StormForgeSharp.cmake)

set(SFENGINEDLL_SHARP_FILES
	Properties/AssemblyInfo.cs
	SFEngine/Tong/SFTongScriptBytecodeBuilder.cs
	SFEngine/SFActorMovementObject.cs
  	SFEngine/SFArrayObject.cs
	SFEngine/SFConnection.cs
	SFEngine/SFConnectionGroup.cs
	SFEngine/SFEngine.cs
	SFEngine/SFGlobalEngine.cs
	SFEngine/SFIMessageRouter.cs
	SFEngine/SFMemoryStream.cs
	SFEngine/SFMessage.cs
	SFEngine/SFMessageParsingUtil.cs
	SFEngine/SFMessageRouter.cs
	SFEngine/SFNetMessageIDGame.cs
	SFEngine/SFNetMessageIDLogin.cs
	SFEngine/SFNetMessageIDPlayInstance.cs
	SFEngine/SFNetSendMessageGame.cs
	SFEngine/SFNetSendMessageLogin.cs
	SFEngine/SFNetSendMessagePlayInstance.cs
	SFEngine/SFObject.cs
	SFEngine/SFStreamDB.cs
	SFEngine/SFTimeUtil.cs
	SFEngine/SFZookeeper.cs
  )

set(SFENGINEDLL_EXT_SHARP_FILES )

if(EXISTS Extension.cmake)
	include(Extension.cmake)
endif()


add_library(SFEngineSharp SHARED ${SFENGINEDLL_SHARP_FILES} ${SFENGINEDLL_EXT_SHARP_FILES})


csharp_set_designer_cs_properties(Properties/AssemblyInfo.cs)

#csharp_set_xaml_cs_properties(
    # App.xaml
    # App.xaml.cs
    # MainWindow.xaml
    # MainWindow.xaml.cs)

set_property(TARGET SFEngineSharp PROPERTY DOTNET_TARGET_FRAMEWORK ${SFSHARP_DOTNET_VERSION})
set_property(TARGET SFEngineSharp PROPERTY WIN32_EXECUTABLE TRUE)
set_property(TARGET SFEngineSharp PROPERTY VS_DOTNET_REFERENCES
    "SFCoreSharp"
    "System"
    "System.Core"
    "System.Data"
    "System.Xml")



add_dependencies(SFEngineSharp SFCoreSharp)


# target_link_libraries(SFEngineSharp ${ENGINE_LINK_LIBS} ${PLATFORM_LIBS})


install (TARGETS SFEngineSharp
         ARCHIVE DESTINATION lib COMPONENT StormForge
         LIBRARY DESTINATION lib COMPONENT StormForge
         RUNTIME DESTINATION bin COMPONENT StormForge)

if(WIN32 AND NOT ENABLE_CLANG)
	install (FILES $<TARGET_PDB_FILE:SFEngineSharp> DESTINATION bin COMPONENT StormForge)
endif()


