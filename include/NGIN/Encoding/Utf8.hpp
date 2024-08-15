//
// Created by Maximiliam Berggren on 12/08/2024.
//

#pragma once
#include <NGIN/Common/Defines.hpp>
#include <NGIN/Types/String.hpp>
#include <string_view>

namespace NGIN::Unicode
{

    NGIN_API static NGIN::String16 FromUtf8ToUtf16(const std::string_view utf8);
    NGIN_API static NGIN::String FromUtf16ToUtf8(const std::string_view utf16);
    NGIN_API static NGIN::String32 FromUtf8ToUtf32(const std::string_view utf8);
    NGIN_API static NGIN::String FromUtf32ToUtf8(const std::string_view utf32);

}// namespace NGIN::Unicode
