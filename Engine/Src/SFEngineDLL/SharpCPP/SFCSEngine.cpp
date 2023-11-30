////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Engine interface
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEngineDLLPCH.h"

#include "SFAssert.h"
#include "Util/SFUtility.h"

#include "Service/SFServices.h"
#include "Service/SFEngineService.h"
#include "SFEngine.h"
#include "Component/SFUnhandledExceptionHandlerComponent.h"

using namespace SF;

//////////////////////////////////////////////////////////////////////////////////////
//
//	Engine interface
//

SFDLL_EXPORT void SFEngine_NativeInitializeTelemetry(const char* serverAddress, uint32_t gameId, const char* authKey)
{
    auto* pEngine = SF::Engine::GetInstance();
    if (pEngine == nullptr)
        return;

    // TODO
    //pEngine->AddComponent<TelemetryComponent>(serverAddress, gameId, authKey);
}

SFDLL_EXPORT void SFEngine_NativeInitializeNativeUnhandledExceptionHandler(const char* crashShellCommand)
{
    auto* pEngine = SF::Engine::GetInstance();
    if (pEngine == nullptr)
        return;

    UnhandledExceptionHandlerComponent* pComponent = pEngine->AddComponent<UnhandledExceptionHandlerComponent>();
    pComponent->SetCrashShellCommand(crashShellCommand);
}

SFDLL_EXPORT void SFEngine_NativeForceCrash()
{
    int* pInt = nullptr;
    *pInt = 0;
}

