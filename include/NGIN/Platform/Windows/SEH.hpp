#pragma once
#ifdef NGIN_PLATFORM_WINDOWS
#include <windows.h>

namespace NGIN::Platform::Windows
{
    void GenerateMiniDump(EXCEPTION_POINTERS* e);

    void PrintStackTrace(EXCEPTION_POINTERS* pExceptionPointers);

    const char* ExceptionCodeToString(DWORD exceptionCode);

    LONG WINAPI UnhandledExceptionHandler(EXCEPTION_POINTERS* pExceptionPointers);
}// namespace NGIN::Platform::Windows

#endif