#include <NGIN/Serialization/JSON/JSONLexer.hpp>

namespace NGIN::Serialization
{
    JSONLexer::JSONLexer(std::istream& input)
        : input(input), currentChar(0)
    {
        Advance();
    }

    JSONToken JSONLexer::NextToken()
    {
        while (currentChar != '\0')
        {
            SkipWhitespace();
            switch (currentChar)
            {
                case '{': {
                    Advance();
                    return {JSONTokenType::OBJECT_START, "{"};
                }
                case '}': {
                    Advance();
                    return {JSONTokenType::OBJECT_END, "}"};
                }
                case '[': {
                    Advance();
                    return {JSONTokenType::ARRAY_START, "["};
                }
                case ']': {
                    Advance();
                    return {JSONTokenType::ARRAY_END, "]"};
                }
                case ',': {
                    Advance();
                    return {JSONTokenType::COMMA, ","};
                }
                case ':': {
                    Advance();
                    return {JSONTokenType::COLON, ":"};
                }
                case 't':
                    return ReadTrue();
                case 'f':
                    return ReadFalse();
                case 'n':
                    return ReadNull();
                case '\"':
                    return ReadString();
                default: {
                    if (isdigit(currentChar) || currentChar == '-')
                        return ReadNumber();
                    return {JSONTokenType::INVALID, ""};
                }
            }
        }
        return {JSONTokenType::END_OF_FILE, ""};
    }

    JSONToken JSONLexer::ReadString()
    {
        String buffer{};
        Advance();// skip the initial double quote
        while (currentChar != '\"' && currentChar != '\0')
        {
            if (currentChar == '\\')
            [[unlikely]]
            {
                // Handle escape sequences
                Advance();// move past the backslash
                switch (currentChar)
                {
                    case '\"':
                        buffer += '\"';
                        break;
                    case '\\':
                        buffer += '\\';
                        break;
                    case '/':
                        buffer += '/';
                        break;
                    case 'b':
                        buffer += '\b';
                        break;
                    case 'f':
                        buffer += '\f';
                        break;
                    case 'n':
                        buffer += '\n';
                        break;
                    case 'r':
                        buffer += '\r';
                        break;
                    case 't':
                        buffer += '\t';
                        break;
                    default:
                        return {JSONTokenType::INVALID, ""};// Handle invalid escape sequences
                }
            } else
            {
                buffer += currentChar;
            }
            Advance();
        }
        Advance();// skip the closing double quote
        return {JSONTokenType::STRING, buffer};
    }

    JSONToken JSONLexer::ReadTrue()
    {
        static constexpr std::string_view text = "true";
        for (int i = 1; i < 4; ++i)
        {
            Advance();
            if (currentChar != text[i])
                return {JSONTokenType::INVALID, ""};// Not a true literal
        }
        Advance();// move past the last character of "true"
        return {JSONTokenType::TRUE, "true"};
    }


    JSONToken JSONLexer::ReadFalse()
    {
        static constexpr std::string_view text = "false";
        for (int i = 1; i < 5; ++i)
        {
            Advance();
            if (currentChar != text[i])
                return {JSONTokenType::INVALID, ""};// Not a false literal
        }
        Advance();// move past the last character of "false"
        return {JSONTokenType::FALSE, "false"};
    }


    JSONToken JSONLexer::ReadNull()
    {
        static constexpr std::string_view text = "null";
        for (int i = 1; i < 4; ++i)
        {
            Advance();
            if (currentChar != text[i])
                return {JSONTokenType::INVALID, ""};// Not a null literal
        }
        Advance();// move past the last character of "null"
        return {JSONTokenType::NULL_TYPE, "null"};
    }


    JSONToken JSONLexer::ReadNumber()
    {
        String buffer{};
        if (currentChar == '-')
        {
            // Handle negative numbers
            buffer += '-';
            Advance();
        }
        while (isdigit(currentChar) || currentChar == '.')
        {
            buffer += currentChar;
            Advance();
        }
        if (currentChar == 'e' || currentChar == 'E')
        {
            // Handle exponent part
            buffer += currentChar;
            Advance();
            if (currentChar == '+' || currentChar == '-')
            {
                buffer += currentChar;
                Advance();
            }
            while (isdigit(currentChar))
            {
                buffer += currentChar;
                Advance();
            }
        }
        return {JSONTokenType::NUMBER, buffer};
    }


    void JSONLexer::Advance()
    {
        input.get(currentChar);
        if (input.eof())
            currentChar = '\0';
    }

    void JSONLexer::SkipWhitespace()
    {
        while (isspace(currentChar) && !input.eof())
            Advance();
    }
}