#pragma once
#include <NGIN/Platform/Windows/SEH.hpp>
#include <windows.h>
#include <DbgHelp.h>
#include <thread>
#include <iostream>

#pragma comment(lib, "dbghelp.lib")

extern std::thread::id mainThreadId;
namespace NGIN::Platform::Windows
{


    void GenerateMiniDump(EXCEPTION_POINTERS* e)
    {
        auto hDbgHelp = LoadLibraryA("dbghelp");
        if (hDbgHelp == nullptr)
            return;
        auto pMiniDumpWriteDump = (decltype(&MiniDumpWriteDump)) GetProcAddress(hDbgHelp, "MiniDumpWriteDump");
        if (pMiniDumpWriteDump == nullptr)
            return;

        char name[MAX_PATH];
        {
            auto nameEnd = name + GetModuleFileNameA(GetModuleHandleA(0), name, MAX_PATH);
            SYSTEMTIME t;
            GetSystemTime(&t);
            wsprintfA(nameEnd - strlen(".exe"),
                      "_%4d%02d%02d_%02d%02d%02d.dmp",
                      t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond);
        }

        auto hFile = CreateFileA(name, GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
        if (hFile == INVALID_HANDLE_VALUE)
            return;

        MINIDUMP_EXCEPTION_INFORMATION exceptionInfo;
        exceptionInfo.ThreadId = GetCurrentThreadId();
        exceptionInfo.ExceptionPointers = e;
        exceptionInfo.ClientPointers = FALSE;

        auto dumped = pMiniDumpWriteDump(
                GetCurrentProcess(),
                GetCurrentProcessId(),
                hFile,
                MINIDUMP_TYPE(MiniDumpWithIndirectlyReferencedMemory | MiniDumpScanMemory),
                e ? &exceptionInfo : nullptr,
                nullptr,
                nullptr);

        CloseHandle(hFile);

        return;
    }

    const char* ExceptionCodeToString(DWORD exceptionCode)
    {
        switch (exceptionCode)
        {
            case EXCEPTION_ACCESS_VIOLATION:
                return "Access Violation";
            case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
                return "Array Bounds Exceeded";
            case EXCEPTION_BREAKPOINT:
                return "Breakpoint";
            case EXCEPTION_COLLIDED_UNWIND:
                return "Collided Unwinded";
            case EXCEPTION_DATATYPE_MISALIGNMENT:
                return "Datatype Misalignment";
            case EXCEPTION_FLT_DENORMAL_OPERAND:
                return "Floating Point Denormal Operand";
            case EXCEPTION_FLT_DIVIDE_BY_ZERO:
                return "Floating Point Divide By Zero";
            case EXCEPTION_FLT_INEXACT_RESULT:
                return "Floating Point Inexact Result";
            case EXCEPTION_FLT_INVALID_OPERATION:
                return "Floating Point Invalid Operation";
            case EXCEPTION_FLT_OVERFLOW:
                return "Floating Point Overflow";
            case EXCEPTION_FLT_STACK_CHECK:
                return "Floating Point Stack Check";
            case EXCEPTION_FLT_UNDERFLOW:
                return "Floating Point Underflow";
            case EXCEPTION_GUARD_PAGE:
                return "Guard Page";
            case EXCEPTION_ILLEGAL_INSTRUCTION:
                return "Illegal Instruction";
            case EXCEPTION_IN_PAGE_ERROR:
                return "In Page Error";
            case EXCEPTION_INT_DIVIDE_BY_ZERO:
                return "Integer Divide By Zero";
            case EXCEPTION_INT_OVERFLOW:
                return "Integer Overflow";
            case EXCEPTION_INVALID_DISPOSITION:
                return "Invalid Disposition";
            case EXCEPTION_INVALID_HANDLE:
                return "Invalid Handle";
            case EXCEPTION_NONCONTINUABLE_EXCEPTION:
                return "Noncontinuable Exception";
            case EXCEPTION_PRIV_INSTRUCTION:
                return "Privileged Instruction";
            case EXCEPTION_SINGLE_STEP:
                return "Single Step";
            case EXCEPTION_STACK_OVERFLOW:
                return "Stack Overflow";
            // ... other exception codes ...
            default:
                return "Unknown Exception";
        }
    }

    void PrintStackTrace(EXCEPTION_POINTERS* pExceptionPointers)
    {
        HANDLE process = GetCurrentProcess();

        HANDLE thread = GetCurrentThread();

        CONTEXT context = *pExceptionPointers->ContextRecord;


        SymInitialize(process, NULL, TRUE);

        STACKFRAME64 frame = {};
        frame.AddrPC.Offset = context.Rip;
        frame.AddrPC.Mode = AddrModeFlat;
        frame.AddrStack.Offset = context.Rsp;
        frame.AddrStack.Mode = AddrModeFlat;
        frame.AddrFrame.Offset = context.Rbp;
        frame.AddrFrame.Mode = AddrModeFlat;

        while (StackWalk64(
                IMAGE_FILE_MACHINE_AMD64,
                process,
                thread,
                &frame,
                &context,
                NULL,
                SymFunctionTableAccess64,
                SymGetModuleBase64,
                NULL))
        {

            DWORD64 address = frame.AddrPC.Offset;
            DWORD displacementLine = 0;
            IMAGEHLP_LINE64 line = {};
            line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);
            char buffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR)];
            PSYMBOL_INFO symbol = (PSYMBOL_INFO) buffer;
            symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
            symbol->MaxNameLen = MAX_SYM_NAME;

            if (SymFromAddr(process, address, NULL, symbol) && SymGetLineFromAddr64(process, address, &displacementLine, &line))
            {
                std::cout << symbol->Name << " at " << line.FileName << ":" << line.LineNumber << std::endl;
            }
        }

        if (pExceptionPointers)
        {
            IMAGEHLP_LINE64 line = {};
            DWORD displacementLine = 0;

            line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);

            SymGetLineFromAddr64(process, (DWORD64) pExceptionPointers->ExceptionRecord->ExceptionAddress, &displacementLine, &line);

            std::cout << "Exception: " << ExceptionCodeToString(pExceptionPointers->ExceptionRecord->ExceptionCode) << std::endl;
            std::cout << "Exception Source: " << line.FileName << ":" << line.LineNumber << std::endl;
        }

        SymCleanup(process);
    }

    LONG WINAPI UnhandledExceptionHandler(EXCEPTION_POINTERS* pExceptionPointers)
    {
        PrintStackTrace(pExceptionPointers);
        //GenerateMiniDump(pExceptionPointers);

        std::cout << "thread id: " << std::this_thread::get_id() << std::endl;
        std::cout << "main thread id: " << mainThreadId << std::endl;
        return EXCEPTION_CONTINUE_SEARCH;
    }
}// namespace NGIN::Platform::Windows