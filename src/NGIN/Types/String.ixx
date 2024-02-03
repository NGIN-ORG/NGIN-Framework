module;

#include <string>
#include <string_view>

export module NGIN.Types:String;

export namespace NGIN
{
    using String = std::string;
    using StringView = std::string_view;
}// namespace NGIN