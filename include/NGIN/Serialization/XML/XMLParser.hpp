#pragma once

#include <NGIN/Common/Defines.hpp>
#include <NGIN/Types/Primitives.hpp>
#include <NGIN/Types/String.hpp>
#include <NGIN/Serialization/XML/XMLLexer.hpp>

namespace NGIN::Serialization
{
    class XMLParser
    {
    public:
        NGIN_API void Parse(const String& input);
        NGIN_API void Parse(std::istream& input);

    private:
        XMLLexer lexer;
    };
}
