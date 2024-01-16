#include <iostream>

///@def NGIN_API
///@brief NGIN_API is a macro used for defining the visibility of functions and classes in the NGIN library.
///
///When building the NGIN library, this macro is defined as "__declspec(dllexport)" to export symbols from the library.
///When using the NGIN library, this macro is defined as "__declspec(dllimport)" to import symbols from the library.
#ifndef NGIN_BUILD_STATIC
#if defined(NGIN_PLATFORM_WINDOWS)
#ifdef NGIN_BUILD_SHARED
#define NGIN_API __declspec(dllexport)
#else
#define NGIN_API __declspec(dllimport)
#endif
#else
#ifdef NGIN_BUILD_SHARED
#define NGIN_API __attribute__((visibility("default")))
#else
#define NGIN_API
#endif
#endif
#else
#define NGIN_API
#endif


///@def NGIN_ERROR
///@brief NGIN_ERROR is a macro used for crashing the program with an error message.
#define NGIN_ERROR(message)                  \
    do {                                     \
        std::cout << (message) << std::endl; \
        std::abort();                        \
    } while (false)

///@def NGIN_ASSERT
///@brief NGIN_ASSERT is a macro used for crashing the program if a condition is not met.
#define NGIN_ASSERT(condition, message)          \
    do {                                         \
        if (!(condition)) [[unlikely]]           \
        {                                        \
            std::cout << (message) << std::endl; \
            std::abort();                        \
        }                                        \
    } while (false)
