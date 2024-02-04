#include <gtest/gtest.h>
#include <string>
#include <type_traits>

import NGIN.Meta;

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
// Test cases
TEST(TypeInfoTest, Full)
{
    using TypeInfo = NGIN::Meta::TypeInfo<TestClass>;
    auto typeName = RemoveAnonymousNamespace(TypeInfo::Full());
    EXPECT_EQ(typeName, "TestClass");
}

TEST(TypeInfoTest, NestedClassFull)
{
    using TypeInfo = NGIN::Meta::TypeInfo<TestClass::NestedClass>;
    auto typeName = RemoveAnonymousNamespace(TypeInfo::Full());
    EXPECT_EQ(typeName, "TestClass::NestedClass");
}

TEST(TypeInfoTest, Namespace)
{
    using TypeInfo = NGIN::Meta::TypeInfo<TestClass>;
    auto namespaceName = RemoveAnonymousNamespace(TypeInfo::Namespace());
    // Assuming TestClass is not within a named namespace, otherwise change the expected string accordingly.
    EXPECT_FALSE(namespaceName.contains("::"));
}

TEST(TypeInfoTest, NestedClassNamespace)
{
    using TypeInfo = NGIN::Meta::TypeInfo<TestClass::NestedClass>;
    auto namespaceName = RemoveAnonymousNamespace(TypeInfo::Namespace());
    EXPECT_EQ(namespaceName, "TestClass");
}
