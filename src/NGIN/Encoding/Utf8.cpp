//
// Created by Maximiliam Berggren on 12/08/2024.
//

#include <NGIN/Encoding/Utf8.hpp>

namespace NGIN::Unicode
{
    NGIN::String FromUtf8ToUtf16(const std::string_view utf8)
    {
        std::u16string utf16_str;
        size_t i = 0;
        while (i < utf8.size())
        {
            uint32_t codepoint = 0;
            unsigned char byte = utf8[i];

            if (byte <= 0x7F)
            {
                codepoint = byte;
                i += 1;
            }
            else if (byte <= 0xDF)
            {
                codepoint = (byte & 0x1F) << 6;
                codepoint |= (utf8[i + 1] & 0x3F);
                i += 2;
            }
            else if (byte <= 0xEF)
            {
                codepoint = (byte & 0x0F) << 12;
                codepoint |= (utf8[i + 1] & 0x3F) << 6;
                codepoint |= (utf8[i + 2] & 0x3F);
                i += 3;
            }
            else if (byte <= 0xF7)
            {
                codepoint = (byte & 0x07) << 18;
                codepoint |= (utf8[i + 1] & 0x3F) << 12;
                codepoint |= (utf8[i + 2] & 0x3F) << 6;
                codepoint |= (utf8[i + 3] & 0x3F);
                i += 4;
            }

            if (codepoint <= 0xFFFF)
            {
                utf16_str.push_back(static_cast<char16_t>(codepoint));
            }
            else
            {
                codepoint -= 0x10000;
                utf16_str.push_back(static_cast<char16_t>(0xD800 | (codepoint >> 10)));
                utf16_str.push_back(static_cast<char16_t>(0xDC00 | (codepoint & 0x3FF)));
            }
        }
        return NGIN::String(reinterpret_cast<const char*>(utf16_str.data()), utf16_str.size() * sizeof(char16_t));
    }

    NGIN::String FromUtf16ToUtf8(const std::string_view utf16)
    {
        std::string utf8_str;
        const char16_t* data = reinterpret_cast<const char16_t*>(utf16.data());
        size_t len           = utf16.size() / sizeof(char16_t);

        for (size_t i = 0; i < len; ++i)
        {
            uint32_t codepoint = data[i];

            if (codepoint >= 0xD800 && codepoint <= 0xDBFF)
            {
                // Handle surrogate pairs
                uint32_t high_surrogate = codepoint;
                uint32_t low_surrogate  = data[++i];
                codepoint               = ((high_surrogate - 0xD800) << 10) + (low_surrogate - 0xDC00) + 0x10000;
            }

            if (codepoint <= 0x7F)
            {
                utf8_str.push_back(static_cast<char>(codepoint));
            }
            else if (codepoint <= 0x7FF)
            {
                utf8_str.push_back(static_cast<char>((codepoint >> 6) | 0xC0));
                utf8_str.push_back(static_cast<char>((codepoint & 0x3F) | 0x80));
            }
            else if (codepoint <= 0xFFFF)
            {
                utf8_str.push_back(static_cast<char>((codepoint >> 12) | 0xE0));
                utf8_str.push_back(static_cast<char>(((codepoint >> 6) & 0x3F) | 0x80));
                utf8_str.push_back(static_cast<char>((codepoint & 0x3F) | 0x80));
            }
            else
            {
                utf8_str.push_back(static_cast<char>((codepoint >> 18) | 0xF0));
                utf8_str.push_back(static_cast<char>(((codepoint >> 12) & 0x3F) | 0x80));
                utf8_str.push_back(static_cast<char>(((codepoint >> 6) & 0x3F) | 0x80));
                utf8_str.push_back(static_cast<char>((codepoint & 0x3F) | 0x80));
            }
        }
        return NGIN::String(utf8_str);
    }

    NGIN::String FromUtf8ToUtf32(const std::string_view utf8)
    {
        std::u32string utf32_str;
        size_t i = 0;
        while (i < utf8.size())
        {
            uint32_t codepoint = 0;
            unsigned char byte = utf8[i];

            if (byte <= 0x7F)
            {
                codepoint = byte;
                i += 1;
            }
            else if (byte <= 0xDF)
            {
                codepoint = (byte & 0x1F) << 6;
                codepoint |= (utf8[i + 1] & 0x3F);
                i += 2;
            }
            else if (byte <= 0xEF)
            {
                codepoint = (byte & 0x0F) << 12;
                codepoint |= (utf8[i + 1] & 0x3F) << 6;
                codepoint |= (utf8[i + 2] & 0x3F);
                i += 3;
            }
            else if (byte <= 0xF7)
            {
                codepoint = (byte & 0x07) << 18;
                codepoint |= (utf8[i + 1] & 0x3F) << 12;
                codepoint |= (utf8[i + 2] & 0x3F) << 6;
                codepoint |= (utf8[i + 3] & 0x3F);
                i += 4;
            }

            utf32_str.push_back(static_cast<char32_t>(codepoint));
        }
        return NGIN::String(reinterpret_cast<const char*>(utf32_str.data()), utf32_str.size() * sizeof(char32_t));
    }

    NGIN::String FromUtf32ToUtf8(const std::u32string_view utf32)
    {
        std::string utf8_str;
        const char32_t* data = reinterpret_cast<const char32_t*>(utf32.data());
        size_t len           = utf32.size() / sizeof(char32_t);

        for (size_t i = 0; i < len; ++i)
        {
            uint32_t codepoint = data[i];

            if (codepoint <= 0x7F)
            {
                utf8_str.push_back(static_cast<char>(codepoint));
            }
            else if (codepoint <= 0x7FF)
            {
                utf8_str.push_back(static_cast<char>((codepoint >> 6) | 0xC0));
                utf8_str.push_back(static_cast<char>((codepoint & 0x3F) | 0x80));
            }
            else if (codepoint <= 0xFFFF)
            {
                utf8_str.push_back(static_cast<char>((codepoint >> 12) | 0xE0));
                utf8_str.push_back(static_cast<char>(((codepoint >> 6) & 0x3F) | 0x80));
                utf8_str.push_back(static_cast<char>((codepoint & 0x3F) | 0x80));
            }
            else
            {
                utf8_str.push_back(static_cast<char>((codepoint >> 18) | 0xF0));
                utf8_str.push_back(static_cast<char>(((codepoint >> 12) & 0x3F) | 0x80));
                utf8_str.push_back(static_cast<char>(((codepoint >> 6) & 0x3F) | 0x80));
                utf8_str.push_back(static_cast<char>((codepoint & 0x3F) | 0x80));
            }
        }
        return NGIN::String(utf8_str);
    }
}// namespace NGIN::Unicode
