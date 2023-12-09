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



#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "Platform/SFCPUInfo.h"

namespace SF
{


#if SF_PLATFORM == SF_PLATFORM_WINDOWS

    class CPUInfo_Windows
    {
    public:
        std::string vendor_ = "";
        std::string brand_ = "";
        bool isIntel_ = false;
        bool isAMD_ = false;
        std::bitset<32> f_1_ECX_;
        std::bitset<32> f_1_EDX_;
        std::bitset<32> f_7_EBX_;
        std::bitset<32> f_7_ECX_;
        std::bitset<32> f_81_ECX_;
        std::bitset<32> f_81_EDX_;

        CPUInfo_Windows()
            : f_1_ECX_{ 0 }
            , f_1_EDX_{ 0 }
            , f_7_EBX_{ 0 }
            , f_7_ECX_{ 0 }
            , f_81_ECX_{ 0 }
            , f_81_EDX_{ 0 }
        {

            int nIds_ = 0;
            int nExIds_ = 0;
            std::vector<std::array<int, 4>> data_{};
            std::vector<std::array<int, 4>> extdata_{};

            //int cpuInfo[4] = {-1};
            std::array<int, 4> cpui;

            // Calling __cpuid with 0x0 as the function_id argument
            // gets the number of the highest valid function ID.
            __cpuid(cpui.data(), 0);
            nIds_ = cpui[0];

            for (int i = 0; i <= nIds_; ++i)
            {
                __cpuidex(cpui.data(), i, 0);
                data_.push_back(cpui);
            }

            // Capture vendor string
            char vendor[0x20];
            memset(vendor, 0, sizeof(vendor));
            *reinterpret_cast<int*>(vendor) = data_[0][1];
            *reinterpret_cast<int*>(vendor + 4) = data_[0][3];
            *reinterpret_cast<int*>(vendor + 8) = data_[0][2];
            vendor_ = vendor;

            // load bitset with flags for function 0x00000001
            if (nIds_ >= 1)
            {
                f_1_ECX_ = data_[1][2];
                f_1_EDX_ = data_[1][3];
            }

            // load bitset with flags for function 0x00000007
            if (nIds_ >= 7)
            {
                f_7_EBX_ = data_[7][1];
                f_7_ECX_ = data_[7][2];
            }

            // Calling __cpuid with 0x80000000 as the function_id argument
            // gets the number of the highest valid extended ID.
            __cpuid(cpui.data(), 0x80000000);
            nExIds_ = cpui[0];

            char brand[0x40];
            memset(brand, 0, sizeof(brand));

            for (int i = 0x80000000; i <= nExIds_; ++i)
            {
                __cpuidex(cpui.data(), i, 0);
                extdata_.push_back(cpui);
            }

            // load bitset with flags for function 0x80000001
            if (nExIds_ >= 0x80000001)
            {
                f_81_ECX_ = extdata_[1][2];
                f_81_EDX_ = extdata_[1][3];
            }

            // Interpret CPU brand string if reported
            if (nExIds_ >= 0x80000004)
            {
                memcpy(brand, extdata_[2].data(), sizeof(cpui));
                memcpy(brand + 16, extdata_[3].data(), sizeof(cpui));
                memcpy(brand + 32, extdata_[4].data(), sizeof(cpui));
                brand_ = brand;
            }

            if (vendor_ == "GenuineIntel")
            {
                isIntel_ = true;
            }
            else if (vendor_ == "AuthenticAMD")
            {
                isAMD_ = true;
            }

        }

        SF_FORCEINLINE const std::string& Vendor() const { return vendor_; }
        SF_FORCEINLINE const std::string& Brand() const { return brand_; }

        SF_FORCEINLINE bool SSE3() const { return f_1_ECX_[0]; }
        SF_FORCEINLINE bool PCLMULQDQ() const { return f_1_ECX_[1]; }
        SF_FORCEINLINE bool MONITOR() const { return f_1_ECX_[3]; }
        SF_FORCEINLINE bool SSSE3() const { return f_1_ECX_[9]; }
        SF_FORCEINLINE bool FMA() const { return f_1_ECX_[12]; }
        SF_FORCEINLINE bool CMPXCHG16B() const { return f_1_ECX_[13]; }
        SF_FORCEINLINE bool SSE41() const { return f_1_ECX_[19]; }
        SF_FORCEINLINE bool SSE42() const { return f_1_ECX_[20]; }
        SF_FORCEINLINE bool MOVBE() const { return f_1_ECX_[22]; }
        SF_FORCEINLINE bool POPCNT() const { return f_1_ECX_[23]; }
        SF_FORCEINLINE bool AES() const { return f_1_ECX_[25]; }
        SF_FORCEINLINE bool XSAVE() const { return f_1_ECX_[26]; }
        SF_FORCEINLINE bool OSXSAVE() const { return f_1_ECX_[27]; }
        SF_FORCEINLINE bool AVX() const { return f_1_ECX_[28]; }
        SF_FORCEINLINE bool F16C() const { return f_1_ECX_[29]; }
        SF_FORCEINLINE bool RDRAND() const { return f_1_ECX_[30]; }


        SF_FORCEINLINE bool MSR() const { return f_1_EDX_[5]; }
        SF_FORCEINLINE bool CX8() const { return f_1_EDX_[8]; }
        SF_FORCEINLINE bool SEP() const { return f_1_EDX_[11]; }
        SF_FORCEINLINE bool CMOV() const { return f_1_EDX_[15]; }
        SF_FORCEINLINE bool CLFSH() const { return f_1_EDX_[19]; }
        SF_FORCEINLINE bool MMX() const { return f_1_EDX_[23]; }
        SF_FORCEINLINE bool FXSR() const { return f_1_EDX_[24]; }
        SF_FORCEINLINE bool SSE() const { return f_1_EDX_[25]; }
        SF_FORCEINLINE bool SSE2() const { return f_1_EDX_[26]; }

        SF_FORCEINLINE bool FSGSBASE() const { return f_7_EBX_[0]; }
        SF_FORCEINLINE bool BMI1() const { return f_7_EBX_[3]; }
        SF_FORCEINLINE bool HLE() const { return isIntel_ && f_7_EBX_[4]; }
        SF_FORCEINLINE bool AVX2() const { return f_7_EBX_[5]; }
        SF_FORCEINLINE bool BMI2() const { return f_7_EBX_[8]; }
        SF_FORCEINLINE bool ERMS() const { return f_7_EBX_[9]; }
        SF_FORCEINLINE bool INVPCID() const { return f_7_EBX_[10]; }
        SF_FORCEINLINE bool RTM() const { return isIntel_ && f_7_EBX_[11]; }
        SF_FORCEINLINE bool AVX512F() const { return f_7_EBX_[16]; }
        SF_FORCEINLINE bool RDSEED() const { return f_7_EBX_[18]; }
        SF_FORCEINLINE bool ADX() const { return f_7_EBX_[19]; }
        SF_FORCEINLINE bool AVX512PF() const { return f_7_EBX_[26]; }
        SF_FORCEINLINE bool AVX512ER() const { return f_7_EBX_[27]; }
        SF_FORCEINLINE bool AVX512CD() const { return f_7_EBX_[28]; }
        SF_FORCEINLINE bool SHA() const { return f_7_EBX_[29]; }

        SF_FORCEINLINE bool PREFETCHWT1() const { return f_7_ECX_[0]; }

        SF_FORCEINLINE bool LAHF() const { return f_81_ECX_[0]; }
        SF_FORCEINLINE bool LZCNT() const { return isIntel_ && f_81_ECX_[5]; }
        SF_FORCEINLINE bool ABM() const { return isAMD_ && f_81_ECX_[5]; }
        SF_FORCEINLINE bool SSE4a() const { return isAMD_ && f_81_ECX_[6]; }
        SF_FORCEINLINE bool XOP() const { return isAMD_ && f_81_ECX_[11]; }
        SF_FORCEINLINE bool TBM() const { return isAMD_ && f_81_ECX_[21]; }

        SF_FORCEINLINE bool SYSCALL() const { return isIntel_ && f_81_EDX_[11]; }
        SF_FORCEINLINE bool MMXEXT() const { return isAMD_ && f_81_EDX_[22]; }
        SF_FORCEINLINE bool RDTSCP() const { return isIntel_ && f_81_EDX_[27]; }
        SF_FORCEINLINE bool _3DNOWEXT() const { return isAMD_ && f_81_EDX_[30]; }
        SF_FORCEINLINE bool _3DNOW() const { return isAMD_ && f_81_EDX_[31]; }

    };
#endif

#if defined(__clang__)
    class CPUInfo_Clang
    {
    private:
        std::string m_Vendor = "";
        std::string m_Flags = "";
        CPUInfo::CPUFeatures m_Features;

    public:
        CPUInfo_Clang()
        {
            ProcessCPUInfo();

            __builtin_cpu_init();

            m_Features.SSE = __builtin_cpu_supports("sse");
            m_Features.SSE2 = __builtin_cpu_supports("sse2");
            m_Features.SSE3 = __builtin_cpu_supports("sse3");
            m_Features.SSSE3 = __builtin_cpu_supports("ssse3");
            m_Features.SSE41 = __builtin_cpu_supports("sse4.1");
            m_Features.SSE42 = __builtin_cpu_supports("sse4.2");
            m_Features.SSE4a = __builtin_cpu_supports("sse4a");

            m_Features.CMOV = __builtin_cpu_supports("cmov");
            m_Features.MMX = __builtin_cpu_supports("mmx");
            m_Features.POPCNT = __builtin_cpu_supports("popcnt");

            m_Features.AVX = __builtin_cpu_supports("avx");
            m_Features.AVX2 = __builtin_cpu_supports("avx2");
            m_Features.AVX512F = __builtin_cpu_supports("avx512f");
            m_Features.AVX512ER = __builtin_cpu_supports("avx512er");
            m_Features.AVX512CD = __builtin_cpu_supports("avx512cd");
            m_Features.AVX512PF = __builtin_cpu_supports("avx512pf");
        }

        void ProcessCPUInfo()
        {
            FILE* cpuinfo = fopen("/proc/cpuinfo", "r");
            if (cpuinfo == nullptr)
            {
                printf("Failed to get cpuinfo");
                return;
            }

            bool bGotVendor = false;
            bool bGotFlags = false;

            char line[4096]{};
            while (fgets(line, 256, cpuinfo))
            {
                if (strncmp(line, "vendor_id", 9) == 0)
                {
                    char* colon = strchr(line, ':');
                    if (colon == NULL || colon[1] == 0)
                    {
                        printf("Invalid vendorId line:'%s'", line);
                        continue;
                    }

                    m_Vendor = colon + 1;
                    bGotVendor = true;
                }
                else if (strncmp(line, "flags", 9) == 0)
                {
                    char* colon = strchr(line, ':');
                    if (colon == NULL || colon[1] == 0)
                    {
                        printf("Invalid flags line:'%s'", line);
                        continue;
                    }

                    m_Flags = colon + 1;
                    bGotFlags = true;
                }

                if (bGotVendor && bGotFlags)
                    break;
            }

            fclose(cpuinfo);
        }

        SF_FORCEINLINE const std::string& Vendor() const { return m_Vendor; }

        SF_FORCEINLINE bool SSE() const { return m_Features.SSE; }
        SF_FORCEINLINE bool SSE2() const { return m_Features.SSE2; }
        SF_FORCEINLINE bool SSE3() const { return m_Features.SSE3; }
        SF_FORCEINLINE bool SSSE3() const { return m_Features.SSSE3; }
        SF_FORCEINLINE bool SSE41() const { return m_Features.SSE41; }
        SF_FORCEINLINE bool SSE42() const { return m_Features.SSE42; }
        SF_FORCEINLINE bool SSE4a() const { return m_Features.SSE4a; }

        SF_FORCEINLINE bool CMOV() const { return m_Features.CMOV; }
        SF_FORCEINLINE bool MMX() const { return m_Features.MMX; }
        SF_FORCEINLINE bool POPCNT() const { return m_Features.POPCNT; }

        SF_FORCEINLINE bool AVX() const { return m_Features.AVX; }
        SF_FORCEINLINE bool AVX2() const { return m_Features.AVX2; }
        SF_FORCEINLINE bool AVX512F() const { return m_Features.AVX512F; }
        SF_FORCEINLINE bool AVX512ER() const { return m_Features.AVX512ER; }
        SF_FORCEINLINE bool AVX512CD() const { return m_Features.AVX512CD; }
        SF_FORCEINLINE bool AVX512PF() const { return m_Features.AVX512PF; }
    };
#endif


    CPUInfo CPUInfo::Instance;

    CPUInfo::CPUInfo()
    {
#if SF_PLATFORM == SF_PLATFORM_WINDOWS
        CPUInfo_Windows CPUInfoImpl;
#else
        CPUInfo_Clang CPUInfoImpl;
#endif

        m_Vendor = CPUInfoImpl.Vendor();

        m_Features.SSE = CPUInfoImpl.SSE() ? 1 : 0;
        m_Features.SSE2 = CPUInfoImpl.SSE2() ? 1 : 0;
        m_Features.SSE3 = CPUInfoImpl.SSE3() ? 1 : 0;
        m_Features.SSSE3 = CPUInfoImpl.SSSE3() ? 1 : 0;
        m_Features.SSE41 = CPUInfoImpl.SSE41() ? 1 : 0;
        m_Features.SSE42 = CPUInfoImpl.SSE42() ? 1 : 0;
        m_Features.SSE4a = CPUInfoImpl.SSE4a() ? 1 : 0;

        m_Features.POPCNT = CPUInfoImpl.POPCNT() ? 1 : 0;
        m_Features.CMOV = CPUInfoImpl.CMOV() ? 1 : 0;
        m_Features.MMX = CPUInfoImpl.MMX() ? 1 : 0;

        m_Features.AVX = CPUInfoImpl.AVX() ? 1 : 0;
        m_Features.AVX2 = CPUInfoImpl.AVX2() ? 1 : 0;
        m_Features.AVX512F = CPUInfoImpl.AVX512F() ? 1 : 0;
        m_Features.AVX512ER = CPUInfoImpl.AVX512ER() ? 1 : 0;
        m_Features.AVX512CD = CPUInfoImpl.AVX512CD() ? 1 : 0;
        m_Features.AVX512PF = CPUInfoImpl.AVX512PF() ? 1 : 0;
    };

} // namespace SF
