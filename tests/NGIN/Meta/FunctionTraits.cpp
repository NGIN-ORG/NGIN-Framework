


import NGIN.Meta;
import std;
import boost.ut;
using namespace boost::ut;
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

suite<"FunctionTraits"> _ = [] {
    "TestFunctionReturnTypeAndArgs "_test = [] {
        using Traits = NGIN::Meta::FunctionTraits<decltype(&TestFunction)>;
        expect(std::is_same_v<Traits::ReturnType, void>);
        expect(std::is_same_v<ArgNTypeOf<decltype(&TestFunction), 0>, int>);
        expect(std::is_same_v<ArgNTypeOf<decltype(&TestFunction), 1>, double>);
    };

    "MemberFunctionReturnTypeAndArgs "_test = [] {
        using Traits = NGIN::Meta::FunctionTraits<decltype(&TestClass::memberFunction)>;
        expect(std::is_same_v<Traits::ReturnType, void>);
        expect(std::is_same_v<ArgNTypeOf<decltype(&TestClass::memberFunction), 0>, int>);
        expect(std::is_same_v<ArgNTypeOf<decltype(&TestClass::memberFunction), 1>, double>);
    };

    "ConstMemberFunctionReturnTypeAndArgs "_test = [] {
        using Traits = NGIN::Meta::FunctionTraits<decltype(&TestClass::constMemberFunction)>;
        expect(std::is_same_v<Traits::ReturnType, void>);
        expect(std::is_same_v<ArgNTypeOf<decltype(&TestClass::constMemberFunction), 0>, int>);
        expect(std::is_same_v<ArgNTypeOf<decltype(&TestClass::constMemberFunction), 1>, double>);
    };

    "CallableObjectReturnTypeAndArgs"_test = [] {
        using Traits = NGIN::Meta::FunctionTraits<TestClass>;
        expect(std::is_same_v<Traits::ReturnType, int>);
        expect(std::is_same_v<ArgNTypeOf<TestClass, 0>, std::string>);
    };

    "NoArgFunctionReturnType"_test = [] {
        void noArgFunction();
        using Traits = NGIN::Meta::FunctionTraits<decltype(&noArgFunction)>;
        expect(std::is_same_v<Traits::ReturnType, void>);
    };

    "MultiArgFunctionDifferentTypes"_test = [] {
        struct CustomType
        {
        };
        void multiTypeFunction(CustomType, const int&, double*);
        using Traits = NGIN::Meta::FunctionTraits<decltype(&multiTypeFunction)>;
        expect(std::is_same_v<ArgNTypeOf<decltype(&multiTypeFunction), 0>, CustomType>);
        expect(std::is_same_v<ArgNTypeOf<decltype(&multiTypeFunction), 1>, const int&>);
        expect(std::is_same_v<ArgNTypeOf<decltype(&multiTypeFunction), 2>, double*>);
    };

    "FunctionNonVoidReturnType"_test = [] {
        std::string nonVoidReturnFunction(int);
        using Traits = NGIN::Meta::FunctionTraits<decltype(&nonVoidReturnFunction)>;
        expect(std::is_same_v<Traits::ReturnType, std::string>);
        expect(std::is_same_v<ArgNTypeOf<decltype(&nonVoidReturnFunction), 0>, int>);
    };

    "FunctionWithRvalueReferenceArgs"_test = [] {
        void rvalueRefFunction(std::string&&);
        using Traits = NGIN::Meta::FunctionTraits<decltype(&rvalueRefFunction)>;
        expect(std::is_same_v<ArgNTypeOf<decltype(&rvalueRefFunction), 0>, std::string&&>);
    };


};
