import NGIN.Meta;
import std;
import boost.ut;
using namespace boost::ut;
namespace
{
    struct TestClass
    {
        struct NestedClass
        {
        };
    };

    // Helper function to remove anonymous namespace mangling
    constexpr NGIN::StringView RemoveAnonymousNamespace(NGIN::StringView name)
    {
        const auto pos = name.find("::");
        return (pos != NGIN::StringView::npos) ? name.substr(pos + 2) : name;
    }

}

suite<"TypeInfo"> _ = []
{
       "Full"_test = []
    {
        using TypeInfo = NGIN::Meta::TypeInfo<TestClass>;
        const auto typeName = RemoveAnonymousNamespace(TypeInfo::Full());
        expect(typeName == "TestClass");
    };

    "NestedClassFull"_test = []
    {
        using TypeInfo = NGIN::Meta::TypeInfo<TestClass::NestedClass>;
           const auto typeName = RemoveAnonymousNamespace(TypeInfo::Full());
        expect(typeName == "TestClass::NestedClass");
    };

    "Namespace"_test = []
    {
        using TypeInfo = NGIN::Meta::TypeInfo<TestClass>;
        const auto namespaceName = RemoveAnonymousNamespace(TypeInfo::Namespace());
        // Assuming TestClass is not within a named namespace, otherwise change the expected string accordingly.
        expect(not namespaceName.contains("::"));
    };

    "NestedClassNamespace"_test = []
    {
        using TypeInfo = NGIN::Meta::TypeInfo<TestClass::NestedClass>;
        const auto namespaceName = RemoveAnonymousNamespace(TypeInfo::Namespace());
        expect(namespaceName == "TestClass");
    };
};
