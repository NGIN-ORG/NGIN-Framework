#pragma once
#include <NGIN/Serialization/JSON/JSONLexer.hpp>
#include <NGIN/Containers/UnorderedMap.hpp>
#include <NGIN/Containers/Vector.hpp>
#include <variant>
#include <type_traits>

namespace NGIN::Serialization
{
    struct JSONValue;

    using JSONString = String;

    using JSONNumber = F64;

    using JSONBoolean = bool;

    using JSONNull = std::nullptr_t;

    struct JSONObject
    {
        NGIN_API JSONValue& operator[](std::string_view key);
        NGIN_API const JSONValue& operator[](std::string_view key) const;

        NGIN_API std::optional<JSONValue> Get(const String& key) const;
        NGIN_API void Set(const String& key, JSONValue&& value);
        NGIN_API void Set(const String& key, const JSONValue& value);

        const Vector<std::pair<String, JSONValue>>& GetAll() const
        {
            return map;
        }

    private:
        Vector<std::pair<String, JSONValue>> map;
    };

    NGIN_API struct JSONArray
    {
        Vector<JSONValue> values;
    };

    NGIN_API struct JSONValue
    {
    public:
        JSONValue() = default;
        JSONValue(const JSONValue&) = default;
        JSONValue(JSONValue&&) = default;
        JSONValue& operator=(const JSONValue&) = default;
        JSONValue& operator=(JSONValue&&) = default;

        explicit JSONValue(JSONString&& val);
        explicit JSONValue(JSONObject&& val);
        explicit JSONValue(JSONArray&& val);
        explicit JSONValue(JSONNumber val);
        explicit JSONValue(JSONBoolean val);
        explicit JSONValue(JSONNull val);


        using VariantType = std::variant<JSONString, JSONObject, JSONArray, JSONNumber, JSONBoolean, JSONNull>;

        enum class Type : UInt8
        {
            STRING,
            OBJECT,
            ARRAY,
            NUMBER,
            BOOLEAN,
            NULL_TYPE,
            INVALID
        };

        template <typename T>
            requires std::is_same_v<T, JSONString> || std::is_same_v<T, JSONObject> || std::is_same_v<T, JSONArray> ||
            std::is_same_v<T, JSONNumber> || std::is_same_v<T, JSONBoolean> || std::is_same_v<T, JSONNull>
        T& Get()
        {
            if (type == Type::INVALID)
                throw std::runtime_error("Invalid type");
            return std::get<T>(value);
        }

        template <typename T>
            requires std::is_same_v<T, JSONString> || std::is_same_v<T, JSONObject> || std::is_same_v<T, JSONArray> ||
            std::is_same_v<T, JSONNumber> || std::is_same_v<T, JSONBoolean> || std::is_same_v<T, JSONNull>
        const T& Get() const
        {
            if (type == Type::INVALID)
                throw std::runtime_error("Invalid type");
            return std::get<T>(value);
        }

        template <typename T>
            requires std::is_same_v<T, JSONString> || std::is_same_v<T, JSONObject> || std::is_same_v<T, JSONArray> ||
            std::is_same_v<T, JSONNumber> || std::is_same_v<T, JSONBoolean> || std::is_same_v<T, JSONNull>
        void Set(T&& val)
        {
            value = std::forward<T>(val);
            if constexpr (std::is_same_v<T, JSONString>)
                type = Type::STRING;
            else if constexpr (std::is_same_v<T, JSONObject>)
                type = Type::OBJECT;
            else if constexpr (std::is_same_v<T, JSONArray>)
                type = Type::ARRAY;
            else if constexpr (std::is_same_v<T, JSONNumber>)
                type = Type::NUMBER;
            else if constexpr (std::is_same_v<T, JSONBoolean>)
                type = Type::BOOLEAN;
            else if constexpr (std::is_same_v<T, JSONNull>)
                type = Type::NULL_TYPE;
        }

        void SetInvalid()
        {
            type = Type::INVALID;
        }

        [[nodiscard]] Type GetType() const
        {
            return type;
        }

    private:
        VariantType value = nullptr;
        Type type = Type::INVALID;
    };


    NGIN_API class JSONParser
    {
    public:
        JSONValue Parse(const String& json);
        JSONValue Parse(std::istream& json);

    private:
        JSONValue ParseValue(JSONLexer& lexer, JSONToken& token);
        JSONObject ParseObject(JSONLexer& lexer);
        JSONArray ParseArray(JSONLexer& lexer);
        static JSONString ParseString(JSONToken& token);
        static JSONNumber ParseNumber(JSONToken& token);
        static JSONBoolean ParseBoolean(JSONToken& token);
        static JSONNull ParseNull(JSONToken& token);
    };
}
