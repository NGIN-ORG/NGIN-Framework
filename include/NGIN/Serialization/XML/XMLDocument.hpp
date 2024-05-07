#pragma once

#include <NGIN/Common/Defines.hpp>
#include <NGIN/Types/Primitives.hpp>
#include <NGIN/Types/String.hpp>

#include <variant>

namespace NGIN::Serialization
{
    class XMLError;

    class XMLAttribute
    {
        String name;
        String value;
    };

    class XMLElement
    {
        String name;
        Vector<XMLAttribute> attributes;
        std::variant<Vector<XMLElement>, String> contentVariant;
        // Vector<XMLElement> children;
        //String content;
    };

    class XMLDocument
    {
        XMLElement root;
    };
}
