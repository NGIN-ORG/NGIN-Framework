
#include <NGIN/System/Info.hpp>
#include <iostream>
#include <winrt/Windows.Security.ExchangeActiveSyncProvisioning.h>
#include <winrt/Windows.System.Profile.h>
#include <winrt/Windows.System.h>

#include <windows.h>

#include <array>
#include <intrin.h>
namespace NGIN::System
{
    Info GetSystemInfo()
    {

        Info info = {};

        // Using Windows Runtime C++ Template Library (WinRT)
        winrt::init_apartment();
        auto analyticsVersionInfo = winrt::Windows::System::Profile::AnalyticsInfo::VersionInfo();

        auto deviceFamily = analyticsVersionInfo.DeviceFamily();
        auto systemVersion = winrt::Windows::System::Profile::AnalyticsInfo::VersionInfo().DeviceFamilyVersion();
        auto easClientDeviceInformation = winrt::Windows::Security::ExchangeActiveSyncProvisioning::EasClientDeviceInformation();

        info.hostName = winrt::to_string(easClientDeviceInformation.FriendlyName());
        // Set the OS name based on the device family
        info.osName = winrt::to_string(analyticsVersionInfo.ProductName());

        // Parse the system version to a human-readable format
        unsigned long long v = _strtoui64(winrt::to_string(systemVersion).c_str(), nullptr, 10);
        unsigned long long v1 = (v & 0xFFFF000000000000L) >> 48;
        unsigned long long v2 = (v & 0x0000FFFF00000000L) >> 32;
        unsigned long long v3 = (v & 0x00000000FFFF0000L) >> 16;
        unsigned long long v4 = v & 0x000000000000FFFFL;
        info.osVersion = std::to_string(v1) + "." + std::to_string(v2) + "." + std::to_string(v3) + "." + std::to_string(v4);

        // Get CPU architecture

        SYSTEM_INFO sysInfo;
        GetNativeSystemInfo(&sysInfo);

        switch (sysInfo.wProcessorArchitecture)
        {
            case PROCESSOR_ARCHITECTURE_AMD64:
                info.architecture = "x64";
                break;
            case PROCESSOR_ARCHITECTURE_ARM:
                info.architecture = "ARM";
                break;
            case PROCESSOR_ARCHITECTURE_ARM64:
                info.architecture = "ARM64";
                break;
            case PROCESSOR_ARCHITECTURE_IA64:
                info.architecture = "Intel Itanium-based";
                break;
            case PROCESSOR_ARCHITECTURE_INTEL:
                info.architecture = "x86";
                break;
            default:
                info.architecture = "Unknown";
        }


        // Get the number of physical/logical cores

        DWORD length = 0;
        GetLogicalProcessorInformation(nullptr, &length);
        std::vector<SYSTEM_LOGICAL_PROCESSOR_INFORMATION> buffer(length / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION));
        GetLogicalProcessorInformation(buffer.data(), &length);


        for (const auto& elem: buffer)
        {
            if (elem.Relationship == RelationProcessorCore)
            {
                ++info.physicalCores;
                DWORD mask = elem.ProcessorMask;
                while (mask)
                {
                    if (mask & 1)
                        ++info.logicalCores;
                    mask >>= 1;
                }
            }
        }

        //Get the name of cpu

        std::array<int, 4> cpuInfo;
        std::array<char, 48> brand;

        // Get the information associated with each extended ID
        __cpuid(cpuInfo.data(), 0x80000000);
        const int maxExtendedId = cpuInfo[0];

        if (maxExtendedId >= 0x80000004)
        {
            // The CPU brand string is returned in 3 parts, each part in a separate call to __cpuid with eax set to 0x80000002, 0x80000003, and 0x80000004
            __cpuid(reinterpret_cast<int*>(brand.data()), 0x80000002);
            __cpuid(reinterpret_cast<int*>(brand.data() + 16), 0x80000003);
            __cpuid(reinterpret_cast<int*>(brand.data() + 32), 0x80000004);
        }

        info.cpuModel = String(brand.data());
        //ram

        MEMORYSTATUSEX memStatus;
        memStatus.dwLength = sizeof(memStatus);
        if (GlobalMemoryStatusEx(&memStatus))
        {
            info.totalMemMB = memStatus.ullTotalPhys / 1024 / 1024;// Convert bytes to megabytes
            info.availableMemMB = memStatus.ullAvailPhys / 1024 / 1024;
            info.totalVirtualMemMB = memStatus.ullTotalPageFile / 1024 / 1024;
            info.availableVirtualMemMB = memStatus.ullAvailPageFile / 1024 / 1024;
        }

        info.systemUptime = static_cast<double>(GetTickCount64()) / 1000.0;

        return info;
    }
}// namespace NGIN::System