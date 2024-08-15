#pragma once
#include <NGIN/Common/Defines.hpp>
#include <NGIN/Containers/UnorderedMap.hpp>
#include <NGIN/Types/Primitives.hpp>
#include <NGIN/Types/String.hpp>
#include <istream>
#include <sstream>

namespace NGIN::Serialization
{
    enum class XMLTokenType : UInt8
    {
        INVALID,
        END_OF_FILE,

        TAG_START,      // <
        TAG_NAME,       //TAG
        TAG_END,        // >
        TAG_CLOSE,      // </
        TAG_START_CLOSE,// />

        ENTITY_REFERENCE,// &

        ATTRIBUTE_NAME,
        ATTRIBUTE_EQUALS,     // =
        ATTRIBUTE_START_QUOTE,// "
        ATTRIBUTE_END_QUOTE,
        ATTRIBUTE_VALUE,

        CDATA_CONTENT,

        COMMENT_START,// <!--
        COMMENT_TEXT,
        COMMENT_END,// -->

        PROCESSING_INSTRUCTION_START,// <?
        PROCESSING_INSTRUCTION_TARGET,
        PROCESSING_INSTRUCTION_CONTENT,
        PROCESSING_INSTRUCTION_END,// ?>

        XML_DECLARATION_START,// <?xml
        XML_DECLARATION_ATTRIBUTE_NAME,
        XML_DECLARATION_ATTRIBUTE_EQUALS,// =
        XML_DECLARATION_ATTRIBUTE_VALUE,


        DOCTYPE_START,// <!DOCTYPE
        DOCTYPE_CONTENT,
        DOCTYPE_END,// >

        NAMESPACE_DECLARATION
    };

    struct XMLToken
    {
        XMLTokenType type;
        String value;
    };

    class XMLLexer
    {
    public:
        XMLLexer(std::istream& input);
        /// @brief Reads the next token from the input stream
        XMLToken NextToken();

        XMLToken ReadTagStart();


        void Advance(Size count = 1);

    private:
        XMLToken ReadTagName();
        XMLToken ReadAttributeName();
        XMLToken ReadAttribute();
        XMLToken ReadAttributeQuote();
        XMLToken ReadCDATA();
        XMLToken ReadContent();
        ///XML spec is stupid and CharData is not the same as CDATA
        XMLToken ReadCharData();
        XMLToken ReadProcessingInstruction();

        XMLToken ReadEntity();


        /// @brief Checks if the character is a valid name start character, according to XML 1.0 spec, 2.3
        static bool IsNameStartChar(char c);
        /// @brief Checks if the character is a valid name character, according to XML 1.0 spec, 2.3
        static bool IsNameChar(char c);
        /// @brief Checks if the character is a valid whitespace character, according to XML 1.0 spec, 2.3
        static bool IsWhitespace(char c);

        /// @brief Advances the current character in the input stream until a non-whitespace character is found
        void SkipWhitespace();
        /// @brief Advances the current character in the input stream until a comment end is found
        void SkipComment();

        String Peek(Size count = 1) const;

        UnorderedMap<String, String> entities;
        std::istream& input;
        char currentChar;
        XMLToken lastToken;
    };
}// namespace NGIN::Serialization
