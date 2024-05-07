#pragma once
#include <NGIN/Common/Defines.hpp>
#include <NGIN/Types/Primitives.hpp>
#include <tuple>
#include <utility>

namespace NGIN::Meta
{
    template <typename F>
    struct FunctionTraits;

    // function pointer
    template <typename R, typename... Args>
    struct FunctionTraits<R (*)(Args...)>
    {
        using ReturnType = R;
        using ArgsTupleType = std::tuple<Args...>;
        template <Size N>
        using ArgNType = std::tuple_element_t<N, ArgsTupleType>;

        static constexpr auto ARGS_INDEX_SEQ = std::make_index_sequence<std::tuple_size_v<ArgsTupleType>>();
        static constexpr std::size_t NUM_ARGS = sizeof...(Args);
    };

    // member function pointer
    template <typename C, typename R, typename... Args>
    struct FunctionTraits<R (C::*)(Args...)>
    {
        using ReturnType = R;
        using ArgsTupleType = std::tuple<Args...>;
        template <Size N>
        using ArgNType = std::tuple_element_t<N, ArgsTupleType>;

        static constexpr auto ARGS_INDEX_SEQ = std::make_index_sequence<std::tuple_size_v<ArgsTupleType>>();
        static constexpr std::size_t NUM_ARGS = sizeof...(Args);
    };

    // const member function pointer
    template <typename C, typename R, typename... Args>
    struct FunctionTraits<R (C::*)(Args...) const>
    {
        using ReturnType = R;
        using ArgsTupleType = std::tuple<Args...>;
        template <Size N>
        using ArgNType = std::tuple_element_t<N, ArgsTupleType>;

        static constexpr auto ARGS_INDEX_SEQ = std::make_index_sequence<std::tuple_size_v<ArgsTupleType>>();
        static constexpr std::size_t NUM_ARGS = sizeof...(Args);
    };

    // Lvalue ref-qualified member function
    template <typename C, typename R, typename... Args>
    struct FunctionTraits<R (C::*)(Args...) &>
    {
        using ReturnType = R;
        using ArgsTupleType = std::tuple<Args...>;
        template <size_t N>
        using ArgNType = std::tuple_element_t<N, ArgsTupleType>;
        static constexpr auto ARGS_INDEX_SEQ = std::make_index_sequence<std::tuple_size_v<ArgsTupleType>>();
        static constexpr std::size_t NUM_ARGS = sizeof...(Args);
    };

    // Rvalue ref-qualified member function
    template <typename C, typename R, typename... Args>
    struct FunctionTraits<R (C::*)(Args...) &&>
    {
        using ReturnType = R;
        using ArgsTupleType = std::tuple<Args...>;
        template <size_t N>
        using ArgNType = std::tuple_element_t<N, ArgsTupleType>;
        static constexpr auto ARGS_INDEX_SEQ = std::make_index_sequence<std::tuple_size_v<ArgsTupleType>>();
        static constexpr std::size_t NUM_ARGS = sizeof...(Args);
    };

    // callable objects, including lambdas
    template <typename F>
    struct FunctionTraits : FunctionTraits<decltype(&F::operator())>
    {
    };
} // namespace NGIN::Meta
