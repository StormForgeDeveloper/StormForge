


set(SUBCOMPONENT_FILES
	Component/SFComponent.h
	Component/SFLibraryComponent.h
	Component/SFLibraryComponent.cpp
	Component/SFLibraryComponentInitializer.h
	Component/SFLibraryComponentInitializer.cpp
	Component/SFLibraryComponentAdapter.h
	#Component/SFLibraryComponentAdapter.cpp
	Component/SFLibraryComponentManager.h
	#Component/SFLibraryComponentManager.cpp
  	Component/SFUnhandledExceptionHandlerComponent.h
  	Component/SFUnhandledExceptionHandlerComponent.cpp
  )

source_group(Component FILES
	${SUBCOMPONENT_FILES} 
)


set(SUBCONTAINER_FILES
	Container/SFCircularBuffer.cpp
	Container/SFCircularBufferQueue.cpp
	Container/SFStackPool.cpp
	Container/SFCircularBuffer.h
	Container/SFCircularBufferQueue.h
	Container/SFCircularPageQueue.h
	Container/SFCircularQueue.h
	Container/SFCircularQueue.inl
	Container/SFContainerTrait.h
	Container/SFContainerTraitBase.h
	Container/SFDoubleLinkedList.h
	Container/SFDoubleLinkedListBase.h
	Container/SFDualSortedMap.h
	Container/SFSortedMap_Base.h
	Container/SFHashTable.h
	Container/SFHashTable2.h
	Container/SFIndexing.h
	Container/SFOrderedLinkedList.h
	Container/SFPageQueue.h
	Container/SFPageQueue.inl
    Container/SFArrayBase.h
	Container/SFArray.h
	Container/SFArraySerialization.h
	Container/SFSortedSet.h
	Container/SFSortedArray.h
	Container/SFSortedMap.h
	Container/SFSpinBuffer.h
	Container/SFSpinBufferMT.h
	Container/SFSpinSharedBuffer.h
	Container/SFStackPool.h
	Container/SFStaticDoubleLinkedList.h
	Container/SFStaticHashTable.h
	Container/SFStaticLinkedList.h
	Container/SFCircularPageQueue.inl
	Container/SFDualSortedMap.inl
	Container/SFArray.inl
	Container/SFSortedArray.inl
	Container/SFSortedMap.inl
	Container/SFSpinBuffer.inl
	Container/SFSpinBufferMT.inl
	Container/SFSpinSharedBuffer.inl
	Container/SFStackPool.inl
	Container/SFSortedSet.inl
  )

source_group(Container FILES
	${SUBCONTAINER_FILES} 
)

set(SUBIO_FILES
	IO/AsyncIO/AsyncIOAdapter.cpp
	IO/AsyncIO/AsyncIOPort.cpp
	IO/AsyncIO/AsyncIOPortSystemImpl.cpp
	IO/AsyncIO/AsyncIOPortWriteBufferQueue.cpp
	IO/AsyncIO/AsyncIOPort_EPOLL.cpp
	IO/AsyncIO/AsyncIOPort_IOCP.cpp
	IO/AsyncIO/AsyncIOPort_KQUEUE.cpp
	IO/AsyncIO/AsyncIOPort_Reactor.cpp
	IO/SFFile.cpp
	IO/SFFile.linux.cpp
	IO/SFFile.win32.cpp
	IO/SFFileInputStream.cpp
	IO/SFFileOutputStream.cpp
	IO/SFFileUtil.h
	IO/SFFileUtil.cpp
	IO/SharedMemory/SFSharedMemory.cpp
	IO/SharedMemory/SFSharedMemory_linux.cpp
	IO/SharedMemory/SFSharedMemory_win.cpp
	IO/AsyncIO/AsyncIOAdapter.h
	IO/AsyncIO/AsyncIOPort.h
	IO/AsyncIO/AsyncIOPortSystemImpl.h
	IO/AsyncIO/AsyncIOPortWriteBufferQueue.h
	IO/AsyncIO/AsyncIOPort_EPOLL.h
	IO/AsyncIO/AsyncIOPort_IOCP.h
	IO/AsyncIO/AsyncIOPort_KQUEUE.h
	IO/AsyncIO/AsyncIOPort_Reactor.h
	IO/SFFile.h
	IO/SFFileInputStream.h
	IO/SFFileOutputStream.h
	IO/SharedMemory/SFSharedMemory.h
  )

source_group(IO FILES
	${SUBIO_FILES} 
)

set(SUBMemoryManager_FILES
	MemoryManager/SFHeapMemory.h
	MemoryManager/SFHeapTree.h
	MemoryManager/SFIMemoryManager.h
	MemoryManager/SFCircularHeap.h
	MemoryManager/SFCircularHeap.cpp
	MemoryManager/SFMemory.h
	MemoryManager/SFMemoryManager.h
	MemoryManager/SFMemoryPool.h
	MemoryManager/SFStackHeap.h
	MemoryManager/SFStackHeap.cpp
	MemoryManager/SFHeapMemory.cpp
	MemoryManager/SFHeapTree.cpp
	MemoryManager/SFIMemoryManager.cpp
	MemoryManager/SFMemory.cpp
	MemoryManager/SFMemoryManager.cpp
	MemoryManager/SFMemoryPool.cpp
  )

source_group(MemoryManager FILES
	${SUBMemoryManager_FILES} 
)

set(SUBUtil_FILES
	Util/AppConfig.h
	Util/AppConfig.cpp
	Util/SFCryptoBase64.cpp
	Util/SFCryptoCrc32.cpp
	Util/SFCryptoCrc32C.cpp
	Util/SFCryptoCrc64.cpp
	Util/SFStringCrcComponent.h
	Util/SFStringCrcComponent.cpp
	Util/SFCryptoSHA.cpp
	Util/SFLog.cpp
	Util/SFLogComponent.cpp
	Util/SFLogOutputLogServerComponent.h
	Util/SFLogOutputLogServerComponent.cpp
	Util/SFPath.cpp
	Util/SFRandom.cpp
	Util/SFTimeUtil.cpp
	Util/SFUniqueIDGenerator.cpp
	Util/SFUtility.cpp
	Util/SFStringFormat.h
	Util/SFStringCrc64.h
	Util/SFStringCrc32.h
	Util/SFStringCrcDB.h
	Util/SFHasher32.h
	Util/SFHasher32C.h
	Util/SFHasher64.h
	Util/SFPathString.h
	Util/SFString.h
	Util/SFStrFormat.h
	Util/SFStrParserUtil.h
	Util/SFStringSerialization.h
	Util/SFStrUtil.h
	Util/SFToString.h
	Util/SFToStringBase.h
	Util/SFStringCrc64.cpp
	Util/SFStringCrcDB.cpp
	Util/SFPathString.cpp
	Util/SFString.cpp
	Util/SFStrParserUtil.cpp
	Util/SFStrUtil.cpp
    Util/SFStrUtil2.cpp
	Util/SFToString.cpp
	Util/SFToStringBase.cpp
	Util/SFCodecHex.cpp
	Util/SFLog.h
	Util/SFLogComponent.h
	Util/SFPath.h
	Util/SFRandom.h
	Util/SFTimeUtil.h
	Util/SFUniqueIDGenerator.h
	Util/SFUtility.h
	Util/SFRandom.inl
	Util/SFTimeUtil.inl
	Util/SFUtility.inl
	Util/SFHashCRC32Table.inl
	Util/SFStrUtil.inl
	Util/SFDebugger.h
	Util/SFDebugger.cpp
  )

source_group(Util FILES
	${SUBUtil_FILES} 
)

set(SUBVariable_FILES
	Variable/SFNamedVariableBox.h
	Variable/SFNamedVariableBox.cpp
	Variable/SFNamedVariableArray.h
	Variable/SFNamedVariableArray.cpp
	Variable/SFVariable.h
	Variable/SFVariable.cpp
	Variable/SFVariableBoxing.h
	Variable/SFVariableBoxing.cpp
	Variable/SFVariableStack.h
	Variable/SFVariableStack.cpp
	Variable/SFVariableTable.h
	Variable/SFVariableTable.cpp
	Variable/SFVariableSerialization.h
	Variable/SFVariableSerialization.cpp
	Variable/SFVariableFactoryService.h
	Variable/SFVariableFactoryService.cpp
	Variable/SFVariableMapBuilder.h
	Variable/SFVariableToString.h
	Variable/SFVariableToString.cpp
	Variable/SFVariableCommonDefs.h
  )

source_group(Variable FILES
	${SUBVariable_FILES} 
)

set(SUBMath_FILES
	Math/SF3DMath.cpp
	Math/SF3DMathSSE.cpp
	Math/SF3DMathSerialization.h
	Math/SF3DMathSerialization.cpp
	Math/SF3DMath.h
	Math/SF3DMathSoft.h
	Math/SF3DMathSSE.h
	Math/SFAngle.h
	Math/SFMath.h
	Math/SFMathConsts.h
	Math/SFMathTypes.h
	Math/SFMathUtil.h
	Math/SF3DMathSoft.inl
	Math/SF3DMath_matrixSoft.inl
	Math/SF3DMath_quaternionSoft.inl
	Math/SF3DMath_vectorSoft.inl
	Math/SFAngle.inl
	Math/SFMath.inl
  )

source_group(Math FILES
	${SUBMath_FILES} 
)

set(SUBScript_FILES
	Script/Tong/SFTongScriptBytecode.cpp
	Script/Tong/SFTongScriptContext.cpp
	Script/Tong/SFTongScriptEnvironment.cpp
	Script/Tong/SFTongScriptEngine.cpp
	Script/Tong/SFTongScriptFunction.cpp
	Script/Tong/SFTongScriptVariable.cpp
	Script/Tong/SFTongScriptBytecode.h
	Script/Tong/SFTongScriptContext.h
	Script/Tong/SFTongScriptBytecodeOpCode.h
	Script/Tong/SFTongScriptEnvironment.h
	Script/Tong/SFTongScriptEngine.h
	Script/Tong/SFTongScriptFunction.h
	Script/Tong/SFTongScriptVariable.h
  )

source_group(Script FILES
	${SUBScript_FILES} 
)


set(SUBObject_FILES
	Object/SFObjectPool.cpp
	Object/SFObject.cpp
	Object/SFObjectManager.cpp
	Object/SFSharedObject.cpp
	Object/SFSharedObjectManager.cpp
	Object/SFObjectPool.h
	Object/SFObject.h
	Object/SFObjectManager.h
	Object/SFSharedObject.h
	Object/SFSharedPointer.h
	Object/SFSharedObjectManager.h
  )

source_group(Object FILES
	${SUBObject_FILES} 
)

set(SUBResult_FILES
	SFResult.h
	SFResult.cpp
	ResultCode/SFResultTable.h
	ResultCode/SFResultTable.cpp
	ResultCode/SFResultCodeLibrary.h
	ResultCode/SFResultCodeLibrary.cpp
	ResultCode/SFResultCodeSystem.h
	ResultCode/SFResultCodeSystem.cpp
  )

source_group(Result FILES
	${SUBResult_FILES} 
)

set(SUBService_FILES
	Service/SFAsyncIOPortService.h
	Service/SFLogService.h
	Service/SFLogService.cpp
	Service/SFScriptService.h
	Service/SFService.h
	Service/SFServices.h
	Service/SFScriptService.cpp
	Service/SFService.cpp
  )

source_group(Service FILES
	${SUBService_FILES} 
)

set(SUBOnline_FILES
	Online/StreamDB/SFStreamDB.h
	Online/StreamDB/SFStreamDB.cpp
	Online/Telemetry/SFTelemetryBR.h
	Online/Telemetry/SFTelemetryBR.cpp
	Online/Telemetry/SFTelemetryService.h
	Online/Telemetry/SFTelemetryService.cpp
	Online/Telemetry/SFTelemetryComponent.h
	Online/Telemetry/SFTelemetryComponent.cpp
	Online/Telemetry/SFTelemetryEventQueue.h
	Online/Telemetry/SFTelemetryEventQueue.cpp
	Online/Websocket/SFWebsocket.h
	Online/Websocket/SFWebsocket.cpp
	Online/Websocket/SFWebsocketComponent.h
	Online/Websocket/SFWebsocketComponent.cpp
	Online/Websocket/SFWebsocketClient.h
	Online/Websocket/SFWebsocketClient.cpp
  )

source_group(Online FILES
	${SUBOnline_FILES} 
)


set(SFCORE_LIB_FILES
	Delegate/SFEventDelegate.h
	Platform/Android/SFifaddrs.h
	SFCorePCH.h
	Platform/SFNativeWindow.h
	Platform/SFStackWalker.h
	Platform/SFStackWalkerComponent.h
	Platform/Android/SFifaddrs.cpp
	Platform/SFNativeWindow.cpp
	Platform/SFStackWalker.cpp
	SFAssert.h
	SFNetAddress.h
	SFNetAddress.cpp
	SFScopeContext.h
	SFTypedefs.h
	SFTypedefs.cpp
	Stream/SFCompressedStream.h
	Stream/SFMemoryStream.h
	Stream/SFStream.h
	Stream/SFStream.cpp
	Stream/SFCompressedStream.cpp
	Stream/SFMemoryStream.cpp

	Task/SFAsyncTaskManager.h
	Task/SFTask.h
	Task/SFTimerScheduler.h
	Task/SFTimerSchedulerAction.h
	Task/SFAsyncTaskManager.cpp
	Task/SFTask.cpp
	Task/SFTimerScheduler.cpp
	Multithread/SFSynchronization.h
	Multithread/SFSystemSynchronization.h
	Multithread/SFThread.h
	Multithread/SFSynchronization.inl
	Multithread/SFSystemSynchronize_win.inl
	Multithread/SFThread.inl
	Multithread/SFSynchronization.cpp
	Multithread/SFThread.cpp

  )




include_directories(./)


add_library(SFCore STATIC ${SUBCOMPONENT_FILES} ${SUBCONTAINER_FILES} ${SUBIO_FILES} ${SUBResult_FILES} ${SUBService_FILES} ${SUBMemoryManager_FILES} ${SUBUtil_FILES} ${SUBVariable_FILES} ${SUBMath_FILES} ${SUBObject_FILES} ${SUBOnline_FILES} ${SUBScript_FILES} ${SFCORE_LIB_FILES})

target_precompile_headers(SFCore PUBLIC SFCorePCH.h)
target_include_directories (SFCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

install (TARGETS SFCore
         ARCHIVE DESTINATION lib COMPONENT StormForge
         LIBRARY DESTINATION lib COMPONENT StormForge
         RUNTIME DESTINATION bin COMPONENT StormForge)


