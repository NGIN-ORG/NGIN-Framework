#pragma once
#if defined(NGIN_PLATFORM_WINDOWS)
#if defined(NGIN_BUILD_SHARED)
#define NGIN_API __declspec(dllexport)
#elif defined(NGIN_SHARED)
#define NGIN_API __declspec(dllimport)
#else
#define NGIN_API
#endif
#else
#if defined(NGIN_BUILD_SHARED)
#define NGIN_API __attribute__((visibility("default")))
#else
#define NGIN_API
#endif
#endif