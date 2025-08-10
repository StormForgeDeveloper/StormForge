////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2019 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Public Interfaces
//
////////////////////////////////////////////////////////////////////////////////


#pragma once 



#if defined(__GNUC__) || defined(__clang__) || SF_PLATFORM == SF_PLATFORM_IOS

#define SF_NOINLINE [[gnu::noinline]] 
#define SF_FORCEINLINE inline __attribute__((always_inline))
//#define SF_STDCALL __attribute__((stdcall))
#define SF_STDCALL 
#define SF_FASTCALL __attribute__((fastcall))
#define SF_TEMPLATE_EXTERN

// clang uses dllimport style
#define SFDLL_IMPORT __attribute__((visibility("default")))
#define SFDLL_EXPORT extern "C" __attribute__((visibility("default"))) 
#define SF_IMPORT __attribute__((visibility("default")))
#define SF_EXPORT __attribute__((visibility("default"))) 
#define SF_SYSTEMAPI 

#else

#define SF_NOINLINE __declspec(noinline)
#define SF_FORCEINLINE __forceinline
#define SF_STDCALL __stdcall
#define SF_FASTCALL __fastcall
#define SF_TEMPLATE_EXTERN extern

#define SFDLL_IMPORT extern "C" __declspec(dllimport)
#define SFDLL_EXPORT extern "C" __declspec(dllexport)
#define SF_IMPORT __declspec(dllimport)
#define SF_EXPORT __declspec(dllexport)
#define SF_SYSTEMAPI APIENTRY


#endif


#ifdef SF_BUILD_ENGINE_DLL
#	define SF_ENGINE_API SF_EXPORT
#else
#	define SF_ENGINE_API SF_IMPORT
#endif



namespace SF {

	// Interface 
	SF_ENGINE_API void* GetInterface(const char* interfaceName);
	

}; // namespace SF

