#pragma once
#ifdef NGIN_BUILD_SHARED
    #define NGIN_API __declspec(dllexport)
#elif NGIN_SHARED
    #define NGIN_API __declspec(dllimport)
#else
    #define NGIN_API
#endif