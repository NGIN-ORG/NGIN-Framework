#pragma once
#include <NGIN/Common/Defines.hpp>
#include <NGIN/Types/String.hpp>
#include <string_view>
#include <type_traits>

namespace NGIN::Meta
{
    /// @brief Retrieves the type name as a string.
    ///
    /// This struct provides functionality to get the type name
    /// of a given type as a compile-time `StringView`.
    /// @tparam T The type whose name is to be retrieved.
    ///
    /// @code
    /// namespace Foo
    /// {
    ///     struct Bar{};
    /// }
    /// std::cout << TypeInfo<Foo::Bar>::Name();      // Outputs: Bar
    /// std::cout << TypeInfo<Foo::Bar>::Namespace(); // Outputs: Foo
    /// std::cout << TypeInfo<Foo::Bar>::Full();      // Outputs: Foo::Bar
    /// @endcode
    template <typename T>
    struct TypeInfo
    {
        static_assert(!std::is_enum_v<T>, "Enum types are not supported");

        /// @brief Gets the compiler-specific signature for the current type.
        ///
        /// Depending on the compiler being used, this function will retrieve
        /// the appropriate signature string.
        ///
        /// @return A `StringView` containing the compiler-specific signature for the type.
        constexpr static std::string_view RawSignature()
        {
#if defined(__clang__) || defined(__GNUC__)
            return __PRETTY_FUNCTION__;
#elif defined(_MSC_VER)
            return __FUNCSIG__;
#else
#error "Unsupported compiler"
#endif
        }

        /// @brief Computes and returns the namespace::name of the type.
        ///
        /// The function computes the name of the type based on the compiler
        /// signature and performs string manipulation to retrieve a clean
        /// version of the type name.
        ///
        /// @return A `std::string_view` containing the name of the type.
        constexpr static std::string_view Full()
        {
            if constexpr (std::is_same_v<T, void*>)
                return "void*";
            if constexpr (std::is_same_v<T, void>)
                return "void";
            UInt64 prefix_len = TypeInfo<void>::RawSignature().find("void");
            UInt64 multiple = TypeInfo<void>::RawSignature().size() - TypeInfo<int>::RawSignature().size();
            UInt64 dummy_len = TypeInfo<void>::RawSignature().size() - 4 * multiple;
            UInt64 target_len = (RawSignature().size() - dummy_len) / multiple;
            std::string_view rv = RawSignature().substr(prefix_len, target_len);
            if (rv.find(' ') != rv.npos)
                return rv.substr(rv.find(' ') + 1);
            return rv;
        }

        /// @brief Computes and returns the name of the type.
        ///
        /// The function computes the class name of the type based on the type signature
        /// and performs string manipulation to retrieve a clean version of the class name.
        ///
        /// @return A `std::string_view` containing the class name.
        constexpr static std::string_view Name()
        {
            constexpr std::string_view fullType = Full();
            constexpr UInt64 lastColons = fullType.rfind("::");
            if (lastColons == std::string_view::npos)
                return fullType;
            return fullType.substr(lastColons + 2);
        }

        /// @brief Computes and returns the namespace of the type.
        ///
        /// The function computes the namespace of the type based on the type signature
        /// and performs string manipulation to retrieve the namespace.
        ///
        /// @return A `std::string_view` containing the namespace.
        constexpr static std::string_view Namespace()
        {
            constexpr std::string_view fullType = Full();
            constexpr UInt64 lastColons = fullType.rfind("::");
            if constexpr (lastColons == std::string_view::npos)
                return {};
            return fullType.substr(0, lastColons);
        }
    };
} // namespace NGIN::Meta
