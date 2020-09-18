



set(SRC_FILES
    XPlatCppSdk/code/stdafx.cpp
    XPlatCppSdk/code/stdafx.h
	XPlatCppSdk/code/include/playfab/QoS/PingResult.h
	XPlatCppSdk/code/include/playfab/QoS/PlayFabQoSApi.h
	XPlatCppSdk/code/include/playfab/QoS/QoS.h
	XPlatCppSdk/code/include/playfab/QoS/QoSResult.h
	XPlatCppSdk/code/include/playfab/QoS/QoSSocket.h
	XPlatCppSdk/code/include/playfab/QoS/RegionResult.h
	XPlatCppSdk/code/include/playfab/QoS/XPlatSocket.h
	XPlatCppSdk/code/include/playfab/PlayFabAdminApi.h
	XPlatCppSdk/code/include/playfab/PlayFabAdminDataModels.h
	XPlatCppSdk/code/include/playfab/PlayFabAdminInstanceApi.h
	XPlatCppSdk/code/include/playfab/PlayFabAndroidHttpPlugin.h
	XPlatCppSdk/code/include/playfab/PlayFabApiSettings.h
	XPlatCppSdk/code/include/playfab/PlayFabAuthenticationApi.h
	XPlatCppSdk/code/include/playfab/PlayFabAuthenticationContext.h
	XPlatCppSdk/code/include/playfab/PlayFabAuthenticationDataModels.h
	XPlatCppSdk/code/include/playfab/PlayFabAuthenticationInstanceApi.h
	XPlatCppSdk/code/include/playfab/PlayFabBaseModel.h
	XPlatCppSdk/code/include/playfab/PlayFabCallRequestContainer.h
	XPlatCppSdk/code/include/playfab/PlayFabCallRequestContainerBase.h
	XPlatCppSdk/code/include/playfab/PlayFabClientApi.h
	XPlatCppSdk/code/include/playfab/PlayFabClientDataModels.h
	XPlatCppSdk/code/include/playfab/PlayFabClientInstanceApi.h
	XPlatCppSdk/code/include/playfab/PlayFabCloudScriptApi.h
	XPlatCppSdk/code/include/playfab/PlayFabCloudScriptDataModels.h
	XPlatCppSdk/code/include/playfab/PlayFabCloudScriptInstanceApi.h
	XPlatCppSdk/code/include/playfab/PlayFabCurlHttpPlugin.h
	XPlatCppSdk/code/include/playfab/PlayFabDataApi.h
	XPlatCppSdk/code/include/playfab/PlayFabDataDataModels.h
	XPlatCppSdk/code/include/playfab/PlayFabDataInstanceApi.h
	XPlatCppSdk/code/include/playfab/PlayFabError.h
	XPlatCppSdk/code/include/playfab/PlayFabEvent.h
	XPlatCppSdk/code/include/playfab/PlayFabEventApi.h
	XPlatCppSdk/code/include/playfab/PlayFabEventBuffer.h
	XPlatCppSdk/code/include/playfab/PlayFabEventPipeline.h
	XPlatCppSdk/code/include/playfab/PlayFabEventRouter.h
	XPlatCppSdk/code/include/playfab/PlayFabEventsApi.h
	XPlatCppSdk/code/include/playfab/PlayFabEventsDataModels.h
	XPlatCppSdk/code/include/playfab/PlayFabEventsInstanceApi.h
	XPlatCppSdk/code/include/playfab/PlayFabGroupsApi.h
	XPlatCppSdk/code/include/playfab/PlayFabGroupsDataModels.h
	XPlatCppSdk/code/include/playfab/PlayFabGroupsInstanceApi.h
	XPlatCppSdk/code/include/playfab/PlayFabIOSHttpPlugin.h
	XPlatCppSdk/code/include/playfab/PlayFabIXHR2HttpPlugin.h
	XPlatCppSdk/code/include/playfab/PlayFabIXHR2HttpRequest.h
	XPlatCppSdk/code/include/playfab/PlayFabJsonHeaders.h
	XPlatCppSdk/code/include/playfab/PlayFabLocalizationApi.h
	XPlatCppSdk/code/include/playfab/PlayFabLocalizationDataModels.h
	XPlatCppSdk/code/include/playfab/PlayFabLocalizationInstanceApi.h
	XPlatCppSdk/code/include/playfab/PlayFabMatchmakerApi.h
	XPlatCppSdk/code/include/playfab/PlayFabMatchmakerDataModels.h
	XPlatCppSdk/code/include/playfab/PlayFabMatchmakerInstanceApi.h
	XPlatCppSdk/code/include/playfab/PlayFabMultiplayerApi.h
	XPlatCppSdk/code/include/playfab/PlayFabMultiplayerDataModels.h
	XPlatCppSdk/code/include/playfab/PlayFabMultiplayerInstanceApi.h
	XPlatCppSdk/code/include/playfab/PlayFabPlatformMacros.h
	XPlatCppSdk/code/include/playfab/PlayFabPlatformTypes.h
	XPlatCppSdk/code/include/playfab/PlayFabPlatformUtils.h
	XPlatCppSdk/code/include/playfab/PlayFabPluginManager.h
	XPlatCppSdk/code/include/playfab/PlayFabProfilesApi.h
	XPlatCppSdk/code/include/playfab/PlayFabProfilesDataModels.h
	XPlatCppSdk/code/include/playfab/PlayFabProfilesInstanceApi.h
	XPlatCppSdk/code/include/playfab/PlayFabServerApi.h
	XPlatCppSdk/code/include/playfab/PlayFabServerDataModels.h
	XPlatCppSdk/code/include/playfab/PlayFabServerInstanceApi.h
	XPlatCppSdk/code/include/playfab/PlayFabSettings.h
	XPlatCppSdk/code/include/playfab/PlayFabSpinLock.h
	XPlatCppSdk/code/include/playfab/PlayFabTransportHeaders.h
	XPlatCppSdk/code/include/playfab/PlayFabWinHttpPlugin.h
	XPlatCppSdk/code/source/playfab/PlayFabAuthenticationContext.cpp
	XPlatCppSdk/code/source/playfab/PlayFabApiSettings.cpp
	XPlatCppSdk/code/source/playfab/PlayFabAdminApi.cpp
	XPlatCppSdk/code/source/playfab/PlayFabAdminInstanceApi.cpp
	XPlatCppSdk/code/source/playfab/PlayFabClientApi.cpp
	XPlatCppSdk/code/source/playfab/PlayFabClientInstanceApi.cpp
	XPlatCppSdk/code/source/playfab/PlayFabMatchmakerApi.cpp
	XPlatCppSdk/code/source/playfab/PlayFabMatchmakerInstanceApi.cpp
	XPlatCppSdk/code/source/playfab/PlayFabServerApi.cpp
	XPlatCppSdk/code/source/playfab/PlayFabServerInstanceApi.cpp
	XPlatCppSdk/code/source/playfab/PlayFabAuthenticationApi.cpp
	XPlatCppSdk/code/source/playfab/PlayFabAuthenticationInstanceApi.cpp
	XPlatCppSdk/code/source/playfab/PlayFabCloudScriptApi.cpp
	XPlatCppSdk/code/source/playfab/PlayFabCloudScriptInstanceApi.cpp
	XPlatCppSdk/code/source/playfab/PlayFabDataApi.cpp
	XPlatCppSdk/code/source/playfab/PlayFabDataInstanceApi.cpp
	XPlatCppSdk/code/source/playfab/PlayFabEventsApi.cpp
	XPlatCppSdk/code/source/playfab/PlayFabEventsInstanceApi.cpp
	XPlatCppSdk/code/source/playfab/PlayFabGroupsApi.cpp
	XPlatCppSdk/code/source/playfab/PlayFabGroupsInstanceApi.cpp
	XPlatCppSdk/code/source/playfab/PlayFabLocalizationApi.cpp
	XPlatCppSdk/code/source/playfab/PlayFabLocalizationInstanceApi.cpp
	XPlatCppSdk/code/source/playfab/PlayFabMultiplayerApi.cpp
	XPlatCppSdk/code/source/playfab/PlayFabMultiplayerInstanceApi.cpp
	XPlatCppSdk/code/source/playfab/PlayFabProfilesApi.cpp
	XPlatCppSdk/code/source/playfab/PlayFabProfilesInstanceApi.cpp
	XPlatCppSdk/code/source/playfab/PlayFabCallRequestContainer.cpp
	XPlatCppSdk/code/source/playfab/PlayFabCallRequestContainerBase.cpp
	XPlatCppSdk/code/source/playfab/PlayFabError.cpp
	XPlatCppSdk/code/source/playfab/PlayFabCurlHttpPlugin.cpp
	XPlatCppSdk/code/source/playfab/PlayFabPluginManager.cpp
	XPlatCppSdk/code/source/playfab/PlayFabSettings.cpp
	XPlatCppSdk/code/source/playfab/PlayFabEvent.cpp
	XPlatCppSdk/code/source/playfab/PlayFabEventApi.cpp
	XPlatCppSdk/code/source/playfab/PlayFabEventBuffer.cpp
	XPlatCppSdk/code/source/playfab/PlayFabEventPipeline.cpp
	XPlatCppSdk/code/source/playfab/PlayFabEventRouter.cpp
	XPlatCppSdk/code/source/playfab/PlayFabSpinLock.cpp
	XPlatCppSdk/code/source/playfab/QoS/RegionResult.cpp
	XPlatCppSdk/code/source/playfab/QoS/PlayFabQoSApi.cpp
	XPlatCppSdk/code/source/playfab/QoS/QoSSocket.cpp
	XPlatCppSdk/code/source/playfab/QoS/XPlatSocket.cpp
)

add_definitions(-DENABLE_PLAYFABADMIN_API)
add_definitions(-DENABLE_PLAYFABSERVER_API)

include_directories(AFTER 
	XPlatCppSdk/code
	)

add_library(libPlayFab ${SRC_FILES})

install (TARGETS libPlayFab
         ARCHIVE DESTINATION lib COMPONENT SF3rdParties
         LIBRARY DESTINATION lib COMPONENT SF3rdParties
         RUNTIME DESTINATION bin COMPONENT SF3rdParties)



