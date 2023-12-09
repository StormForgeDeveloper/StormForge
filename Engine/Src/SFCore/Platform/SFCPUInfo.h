////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : CPU info
//	
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"


namespace SF
{
    /////////////////////////////////////////////////////////////////////
    // 
    // class CPUInfo
    //   - Based on MS sample for windows
    //      https://learn.microsoft.com/en-us/cpp/intrinsics/cpuid-cpuidex?view=msvc-170
    //   - __builtin_cpu_supports for linux based system
    //      https://gcc.gnu.org/onlinedocs/gcc/x86-Built-in-Functions.html

    class CPUInfo
    {
    public:

        struct CPUFeatures
        {
            uint SSE : 1;
            uint SSE2 : 1;
            uint SSE3 : 1;
            uint SSSE3 : 1;
            uint SSE41 : 1;
            uint SSE42 : 1;
            uint SSE4a : 1;

            uint POPCNT : 1;
            uint CMOV : 1;
            uint MMX : 1;

            uint AVX : 1;
            uint AVX2 : 1;
            uint AVX512F : 1;
            uint AVX512CD : 1;
            uint AVX512ER : 1;
            uint AVX512PF : 1;
            //uint AVX512VL: 1;
            //uint AVX512BW : 1;
            //uint AVX512DQ : 1;
            //uint AVX512VBMI : 1;
            //uint AVX512IFMA : 1;
            //uint AVX5124VNNIW : 1;
            //uint AVX5124FMAPS : 1;
            //uint AVX512VPOPCNTDQ : 1;
            //uint AVX512VBMI2 : 1;
            //uint AVX512VNNI : 1;
            //uint AVX512BITALG : 1;
        };


    public:
        // getters
        SF_FORCEINLINE static const std::string& Vendor() { return Instance.m_Vendor; }

        SF_FORCEINLINE static const CPUFeatures& GetFeatures() { return Instance.m_Features; }

    private:

        // singleton instance
        static CPUInfo Instance;

        // Vendor string
        std::string m_Vendor;

        // Feature flags
        CPUFeatures m_Features;

        // constructor
        CPUInfo();
    };


} // namespace SF


