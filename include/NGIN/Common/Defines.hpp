/**
 * @brief NGIN_API is a macro used for defining the visibility of functions and classes in the NGIN library.
 *
 * When building the NGIN library, this macro is defined as "__declspec(dllexport)" to export symbols from the library.
 * When using the NGIN library, this macro is defined as "__declspec(dllimport)" to import symbols from the library.
 */
#ifndef NGIN_BUILD_STATIC
#if defined(_MSC_VER)
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

#ifdef NGIN_THROW_EXCEPTIONS

// When NGIN_THROW_EXCEPTIONS is defined, NGIN_CHECK will simply call the function.
// It is assumed that the function itself handles exceptions internally.
#define NGIN_CHECK(func) \
    func

#else

// When NGIN_THROW_EXCEPTIONS is not defined, NGIN_CHECK will evaluate the function.
// If the function returns false, it will throw a runtime_error.
#define NGIN_CHECK(func)                                                    \
    do {                                                                    \
        if (!(func)) throw std::runtime_error("NGIN_CHECK failed: " #func); \
    } while (0)

#endif
