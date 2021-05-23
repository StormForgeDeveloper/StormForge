

include(../../../build/StormForgeSharp.cmake)


set(SFCORE_SHARP_FILES
	ResultCode/ResultCode.cs
	ResultCode/SFResultCodeDB.cs
	ResultCode/SFResultCodeEngine.cs
	ResultCode/SFResultCodeGame.cs
	ResultCode/SFResultCodeLibrary.cs
	ResultCode/SFResultCodeLogin.cs
	ResultCode/SFResultCodeSvr.cs
	ResultCode/SFResultCodeSystem.cs
	SFGameTypes.cs
	SFResult.cs
	SFStringCrc32.cs
	SFStringCrc64.cs
  )

set(SFCORE_EXT_SHARP_FILES )


add_library(SFCoreSharp SHARED ${SFCORE_SHARP_FILES} ${SFCORE_EXT_SHARP_FILES})


csharp_set_designer_cs_properties(Properties/AssemblyInfo.cs)

#csharp_set_xaml_cs_properties(
    # App.xaml
    # App.xaml.cs
    # MainWindow.xaml
    # MainWindow.xaml.cs)

set_property(TARGET SFCoreSharp PROPERTY DOTNET_TARGET_FRAMEWORK ${SFSHARP_DOTNET_VERSION})
set_property(TARGET SFCoreSharp PROPERTY WIN32_EXECUTABLE TRUE)
set_property(TARGET SFCoreSharp PROPERTY VS_DOTNET_REFERENCES
    "System"
    "System.Core"
    "System.Data"
    "System.Xml")



# target_link_libraries(SFCoreSharp ${ENGINE_LINK_LIBS} ${PLATFORM_LIBS})


install (TARGETS SFCoreSharp
         ARCHIVE DESTINATION lib COMPONENT StormForge
         LIBRARY DESTINATION lib COMPONENT StormForge
         RUNTIME DESTINATION bin COMPONENT StormForge)

if(WIN32 AND NOT ENABLE_CLANG)
	install (FILES $<TARGET_PDB_FILE:SFCoreSharp> DESTINATION bin COMPONENT StormForge)
endif()


