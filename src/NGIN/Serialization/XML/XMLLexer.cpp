#include <NGIN/Serialization/XML/XMLLexer.hpp>


namespace NGIN::Serialization
{
    XMLLexer::XMLLexer(std::istream& input)
        : input(input), currentChar(0)
    {
        Advance();
    }

    XMLToken XMLLexer::NextToken()
    {
        if (lastToken.type == XMLTokenType::INVALID)
            return lastToken;
        while (currentChar != '\0')
        {
            SkipWhitespace();
            switch (currentChar)
            {
                case '<':
                    return ReadTagStart();
                case '>':
                    Advance();
                    lastToken = {XMLTokenType::TAG_END, ">"};
                    return lastToken;
                default:
                    switch (lastToken.type)
                    {
                        case XMLTokenType::TAG_START:
                            return ReadTagName();
                        case XMLTokenType::TAG_CLOSE:
                            return ReadTagName();
                        case XMLTokenType::TAG_NAME:
                            return ReadAttributeName();
                        case XMLTokenType::TAG_END:
                            return ReadContent();
                        case XMLTokenType::ATTRIBUTE_NAME:
                            return ReadAttribute();
                        case XMLTokenType::ATTRIBUTE_START_QUOTE:
                            return ReadAttributeQuote();
                        case XMLTokenType::ATTRIBUTE_END_QUOTE:
                            ReadAttributeName();
                        case XMLTokenType::ATTRIBUTE_VALUE:
                            return ReadAttributeName();
                        // case XMLTokenType::PROCESSING_INSTRUCTION_START:
                        //return ReadProcessingInstruction();
                        default:
                            return {XMLTokenType::INVALID, "NOT RECOGNIZED"};
                    }
            }
        }
        return {XMLTokenType::END_OF_FILE};

    }


    XMLToken XMLLexer::ReadTagStart()
    {
        Advance();
        switch (currentChar)
        {
            case '/':
                Advance();
                lastToken = {XMLTokenType::TAG_CLOSE, "</"};
                return lastToken;
            case '?':
                Advance();
                lastToken = {XMLTokenType::PROCESSING_INSTRUCTION_START, "<?"};
                return lastToken;
            case '!':
                if (Peek(2) == "--")
                {
                    SkipComment();
                    return NextToken();
                }
                if (Peek(7) == "[CDATA[")
                {
                    Advance(8);
                    return ReadCDATA();
                }
                Advance();

                return {XMLTokenType::INVALID, "NOT RECOGNIZED"};
            default:
                lastToken = {XMLTokenType::TAG_START, "<"};
                return lastToken;
        }

    }

    XMLToken XMLLexer::ReadTagName()
    {
        String tagName;

        if (IsNameStartChar(currentChar))
            tagName.push_back(currentChar);
        else
            return {XMLTokenType::INVALID, "Invalid tag name"};
        Advance();
        while (IsNameChar(currentChar))
        {
            tagName.push_back(currentChar);
            Advance();
        }

        lastToken = {XMLTokenType::TAG_NAME, std::move(tagName)};
        return lastToken;
    }

    XMLToken XMLLexer::ReadAttributeName()
    {
        String attrName;
        SkipWhitespace();

        if (currentChar == '/')
        {
            Advance();
            if (currentChar == '>')
            {
                Advance();
                lastToken = {XMLTokenType::TAG_CLOSE, "/>"};
                return lastToken;
            }
            return {XMLTokenType::INVALID, "Unrecognized character '/'"};
        }

        if (currentChar == '>')
        {
            Advance();
            lastToken = {XMLTokenType::TAG_END};
            return lastToken;
        }

        while (IsNameChar(currentChar))
        {
            attrName.push_back(currentChar);
            Advance();
        }

        if (attrName.empty())
            return {XMLTokenType::INVALID, "Missing attribute name"};

        lastToken = {XMLTokenType::ATTRIBUTE_NAME, std::move(attrName)};
        return lastToken;
    }

    XMLToken XMLLexer::ReadAttribute()
    {
        if (currentChar == '=')
        {
            Advance();
            return {XMLTokenType::ATTRIBUTE_EQUALS, "="};
        }

        if (currentChar == '"' || currentChar == '\'')
        {
            lastToken = {XMLTokenType::ATTRIBUTE_START_QUOTE, String(currentChar)};
            Advance();
            return lastToken;
        }

        if (currentChar == '>')
        {
            Advance();
            lastToken = {XMLTokenType::TAG_END};
            return lastToken;
        }
        ///TODO: don't know if this is correct
        if (currentChar == '/')
        {
            Advance();
            if (currentChar == '>')
            {
                Advance();
                lastToken = {XMLTokenType::TAG_CLOSE, "/>"};
                return lastToken;
            }
        }
        return {XMLTokenType::INVALID, "Unable to read attribute value"};
    }

    XMLToken XMLLexer::ReadAttributeQuote()
    {
        if (currentChar == lastToken.value.back())
        {
            Advance();
            lastToken = {XMLTokenType::ATTRIBUTE_END_QUOTE, lastToken.value};
            return lastToken;
        }

        if (currentChar == '>')
            return {XMLTokenType::INVALID, "Invalid char '>' in attribute value"};

        if (currentChar == '&')
            return ReadEntity();


        String buffer;

        while (currentChar != lastToken.value.back() && currentChar != '<' && currentChar != '/')
        {
            if (IsWhitespace(currentChar))
            {
                SkipWhitespace();
                currentChar = '\x20';
            }
            buffer.push_back(currentChar);
            Advance();
        }

        return {XMLTokenType::ATTRIBUTE_VALUE, buffer};
    }

    XMLToken XMLLexer::ReadCDATA()
    {
        String cdata;
        while (Peek(3) != "]]>")
        {
            if (IsWhitespace(currentChar))
            {
                SkipWhitespace();
                cdata.push_back('\x20');
            } else
            {
                cdata.push_back(currentChar);
                Advance();
            }
        }
        cdata.push_back(currentChar);
        Advance(4);
        return {XMLTokenType::CDATA_CONTENT, cdata};
    }

    XMLToken XMLLexer::ReadCharData()
    {
        String content = "";
        while (currentChar != '<' && currentChar != '&' && currentChar != '\0')
        {
            if (currentChar == ']')
            {
                if (Peek(2) == "]>")
                    return {XMLTokenType::INVALID, "Invalid CDATA end sequence"};
            }
            content.push_back(currentChar);
            Advance();
        }
        return {XMLTokenType::CDATA_CONTENT, std::move(content)};
    }

    XMLToken XMLLexer::ReadContent()
    {
        if (currentChar == '<')
            return ReadTagStart();
        if (currentChar == '&')
            return ReadEntity();
        return ReadCharData();
    }

    void XMLLexer::Advance(Size count)
    {
        char test = '\n';
        while (count-- > 0)
        {
            input.get(currentChar);
            if (input.eof())
                currentChar = '\0';
        }
    }

    XMLToken XMLLexer::ReadEntity()
    {
        Advance();
        String entityCode;

        if (!IsNameStartChar(currentChar))
            return {XMLTokenType::INVALID, "Invalid entity reference"};
        entityCode.push_back(currentChar);
        Advance();
        while (IsNameChar(currentChar))
        {
            entityCode.push_back(currentChar);
            Advance();
        }
        if (currentChar != ';')
            return {XMLTokenType::INVALID, "Invalid entity reference"};
        Advance();
        return {XMLTokenType::ENTITY_REFERENCE, std::move(entityCode)};

    }


    inline bool XMLLexer::IsNameStartChar(char c)
    {
        return (c == ':' || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_');
    }

    inline bool XMLLexer::IsNameChar(char c)
    {
        return IsNameStartChar(c) || (c >= '0' && c <= '9') || c == '-' || c == '.';
    }

    inline bool XMLLexer::IsWhitespace(char c)
    {
        return c == '\x20' || c == '\x09' || c == '\x0D' || c == '\x0A';
    }

    inline void XMLLexer::SkipWhitespace()
    {
        while (IsWhitespace(currentChar))
            Advance();
    }

    //TODO: -- should not be allowed in comments
    void XMLLexer::SkipComment()
    {
        while (Peek(3) != "-->")
            Advance(4);
    }

    String XMLLexer::Peek(const Size count) const
    {
        const std::istream::pos_type pos = input.tellg();

        String buffer;
        char c;
        for (Size i = 0; i < count; ++i)
        {
            if (input.eof())
                break;
            input.get(c);
            buffer.push_back(c);
        }

        input.seekg(pos);
        return std::move(buffer);
    }
}