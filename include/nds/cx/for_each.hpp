#ifndef INCLUDE_NDS_CX_FOR_EACH_HPP_NDS
#define INCLUDE_NDS_CX_FOR_EACH_HPP_NDS

namespace nds::cx
{
    template<class T> struct wrapper{ using type = T; };

    namespace internal
    {
        template<class Pack>
        class for_each;

        template<template<class...> class Pack, class... Ts>
        class for_each<Pack<Ts...>>
        {
        public:
            template<class F>
            void operator()(F&& f) const
            {
                (f(nds::cx::wrapper<Ts>{}), ...);
            }
        };
    } // internal

    template<class Pack>
    constexpr internal::for_each<Pack> for_each{};
} // nds

#endif // INCLUDE_NDS_CX_FOR_EACH_HPP_NDS
