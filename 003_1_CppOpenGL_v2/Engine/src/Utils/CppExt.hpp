    //
// Created by martsinkevich on 18.01.2018.
//

#pragma once

#include <tuple>
#include <type_traits>

using namespace std::literals;

#define XSTRINGIFY(A) STRINGIFY(A)
#define STRINGIFY(A) #A

namespace ext
{
    namespace detail
    {
        template<int... Is>
        struct seq { };

        template<int N, int... Is>
        struct gen_seq : gen_seq<N - 1, N - 1, Is...> { };

        template<int... Is>
        struct gen_seq<0, Is...> : seq<Is...> { };

        template<typename T, typename F, int... Is>
        inline void for_each(T&& t, F f, seq<Is...>)
        {
            auto l = { (f(std::get<Is>(t)), 0)... };
        }


        template <typename T, typename = std::void_t<>>
        struct has_value_type : std::false_type {};

        template <typename T>
        struct has_value_type<T, std::void_t<typename T::value_type>> : std::true_type {};

        template <typename T>
        inline auto inner_type_helper(T&& t)
        {
            if constexpr (has_value_type<T>())
            {
                return std::declval<typename T::value_type>();
            }
            else
            {
                return *std::begin(t);
            }
        }
    }

    template<typename... Ts, typename F>
    inline void for_each(std::tuple<Ts...> const& t, F f)
    {
        detail::for_each(t, f, detail::gen_seq<sizeof...(Ts)>());
    }

    template <typename T>
    inline size_t objectId(const T& object)
    {
        return reinterpret_cast<size_t>(&object);
    }

    inline size_t genUniqueObjectId()
    {
        static size_t id = 0;
        return ++id;
    }

    template <typename T>
    inline size_t classId()
    {
        static int _id;
        return reinterpret_cast<size_t>(&_id);
    }

    template <typename T>
    using inner_type = decltype(detail::inner_type_helper(std::declval<T>()));

    template <typename T>
    struct function_traits
        : public function_traits<decltype(&T::operator())>
    {};

    template <typename ClassType, typename ReturnType, typename... Args>
    struct function_traits<ReturnType(ClassType::*)(Args...) const>
    {
        enum { arity = sizeof...(Args) };

        typedef ReturnType result_type;

        template <size_t i>
        struct arg
        {
            typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
        };
    };



}
