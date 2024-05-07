#include <boost/ut.hpp>
#include <sstream>
#include <NGIN/Serialization/JSON/JSONLexer.hpp>

using namespace boost::ut;
using namespace NGIN::Serialization;

suite<"JSONLexerTests"> _ = [] {

    const std::string json = R"({
        "key": true,
        "number": 123,
        "null_value": null,
        "string_value": "Hello, World!",
        "nested_object": {
            "nested_key": false
        },
        "array_value": [1, 2, 3]
    })";

    "TokenIdentification"_test = [&json] {
        std::istringstream input(json);
        JSONLexer lexer(input);
        expect(lexer.NextToken().type == JSONTokenType::OBJECT_START);
        expect(lexer.NextToken().type == JSONTokenType::STRING);
        expect(lexer.NextToken().type == JSONTokenType::COLON);
        expect(lexer.NextToken().type == JSONTokenType::TRUE);
        expect(lexer.NextToken().type == JSONTokenType::COMMA);
        expect(lexer.NextToken().type == JSONTokenType::STRING);
        expect(lexer.NextToken().type == JSONTokenType::COLON);
        expect(lexer.NextToken().type == JSONTokenType::NUMBER);
        expect(lexer.NextToken().type == JSONTokenType::COMMA);
        expect(lexer.NextToken().type == JSONTokenType::STRING);
        expect(lexer.NextToken().type == JSONTokenType::COLON);
        expect(lexer.NextToken().type == JSONTokenType::NULL_TYPE);
        expect(lexer.NextToken().type == JSONTokenType::COMMA);
        expect(lexer.NextToken().type == JSONTokenType::STRING);
        expect(lexer.NextToken().type == JSONTokenType::COLON);
        expect(lexer.NextToken().type == JSONTokenType::STRING);
        expect(lexer.NextToken().type == JSONTokenType::COMMA);
        expect(lexer.NextToken().type == JSONTokenType::STRING);
        expect(lexer.NextToken().type == JSONTokenType::COLON);
        expect(lexer.NextToken().type == JSONTokenType::OBJECT_START);
        expect(lexer.NextToken().type == JSONTokenType::STRING);
        expect(lexer.NextToken().type == JSONTokenType::COLON);
        expect(lexer.NextToken().type == JSONTokenType::FALSE);
        expect(lexer.NextToken().type == JSONTokenType::OBJECT_END);
        expect(lexer.NextToken().type == JSONTokenType::COMMA);
        expect(lexer.NextToken().type == JSONTokenType::STRING);
        expect(lexer.NextToken().type == JSONTokenType::COLON);
        expect(lexer.NextToken().type == JSONTokenType::ARRAY_START);
        expect(lexer.NextToken().type == JSONTokenType::NUMBER);
        expect(lexer.NextToken().type == JSONTokenType::COMMA);
        expect(lexer.NextToken().type == JSONTokenType::NUMBER);
        expect(lexer.NextToken().type == JSONTokenType::COMMA);
        expect(lexer.NextToken().type == JSONTokenType::NUMBER);
        expect(lexer.NextToken().type == JSONTokenType::ARRAY_END);
        expect(lexer.NextToken().type == JSONTokenType::OBJECT_END);
        expect(lexer.NextToken().type == JSONTokenType::END_OF_FILE);
    };

    "ReadString"_test = [&json] {
        std::istringstream input(json);
        JSONLexer lexer(input);
        lexer.NextToken();// skip object start
        lexer.NextToken();// skip first string key
        lexer.NextToken();// skip colon
        auto token = lexer.NextToken();
        expect(token.type == JSONTokenType::TRUE);
        expect(token.value == "true");
    };

    "ReadTrue"_test = [&json] {
        std::istringstream input(json);
        JSONLexer lexer(input);
        lexer.NextToken();// skip object start
        lexer.NextToken();// skip first string key
        lexer.NextToken();// skip colon
        lexer.NextToken();// skip true value
        auto token = lexer.NextToken();
        expect(token.type == JSONTokenType::COMMA);
    };

    // Other tests for ReadFalse, ReadNull, ReadNumber can follow similar patterns
};
