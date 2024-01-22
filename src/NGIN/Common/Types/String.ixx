module;

#include <string>
#include <string_view>

export module NGIN.Common.Types:String;

export namespace NGIN
{
    using String = std::string;
    using StringView = std::string_view;
}// namespace NGIN