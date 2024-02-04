#include <gtest/gtest.h>
#include <string>
#include <type_traits>

import NGIN.Meta;

namespace
{
    // A set of test functions and objects to use with FunctionTraits
    void TestFunction(int, double) {}

    struct TestClass
    {
        void memberFunction(int, double) {}
        void constMemberFunction(int, double) const {}
        int operator()(std::string) { return 0; }
    };


    // Helper type alias to simplify the tests
    template<typename F, std::size_t N>
    using ArgNTypeOf = typename NGIN::Meta::FunctionTraits<F>::template ArgNType<N>;
}// namespace

// Test cases
TEST(FunctionTraitsTest, FunctionPointer)
{
    using Traits = NGIN::Meta::FunctionTraits<decltype(&TestFunction)>;
    EXPECT_TRUE((std::is_same_v<Traits::ReturnType, void>) );
    EXPECT_TRUE((std::is_same_v<ArgNTypeOf<decltype(&TestFunction), 0>, int>) );
    EXPECT_TRUE((std::is_same_v<ArgNTypeOf<decltype(&TestFunction), 1>, double>) );
}

TEST(FunctionTraitsTest, MemberFunctionPointer)
{
    using Traits = NGIN::Meta::FunctionTraits<decltype(&TestClass::memberFunction)>;
    EXPECT_TRUE((std::is_same_v<Traits::ReturnType, void>) );
    EXPECT_TRUE((std::is_same_v<ArgNTypeOf<decltype(&TestClass::memberFunction), 0>, int>) );
    EXPECT_TRUE((std::is_same_v<ArgNTypeOf<decltype(&TestClass::memberFunction), 1>, double>) );
}

TEST(FunctionTraitsTest, ConstMemberFunctionPointer)
{
    using Traits = NGIN::Meta::FunctionTraits<decltype(&TestClass::constMemberFunction)>;
    EXPECT_TRUE((std::is_same_v<Traits::ReturnType, void>) );
    EXPECT_TRUE((std::is_same_v<ArgNTypeOf<decltype(&TestClass::constMemberFunction), 0>, int>) );
    EXPECT_TRUE((std::is_same_v<ArgNTypeOf<decltype(&TestClass::constMemberFunction), 1>, double>) );
}

TEST(FunctionTraitsTest, CallableObject)
{
    using Traits = NGIN::Meta::FunctionTraits<TestClass>;
    EXPECT_TRUE((std::is_same_v<Traits::ReturnType, int>) );
    EXPECT_TRUE((std::is_same_v<ArgNTypeOf<TestClass, 0>, std::string>) );
}