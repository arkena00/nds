#ifndef INCLUDE_NDS_CX_INDEX_OF_HPP_NDS
#define INCLUDE_NDS_CX_INDEX_OF_HPP_NDS

#define nds_cx_error_value(Source, Err, ...) ::nds::cx::cx_error_value<Source, Err< __VA_ARGS__ > >::value

namespace nds::cx
{
    template<class...>
    struct cx_err;

    namespace errs
    {
        template<class...>
        struct out_of_range;
    } // errs

    template<class Source, class Err>
    struct cx_error_occured;

    template<template<class...> class Source, class Err>
    struct cx_error_occured_tpl;

    template<class Source, class Err>
    struct cx_error_value { static constexpr auto value = cx_error_occured<Source, Err>{}; };

    template<class T, class Container>
    struct index_of;

    template<class T, template<class...> class Container>
    struct index_of<T, Container<>>
    {
        constexpr static auto value = nds_cx_error_value(index_of, errs::out_of_range);
    };

    template<class T, template<class...> class Container, class... Ts>
    struct index_of<T, Container<T, Ts...>>
    {
        constexpr static auto value = 0;
    };

    template<class T, template<class...> class Container, class T_test, class... Ts>
    struct index_of<T, Container<T_test, Ts...>>
    {
        constexpr static auto value = 1 + index_of<T, Container<Ts...>>::value;
    };
} // nds::cx

#endif // INCLUDE_NDS_CX_INDEX_OF_HPP_NDS
