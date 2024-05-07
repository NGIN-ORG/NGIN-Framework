#include <NGIN/Meta/TypeInfo.hpp>
#include <boost/ut.hpp>
using namespace boost::ut;

namespace
{
    class TestClass
    {
    public:
        struct NestedClass {};
    };

    // Helper function to remove anonymous namespace mangling
    constexpr std::string_view RemoveAnonymousNamespace(const std::string_view name)
    {
        const auto pos = name.find("::");
        return (pos != std::string_view::npos) ? name.substr(pos + 2) : name;
    }

}

suite<"TypeInfo"> _ = [] {
    "FullTypeName"_test = [] {
        using TypeInfo      = NGIN::Meta::TypeInfo<TestClass>;
        const auto typeName = TypeInfo::Full();
        expect(typeName == "TestClass" || typeName == "`anonymous namespace'::TestClass");
    };

    "FullNestedTypeName"_test = [] {
        using TypeInfo      = NGIN::Meta::TypeInfo<TestClass::NestedClass>;
        const auto typeName = TypeInfo::Full();
        expect(typeName == "TestClass::NestedClass" || typeName == "`anonymous namespace'::TestClass::NestedClass");
    };

    "EmptyNamespace"_test = [] {
        using TypeInfo           = NGIN::Meta::TypeInfo<TestClass>;
        const auto namespaceName = TypeInfo::Namespace();
        expect(namespaceName == "" || namespaceName == "`anonymous namespace'");
    };

    "NestedClassNamespace"_test = [] {
        using TypeInfo           = NGIN::Meta::TypeInfo<TestClass::NestedClass>;
        const auto namespaceName = TypeInfo::Namespace();
        expect(namespaceName == "TestClass" || namespaceName == "`anonymous namespace'::TestClass");
    };

    "TypenameIsSameAsName"_test = [] {
        using TypeInfo      = NGIN::Meta::TypeInfo<TestClass>;
        const auto typeName = TypeInfo::Name();
        expect(typeName == "TestClass");
    };

    "NestedTypenameIsSameAsType"_test = [] {
        using TypeInfo      = NGIN::Meta::TypeInfo<TestClass::NestedClass>;
        const auto typeName = TypeInfo::Name();
        expect(typeName == "NestedClass");
    };

    "CompilerSupportsRawSignature"_test = [] {
        using TypeInfo          = NGIN::Meta::TypeInfo<TestClass>;
        const auto rawSignature = TypeInfo::RawSignature();
        // Raw signature tests can be compiler specific
        expect(rawSignature.size() > 0);
    };
};
