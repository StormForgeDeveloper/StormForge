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

SFDLL_EXPORT void SFEngine_NativeSetTitleUID(const uint8_t* titleUIDBytes)
{
    Util::SetTitleUID(Guid::FromBytes(titleUIDBytes));
}

SFDLL_EXPORT intptr_t SFEngine_NativeGetTitleUID()
{
    return (intptr_t)Util::GetTitleUID().data;
}

SFDLL_EXPORT void SFEngine_NativeSetTitleEnv(const char* titleEnv)
{
    Util::SetTitleEnv(titleEnv);
}

SFDLL_EXPORT const char* SFEngine_NativeGetTitleEnv()
{
    return Util::GetTitleEnv();
}

SFDLL_EXPORT void SFEngine_NativeInitializeNativeUnhandledExceptionHandler(const char* crashDumpfilePrefix, const char* crashShellCommand)
{
    auto* pEngine = SF::Engine::GetInstance();
    if (pEngine == nullptr)
        return;

    UnhandledExceptionHandlerComponent* pComponent = pEngine->AddComponent<UnhandledExceptionHandlerComponent>();
    pComponent->SetCrashDumpFilePrefix(crashDumpfilePrefix);
    pComponent->SetCrashShellCommand(crashShellCommand);
}

SFDLL_EXPORT void SFEngine_NativeSetCrashShellCommand(const char* crashShellCommand)
{
    auto* pEngine = SF::Engine::GetInstance();
    if (pEngine == nullptr)
        return;

    UnhandledExceptionHandlerComponent* pComponent = pEngine->GetComponent<UnhandledExceptionHandlerComponent>();
    if (pComponent)
    {
        pComponent->SetCrashShellCommand(crashShellCommand);
    }
}

SFDLL_EXPORT const char* SFEngine_NativeGetLogFileName()
{
    return Service::LogModule->GetLogFileName();;
}

SFDLL_EXPORT void SFEngine_NativeForceCrash()
{
    int* pInt = nullptr;
    *pInt = 0;
}
