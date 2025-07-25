
if(WIN32)
include_directories(AFTER 
	$ENV{FBX_SDK_PATH}/include
)

else()
include_directories(AFTER 
	../../../../FBXSDK/include
)

endif()

set(SUBAudio_FILES
    Audio/SFAudioTypes.h
    Audio/SFAudio.h
	Audio/SFAudio.cpp
    Audio/SFAudioBuffer.h
	Audio/SFAudioBuffer.cpp
    Audio/SFAudioSource.h
    Audio/SFAudioSource.cpp
    Audio/SFAudioListener.h
    Audio/SFAudioListener.cpp
    Audio/SFAudioService.h
    Audio/SFAudioService.cpp
	)

if(SF_USE_OPENAL)

	list(APPEND SUBAudio_FILES 
		Audio/OpenAL/SFAudioSourceOpenAL.h
		Audio/OpenAL/SFAudioSourceOpenAL.cpp
		Audio/OpenAL/SFAudioListenerOpenAL.h
		Audio/OpenAL/SFAudioListenerOpenAL.cpp
		Audio/OpenAL/SFAudioRecorderOpenAL.h
		Audio/OpenAL/SFAudioRecorderOpenAL.cpp
		Audio/OpenAL/SFAudioOpenAL.h
		Audio/OpenAL/SFAudioOpenAL.cpp
		Audio/OpenAL/SFAudioDeviceOpenAL.h
		Audio/OpenAL/SFAudioDeviceOpenAL.cpp
		Audio/OpenAL/SFAudioEngineComponentOpenAL.h
		Audio/OpenAL/SFAudioEngineComponentOpenAL.cpp
	  )
endif()

if(SF_USE_WSAPI)

	list(APPEND SUBAudio_FILES 
		Audio/WSAPI/SFAudioSourceWSAPI.h
		Audio/WSAPI/SFAudioSourceWSAPI.cpp
		Audio/WSAPI/SFAudioListenerWSAPI.h
		Audio/WSAPI/SFAudioListenerWSAPI.cpp
		Audio/WSAPI/SFAudioRecorderWSAPI.h
		Audio/WSAPI/SFAudioRecorderWSAPI.cpp
		Audio/WSAPI/SFAudioWSAPI.h
		Audio/WSAPI/SFAudioWSAPI.cpp
		Audio/WSAPI/SFAudioDeviceWSAPI.h
		Audio/WSAPI/SFAudioDeviceWSAPI.cpp
		Audio/WSAPI/SFAudioEngineComponentWSAPI.h
		Audio/WSAPI/SFAudioEngineComponentWSAPI.cpp
	  )
endif()

source_group(Audio FILES
	${SUBAudio_FILES} 
)

set(SUBNet_FILES
	Net/SFConnection.h
	Net/SFConnectionAction.h
	Net/SFConnectionActions.h
	Net/SFConnectionMUDP.h
	Net/SFConnectionTasks.h
	Net/SFConnectionTCP.h
	Net/SFConnectionUDP.h
	Net/SFConnectionUDPBase.h
	Net/SFConnectionQuic.h
	Net/SFConnectionQuic.cpp
	Net/SFMessageID.h
	Net/SFMessage.h
	Net/SFMessageWindow.h
	Net/SFNetConst.h
	Net/SFNetCtrl.h
	Net/SFNetCtrlIDs.h
	Net/SFNetDef.h
	Net/SFNetRawUDP.h
	Net/SFNetSocket.h
	Net/SFNetSvrDef.h
	Net/SFNetSystem.h
	Net/SFNetSystem_EPOLL.h
	Net/SFNetSystem_KQUEUE.h
	Net/SFNetSystem_Linux.h
	Net/SFNetSystem_WinIOCP.h
	Net/SFNetToString.h
	Net/SFNetUtil.h
	Net/SFNetDef.inl
	Net/SFNetSystem_Linux.inl
	Net/SFNetSystem_WinIOCP.inl
    Net/SFMessageEndpoint.h
    Net/SFMessageEndpoint.cpp
	Net/SFConnection.cpp
	Net/SFConnectionAction.cpp
	Net/SFConnectionActions.cpp
	Net/SFConnectionMUDP.cpp
	Net/SFConnectionMUDPClient.cpp
	Net/SFConnectionPeerTCP.cpp
	Net/SFConnectionTasks.cpp
	Net/SFConnectionTCP.cpp
	Net/SFConnectionUDP.cpp
	Net/SFConnectionUDPBase.cpp
	Net/SFMessage.cpp
	Net/SFMessageData.h
	Net/SFMessageWindow.cpp
	Net/SFNetCtrl.cpp
	Net/SFNetDef.cpp
	Net/SFNetRawUDP.cpp
    Net/SFNetUDP.h
    Net/SFNetUDP.cpp
	Net/SFNetSocket.cpp
	Net/SFNetSvrDef.cpp
	Net/SFNetSystem.cpp
	Net/SFNetSystem_EPOLL.cpp
	Net/SFNetSystem_KQUEUE.cpp
	Net/SFNetSystem_Linux.cpp
	Net/SFNetSystem_WinIOCP.cpp
	Net/SFNetToString.cpp
	Net/SFNetUtil.cpp
	Net/SFNetMessageCollection.h
	Net/SFNetMessageCollection.cpp
	Net/SFNetPacketData.h
	Net/SFNetPacketData.cpp
  )

source_group(Net FILES
	${SUBNet_FILES} 
)


set(SUBService_FILES
	Service/SFConnectionManagerService.h
	Service/SFEngineService.h
	Service/SFEngineServices.h
	Service/SFEngineServices.cpp
	#Service/SFIAssetImporterFactory.h
	#Service/SFIAssetSerializerFactory.h
	#Service/SFIGraphicDevice.h
	Service/SFNetSystemService.h
	Service/SFResourceManagerService.h
  )

source_group(Service FILES
	${SUBService_FILES} 
)

# set(SUBAsset_FILES
	# Asset/Exporter/SFAssetExporter.h
	# Asset/Importer/SFAssetImportContext.h
	# Asset/Importer/SFAssetImporter.h
	# Asset/Importer/SFAssetImporter3DAsset.h
	# Asset/Importer/SFAssetImporter3DAssetFBX.h
	# Asset/Importer/SFAssetImporterBinary.h
	# Asset/Importer/SFAssetImporterFactory.h
	# Asset/Importer/SFAssetImporterTexture.h
	# Asset/Importer/SFAssetImporterTextureJPG.h
	# Asset/Importer/SFAssetImporterTexturePNG.h
	# Asset/Importer/SFAssetImporterTextureTGA.h
	# Asset/Package/SFAssetPackage.h
	# Asset/Package/SFAssetPackageSerializer.h
	# Asset/Serializer/SFAssetSerializer.h
	# Asset/Serializer/SFAssetSerializerFactory.h
	# Asset/Serializer/SFAssetSerializerTexture.h
	# Asset/Exporter/SFAssetExporter.cpp
	# Asset/Importer/SFAssetImportContext.cpp
	# Asset/Importer/SFAssetImporter.cpp
	# Asset/Importer/SFAssetImporter3DAsset.cpp
	# Asset/Importer/SFAssetImporter3DAssetFBX.cpp
	# Asset/Importer/SFAssetImporterBinary.cpp
	# Asset/Importer/SFAssetImporterFactory.cpp
	# Asset/Importer/SFAssetImporterTexture.cpp
	# Asset/Importer/SFAssetImporterTextureJPG.cpp
	# Asset/Importer/SFAssetImporterTexturePNG.cpp
	# Asset/Importer/SFAssetImporterTextureTGA.cpp
	# Asset/Package/SFAssetPackage.cpp
	# Asset/Package/SFAssetPackageSerializer.cpp
	# Asset/Serializer/SFAssetSerializer.cpp
	# Asset/Serializer/SFAssetSerializerFactory.cpp
	# Asset/Serializer/SFAssetSerializerTexture.cpp
  # )

# source_group(Asset FILES
	# ${SUBAsset_FILES} 
# )

# set(SUBResource_FILES
	# Resource/SFAnimation.h
	# Resource/SFDeviceMesh.h
	# Resource/SFDeviceResource.h
	# Resource/SFDeviceTexture.h
	# Resource/SFGraphicBuffer.h
	# Resource/SFIndexBuffer.h
	# Resource/SFMesh.h
	# Resource/SFRawBinary.h
	# Resource/SFResource.h
	# Resource/SFResourceFactory.h
	# Resource/SFResourceManager.h
	# Resource/SFSparseResourceFactory.h
	# Resource/SFTexture.h
	# Resource/SFTextureFormat.h
	# Resource/SFTextureFormatDescription.h
	# Resource/SFVertexBuffer.h
	# Resource/SFAnimation.cpp
	# Resource/SFDeviceMesh.cpp
	# Resource/SFDeviceResource.cpp
	# Resource/SFDeviceTexture.cpp
	# Resource/SFGraphicBuffer.cpp
	# Resource/SFIndexBuffer.cpp
	# Resource/SFMesh.cpp
	# Resource/SFRawBinary.cpp
	# Resource/SFResource.cpp
	# Resource/SFResourceFactory.cpp
	# Resource/SFResourceManager.cpp
	# Resource/SFSparseResourceFactory.cpp
	# Resource/SFTexture.cpp
	# Resource/SFTextureFormatDescription.cpp
	# Resource/SFVertexBuffer.cpp
  # )

# source_group(Resource FILES
	# ${SUBResource_FILES} 
# )

# set(SUBGraphics_FILES
	# Graphics/SFGraphicDevice.cpp
	# Graphics/SFGraphicDeviceGLES.cpp
	# Graphics/SFGraphicDeviceGLES_EGL.cpp
	# Graphics/SFGraphicDeviceVulkan.cpp
	# Graphics/SFRenderCommand.cpp
	# Graphics/SFRenderCommands.cpp
	# Graphics/SFRenderItem.cpp
	# Graphics/SFRenderPipeline.cpp
	# Graphics/SFRenderPipelineStage.cpp
	# Graphics/SFRenderTargetChain.cpp
	# Graphics/SFRenderThread.cpp
	# Graphics/Vulkan/SFRenderTargetChainVulkan.cpp
	# Graphics/Vulkan/SFVulkanRenderPass.cpp
	# Graphics/Vulkan/SFVulkanTexture.cpp
	# Graphics/Vulkan/SFVulkanDebug.cpp
	# Graphics/Vulkan/SFVulkanLibrary.cpp
	# Graphics/Vulkan/SFVulkanLogicalDevice.cpp
	# Graphics/Vulkan/SFVulkanPhysicalDevice.cpp
	# Graphics/Vulkan/SFVulkanSystem.cpp
	# Graphics/SFGraphicDevice.h
	# Graphics/SFGraphicDeviceGLES.h
	# Graphics/SFGraphicDeviceGLES_EGL.h
	# Graphics/SFGraphicDeviceVulkan.h
	# Graphics/SFRenderCommand.h
	# Graphics/SFRenderCommands.h
	# Graphics/SFRenderItem.h
	# Graphics/SFRenderPipeline.h
	# Graphics/SFRenderPipelineStage.h
	# Graphics/SFRenderTargetChain.h
	# Graphics/SFRenderThread.h
	# Graphics/Vulkan/SFRenderTargetChainVulkan.h
	# Graphics/Vulkan/SFVulkanRenderPass.h
	# Graphics/Vulkan/SFVulkanTexture.h
	# Graphics/Vulkan/SFVulkanDebug.h
	# Graphics/Vulkan/SFVulkanLibrary.h
	# Graphics/Vulkan/SFVulkanLogicalDevice.h
	# Graphics/Vulkan/SFVulkanPhysicalDevice.h
	# Graphics/Vulkan/SFVulkanSystem.h
  # )

# source_group(Graphics FILES
	# ${SUBGraphics_FILES} 
# )

set(SUBEngine_FILES
	SFEngine.h
	EngineObject/SFEngineObject.cpp
	EngineObject/SFEngineObjectManager.cpp
	EngineObject/SFEngineTask.cpp
	EngineObject/SFEngineTaskManager.cpp
	EngineObject/SFEngineTasks.cpp
	EngineObject/SFRenderTask.cpp
	EngineObject/SFEngineObject.h
	EngineObject/SFEngineObjectManager.h
	EngineObject/SFEngineTask.h
	EngineObject/SFEngineTaskManager.h
	EngineObject/SFEngineTasks.h
	EngineObject/SFRenderTask.h
	SFEngine.Android.cpp
	SFEngine.cpp
	SFEngine.IOS.cpp
	SFEngine.Win.cpp
	SFEngine.Linux.cpp
	Util/SFToStringEngineTypes.cpp
	Types/SFEngineTypedefs.h
	Types/SFEngineTypedefs.inl
	Types/SFEngineTypedefs.cpp
	Types/SFEngineTypeVariable.h
	Types/SFEngineTypeVariable.cpp
	Types/SFEngineTypeSerialization.h
	Types/SFEngineTypeSerialization.cpp
	Util/SFToStringEngineTypes.h
	
	Interfaces/SFPublicInterface.h
	Interfaces/SFPublicTypes.h
	Interfaces/Sharp/SFCSUtil.h
	Interfaces/Sharp/SFCSUtil.cpp
  )

source_group(Engine FILES
	${SUBEngine_FILES} 
)

set(SUBApplication_FILES
  	Application/Android/AndroidApp.cpp
	Application/Android/AndroidAppTasks.cpp
	Application/Linux/LinuxApp.h
  	Application/Linux/LinuxApp.cpp
	Application/Linux/LinuxAppTasks.cpp
	Application/SFApplicationBase.cpp
	Application/IOS/IOSApp.cpp
	Application/IOS/IOSAppTasks.cpp
	Application/Win/WindowsApp.cpp
	Application/Win/WindowsAppTasks.cpp
  	Application/Android/AndroidApp.h
	Application/Android/AndroidAppTasks.h
	Application/SFApplicationBase.h
	Application/IOS/IOSApp.h
	Application/IOS/IOSAppTasks.h
	Application/Win/WindowsApp.h
	Application/Win/WindowsAppTasks.h
  )

source_group(Application FILES
	${SUBApplication_FILES} 
)

source_group(Engine FILES
	${SUBEngine_FILES} 
)

set(SUBOnline_FILES
	Online/SFOnlineClient.h
	Online/SFOnlineClient.cpp
	Online/SFOnlineClientComponent.h
	Online/SFOnlineClientComponent.cpp
	Online/SFOnlineSession.h
	Online/SFOnlineSession.cpp
	Online/SFOnlineSessionComponent.h
	Online/SFOnlineSessionComponent.cpp
	Online/SFOnlineSessionGame.h
	Online/SFOnlineSessionGame.cpp
	Online/SFOnlineSessionGameplay.h
	Online/SFOnlineSessionGameplay.cpp
	Online/SFOnlineActor.h
	Online/SFOnlineActor.cpp
    Online/SFOnlineNotificationClient.h
    Online/SFOnlineNotificationClient.cpp
  )

source_group(Online FILES
	${SUBOnline_FILES} 
)

set(SFENGINE_LIB_FILES
	StreamDB/SFStreamDBDirectory.h
	StreamDB/SFStreamDBDirectory.cpp
	# SceneGraph/SFScene.cpp
	# SceneGraph/SFSceneNode.cpp
	# SceneGraph/SFSceneNodeComponent.cpp
	# SceneGraph/SFSceneNodeComponentMesh.cpp
	# SceneGraph/SFSceneNodeComponentSkeletalMesh.cpp
	Service/SFEngineService.cpp
	
	Actor/Movement/SFActorMovement.h
	Actor/Movement/SFActorMovement.cpp
	Actor/Movement/SFActorMovementManager.h
	Actor/Movement/SFActorMovementManager.cpp

	ResultCode/SFResultCodeEngine.h
	ResultCode/SFResultCodeEngine.cpp
	ResultCode/SFResultCodeEngineComponent.h
	ResultCode/SFResultCodeEngineComponent.cpp
	ResultCode/SFResultCodeGame.h
	ResultCode/SFResultCodeGame.cpp
	ResultCode/SFResultCodeLogin.h
	ResultCode/SFResultCodeLogin.cpp
	ResultCode/SFResultCodeNet.h
	ResultCode/SFResultCodeNet.cpp
	# SceneGraph/SFScene.h
	# SceneGraph/SFSceneNode.h
	# SceneGraph/SFSceneNodeComponent.h
	# SceneGraph/SFSceneNodeComponentMesh.h
	# SceneGraph/SFSceneNodeComponentSkeletalMesh.h

	Service/SFConnectionManagerService.h
	Service/SFEngineServices.h
	Service/SFEngineService.cpp
	Service/SFEngineService.h
	#Service/SFIAssetImporterFactory.h
	#Service/SFIAssetSerializerFactory.h
	# Service/SFIGraphicDevice.h
	Service/SFNetSystemService.h
	# Service/SFResourceManagerService.h

    SFEnginePCH.h

	StormForge.natvis
  )


#${SUBAsset_FILES} ${SUBResource_FILES} 

add_library(SFEngine STATIC ${SFENGINE_LIB_FILES} ${SUBAudio_FILES} ${SUBNet_FILES}  ${SUBService_FILES} ${SUBGraphics_FILES} ${SUBEngine_FILES} ${SUBApplication_FILES} ${SUBOnline_FILES})

target_precompile_headers(SFEngine PRIVATE SFEnginePCH.h)

target_include_directories (SFEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}../SFCore ${CMAKE_CURRENT_SOURCE_DIR}../SFEngine)

install (TARGETS SFEngine
         ARCHIVE DESTINATION lib COMPONENT StormForge
         LIBRARY DESTINATION lib COMPONENT StormForge
         RUNTIME DESTINATION bin COMPONENT StormForge)

