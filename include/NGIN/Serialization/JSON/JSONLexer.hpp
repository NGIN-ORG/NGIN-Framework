#pragma once
#include <NGIN/Common/Defines.hpp>
#include <NGIN/Types/Primitives.hpp>
#include <NGIN/Types/String.hpp>
#include <istream>
#include <sstream>

namespace NGIN::Serialization
{
    NGIN_API enum class JSONTokenType : UInt8
    {
        INVALID,
        STRING,
        NUMBER,
        TRUE,
        FALSE,
        NULL_TYPE,
        OBJECT_START,
        OBJECT_END,
        ARRAY_START,
        ARRAY_END,
        COMMA,
        COLON,
        END_OF_FILE
    };

    NGIN_API struct JSONToken
    {
        JSONTokenType type;
        String value;
    };

    class JSONLexer
    {
    public:
        NGIN_API explicit JSONLexer(std::istream& input);
        /// @brief Reads the next token from the input stream
        NGIN_API JSONToken NextToken();
        /// @brief Reads a string token from the input stream
        NGIN_API JSONToken ReadString();
        /// @brief Reads a true token from the input stream
        NGIN_API JSONToken ReadTrue();
        /// @brief Reads a false token from the input stream
        NGIN_API JSONToken ReadFalse();
        /// @brief Reads a null token from the input stream
        NGIN_API JSONToken ReadNull();
        /// @brief Reads a number token from the input stream
        NGIN_API JSONToken ReadNumber();

    private:
        /// @brief Advances the current character in the input stream
        void Advance();
        /// @brief Advances the current character in the input stream until a non-whitespace character is found
        void SkipWhitespace();

        std::istream& input;
        char currentChar;
    };
}
