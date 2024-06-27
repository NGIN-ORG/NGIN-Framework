#pragma once
#include <NGIN/Common/Defines.hpp>
#include <NGIN/Types/Primitives.hpp>
#include <SIMDString.h>
#include <cstdlib>
#include <string>

namespace NGIN
{
    /// @brief A type alias for the STL complient SIMDString.
    using String = SIMDString<Char, 48>;
    /// @brief A type alias for a string with 16-bit characters.
    using String16 = std::basic_string<Char16>;
    /// @brief A type alias for a string with 32-bit characters.
    using String32 = std::basic_string<Char32>;
    /// @brief A type alias for a string with the wide character type.
    using WString = std::basic_string<WChar>;

    class Stringifiable
    {
    public:
        virtual ~Stringifiable()        = default;
        virtual String ToString() const = 0;
        virtual WString ToWString() const
        {
            String str = ToString();
            if (str.empty())
                return std::wstring();

            size_t chars_needed = std::mbstowcs(nullptr, str.c_str(), 0);
            if (chars_needed == (size_t) -1)
            {
                throw std::runtime_error("Error converting string to wstring");
            }

            std::wstring wstr(chars_needed, 0);
            std::mbstowcs(&wstr[0], str.c_str(), chars_needed);

            return wstr;
        }
    };

    // Concept to check if std::to_string is applicable
    template<typename T>
    concept ToStringable = requires(T x) {
        {
            std::to_string(x)
        } -> std::convertible_to<std::string>;
    };

    template<typename T>
    concept ToWStringable = requires(T x) {
        {
            std::to_wstring(x)
        } -> std::convertible_to<std::wstring>;
    };

    // Concept to check if the type is derived from Stringifiable
    template<typename T>
    concept IsStringifiable = std::is_base_of_v<Stringifiable, std::decay_t<T>>;


    template<typename T>
    String ToString(T&& value)
    {
        if constexpr (IsStringifiable<T>)
        {
            return std::forward<T>(value).ToString();
        }
        else if constexpr (ToStringable<T>)
        {
            return String(std::to_string(std::forward<T>(value)));
        }
        else
        {
            static_assert(false, "No suitable ToString implementation for this type");
            return "";
        }
    }

    // Specialization for std::string to directly return the string
    template<>
    inline String ToString<std::string>(std::string&& value)
    {
        return String(std::forward<std::string>(value));
    }


    template<typename T>
    WString ToWString(T&& value)
    {
        if constexpr (IsStringifiable<T>)
        {
            return std::forward<T>(value).ToWString();
        }
        else if constexpr (ToWStringable<T>)
        {
            return String(std::to_wstring(std::forward<T>(value)));
        }
        else
        {
            static_assert(false, "No suitable ToString implementation for this type");
            return "";
        }
    }

    // Specialization for std::string to directly return the string
    template<>
    inline WString ToWString<std::wstring>(std::wstring&& value)
    {
        return WString(std::forward<std::wstring>(value));
    }


}// namespace NGIN
