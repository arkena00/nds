#ifndef INCLUDE_NDS_CX_INDEX_OF_HPP_NDS
#define INCLUDE_NDS_CX_INDEX_OF_HPP_NDS

namespace nds::cx
{
    namespace internal
    {
        struct cx_err_type_not_found;
    } // internal

    template<class T, class Container>
    struct index_of;

    template<class T, template<class...> class Container>
    struct index_of<T, Container<>>
    {
        constexpr static auto value = internal::cx_err_type_not_found;
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
