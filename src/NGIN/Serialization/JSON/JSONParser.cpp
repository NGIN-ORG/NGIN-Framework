#include <NGIN/Serialization/JSON/JSONParser.hpp>

namespace NGIN::Serialization
{
    JSONValue& JSONObject::operator[](std::string_view key)
    {
        // Search for the key and return a reference to its value
        for (auto& [k, v]: map)
        {
            if (k == key)
                return v;
        }
        // If the key is not found, add a new element and return a reference to it
        map.emplace_back(key, JSONValue{});
        return map.back().second;
    }

    const JSONValue& JSONObject::operator[](const std::string_view key) const
    {
        // Search for the key and return a const reference to its value
        for (const auto& [k, v]: map)
        {
            if (k == key)
                return v;
        }
        throw std::runtime_error("Key not found");
    }

    std::optional<JSONValue> JSONObject::Get(const String& key) const
    {
        // Search for the key and return an optional value
        for (const auto& [k, v]: map)
        {
            if (k == key)
                return v;
        }
        return std::nullopt;
    }

    void JSONObject::Set(const String& key, JSONValue&& value)
    {
        for (auto& [k, v]: map)
        {
            if (k == key)
            {
                v = std::move(value);
                return;
            }
        }
        map.emplace_back(key, std::move(value));
    }

    void JSONObject::Set(const String& key, const JSONValue& value)
    {
        for (auto& [k, v]: map)
        {
            if (k == key)
            {
                v = value;
                return;
            }
        }
        map.emplace_back(key, value);
    }

    JSONValue::JSONValue(JSONString&& val)
        : value{std::move(val)},
          type{Type::STRING} {}

    JSONValue::JSONValue(JSONObject&& val)
        : value{std::move(val)},
          type{Type::OBJECT} {}

    JSONValue::JSONValue(JSONArray&& val)
        : value{std::move(val)},
          type{Type::ARRAY} {}

    JSONValue::JSONValue(JSONNumber val)
        : value{val},
          type{Type::NUMBER} {}

    JSONValue::JSONValue(JSONBoolean val)
        : value{val},
          type{Type::BOOLEAN} {}

    JSONValue::JSONValue(JSONNull val)
        : value{val},
          type{Type::NULL_TYPE} {}

    JSONValue JSONParser::Parse(const String& json)
    {
        std::istringstream stream(json.c_str());
        return Parse(stream);
    }

    JSONValue JSONParser::Parse(std::istream& input)
    {
        JSONLexer lexer(input);
        const auto [type, value] = lexer.NextToken();
        if (type == JSONTokenType::OBJECT_START)
            return JSONValue(ParseObject(lexer));
        if (type == JSONTokenType::ARRAY_START)
            return JSONValue(ParseArray(lexer));
        throw std::runtime_error("Invalid JSON format");
    }

    JSONValue JSONParser::ParseValue(JSONLexer& lexer, JSONToken& token)
    {
        switch (token.type)
        {
            case JSONTokenType::STRING:
                return JSONValue{ParseString(token)};
            case JSONTokenType::NUMBER:
                return JSONValue{ParseNumber(token)};
            case JSONTokenType::TRUE:
            case JSONTokenType::FALSE:
                return JSONValue{ParseBoolean(token)};
            case JSONTokenType::NULL_TYPE:
                return JSONValue{ParseNull(token)};
            case JSONTokenType::OBJECT_START:
                return JSONValue{ParseObject(lexer)};
            case JSONTokenType::ARRAY_START:
                return JSONValue{ParseArray(lexer)};
            default:
                throw std::runtime_error("Invalid JSON value");
        }
    }

    JSONObject JSONParser::ParseObject(JSONLexer& lexer)
    {
        JSONObject object;
        JSONToken token = lexer.NextToken();
        while (token.type != JSONTokenType::OBJECT_END)
        {
            //Find key
            if (token.type != JSONTokenType::STRING)
                throw std::runtime_error("Expected string for key in object");
            String key = std::move(token.value);

            //look for colon
            token = lexer.NextToken();
            if (token.type != JSONTokenType::COLON)
                throw std::runtime_error("Expected colon after key in object");

            //Parse value
            token = lexer.NextToken();
            object.Set(key, ParseValue(lexer, token));

            //Check for comma
            token = lexer.NextToken();// Comma or object end
            if (token.type == JSONTokenType::COMMA)
                token = lexer.NextToken();// Next key or object end
        }
        return object;
    }

    JSONArray JSONParser::ParseArray(JSONLexer& lexer)
    {
        JSONArray arr;
        JSONToken token = lexer.NextToken();

        while (token.type != JSONTokenType::ARRAY_END)
        {
            arr.values.push_back(ParseValue(lexer, token));
            token = lexer.NextToken();// Comma or array end
            if (token.type == JSONTokenType::COMMA)
                token = lexer.NextToken();// Next value or array end
        }

        return arr;
    }

    JSONString JSONParser::ParseString(JSONToken& token)
    {
        auto& [type, value] = token;
        if (type != JSONTokenType::STRING)
        {
            throw std::runtime_error("Expected string token");
        }
        return value;
    }

    JSONNumber JSONParser::ParseNumber(JSONToken& token)
    {
        auto& [type, value] = token;
        if (type != JSONTokenType::NUMBER)
        {
            throw std::runtime_error("Expected number token");
        }
        try
        {
            return std::stod(value.c_str());
        } catch (const std::invalid_argument& ia)
        {
            throw std::runtime_error("Invalid number format");
        } catch (const std::out_of_range& orr)
        {
            throw std::runtime_error("Number out of range");
        }
    }

    JSONBoolean JSONParser::ParseBoolean(JSONToken& token)
    {

        auto& [type, value] = token;
        if (type == JSONTokenType::TRUE)
        {
            return true;
        } else if (type == JSONTokenType::FALSE)
        {
            return false;
        } else
        {
            throw std::runtime_error("Expected true or false token");
        }


    }

    JSONNull JSONParser::ParseNull(JSONToken& token)
    {
        auto& [type, value] = token;
        if (type != JSONTokenType::NULL_TYPE)
        {
            throw std::runtime_error("Expected null token");
        }
        return nullptr;// std::nullptr_t is simply null
    }

}