module;

#include <type_traits>

export module NGIN.Meta:TypeInfo;

export import NGIN.Types;

export namespace NGIN::Meta
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
    /// std::cout << TypeInfo<Foo::Bar>::Class();     // Outputs: Bar
    /// std::cout << TypeInfo<Foo::Bar>::Namespace(); // Outputs: Foo
    /// std::cout << TypeInfo<Foo::Bar>::Full();      // Outputs: Foo::Bar
    /// @endcode
    template<typename T>
    struct TypeInfo
    {
        static_assert(!std::is_enum_v<T>, "Enum types are not supported");

        /// @brief Gets the compiler-specific signature for the current type.
        ///
        /// Depending on the compiler being used, this function will retrieve
        /// the appropriate signature string.
        ///
        /// @return A `StringView` containing the compiler-specific signature for the type.
        constexpr static StringView Signature()
        {
#if defined(__clang__) || defined(__GNUC__)
            return __PRETTY_FUNCTION__;
#elif defined(_MSC_VER)
            return __FUNCSIG__;
#else
#error "Unsupported compiler"
#endif
        }

        /// @brief Computes and returns the name of the type.
        ///
        /// The function computes the name of the type based on the compiler
        /// signature and performs string manipulation to retrieve a clean
        /// version of the type name.
        ///
        /// @return A `StringView` containing the name of the type.
        constexpr static StringView Full()
        {
            if constexpr (std::is_same_v<T, void*>)
                return "void*";
            if constexpr (std::is_same_v<T, void>)
                return "void";

            const UInt64 prefix_len = TypeInfo<void>::Signature().find("void");
            const UInt64 multiple = TypeInfo<void>::Signature().size() - TypeInfo<int>::Signature().size();
            const UInt64 dummy_len = TypeInfo<void>::Signature().size() - 4 * multiple;
            const UInt64 target_len = (Signature().size() - dummy_len) / multiple;
            StringView rv = Signature().substr(prefix_len, target_len);
            if (rv.rfind(' ') == rv.npos)
                return rv;
            return rv.substr(rv.rfind(' ') + 1);
        }

        /// @brief Computes and returns the class name of the type.
        ///
        /// The function computes the class name of the type based on the type signature
        /// and performs string manipulation to retrieve a clean version of the class name.
        ///
        /// @return A `StringView` containing the class name.
        constexpr static StringView Name()
        {
            const StringView fullType = Full();
            const UInt64 lastColons = fullType.rfind("::");
            if (lastColons == StringView::npos)
                return fullType;
            return fullType.substr(lastColons + 2);
        }

        /// @brief Computes and returns the namespace of the type.
        ///
        /// The function computes the namespace of the type based on the type signature
        /// and performs string manipulation to retrieve the namespace.
        ///
        /// @return A `StringView` containing the namespace.
        constexpr static StringView Namespace()
        {
            const StringView fullType = Full();
            const UInt64 lastColons = fullType.rfind("::");
            if (lastColons == StringView::npos)
                return {};
            return fullType.substr(0, lastColons);
        }
    };
}