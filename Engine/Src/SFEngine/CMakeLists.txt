﻿

include_directories(AFTER 
	../../../3rdParties/FBXSDK/2019.0/include
)

set(SFENGINE_LIB_FILES
  	Application/Android/AndroidApp.cpp
	Application/Android/AndroidAppTasks.cpp
	Application/SFApplicationBase.cpp
	Application/IOS/IOSApp.cpp
	Application/IOS/IOSAppTasks.cpp
	Application/Win/WindowsApp.cpp
	Application/Win/WindowsAppTasks.cpp
	Asset/Exporter/SFAssetExporter.cpp
	Asset/Importer/SFAssetImportContext.cpp
	Asset/Importer/SFAssetImporter.cpp
	Asset/Importer/SFAssetImporter3DAsset.cpp
	Asset/Importer/SFAssetImporter3DAssetFBX.cpp
	Asset/Importer/SFAssetImporterBinary.cpp
	Asset/Importer/SFAssetImporterFactory.cpp
	Asset/Importer/SFAssetImporterTexture.cpp
	Asset/Importer/SFAssetImporterTextureJPG.cpp
	Asset/Importer/SFAssetImporterTexturePNG.cpp
	Asset/Importer/SFAssetImporterTextureTGA.cpp
	Asset/Package/SFAssetPackage.cpp
	Asset/Package/SFAssetPackageSerializer.cpp
	Asset/Serializer/SFAssetSerializer.cpp
	Asset/Serializer/SFAssetSerializerFactory.cpp
	Asset/Serializer/SFAssetSerializerTexture.cpp
	Component/SFConnectionManagerComponent.cpp
	EngineObject/SFEngineObject.cpp
	EngineObject/SFEngineObjectManager.cpp
	EngineObject/SFEngineTask.cpp
	EngineObject/SFEngineTaskManager.cpp
	EngineObject/SFEngineTasks.cpp
	EngineObject/SFRenderTask.cpp
	Graphics/SFGraphicDevice.cpp
	Graphics/SFGraphicDeviceGLES.cpp
	Graphics/SFGraphicDeviceGLES_EGL.cpp
	Graphics/SFGraphicDeviceVulkan.cpp
	Graphics/SFRenderCommand.cpp
	Graphics/SFRenderCommands.cpp
	Graphics/SFRenderItem.cpp
	Graphics/SFRenderPipeline.cpp
	Graphics/SFRenderPipelineStage.cpp
	Graphics/SFRenderTargetChain.cpp
	Graphics/SFRenderThread.cpp
	Graphics/Vulkan/SFRenderTargetChainVulkan.cpp
	Graphics/Vulkan/SFVulkanRenderPass.cpp
	Graphics/Vulkan/SFVulkanTexture.cpp
	Graphics/Vulkan/SFVulkanDebug.cpp
	Graphics/Vulkan/SFVulkanLibrary.cpp
	Graphics/Vulkan/SFVulkanLogicalDevice.cpp
	Graphics/Vulkan/SFVulkanPhysicalDevice.cpp
	Graphics/Vulkan/SFVulkanSystem.cpp
	Net/SFConnection.cpp
	Net/SFConnectionAction.cpp
	Net/SFConnectionActions.cpp
	Net/SFConnectionGroup.cpp
	Net/SFConnectionManager.cpp
	Net/SFConnectionManagerTask.cpp
	Net/SFConnectionMUDP.cpp
	Net/SFConnectionMUDPClient.cpp
	Net/SFConnectionPeerTCP.cpp
	Net/SFConnectionTasks.cpp
	Net/SFConnectionTCP.cpp
	Net/SFConnectionUDP.cpp
	Net/SFConnectionUDPBase.cpp
	Net/SFLoopbackConnection.cpp
	Net/SFMessage.cpp
	Net/SFMessageWindow.cpp
	Net/SFNetCtrl.cpp
	Net/SFNetDef.cpp
	Net/SFNetRawUDP.cpp
	Net/SFNetServerPeerTCP.cpp
	Net/SFNetServerTCP.cpp
	Net/SFNetServerUDP.cpp
	Net/SFNetSocket.cpp
	Net/SFNetSvrDef.cpp
	Net/SFNetSystem.cpp
	Net/SFNetSystem_EPOLL.cpp
	Net/SFNetSystem_KQUEUE.cpp
	Net/SFNetSystem_Linux.cpp
	Net/SFNetSystem_WinIOCP.cpp
	Net/SFNetToString.cpp
	Net/SFNetUtil.cpp
	Resource/SFAnimation.cpp
	Resource/SFDeviceMesh.cpp
	Resource/SFDeviceResource.cpp
	Resource/SFDeviceTexture.cpp
	Resource/SFGraphicBuffer.cpp
	Resource/SFIndexBuffer.cpp
	Resource/SFMesh.cpp
	Resource/SFRawBinary.cpp
	Resource/SFResource.cpp
	Resource/SFResourceFactory.cpp
	Resource/SFResourceManager.cpp
	Resource/SFSparseResourceFactory.cpp
	Resource/SFTexture.cpp
	Resource/SFTextureFormatDescription.cpp
	Resource/SFVertexBuffer.cpp
	SceneGraph/SFScene.cpp
	SceneGraph/SFSceneNode.cpp
	SceneGraph/SFSceneNodeComponent.cpp
	SceneGraph/SFSceneNodeComponentMesh.cpp
	SceneGraph/SFSceneNodeComponentSkeletalMesh.cpp
	ServerConfig/SFEnum.cpp
	ServerConfig/SFServerConfig.cpp
	ServerConfig/SFServerConfigXML.cpp
	ServerConfig/SFServerConfigZooKeeper.cpp
	Service/SFEngineService.cpp
	SFEngine.Android.cpp
	SFEngine.cpp
	SFEngine.IOS.cpp
	SFEngine.Win.cpp
	String/SFToStringEngineTypes.cpp
	Types/SFEngineTypedefs.cpp
	ZooKeeper/SFZooKeeper.cpp

  	Application/Android/AndroidApp.h
	Application/Android/AndroidAppTasks.h
	Application/SFApplicationBase.h
	Application/IOS/IOSApp.h
	Application/IOS/IOSAppTasks.h
	Application/Win/WindowsApp.h
	Application/Win/WindowsAppTasks.h
	Asset/Exporter/SFAssetExporter.h
	Asset/Importer/SFAssetImportContext.h
	Asset/Importer/SFAssetImporter.h
	Asset/Importer/SFAssetImporter3DAsset.h
	Asset/Importer/SFAssetImporter3DAssetFBX.h
	Asset/Importer/SFAssetImporterBinary.h
	Asset/Importer/SFAssetImporterFactory.h
	Asset/Importer/SFAssetImporterTexture.h
	Asset/Importer/SFAssetImporterTextureJPG.h
	Asset/Importer/SFAssetImporterTexturePNG.h
	Asset/Importer/SFAssetImporterTextureTGA.h
	Asset/Package/SFAssetPackage.h
	Asset/Package/SFAssetPackageSerializer.h
	Asset/Serializer/SFAssetSerializer.h
	Asset/Serializer/SFAssetSerializerFactory.h
	Asset/Serializer/SFAssetSerializerTexture.h
	Component/SFConnectionManagerComponent.h
	EngineObject/SFEngineObject.h
	EngineObject/SFEngineObjectManager.h
	EngineObject/SFEngineTask.h
	EngineObject/SFEngineTaskManager.h
	EngineObject/SFEngineTasks.h
	EngineObject/SFRenderTask.h
	Graphics/SFGraphicDevice.h
	Graphics/SFGraphicDeviceGLES.h
	Graphics/SFGraphicDeviceGLES_EGL.h
	Graphics/SFGraphicDeviceVulkan.h
	Graphics/SFRenderCommand.h
	Graphics/SFRenderCommands.h
	Graphics/SFRenderItem.h
	Graphics/SFRenderPipeline.h
	Graphics/SFRenderPipelineStage.h
	Graphics/SFRenderTargetChain.h
	Graphics/SFRenderThread.h
	Graphics/Vulkan/SFRenderTargetChainVulkan.h
	Graphics/Vulkan/SFVulkanRenderPass.h
	Graphics/Vulkan/SFVulkanTexture.h
	Graphics/Vulkan/SFVulkanDebug.h
	Graphics/Vulkan/SFVulkanLibrary.h
	Graphics/Vulkan/SFVulkanLogicalDevice.h
	Graphics/Vulkan/SFVulkanPhysicalDevice.h
	Graphics/Vulkan/SFVulkanSystem.h
	Net/SFConnection.h
	Net/SFConnectionAction.h
	Net/SFConnectionActions.h
	Net/SFConnectionGroup.h
	Net/SFConnectionManager.h
	Net/SFConnectionManagerTask.h
	Net/SFConnectionMUDP.h
	Net/SFConnectionTasks.h
	Net/SFConnectionTCP.h
	Net/SFConnectionUDP.h
	Net/SFConnectionUDPBase.h
	Net/SFLoopbackConnection.h
	Net/SFMessage.h
	Net/SFMessageWindow.h
	Net/SFNetConst.h
	Net/SFNetCtrl.h
	Net/SFNetCtrlIDs.h
	Net/SFNetDef.h
	Net/SFNetRawUDP.h
	Net/SFNetServerTCP.h
	Net/SFNetServerPeerTCP.h
	Net/SFNetServerUDP.h
	Net/SFNetSocket.h
	Net/SFNetSvrDef.h
	Net/SFNetSystem.h
	Net/SFNetSystem_EPOLL.h
	Net/SFNetSystem_KQUEUE.h
	Net/SFNetSystem_Linux.h
	Net/SFNetSystem_WinIOCP.h
	Net/SFNetToString.h
	Net/SFNetUtil.h
	Resource/SFAnimation.h
	Resource/SFDeviceMesh.h
	Resource/SFDeviceResource.h
	Resource/SFDeviceTexture.h
	Resource/SFGraphicBuffer.h
	Resource/SFIndexBuffer.h
	Resource/SFMesh.h
	Resource/SFRawBinary.h
	Resource/SFResource.h
	Resource/SFResourceFactory.h
	Resource/SFResourceManager.h
	Resource/SFSparseResourceFactory.h
	Resource/SFTexture.h
	Resource/SFTextureFormat.h
	Resource/SFTextureFormatDescription.h
	Resource/SFVertexBuffer.h
	ResultCode/SFResultCodeEngine.h
	SceneGraph/SFScene.h
	SceneGraph/SFSceneNode.h
	SceneGraph/SFSceneNodeComponent.h
	SceneGraph/SFSceneNodeComponentMesh.h
	SceneGraph/SFSceneNodeComponentSkeletalMesh.h
	ServerConfig/SFEnum.h
	ServerConfig/SFServerConfig.h
	ServerConfig/SFServerConfigXML.h
	ServerConfig/SFServerConfigZooKeeper.h
	Service/SFConnectionManagerService.h
	Service/SFEngineService.h
	Service/SFEngineServices.h
	Service/SFIAssetImporterFactory.h
	Service/SFIAssetSerializerFactory.h
	Service/SFIGraphicDevice.h
	Service/SFNetSystemService.h
	Service/SFResourceManagerService.h
	SFEngine.h
	SFEnginePCH.h
	String/SFToStringEngineTypes.h
	Types/SFEngineTypedefs.h
	ZooKeeper/SFZooKeeper.h
	Net/SFConnection.inl
	Net/SFConnectionManager.inl
	Net/SFMessage.inl
	Net/SFNetCtrl.inl
	Net/SFNetDef.inl
	Net/SFNetSystem_Linux.inl
	Net/SFNetSystem_WinIOCP.inl

  )





add_library(SFEngine STATIC ${SFENGINE_LIB_FILES})


target_include_directories (SFEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}../SFCore ${CMAKE_CURRENT_SOURCE_DIR}../SFEngine)

